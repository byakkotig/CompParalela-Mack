# Projeto - Tartaruga 

## Sobre o projeto

O projeto consiste em construir uma solução paralela cujo valor de S seja o maior possível, ou seja, possua a melhor aproximação para a série de Taylor calculando o valor de e. O grupo deverá apresentar os seguintes resultados na entrega:

• O valor de e final calculado;

• O tempo T que levou para atingir esse valor

Os códigos criados foram: 

Após a criação dos códigos foram respondidas as questões realizadas pelo professor.

Este documento contém instruções detalhadas sobre como compilar, executar e verificar os resultados do programa entregue.

Testes foram realizados no terminal Linux Ubuntu.


## Integrantes

- André Akio Morita Osakawa - 10340045
- Rafael de Souza Oliveira Cerqueira Tinôco - 10401436
- Rodrigo Mileo Lourenço Gil - 10390174


## Instalação

Usando o `git`, clone o repositório usando o seguinte comando:

`git clone https://github.com/byakkotig/CompParalela-Mack.git`, depois use o comando `cd CompParalela-Mack` para entrar na pasta e o comando `cd Projeto` para entrar na pasta do lab

## Compilação e Execução

O exercicio proposto pelo professor consiste em usar o comando `time` no terminal Linux para mostrar o tempo de execução de cada código, além disso pede-se para executar os códigos com 1, 2 ,4, 6 e 8 processadores, para isso usamos o comando `taskset -c [número dos processadores]`.

Os comando utilizados foram: 

- Para 1 processador `time taskset -c 0 [nome_do_arquivo]` 

- Para 2 processadores `time taskset -c 0,1 [nome_do_arquivo]`

- Para 4 processadores `time taskset -c 0,1,2,3 [nome_do_arquivo]`

- Para 6 processadores `time taskset -c 0,1,2,3,4,5 [nome_do_arquivo]`

- Para 8 processadores `time taskset -c 0,1,2,3,4,5,6,7 [nome_do_arquivo]`


(arrumar dps)
Para compilar o código `` que contém o código com a versão serial entre na pasta do projeto e no terminal, utilize o comando `gcc .c -o  -lm` e para executá-lo digite o comando `time taskset -c [número dos processadores] ./`. Como visto no exemplo abaixo.

### Prints da execução dos códigos estão tanto na pasta `assets` quanto nas instruções de cada exercicio abaixo

## Resolução dos exercicios propostos

Primeiramente, segue abaixo o print do comando `cat /proc/cpuinfo` pedido pelo professor, para mostrar o processador utilizado para os testes e para a criação dos gráficos.

![alt](/Projeto/assets/processador.png)