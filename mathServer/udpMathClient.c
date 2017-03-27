#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define MAX_MSG 100
#define OPERATION_CHARS 3
#define ARGS_MIN_LIMIT 3

int main(int argc, char *argv[]) {
	int sd, rc, i;
	struct sockaddr_in client;		/* dados do cliente local   */
	struct sockaddr_in server;	/* dados do servidor remoto */

	/* Confere o numero de argumentos passados para o programa */
	if(argc < ARGS_MIN_LIMIT) {
		printf("Uso correto: %s <ip_do_servidor> <porta_do_servidor> <dado1> ... <dadoN> \n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Preenchendo as informacoes de identificacao do remoto */
	server.sin_family			=	AF_INET;
	server.sin_addr.s_addr	=	inet_addr(argv[1]);
	server.sin_port			=	htons(atoi(argv[2]));

	/* Preenchendo as informacoes de identificacao do cliente */
	client.sin_family 	 = AF_INET;
	client.sin_addr.s_addr= htonl(INADDR_ANY);  
	client.sin_port 	     = htons(0); /* usa porta livre entre (1024-5000)*/

	/* Criando um socket. Nesse momento a variavel
	 * sd contem apenas dados sobre familia e protocolo
	 */
	sd = socket(AF_INET,SOCK_DGRAM,0);
	if(sd < 0) {
		printf("%s: não pode abrir o socket \n",argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Relacionando o socket sd com a estrutura client
	 * Depois do bind, sd faz referencia a protocolo local, 
	 * ip local e porta local
	 */
	rc = bind(sd, (struct sockaddr *) &client, sizeof(client));

	if(rc < 0) {
		printf("%s: não pode fazer um bind da porta\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Enviando um pacote para cada parametro informado */
	for(i=3; i<argc; i++) {

		rc = sendto(sd, argv[i], strlen(argv[i]), 0, (struct sockaddr *) &server,
				sizeof(server));

		if(rc<0) {
			printf("%s: nao pode enviar dados %d \n",argv[0],i-1);
			close(sd);
			exit(EXIT_FAILURE);
		}
		printf("Enviando parametro %d: %s\n", i-2, argv[i]);
	} /* fim do for (laco) */

	/* Espera a resposta do servidor */
	double * result = malloc(sizeof(double));

	unsigned int server_len = sizeof(server);

	int responsed = recvfrom(sd, result, sizeof(double), 0,
			(struct sockaddr *) &server, (socklen_t *) &(server_len));

	if(responsed) {
		printf("Result is %lf\n", *result);
	} else {
		printf("Some error occurs!\n");
	}

	return 0;
} /* fim do programa */
