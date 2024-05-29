#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h> // Para aritmética de precisão arbitrária
#include <omp.h>

void calcularFatoriais(mpfr_t *fatoriais, int n, int precisaoBits) {
    mpfr_init2(fatoriais[0], precisaoBits);
    mpfr_set_ui(fatoriais[0], 1, MPFR_RNDN);

    for (int i = 1; i <= n; i++) {
        mpfr_init2(fatoriais[i], precisaoBits);
        mpfr_mul_ui(fatoriais[i], fatoriais[i-1], i, MPFR_RNDN);
    }
}

// Função para calcular a constante de Euler
void euler(int n, int nBits, int num_threads, mpfr_t resultado) {
    mpfr_set_default_prec(nBits);
    mpfr_set_ui(resultado, 0.0, MPFR_RNDN); // Define o resultado como 0.0

    mpfr_t* fatoriais = malloc((n+1) * sizeof(mpfr_t)); // Aloca memória para o vetor de fatoriais
    calcularFatoriais(fatoriais, n, nBits); // Calcula os fatoriais

    #pragma omp parallel num_threads(num_threads)
    {
        mpfr_t inverso_fatorial;
        mpfr_init2(inverso_fatorial, nBits);

        #pragma omp for
        for(int i = 0; i < n; i++) {
            mpfr_ui_div(inverso_fatorial, 1, fatoriais[i], MPFR_RNDN); // Calcula a inversa do fatorial

            #pragma omp critical
            {
                mpfr_add(resultado, resultado, inverso_fatorial, MPFR_RNDN); // Adiciona na soma total
            }
        }

        // Libera a memória alocada
        mpfr_clear(inverso_fatorial);
    }

    for(int i = 0; i <= n; i++) {
        mpfr_clear(fatoriais[i]); // Libera a memória alocada
    }
    free(fatoriais);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("\nEntre três argumentos. 1: Quantidade de threads a serem executadas. 2: Iterações. 3: Número de bits\n");
        return 1;
    }
    // Converte os argumentos para inteiros
    int num_threads = strtol(argv[1], NULL, 10);
    int iteracoes = strtol(argv[2], NULL, 10);
    int num_bits = strtol(argv[3], NULL, 10);

    mpfr_t euler_const;
    mpfr_init2(euler_const, num_bits);

    euler(iteracoes, num_bits, num_threads, euler_const); // Calcula a constante de Euler

    printf("A constante de Euler calculada até o decimal %d é: ", num_bits);
    mpfr_out_str(stdout, 10, 0, euler_const, MPFR_RNDN);
    printf("\n");

    mpfr_clear(euler_const);

    return 0;
}