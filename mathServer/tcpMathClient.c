#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_SIZE	80
#define MIN_ARGUMENTS_SIZE 3

int main(int argc, char * argv[]) {
	struct  sockaddr_in server; /* contem dados do servidor 	*/
	int     sd;					/* socket descriptor              */
	char    bufout[MAX_SIZE];	/* buffer de dados enviados  */
	double * result = malloc(sizeof(double));

	/* Confere o numero de argumentos passados para o programa */
	if(argc < MIN_ARGUMENTS_SIZE) {
		printf("uso correto: %s <ip_do_servidor> <porta_do_servidor>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset((char *)&server, 0, sizeof(server)); /* limpa buffer */
	memset((char *)&bufout, 0, sizeof(bufout)); /* limpa buffer */

	bzero((char *) &server, sizeof(server)); /* write 0 value bytes */

	server.sin_family = AF_INET; /* config. socket p. internet*/
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port = htons(atoi(argv[2]));

	/* Cria socket */
	sd = socket(AF_INET, SOCK_STREAM, 0);

	if (sd < 0) {
		fprintf(stderr, "Criacao do socket falhou!\n");
		exit(EXIT_FAILURE);
	}

	/* Conecta socket ao servidor definido */
	if (connect(sd, (struct sockaddr *) &server, sizeof server) < 0) {
		fprintf(stderr,"Tentativa de conexao falhou!\n");
		exit(EXIT_FAILURE);
	}

	while (1) {
		printf("> ");
		fgets(bufout, MAX_SIZE, stdin); /* le dados do teclado */
		send(sd, &bufout, strlen(bufout), 0); /* enviando dados ...  */

		if (strncmp(bufout, "FIM", 3) == 0) {
			break;
		}

		recv(sd, result, 80, 0);

		printf("Result is %lf\n", *result);

	} /* fim while */

	printf("------- encerrando conexao com o servidor -----\n");
	close (sd);

	return (0);
} /* fim do programa */
