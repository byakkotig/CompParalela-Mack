# Laboratório 2 - Matriz vetor

## Sobre o projeto

Esse projeto consiste em criar um código para resolver o problema de multiplicação de matriz-vetor usando paralelismo, para isso utilizamos Pthreads. 

Os códigos criados foram: 

- `Lab2bv1` que contém o código com pararelismo 

- `Lab2bSerial` que contém o código com a versão serial 

- `Lab2bv2`que contém a versão com paralelismo melhorada. 

Após a criação dos códigos foram respondidas as questões realizadas pelo professor.

Este documento contém instruções detalhadas sobre como compilar, executar e verificar os resultados do programa entregue.

Testes foram realizados no terminal Linux Ubuntu.

## Integrantes

- André Akio Morita Osakawa - 10340045
- Rafael de Souza Oliveira Cerqueira Tinôco - 10401436
- Rodrigo Mileo Lourenço Gil - 10390174

## Instalação

Usando o `git`, clone o repositório usando o seguinte comando:

`git clone https://github.com/byakkotig/CompParalela-Mack.git`, depois use o comando `cd CompParalela-Mack` para entrar na pasta e o comando `cd Lab02b` para entrar na pasta do lab

## Compilação e Execução

O exercicio proposto pelo professor consiste em usar o comando `time` no terminal Linux para mostrar o tempo de execução de cada código, além disso pede-se para executar os códigos com 1, 2 ,4, 6 e 8 processadores, para isso usamos o comando `taskset -c [número dos processadores]`.

Os comando utilizados foram: 

- Para 1 processador `time taskset -c 0 [nome_do_arquivo]` 

- Para 2 processadores `time taskset -c 0,1 [nome_do_arquivo]`

- Para 4 processadores `time taskset -c 0,1,2,3 [nome_do_arquivo]`

- Para 6 processadores `time taskset -c 0,1,2,3,4,5 [nome_do_arquivo]`

- Para 8 processadores `time taskset -c 0,1,2,3,4,5,6,7 [nome_do_arquivo]`


Para compilar o código `Lab2bv1.c` com paralelismo, entre na pasta do projeto e no terminal, utilize o comando `gcc Lab2bv1.c -o Lab2bv1` e para executá-lo digite o comando `time taskset -c [número dos processadores] ./Lab2bv1`. Como visto no exemplo abaixo.

![alt](/Lab02b/assets/compilacao1.png)

Para compilar o código `Lab2bSerial` que contém o código com a versão serial entre na pasta do projeto e no terminal, utilize o comando `gcc Lab2bSerial.c -o Lab2bSerial` e para executá-lo digite o comando `time ./Lab2bSerial`. Como visto no exemplo abaixo.

![alt](/Lab02b/assets/compilacao2.png)

Para compilar o código `Lab2bv2.c` que é a versão melhorada, entre na pasta do projeto e no terminal, utilize o comando `gcc Lab2bv2.c -o Lab2bv2` e para executá-lo digite o comando `time taskset -c [número dos processadores] ./Lab2bv2`. Como visto no exemplo abaixo.

![alt](/Lab02b/assets/compilacao3.png)

### Prints da execução dos códigos estão tanto na pasta `assets` quanto nas instruções de cada exercicio abaixo

## Resolução dos exercicios propostos

Primeiramente, segue abaixo o print do comando `cat /proc/cpuinfo` pedido pelo professor, para mostrar o processador utilizado para os testes e para a criação dos gráficos.

![alt](/Lab02b/assets/processador.png)


1. Qual o tempo de execução serial e paralelo para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico contendo todos os tempos de execução

Abaixo segue os prints dos tempos de execução dos códigos serial e pararelo, depois o gráfico montado a partir dos resultados

#### Tempo versão Serial

![alt](/Lab02b/assets/serial1.png)
![alt](/Lab02b/assets/serial2.png)


#### Tempo versão Pararela

1 Processador

![alt](/Lab02b/assets/par1p1.png)
![alt](/Lab02b/assets/par1p2.png)

2 Processadores

![alt](/Lab02b/assets/par2p1.png)
![alt](/Lab02b/assets/par2p2.png)

4 Processadores

![alt](/Lab02b/assets/par4p1.png)
![alt](/Lab02b/assets/par4p2.png)

6 Processadores

![alt](/Lab02b/assets/par6p1.png)
![alt](/Lab02b/assets/par6p2.png)


8 Processadores

![alt](/Lab02b/assets/par8p1.png)
![alt](/Lab02b/assets/par8p2.png)


#### Gráfico de tempo

![alt](/Lab02b/assets/graf1.png)

2. Qual o speedup para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico mostrando os diferentes valores de speedup.

#### Gráfico Speedup


![alt](/Lab02b/assets/tab1.png)
![alt](/Lab02b/assets/graf2.png)

3. Como você acha que poderia melhorar o seu algoritmo para obter maior benefício com o paralelismo? Para provar seu ponto, refaça a solução com essa abordagem e construa um novo gráfico de speedup para 1, 2, 4, 6 e 8 processadores.

Para melhorar o algoritimo retiramos os prints das matrizes e deixamos apenas mostrar o tempo que levou para a execução, além disso modificamos o código para dividir as linhas da matriz entre as threads de maneira mais equilibrada, se o número de linhas não é um múltiplo do número de threads, as primeiras remainder threads (threads restantes) recebem uma linha extra. Isso garante que todas as threads tenham aproximadamente a mesma quantidade de trabalho a fazer, otimizando o paralelismo.

#### Tempo versão paralela melhorada

1 Processador

![alt](/Lab02b/assets/par-mel1.png)

2 Processadores

![alt](/Lab02b/assets/par-mel2.png)

4 Processadores

![alt](/Lab02b/assets/par-mel4.png)

6 Processadores

![alt](/Lab02b/assets/par-mel6.png)

8 Processadores

![alt](/Lab02b/assets/par-mel8.png)

#### Gráfico Speedup

![alt](/Lab02b/assets/tab2.png)
![alt](/Lab02b/assets/graf3.png)