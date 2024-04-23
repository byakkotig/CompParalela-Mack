#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double f(double x) {
    return 5 + sin(x); // example function
}

void CalculateArea(double a, double b, int n, int thread_count, double* global_result_p){
    double h, x, my_result;
    double local_a, local_b;
    int i, local_n;
    int my_rank = omp_get_thread_num();

    h = (b-a)/n;
    local_n = n/thread_count;
    local_a = a + my_rank*local_n*h;
    local_b = local_a + local_n*h;
    my_result = (f(local_a)+ f(local_b))/2.0;
    for (i = 1; i <= local_n - 1; i++){
        x = local_a + i*h;
        my_result += f(x);
    }
    my_result = my_result * h;

    #pragma omp critical
    *global_result_p += my_result;
}

int main(int argc, char* argv[]) {
    double global_result = 0.0; /* Store result in global_result */
    double a, b;                 /* Left and right endpoints      */
    int n;                       /* Total number of trapezoids    */
    int thread_count;

    if(argc != 5) {
        printf("Usage: %s <a> <b> <n> <thread_count>\n", argv[0]);
        return 1;
    }

    a = strtod(argv[1], NULL);
    b = strtod(argv[2], NULL);
    n = strtol(argv[3], NULL, 10);
    thread_count = strtol(argv[4], NULL, 10);

    #pragma omp parallel num_threads(thread_count)
    CalculateArea(a, b, n, thread_count, &global_result);

    printf("A integral estimada é: %.14e\n", global_result);
    return 0;
}