#include <stdio.h>
#include <stdlib.h>

int m, n;
double **A, *x, *y;

void math_vect() {
    int i, j;

    for (i = 0; i < m; i++) {
        y[i] = 0;
        for (j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
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

    // Alocar memÃ³ria para A, x e y
    A = malloc(m * sizeof(double *));
    for(int i = 0; i < m; i++) {
        A[i] = malloc(n * sizeof(double));
    }
    
    x = malloc(n * sizeof(double));
    
    y = malloc(m * sizeof(double));

    // Receber input para A e x
    // printf("Digite os elementos da matriz A:\n");
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

    // Chamar math_vect
    math_vect();

    // Imprimir o vetor resultante
    printf("Vetor resultante:\n");
    print_vector(y, m);

    // Imprimir a matriz resultante
    printf("Matriz resultante:\n");
    print_vector(y, m);

    return 0;
}