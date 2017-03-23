/* Lab Redes II - Prof. Fernando W. Cruz       */
/* Codigo: tcpClient2.c	- dialogo bidirecional */
/* *********************************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_SIZE	80

/* Maximus quantity of args passed */
#define ARG_SIZE	3

int main(int argc,char * argv[]) {
	struct	sockaddr_in ladoServ; /* contem dados do servidor */
	int     sd; /* socket descriptor */
	int     n; /* numero de caracteres lidos do servidor */
	char    bufout[MAX_SIZE]; /* buffer de dados enviados */
	char	bufin[MAX_SIZE]; /* buffer p receber dados */

	memset((char *) &ladoServ,0,sizeof(ladoServ)); /* limpa estrutura */
	memset((char *) &bufout,0,sizeof(bufout)); /* limpa buffer */

	/* Confere o numero de argumentos passados para o programa */
	if(argc < ARG_SIZE)  {
		printf("Uso correto: %s <ip_do_servidor> <porta_do_servidor>\n", argv[0]);
		exit(1);
	}

	ladoServ.sin_family = AF_INET; /* config. socket p. internet*/
	ladoServ.sin_addr.s_addr = inet_addr(argv[1]); /* ip servidor */
	ladoServ.sin_port = htons(atoi(argv[2])); /* porta servidor */

	/* Cria socket */
	sd = socket(PF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		fprintf(stderr, "Criacao do socket falhou!\n");
		exit(1);
	}

	/* Conecta socket ao servidor definido */
	if (connect(sd, (struct sockaddr *) & ladoServ, sizeof(ladoServ)) < 0) {
		fprintf(stderr,"Tentativa de conexao falhou!\n");
		exit(1);
	}

	while (1) {
		memset(&bufin, 0x0, sizeof(bufin));
		memset(&bufout, 0x0, sizeof(bufout));
		printf("CLIENTE# Digite algo (FIM - para terminar): ");
		fgets(bufout, MAX_SIZE, stdin);
		send(sd,&bufout,strlen(bufout),0);
		if (strncmp(bufout, "FIM",3) == 0)
			break;
		printf("Cliente# ");
		n = recv(sd, &bufin, sizeof(bufin), 0);
		if (strncmp(bufin, "FIM", 3) == 0)
			break;
		printf("<- %s", bufin);
	} /* fim while */

	printf("------- encerrando conexao -----\n");

	close (sd); /* fecha a conexao */

	return (0);
} /* fim do programa */
