#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <mpfr.h>

// Função para calcular o fatorial
void fatorial(mpfr_t resultado, int n) {
    mpfr_set_d(resultado, 1.0, MPFR_RNDN); // Inicializa o resultado com 1
    for(int i = 1; i <= n; i++) {
        mpfr_mul_ui(resultado, resultado, i, MPFR_RNDN); // Multiplica o resultado por i
    }
}

// Função para calcular a constante de Euler
void euler(mpfr_t e, int precisao, int iteracoes, int num_threads) {
    mpfr_set_default_prec(precisao);
    mpfr_t *euler_partials = malloc(num_threads * sizeof(mpfr_t));

    for (int i = 0; i < num_threads; i++) {
        mpfr_init2(euler_partials[i], precisao);
        mpfr_set_d(euler_partials[i], 0.0, MPFR_RNDN);
    }

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        mpfr_t fatorial_atual, temp;
        mpfr_init2(fatorial_atual, precisao);
        mpfr_init2(temp, precisao);

        #pragma omp for
        for(int n = 0; n < iteracoes; n++) {
            fatorial(fatorial_atual, n); // Calcula o fatorial
            mpfr_ui_div(temp, 1, fatorial_atual, MPFR_RNDN); // Calcula o termo da série
            mpfr_add(euler_partials[thread_id], euler_partials[thread_id], temp, MPFR_RNDN); // Adiciona o termo a e
        }

        mpfr_clear(fatorial_atual);
        mpfr_clear(temp);
    }

    mpfr_set_d(e, 0.0, MPFR_RNDN); // Inicializa e com 1
    for (int i = 0; i < num_threads; i++) {
        mpfr_add(e, e, euler_partials[i], MPFR_RNDN); // Adiciona o termo a e
        mpfr_clear(euler_partials[i]);
    }
    free(euler_partials);

    mpfr_printf("A constante de Euler calculada até o decimal %d é: %.3000Rf\n", precisao, e);
    mpfr_clear(e);
}

int main(int argc, char *argv[]) {
    if(argc != 4) {
        printf("Uso: %s <número de threads> <número de iterações> <número de bits de precisão>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    int iteracoes = atoi(argv[2]);
    int precisao = atoi(argv[3]);

    mpfr_t e;
    mpfr_init2(e, precisao);

    euler(e, precisao, iteracoes, num_threads); // Calcula a constante de Euler

    mpfr_clear(e);

    return 0;
}