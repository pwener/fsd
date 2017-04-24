## 1. Introdução


## 2. Objetivo

## 3. Ambiente e configuração
Todos os experimentos abaixo foram executados numa distribuição linux chamada kubuntu, que difere fundamentalmente em termos de interface com o ubuntu. Portanto, deve ser possivel executar os mesmos passos em qualquer versão do Ubuntu 14.04, bem como em um Debian 7.

## 4. Desenvolvimento

## 4.1. Instalação

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

## 4.2. Testando MPI

Para familiarização com o MPI, decidiu-se testar com o código de um tutorial no [github](https://github.com/wesleykendall/mpitutorial/tree/gh-pages/tutorials/mpi-hello-world/code/mpi_hello_world.c), o código é um típico "Hello World".

O exemplo contava com um makefile que basicamente usava um compilador especial para gerar o executável, chama-se _mpicc_. Basicamente foi obtido os seguintes resultados:

```shell
$ make
mpicc -o hello_world hello_world.c
$ ./hello_world
Hello world from processor wenerianus, rank 0 out of 1 processors
```

No tutorial seguido para esse teste ainda havia documentação sobre execução paralela em vários hosts, mais informações: http://mpitutorial.com/tutorials/mpi-hello-world/

## 5. Dificuldades

### 5.1 Problemas encontrados

### 5.2 Limitações de código

## 6. Referências
