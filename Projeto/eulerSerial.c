//Versao 1

#include <stdio.h>
#include <mpfr.h>
//Usa-se MPFR pois pode-se definir a precisão das variáveis usadas, enquanto variáveis como double possuem apenas 15 dígitos decimais.
//A biblioteca GMP não foi utilizada pois MPFR fornece mais liberdade quanto à precisão da variável e ao método de arredondamento
//Não se sabe qual o tipo de arredondamento usado na biblioteca GMP, sendo que o desejado é o arredondamento para o mais próximo devido à grande quantidade de somas.
//https://gmplib.org/list-archives/gmp-discuss/2009-April/003667.html
//Quando somam-se muitos números, os erros de arredondamento podem se acumular. O arredondamento escolhido é o arredondamento para o mais próximo
//Por exemplo, caso o arredondamento seja sempre para cima ou sempre arredonda para baixo, pode haver um viés sistemático nos resultados, sendo muito baixos ou muito altos
//No arredondamento para o mais próximo tais erros tendem a se cancelar parcialmente, por isso é visado nesse projeto como o arredondamento ideal

mpfr_t fatorial_atual, euler;
//O uso de uma variável global funciona efetivamente apenas para o modo serial
//Claramente funcionaria também para o modo paralelo mas seria necessário fazer as outras threads esperarem enquanto essa variável é modificada
//Idealmente, no modo paralelo, é ideal uma variável dessa para cada escopo local de cada thread ou usar uma função recursiva para não ser necessário o uso da variável
//O método recursivo poderia ser aplicado no modo serial também
//A variável euler é usada para guardar o valor total da somatória das fatoriais

void mudar_fatorial(int n) { mpfr_mul_si(fatorial_atual, fatorial_atual, (n != 0) ? n : 1, MPFR_RNDN); }
//Nessa função multiplica-se a variável fatorial atual, que guarda o valor atual do fatorial, pelo número n atual na função de euler
//Essa abordagem é melhor pois evita multiplos cálculos desnecessários para encontrar a fatorial, sendo que a próxima fatorial a ser utilizada é sempre a fatorial de n + 1
//Ou seja, a próxima fatorial a ser usada no euler é sempre a fatorial anterior multiplicada pelo n atual, valor que vai ser armazenado na variável fatorial_atual
//Caso o valor n atual seja 0, irá multiplicar por 1, isso serve apenas para evitar erros, pois a fatorial de 0 é 1
//Considerando que a variável fatorial_atual inicia por 1, deve-se multiplicar por 1 caso n = 0 para manter o valor correto
//A função usada mpfr_mul_si serve para multiplicar o valor de fatorial_atual pelo valor de n, guardando o resultado em fatorial_atual
//O último parámetro de mpfr_mul_si representa o método de arredondamento, que nesse caso será o arredondamento para o mais próximo (MPFR_RNDN: round to nearest)

void calcular_euler(int num_loops) {
    int n = 0;
    mpfr_t temp;
    mpfr_init2(temp, 100);
    mpfr_init_set_d(temp, 1.0, MPFR_RNDN);
    mpfr_init2(euler, 100);
    mpfr_init_set_d(euler, 0.0, MPFR_RNDN);
    while(n < num_loops) {
        mpfr_add(euler, euler, temp, MPFR_RNDN);
        n++;
        mudar_fatorial(n);
        mpfr_set_d(temp, 1.0, MPFR_RNDN);
        mpfr_div(temp, temp, fatorial_atual, MPFR_RNDN);
    }
    mpfr_clear(temp);
}
//Temp inicia com valor 1 e euler com valor 0, temp é a variável que irá guardar o valor de 1 que será divido pela fatorial atual
//Roda num loop while até 100 para calcular todos os 100 dígitos
//Adiciona o valor da variável temp à euler e roda a função de mudar o valor da fatorial para próxima
//Após isso divide temp pela fatorial atual
//Por fim limpa a variável temp
//Ou seja, é a soma dos valores de 1 divido pelas fatoriais somados ao valor de euler

int main() {
    mpfr_set_default_prec(100);
    mpfr_init2(fatorial_atual, 100);
    mpfr_init_set_d(fatorial_atual, 1.0, MPFR_RNDN);
    calcular_euler(100);
    mpfr_printf("A constante de Euler calculada até o decimal 100 é: %.100Rf\n", euler);
    mpfr_clear(fatorial_atual);
    mpfr_clear(euler);
    return 0;
}
//Aumentando a precisão com mpfr_set_default_prec para mostrar números que seriam considerados insignificantes a fim de mostrar mais casas decimais
//Inicializando a variável fatorial_atual com 100 casas decimais com mpfr_init2 e declarando seu valor como 1 com mpfr_init_set_d, e o método de arredondamento para o mais próximo (MPFR_RNDN: round to nearest)
//Limpa as variáveis de fatorial atual e euler