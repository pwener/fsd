/* Lab Redes II - Prof. Fernando W. Cruz	*/
/* Codigo: tcpServer2.c						*/
/********************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define QLEN	5 /* tamanho da fila de clientes  */
#define MAX_SIZE	80 /* tamanho do buffer */

int atende_cliente(int descritor, struct sockaddr_in endCli);

int main(int argc, char *argv[]) {
	struct sockaddr_in endServ;  /* endere�o do servidor   */
	struct sockaddr_in endCli;   /* endere�o do cliente    */
	int    sd, novo_sd;          /* socket descriptors */
	int    pid, alen,n;

	if (argc<3) {
		printf("Digite IP e Porta para este servidor\n");
		exit(1);
	}

	// memset((char *)&endServ,0,sizeof(endServ)); /* limpa variavel endServ */
	bzero((char *) &endServ, sizeof(endServ));

	endServ.sin_family = AF_INET; /* familia TCP/IP */
	endServ.sin_addr.s_addr = inet_addr(argv[1]); /* endere�o IP */
	endServ.sin_port = htons(atoi(argv[2])); /* PORTA */

	/* Cria socket */
	sd = socket(AF_INET, SOCK_STREAM, 0); /* Create a IPV4 socket */

	if (sd < 0) {
		fprintf(stderr, "Falha ao criar socket!\n");
		exit(EXIT_FAILURE);
	}

	/* liga socket a porta e ip */
	if (bind(sd, (struct sockaddr *) &endServ, sizeof(endServ)) < 0) {
		fprintf(stderr, "Ligacao Falhou!\n");
		exit(EXIT_FAILURE);
	}

	/* Ouve porta */
	if (listen(sd, QLEN) < 0) {
		fprintf(stderr, "Falhou ouvindo porta!\n");
		exit(EXIT_FAILURE);
	}

	printf("Servidor ouvindo no IP %s, na porta %s ...\n\n", argv[1], argv[2]);
	/* Aceita conexoes */
	alen = sizeof(endCli);
	while(1) {
		/* espera nova conexao de um processo cliente ... */
		if ( (novo_sd=accept(sd, (struct sockaddr *)&endCli, &alen)) < 0) {
			fprintf(stdout, "Falha na conexao\n");
			exit(EXIT_FAILURE);
		}
		fprintf(stdout, "Cliente %s: %u conectado.\n", inet_ntoa(endCli.sin_addr), ntohs(endCli.sin_port));
		atende_cliente(novo_sd, endCli);
	} /* fim for */

} /* fim do programa */


int atende_cliente(int descritor, struct sockaddr_in endCli) {
	char bufin[MAX_SIZE];

	int n;

	while (1) {
		memset(&bufin, 0x0, sizeof(bufin));
		n = recv(descritor, &bufin, sizeof(bufin),0);
		if (strncmp(bufin, "FIM", 3) == 0) {
			break;
		}

		fprintf(stdout, "[%s:%u] => %s\n", inet_ntoa(endCli.sin_addr), ntohs(endCli.sin_port), bufin);
   } /* fim while */

	fprintf(stdout, "Encerrando conexao com %s:%u ...\n\n", inet_ntoa(endCli.sin_addr), ntohs(endCli.sin_port));
	close (descritor);

} /* fim atende_cliente */
