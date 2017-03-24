/********************************/
/* Lab.Redes 2 - udpServer.c    */
/********************************/ 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* close() */
#include <string.h> /* memset() */

#define MAX_MSG 100
#define A_INDEX 0
#define OP_INDEX 1
#define B_INDEX 2

double sum(double a, double b) {
	return a + b;
}

double sub(double a, double b) {
	return a - b;
}

double division(double a, double b) {
	return a / b;
}

double mul(double a, double b) {
	return a * b;
}

double calc(char * argv[]) {
	int a = atoi(argv[A_INDEX]);
	int b = atoi(argv[B_INDEX]);

	double result = 0;

	if (strcmp(argv[OP_INDEX], "+") == 0) {
		result = sum(a, b);
	}

	if (strcmp(argv[OP_INDEX], "-") == 0) {
		result = sub(a, b);
	}

	if (strcmp(argv[OP_INDEX], "*") == 0) {
		result = mul(a, b);
	}

	if (strcmp(argv[OP_INDEX], "/") == 0) {
		result = division(a, b);
	}

	return result;
}

int main(int argc, char *argv[]) {
	int sd, rc, n, tam_Cli;
	int counter = 0;
	struct sockaddr_in endCli;   /* Vai conter identificacao do cliente */
	struct sockaddr_in endServ;  /* Vai conter identificacao do servidor local */
	char   msg[MAX_MSG];/* Buffer que armazena os dados que chegaram via rede */
	double result = -1;
	char * form[3];

	form[0] = malloc(sizeof(char*) * 3);
	form[1] = malloc(sizeof(char*) * 3);
	form[2] = malloc(sizeof(char*) * 3);

	if (argc<3) {
		printf("Digite IP e Porta para este servidor\n");
		exit(1); 
	}

	/* Criacao do socket UDP */
	sd=socket(AF_INET, SOCK_DGRAM, 0);
	
	if(sd<0) {
		printf("%s: nao pode abrir o socket \n",argv[0]);
		exit(1);  
	}

	bzero((char *) &endServ, sizeof(endServ));

	/* Preenchendo informacoes sobre o servidor */
	endServ.sin_family 	  = AF_INET;
	endServ.sin_addr.s_addr = inet_addr(argv[1]);
	endServ.sin_port 	  = htons(atoi(argv[2]));

	/* Fazendo um bind na porta local do servidor */
	rc = bind (sd, (struct sockaddr *) &endServ, sizeof(endServ));
	
	if(rc < 0) {
		printf("%s: nao pode fazer bind na porta %s \n", argv[0], argv[2]);
		exit(1);
	}

	printf("%s: esperando por dados no IP: %s, porta UDP numero: %s\n", argv[0], argv[1], argv[2]);

	/* Este servidor entra num loop infinito esperando dados de clientes */
	while(1) {
		/* inicia o buffer */
		memset(msg,0x0,MAX_MSG);
		tam_Cli = sizeof(endCli);

		/* Recebe uma msg(equacao)  */
		n = recvfrom(sd, msg, MAX_MSG, 0, (struct sockaddr *) &endCli, &tam_Cli);

		/* Imprime a formula recebida e os dados do cliente */
		char * client_addr = inet_ntoa(endCli.sin_addr);
		int client_port = ntohs(endCli.sin_port);

		printf("{IP_R: %s, Porta_R: %u} => %s\n", client_addr, client_port, msg);

		/* Se conseguiu obter mensagem deve calcular a formula */
		if(n < 0) {
			printf("%s: nao pode receber dados \n",argv[0]);
			continue;
		} else {

			strcpy(form[counter], msg);
			counter++;

			if(counter == 3) {
				result = calc(form);

				double * result_pointer = &result;

				sendto(sd, result_pointer, sizeof(double), 0, (struct sockaddr *) &endCli, sizeof(endCli));
				break;
			}
		}
	} /* fim do while */

	return 0;

} /* fim do programa */
