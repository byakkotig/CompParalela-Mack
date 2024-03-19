#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int m, n, thread_count;
double **A, *x, *y;

void *Pth_math_vect(void *rank) {
    long my_rank = (long) rank;
    int i, j;
    int local_m = m / thread_count;
    int remainder = m % thread_count;
    int my_first_row = my_rank * local_m + (my_rank < remainder ? my_rank : remainder);
    int my_last_row = my_first_row + local_m - (my_rank < remainder ? 0 : 1);

    for (i = my_first_row; i <= my_last_row; i++) {
        y[i] = 0;
        for (j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    return NULL;
}


int main() {
    m = 100;
    n = 100;
//  m = linha; n = coluna
    thread_count = 100;

    if (thread_count > m) {
        printf("Erro: mais threads do que linhas!\n");
        return -1;
    }

    // Alocar memÃ³ria para A, x e y
    A = malloc(m * sizeof(double *));
    for(int i = 0; i < m; i++) {
        A[i] = malloc(n * sizeof(double));
    }
    
    x = malloc(n * sizeof(double));
    
    y = malloc(m * sizeof(double));

    // Receber input para A e x
    int cont = 1;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            A[i][j] = cont;
            cont += 1;
        }
    }

	// Criar threads e chamar Pth_math_vect
	pthread_t* thread_handles = malloc(thread_count * sizeof(pthread_t));
	
	for(long thread = 0; thread < thread_count; thread++) {
		pthread_create(&thread_handles[thread], NULL, Pth_math_vect, (void*) thread);
	}

	for(long thread = 0; thread < thread_count; thread++) {
		pthread_join(thread_handles[thread], NULL);
	}

	free(thread_handles);

	return 0;
}