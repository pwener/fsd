<center> <h1>Relatório da disciplina de Sistemas distribuídos</h1></center>
<center>
Fundamentos de Sistemas Distribuídos </br>
Aluno: Phelipe Wener </br>
Matrícula: 12/0132893 </br>

## 1. Objetivo
  O objetivo desse experimento é que o aluno compreenda as características
inerentes à construção de aplicações distribuídas, incluindo passagem de parâmetros,
envolvendo módulos cliente e servidor conectados por sockets UDP e TCP.

## 2. Ambiente e configuração
Todos os experimentos abaixo foram executados numa distribuição linux chamada kubuntu, que difere fundamentalmente em termos de interface com o ubuntu. Portanto, deve ser possivel executar os mesmos passos em qualquer versão do Ubuntu 14.04, bem como em um Debian 7.

Já na compilação do código, foi utilizado gcc na versão 4.8.4, com a flag `-Wall` ativa, tal que seja possível corrigir todos warnings acusados pelo compilador.


### 3. Utilizando protocolo UDP
Os códigos <b>udpMathClient.c</b>(Cliente) e <b>UdpMathServer.c</b>(Servidor) se comunicam afim de retornar o resultado de uma operação matemática simples (soma, subtração, multiplicação e divisão). Os passos executados pelo código se resumem da seguinte forma:

* Servidor fica esperando uma requisição em uma porta x
* Cliente manda uma operação simples para o endereço do servidor com a porta x
* Servidor recebe a operação realizando o cálculo
* Servidor responde ao cliente o resultado
* Cliente imprime o resultado

No terminal, as seguintes telas foram obtidas:

- Servidor ligado

```
$ ./ums 192.168.0.23 9090
./ums: esperando por dados no IP: 192.168.0.23, porta UDP numero: 9090
```

- Cliente enviando operação e recebendo resultado

```
$ ./umc 192.168.0.23 9090 5 + 7
Enviando parametro 1: 5
Enviando parametro 2: +
Enviando parametro 3: 7
Result is 12.000000
```
