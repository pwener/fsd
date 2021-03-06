#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define QLEN		5		/* tamanho da fila de clientes  */
#define MAX_SIZE	80		/* tamanho do buffer */

#define MIN_ARGUMENTS_SIZE 3

void reply(int descritor, struct sockaddr_in client)  {
	char bufin[MAX_SIZE];
	char op;
	int a, b, n; // a and b operands, n recv
	double result;

	while (1) {
		memset(&bufin, 0x0, sizeof(bufin));
		n = recv(descritor, &bufin, sizeof(bufin), 0);

		if(n < 0) {
			printf("Algum erro ocorreu ao receber mensagem\n");
		}

		if (strncmp(bufin, "FIM", 3) == 0) {
			break;
		}

		sscanf(bufin, "%d %c %d", &a, &op, &b);

		switch(op) {
			case '+':
				result = a + b;
				break;
			case '-':
				result = a - b;
				break;
			case '*':
				result = a * b;
				break;
			case '/':
				result = a / b;
				break;
			default:
				printf("Operation invalid");
		}

		send(descritor, &result, sizeof(double), 0);

		printf("[%s:%d] => %s\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port), bufin);
	} /* fim while */

	printf("Encerrando conexao com %s:%u ...\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

	close (descritor);
} /* fim atende_cliente */


int main(int argc, char *argv[]) {
	struct sockaddr_in server;		/* endere�o do servidor   */
	struct sockaddr_in client;		/* endere�o do cliente    */
	int sd, novo_sd;				/* socket descriptors */
	int pid;

	if (argc < MIN_ARGUMENTS_SIZE) {
		printf("Digite IP e Porta para este servidor\n");
		exit(EXIT_FAILURE);
	}

	memset((char *) &server, 0, sizeof(server)); /* Limpa variavel server */
	server.sin_family = AF_INET; /* Familia TCP/IP */
	server.sin_addr.s_addr = inet_addr(argv[1]); /* Endere�o IP */
	server.sin_port = htons(atoi(argv[2])); /* PORTA */

	/* Cria socket */
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		printf("Falha ao criar socket!\n");
		exit(EXIT_FAILURE);
	}

	/* Liga socket a porta e ip */
	if (bind(sd, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Ligacao Falhou!\n");
		exit(EXIT_FAILURE);
	}

	/* Ouve porta */
	if (listen(sd, QLEN) < 0) {
		printf("Falhou ouvindo porta!\n");
		exit(EXIT_FAILURE);
	}

	printf("Servidor ouvindo no IP %s, na porta %s ...\n\n", argv[1], argv[2]);

	/* Aceita conexoes */
	unsigned int alen = sizeof(client);

	while(1) {
		/* espera nova conexao de um processo cliente ... */	
		if ( (novo_sd=accept(sd, (struct sockaddr *)&client, (socklen_t *) &(alen))) < 0) {
			printf("Falha na conexao\n");
			exit(EXIT_FAILURE);
		}

		pid = fork(); /* Inicia novo processo */

		if (pid < 0) {
			printf("Falha na criacao do processo filho!\n");
		} else if (pid == 0) { /* processo filho */
			close (sd); /* encerra o socket sd */
			printf("Client %s: %u conectado.\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port)); 
			reply(novo_sd, client);
			exit(0);
		} /* fim else-if */

		/* processo pai */
		close (novo_sd);
	} /* fim for */
} /* fim do programa */

void allocate_opf(char * op) {
	op = malloc(sizeof(char) * sizeof(double));
}
