## 1. Introdução


## 2. Objetivo

## 3. Ambiente e configuração
Esse experimento foi executado em duas distribuições linux parecidas, o kubuntu e o ubuntu, que difere fundamentalmente em termos de interface um do outro. Portanto, deve ser possivel executar os mesmos passos em qualquer versão do Ubuntu 14.04, bem como em um Debian 7.

Para o experimento foi utilizado uma topologia com três maquinas, o qual uma tem um endereço IP fixo.

O relatório recomenda o uso do pacote dhcp3, porém ao passar o pacote para instalação via apt(Gerenciador de pacotes do Debian), o mesmo instalou o pacote isc-dhcp-server. Segundo [1] esse pacote é o mesmo dhcp3, apenas atualizaram o nome em distribuições mais recentes.

## 4. Desenvolvimento

### 4.1 Configurando Servidor

- Primeiramente foi parado o network-manager com o comando:

```
$ sudo stop network-manager
```

- Foi configurado o arquivo `/etc/dhcp/dhcpd.conf` de acordo com o roteiro, utilizando as seguintes configurações:

```

```

-


### 4.2 Configurando Cliente


### 4.3 Obtendo endereço


## 5. Dificuldades

### 5.1 Problemas encontrados

### 5.2 Limitações de código

## 6. Referências

[1] https://wiki.debian.org/DHCP_Server
