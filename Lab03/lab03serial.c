#include <stdio.h>
#include <math.h>

// Definindo a função f(x) = sin(x)
double f(double x) {
    return 5.0 + sin(x);
}

double trapezoidal_rule(double a, double b, int n) {
    double h = (b - a) / n;
    double approx = (f(a) + f(b)) / 2.0;
    for (int i = 1; i <= n - 1; i++) {
        double x_i = a + i * h;
        approx += f(x_i);
    }
    approx = h * approx;
    return approx;
}

int main() {
    double a = 0.0; // limite inferior
    double b = 10.0; // limite superior
    int n = 1000000000.0; // número de subintervalos

    double result = trapezoidal_rule(a, b, n);
    printf("A integral aproximada de f(x) = sin(x) de %f a %f é %f\n", a, b, result);

    return 0;
}
