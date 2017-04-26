## 1. Introdução


## 2. Objetivo

## 3. Ambiente e configuração
Todos os experimentos abaixo foram executados numa distribuição linux chamada kubuntu, que difere fundamentalmente em termos de interface com o ubuntu. Portanto, deve ser possivel executar os mesmos passos em qualquer versão do Ubuntu 14.04, bem como em um Debian 7.

A implementação MPI escolhida foi o MPICH2, no desenvolvimento do projeto tem um tópico onde isso será tratado.

## 4. Desenvolvimento

### 4.1. Instalação

Dentre as implementações do MPI, foi escolhido o MPICH, tal que segundo a [página de download](http://www.mpich.org/downloads/) a API tem distribuição compativel com o sistema operacional utilizado nesse experimento. Para instação foi utilizado o comando:

```
$ sudo apt-get instal mpich
```

Depois foi utilizado o comando a seguir para verificação da instalação:

```
$ mpiexec --version
HYDRA build details:
    Version:                                 3.0.4
    Release Date:                            Wed Apr 24 10:08:10 CDT 2013
...
```

Várias linhas de configuração foram exibidas também.

### 4.2. Testando MPI

Para familiarização com o MPI, decidiu-se testar com o código de um tutorial no [github](https://github.com/wesleykendall/mpitutorial/tree/gh-pages/tutorials/mpi-hello-world/code/mpi_hello_world.c), o código é um típico "Hello World".

O exemplo contava com um makefile que basicamente usava um compilador especial para gerar o executável, chama-se _mpicc_. Basicamente foi obtido os seguintes resultados:

```shell
$ make
mpicc -o hello_world hello_world.c
$ ./hello_world
Hello world from processor wenerianus, rank 0 out of 1 processors
```

No tutorial seguido para esse teste ainda havia documentação sobre execução paralela em vários hosts, mais informações: http://mpitutorial.com/tutorials/mpi-hello-world/

### 4.3 Desenvolvimento do problema

- O roteiro pede que o programa manipule um vetor de 1.000.000.000 de posições do tipo float, iniciado com a seguinte formula: `V[i] = (i - tamanho_vetor/2) ** 2`.

- Em seguida o programa calcula cada posição do vetor de acordo com a formula: `V[i] = raiz_quadrada(v[i])`

- Primeiramente o programa foi executado na versão sequencial/convencional:

```java
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define VECTOR_LEN 1000000000

// V[i] = (i – tamanho_do_vetor/2) ** 2;
int main() {
	float v[VECTOR_LEN];

	int x;

	for(x = 0; x < VECTOR_LEN; x++) {
		v[x] = pow((x - (VECTOR_LEN/2)), 2);
	}

	return 0;
}
```

- Em seguida o programa foi compilado com o comando `$ gcc pure_exp.c -Wall -o pure -lm`

- Então ao executar o programa usando `$ ./pure` obtemos o erro de Falha de segmentação, comum quando um programa tenta acessar região de memória inválida. É de se esperar que esse erro seja oriundo da grande alocação de memória utilizada na definição do vetor. [CITAR MEMORIA LIMITE DE CADA PROCESSO]

- Após, foi criado o mesmo código usando MPI:

```java
#include <mpi.h>
#include <stdio.h>
#include <math.h>

#define VECTOR_LEN 1000000000

int main(int argc, char** argv) {
  // Initialize the MPI environment. The two arguments to MPI Init are not
  // currently used by MPI implementations, but are there in case future
  // implementations might need the arguments.
  MPI_Init(NULL, NULL);

  // Get the number of processes
  int world_size = 1;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  float v[VECTOR_LEN];

  int x;

  for(x = 0; x < VECTOR_LEN; x++) {
    v[x] = pow((x - (VECTOR_LEN/2)), 2);
  }

  // Finalize the MPI environment. No more MPI calls can be made after this
  MPI_Finalize();
}
```

- 

## 5. Dificuldades

### 5.1 Problemas encontrados

### 5.2 Limitações de código

## 6. Referências
