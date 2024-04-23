# Laboratório 3 - Cálculo da área sob a curva através da soma de trapézios usando OpenMP

## Sobre o projeto

Esse projeto consiste em criar um código para resolver o problema do cálculo da área sob a curva através da soma de trapézios em um gráfico, foram criadas três códigos para a resolução do problema.

Os códigos criados foram: 

- `lab3paralelo` que contém o código com solução paralela utilizando OpenMP

- `lab3serial` que contém o código com a versão serial 

- `lab3paralelocrit`que contém a versão paralela com a diretiva critical pedido pelo professor

Após a criação dos códigos foram respondidas as questões realizadas pelo professor.

Este documento contém instruções detalhadas sobre como compilar, executar e verificar os resultados do programa entregue.

Testes foram realizados no terminal Linux Ubuntu.

## Integrantes

- André Akio Morita Osakawa - 10340045
- Rafael de Souza Oliveira Cerqueira Tinôco - 10401436
- Rodrigo Mileo Lourenço Gil - 10390174

## Instalação

Usando o `git`, clone o repositório usando o seguinte comando:

`git clone https://github.com/byakkotig/CompParalela-Mack.git`, depois use o comando `cd CompParalela-Mack` para entrar na pasta e o comando `cd Lab03` para entrar na pasta do lab

## Compilação e Execução

O exercicio proposto pelo professor consiste em usar o comando `time` no terminal Linux para mostrar o tempo de execução de cada código, além disso pede-se para executar os códigos com 1, 2 ,4, 6 e 8 processadores, para isso usamos o comando `taskset -c [número dos processadores]`.

Os comando utilizados foram: 

- Para 1 processador `time taskset -c 0 [nome_do_arquivo]` 

- Para 2 processadores `time taskset -c 0,1 [nome_do_arquivo]`

- Para 4 processadores `time taskset -c 0,1,2,3 [nome_do_arquivo]`

- Para 6 processadores `time taskset -c 0,1,2,3,4,5 [nome_do_arquivo]`

- Para 8 processadores `time taskset -c 0,1,2,3,4,5,6,7 [nome_do_arquivo]`

Para compilar o código `lab3serial` que contém o código com a versão serial entre na pasta do projeto e no terminal, utilize o comando `gcc lab3serial.c -o lab3serial -lm` e para executá-lo digite o comando `time taskset -c [número dos processadores] ./lab3serial`. Como visto no exemplo abaixo.

![alt](/Lab03/assets/compilacao1.png)
![alt](/Lab03/assets/compilacao.png)

Para compilar o código `lab3paralelo.c` com paralelismo, entre na pasta do projeto e no terminal, utilize o comando `gcc -fopenmp lab3paralelo.c -o lab3paralelo -lm` e para executá-lo digite o comando `time taskset -c [número dos processadores] ./lab3paralelo [valor de a] [valor de b] [valor de n] [numero de threads]`. Como visto no exemplo abaixo.

![alt](/Lab03/assets/compilacao2.png)
![alt](/Lab03/assets/paralelo1.png)

Para compilar o código `lab3paralelocrit.c` com a diretiva critical, entre na pasta do projeto e no terminal, utilize o comando `gcc -fopenmp lab3paralelocrit.c -o lab3paralelocrit -lm` e para executá-lo digite o comando `time taskset -c [número dos processadores] ./lab3paralelocrit [valor de a] [valor de b] [valor de n] [numero de threads]`. Como visto no exemplo abaixo.

![alt](/Lab03/assets/compilacao3.png)
![alt](/Lab03/assets/critical1.png)

### Prints da execução dos códigos estão tanto na pasta `assets` quanto nas instruções de cada exercicio abaixo

## Resolução dos exercicios propostos

Primeiramente, segue abaixo o print do comando `cat /proc/cpuinfo` pedido pelo professor, para mostrar o processador utilizado para os testes e para a criação dos gráficos.

![alt](/Lab03/assets/processador.png)

1. Qual o tempo de execução serial e paralelo para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico contendo todos os tempos de execução

Abaixo segue os prints dos tempos de execução dos códigos serial e pararelo, depois o gráfico montado a partir dos resultados

#### Tempo versão Serial

Os valores dos parâmetros utilizados foram: a = 0, b = 10 e n = 1000000000

1 processador

![alt](/Lab03/assets/serial1.png)
![alt](/Lab03/assets/serial1t.png)

2 processadores

![alt](/Lab03/assets/serial2.png)
![alt](/Lab03/assets/serial2t.png)

4 processadores

![alt](/Lab03/assets/serial4.png)
![alt](/Lab03/assets/serial4t.png)

6 processadores

![alt](/Lab03/assets/serial6.png)
![alt](/Lab03/assets/serial6t.png)

8 processadores

![alt](/Lab03/assets/serial8.png)
![alt](/Lab03/assets/serial8t.png)

#### Tempo versão Pararela / Os valores utilizados foram a = 0, b = 10, n = 1000000000 e num de threads (1,2,4,6,8) como visto nos prints

1 processador

![alt](/Lab03/assets/paralelo1.png)
![alt](/Lab03/assets/paralelo1t.png)

2 processadores

![alt](/Lab03/assets/paralelo2.png)
![alt](/Lab03/assets/paralelo2t.png)

4 processadores

![alt](/Lab03/assets/paralelo4.png)
![alt](/Lab03/assets/paralelo4t.png)

6 processadores

![alt](/Lab03/assets/paralelo6.png)
![alt](/Lab03/assets/paralelo6t.png)

8 processadores 

![alt](/Lab03/assets/paralelo8.png)
![alt](/Lab03/assets/paralelo8t.png)

#### Gráfico de tempo

![alt](/Lab03/assets/tabela1.png)
![alt](/Lab03/assets/grafico1.png)

2. Qual o speedup para 1, 2, 4, 6 e 8 processadores? Desenhe um gráfico mostrando os diferentes valores de speedup.

#### Gráfico Speedup versão Paralela

![alt](/Lab03/assets/tabela2.png)
![alt](/Lab03/assets/grafico2.png)

3. Introduza na sua solução a diretiva critical. O que muda? Para provar seu ponto, refaça a solução com essa abordagem, calcule os novos valores e construa um novo gráfico de speedup para 1, 2, 4, 6 e 8 processadores.

Com a diretiva critical #pragma omp critical, ela garante que apenas uma thread execute o bloco de código crítico de cada vez, também chamado como exclusão mútua, isso evita que condições de corrida ocorram, quando várias threads tentam atualizar a mesma variável (global_result_p neste caso) ao mesmo tempo. Essa diretiva também pode reduzir o desempenho, pois ele força a execução serial de um bloco de código.


#### Tempo versão paralela com diretiva critical / Os valores utilizados foram a = 0, b = 10, n = 1000000000 e num de threads (1,2,4,6,8) como visto nos prints

1 processador

![alt](/Lab03/assets/critical1.png)
![alt](/Lab03/assets/critical1t.png)

2 processadores

![alt](/Lab03/assets/critical2.png)
![alt](/Lab03/assets/critical2t.png)

4 processadores

![alt](/Lab03/assets/critical4.png)
![alt](/Lab03/assets/critical4t.png)

6 processadores

![alt](/Lab03/assets/critical6.png)
![alt](/Lab03/assets/critical6t.png)

8 processadores

![alt](/Lab03/assets/critical8.png)
![alt](/Lab03/assets/critical8t.png)

#### Gráfico Speedup versão Critical

![alt](/Lab03/assets/tabela3.png)
![alt](/Lab03/assets/grafico3.png)