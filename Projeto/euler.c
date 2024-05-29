#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>

void calcularFatoriais(mpfr_t *fatoriais, int n, int precisaoBits) {
    mpfr_init2(fatoriais[0], precisaoBits);
    mpfr_set_ui(fatoriais[0], 1, MPFR_RNDN);

    for (int i = 1; i <= n; i++) {
        mpfr_init2(fatoriais[i], precisaoBits);
        mpfr_mul_ui(fatoriais[i], fatoriais[i-1], i, MPFR_RNDN);
    }
}

void euler(int n, int nBits, mpfr_t resultado) {
    mpfr_set_default_prec(nBits);
    mpfr_set_ui(resultado, 0.0, MPFR_RNDN);

    mpfr_t* fatoriais = malloc((n+1) * sizeof(mpfr_t));
    calcularFatoriais(fatoriais, n, nBits);

    mpfr_t inverso_fatorial;
    mpfr_init2(inverso_fatorial, nBits);

    for(int i = 0; i < n; i++) {
        mpfr_ui_div(inverso_fatorial, 1, fatoriais[i], MPFR_RNDN);
        mpfr_add(resultado, resultado, inverso_fatorial, MPFR_RNDN);
    }

    mpfr_clear(inverso_fatorial);

    for(int i = 0; i <= n; i++) {
        mpfr_clear(fatoriais[i]);
    }
    free(fatoriais);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Uso: %s <iteracoes> <precisao_bits>\n", argv[0]);
        return 1;
    }

    int iteracoes = strtol(argv[1], NULL, 10);
    int num_bits = strtol(argv[2], NULL, 10);

    mpfr_t euler_const;
    mpfr_init2(euler_const, num_bits);

    euler(iteracoes, num_bits, euler_const);

    printf("A constante de Euler calculada até o decimal %d é: ", num_bits);
    mpfr_out_str(stdout, 10, 0, euler_const, MPFR_RNDN);
    printf("\n");

    mpfr_clear(euler_const);

    return 0;
}