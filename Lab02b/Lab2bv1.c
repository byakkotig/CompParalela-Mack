#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int m, n, thread_count;
double **A, *x, *y;
double **result;

void *Pth_math_vect(void *rank) {
    long my_rank = (long) rank;
    int i, j;
    int local_m = m / thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank == thread_count - 1) ? m - 1 : (my_rank + 1) * local_m - 1;

    if (my_first_row >= m) {
        printf("Erro: mais threads do que linhas!\n");
        exit(-1);
    }

    for (i = my_first_row; i <= my_last_row; i++) {
        y[i] = 0;
        for (j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    return NULL;
}

void print_matrix(double **matrix, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_vector(double *vector, int size) {
    for(int i = 0; i < size; i++) {
        printf("%.2f ", vector[i]);
    }
    printf("\n");
}

int main() {
    m = 100;

    n = 100;

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

	// Imprimir a matriz A
	printf("Matriz A:\n");
	print_matrix(A, m, n);

	//printf("Digite os elementos do vetor x:\n");
	for(int i = 0; i < n; i++) {
		x[i] = i;
	}

	// Imprimir o vetor x
	printf("Vetor x:\n");
	print_vector(x, n);

	// Criar threads e chamar Pth_math_vect
	pthread_t* thread_handles = malloc(thread_count * sizeof(pthread_t));
	
	for(long thread = 0; thread < thread_count; thread++) {
		pthread_create(&thread_handles[thread], NULL, Pth_math_vect, (void*) thread);
	}

	for(long thread = 0; thread < thread_count; thread++) {
		pthread_join(thread_handles[thread], NULL);
	}

	free(thread_handles);

	// Armazenar os resultados de y em uma nova matriz
	result = malloc(m * sizeof(double *));
	for(int i = 0; i < m; i++) {
		result[i] = malloc(sizeof(double));
		result[i][0] = y[i];
	}

	// Imprimir a matriz resultante
	printf("Matriz resultante:\n");
	for(int i = 0; i < m; i++) {
		printf("%.2f\n", result[i][0]);
	}

	return 0;
}