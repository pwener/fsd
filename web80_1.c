/* web80.c :Este eh um Web Server extremamente simples: */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <sys/uio.h>

#define TRUE    1
#define FALSE   0

int main(int argc,char **argv) {
  int z, sd;         		/* Descritor de Socket do Web Server 	*/
  int novo_sd;        		/* Descritor com dados do cliente	*/
  int alen;             	/* Tamanho do Endereco			*/
  struct sockaddr_in end_web;	/* Endereco do Web Server 		*/
  struct sockaddr_in end_cli;	/* Endereco do Cliente			*/
  int b = TRUE;       		/* Reutilizacao do ender.SO_REUSEADDR 	*/
  FILE *rx;                	/* Stream de Leitura 			*/
  FILE *tx;               	/* Stream de Escrita			*/
  char getbuf[2048];        	/* GET buffer 				*/
  time_t td;       		/* Current date & time 			*/

  sd = socket(AF_INET,SOCK_STREAM,0);

  /* Web address on port 80: */
  memset(&end_web, 0, sizeof end_web);
  end_web.sin_family 	   = AF_INET;
  end_web.sin_port 	   = ntohs(8084);
  end_web.sin_addr.s_addr  = ntohl(INADDR_ANY);

  z = bind(sd,(struct sockaddr *)&end_web, sizeof end_web);
  /* Ativa a opcao SO_REUSEADDR :  */
  z = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &b, sizeof b);
  z = listen(sd,10);

  /* Recebe uma msg e retorna um arquivo html */
  alen = sizeof end_cli;

  while(1) {
   /* Espera pela conexao de um Web Browser: */
    novo_sd = accept(sd,(struct sockaddr *)&end_cli, &alen);
    z = read(novo_sd, getbuf, sizeof getbuf);
    printf("Msg de chegada = %s\n", getbuf);
    /* Resposta com um documento HTML */
    z = write(novo_sd, "<html>alo mundo!!!</html>", sizeof getbuf);
  } /* fim-for */
 return 0;
} /* fim-main */
