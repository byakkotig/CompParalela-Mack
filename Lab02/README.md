# Laboratório 2 - Matriz vetor

## Sobre o projeto

Esse projeto consiste em criar um código para resolver o problema de multiplicação de matrizes, para isso utilizamos Pthreads.

Este documento contém instruções detalhadas sobre como compilar, executar e verificar os resultados do programa entregue.

Testes foram realizados na plataforma AWS

## Integrantes

- André Akio Morita Osakawa - 10340045
- Rafael de Souza Oliveira Cerqueira Tinôco - 10401436
- Rodrigo Mileo Lourenço Gil - 10390174

## Instalação

Usando o `git`, clone o repositório usando o seguinte comando:

`git clone https://github.com/byakkotig/CompParalela-Mack.git`, depois use o comando `cd CompParalela-Mack` para entrar na pasta e o comando `cd Lab02` para entrar na pasta do lab

## Compilação e Execução

Para compilar o código, entre na pasta do projeto e no terminal, utilize o comando `gcc mult_matriz.c -o mult_matriz` e para executá-lo digite o comando `./mult_matriz`.

![alt](/Lab02/assets/compilacao.png)

### Prints da execução dos códigos estão tanto na pasta `assets` quanto nas instruções de cada exercicio abaixo

## Resolução do exercicio proposto

Como solicitado, segue abaixo o print da execução do programa de multiplicação de matrizes utilizando pthreads. O programa pede que o usuário digite o número de linhas e colunas da matriz A e quantas threads ele deseja, depois o usuário insere os valores desejados na matriz e no vetor e a saída é sua matriz resultante.

### Teste 1: Matrix 3x3 e numero de threads = 3

![alt](/Lab02/assets/teste1.png)

### Teste 2: Matrix 10x10 e número de threads = 5

![alt](/Lab02/assets/teste2p1.png)
![alt](/Lab02/assets/teste2p2.png)