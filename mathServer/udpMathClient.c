/********************************/
/* Lab.Redes 2 udpClient.c      */
/********************************/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> /* memset() */
#include <sys/time.h> /* select() */

#define MAX_MSG 100
#define ARGS_MIN_LIMIT 3

int main(int argc, char *argv[]) {
	int sd, rc, i;
	struct sockaddr_in ladoCli;		/* dados do cliente local   */
	struct sockaddr_in ladoServ;	/* dados do servidor remoto */

	/* Confere o numero de argumentos passados para o programa */
	if(argc < ARGS_MIN_LIMIT) {
		printf("Uso correto: %s <ip_do_servidor> <porta_do_servidor> <dado1> ... <dadoN> \n", argv[0]);
		exit(1);
	}

	/* Preenchendo as informacoes de identificacao do remoto */
	ladoServ.sin_family			=	AF_INET;
	ladoServ.sin_addr.s_addr	=	inet_addr(argv[1]);
	ladoServ.sin_port			=	htons(atoi(argv[2]));

	/* Preenchendo as informacoes de identificacao do cliente */
	ladoCli.sin_family 	 = AF_INET;
	ladoCli.sin_addr.s_addr= htonl(INADDR_ANY);  
	ladoCli.sin_port 	     = htons(0); /* usa porta livre entre (1024-5000)*/

	/* Criando um socket. Nesse momento a variavel
	 * sd contem apenas dados sobre familia e protocolo
	 */
	sd = socket(AF_INET,SOCK_DGRAM,0);
	if(sd<0) {
		printf("%s: n�o pode abrir o socket \n",argv[0]);
		exit(1);
	}

	/* Relacionando o socket sd com a estrutura ladoCli
	 * Depois do bind, sd faz referencia a protocolo local, 
	 * ip local e porta local
	 */
	rc = bind(sd, (struct sockaddr *) &ladoCli, sizeof(ladoCli));
	
	if(rc<0) {
		printf("%s: n�o pode fazer um bind da porta\n", argv[0]);
		exit(1); 
	}

	/* Enviando um pacote para cada parametro informado */
	for(i=3;i<argc;i++) {
		rc = sendto(sd, argv[i], strlen(argv[i]), 0,(struct sockaddr *) &ladoServ, sizeof(ladoServ));
		if(rc<0) {
			printf("%s: nao pode enviar dados %d \n",argv[0],i-1);
			close(sd);
			exit(1); }
		printf("Enviando parametro %d: %s\n", i-2, argv[i]);
	} /* fim do for (laco) */

	double * result = malloc(sizeof(double));

	int tam_cli = sizeof(ladoServ);

	int responsed = recvfrom(sd, result, sizeof(double), 0, (struct sockaddr *) &ladoServ, &tam_cli);

	printf("Result is %lf\n", *result);

	return 1;
} /* fim do programa */