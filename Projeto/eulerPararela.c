#include <stdio.h>
#include <mpfr.h>
#include <omp.h>

mpfr_t fatorial_atual, euler;

void mudar_fatorial(int n) { mpfr_mul_si(fatorial_atual, fatorial_atual, (n != 0) ? n : 1, MPFR_RNDN); }

void calcular_euler(int num_loops, int num_bits) {
    mpfr_t euler;
    mpfr_init2(euler, num_bits);
    mpfr_init_set_d(euler, 0.0, MPFR_RNDN);

    #pragma omp parallel for
    for(int n = 0; n < num_loops; n++) {
        mpfr_t fatorial_atual, temp;
        mpfr_init2(fatorial_atual, num_bits);
        mpfr_init_set_d(fatorial_atual, 1.0, MPFR_RNDN);
        mpfr_init2(temp, num_bits);
        mpfr_init_set_d(temp, 1.0, MPFR_RNDN);

        for(int i = 1; i <= n; i++) {
            mpfr_mul_si(fatorial_atual, fatorial_atual, i, MPFR_RNDN);
        }

        mpfr_div(temp, temp, fatorial_atual, MPFR_RNDN);
        mpfr_add(euler, euler, temp, MPFR_RNDN);

        mpfr_clear(fatorial_atual);
        mpfr_clear(temp);
    }

    mpfr_printf("A constante de Euler calculada até o decimal %d é: %.100Rf\n", num_bits, euler);
    mpfr_clear(euler);
}

int main() {
    int num_threads, num_loops, num_bits;
    printf("Digite o número de threads: ");
    scanf("%d", &num_threads);
    printf("Digite o número de iterações: ");
    scanf("%d", &num_loops);
    printf("Digite o número de bits: ");
    scanf("%d", &num_bits);

    omp_set_num_threads(num_threads);
    mpfr_set_default_prec(num_bits);
    calcular_euler(num_loops, num_bits);
    return 0;
}