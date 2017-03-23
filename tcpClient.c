/********************************/
/* Lab.Redes 2  tcpClient.c     */
/********************************/ 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> /* close */

#define MAX_MSG 100

int main (int argc, char *argv[]) {

	int sd, rc, i;
	struct sockaddr_in ladoCli;  /* dados do cliente */
	struct sockaddr_in ladoServ; /* dados do servidor */

	if(argc < 4) {
		printf("Uso: %s <ip_serv> <porta_serv> <data1> ...  <dataN>\n",argv[0]);
		exit(1);
	}

	/* dados do servidor */
	ladoServ.sin_family	   = AF_INET;
	ladoServ.sin_addr.s_addr = inet_addr(argv[1]);
	ladoServ.sin_port 	   = htons(atoi(argv[2]));

	/* dados do cliente */
	ladoCli.sin_family	  = AF_INET;
	ladoCli.sin_addr.s_addr = htonl(INADDR_ANY);
	ladoCli.sin_port	  = htons(0);
	for (i=3;i<argc;i++) {
	/* criando um socket */
		sd = socket(AF_INET, SOCK_STREAM, 0);
		if(sd<0) {
			printf("Nao foi possivel abrir o socket ");
			exit(1);
		}

		/* faz um bind para a porta escolhida */
		rc = bind(sd, (struct sockaddr *) &ladoCli, sizeof(ladoCli));
		if(rc<0) {
			printf("Nao foi possivel fazer o bind na porta TCP");
			exit(1);
	}

	printf("------ Estabelecendo conexao -------\n");
	/* faz a conexao com o servidor */
	rc = connect(sd, (struct sockaddr *) &ladoServ, sizeof(ladoServ));
	if(rc<0) {
		printf("Nao foi possivel conectar");
		exit(1);
	}

	printf("Enviando dado %u => %s \n", i-2, argv[i]);
	rc = send(sd, argv[i], strlen(argv[i]) + 1, 0);

	if(rc<0) {
		printf("Nao foi possivel enviar dados");
		close(sd);
		exit(1);
	}

	printf("------ Encerrando conexao ---------\n\n");
	close(sd);
	} /* fim-do-for */

	return 0; 

} /* fim do programa */
