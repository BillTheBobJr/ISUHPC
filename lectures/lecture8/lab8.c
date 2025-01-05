#include <stdio.h>
#include <math.h>

const double e = 2.718281828459f;

int factorial(int n) {
    if(n <= 1) return 1;
    return n * factorial(n-1);
}

double myExp(double x, int kmax) {
    int x0 = x;
    double z = x - x0;
    double exp0 = pow(e,x0);
    double s = 0;

    for(int k = 0; k < kmax; k++) {
        double delta = (pow(z,k))/factorial(k);
        s += delta;

        if(delta < (double)(1E-14)) break;
        }
    return exp0*s;
}

void expOnArr(double n[], int len) {
    for(int i = 0; i < len; i++) {
        n[i] = myExp(n[i], 100);
    }
}

void writeArr(double arr[], int len) {
    FILE* outfile = fopen("output.data", "w");

    for(int i = 0; i < len; i++) fprintf(outfile, "%10.14f\n", arr[i]);

    fclose(outfile);
}

int main() {
    double x[5];
    printf("Input 5 floats to test Exp:");
    scanf("%lf,%lf,%lf,%lf,%lf", &x[0], &x[1], &x[2], &x[3], &x[4]);
    expOnArr(x, 5);
    printf("%lf, %lf, %lf, %lf, %lf\n", x[0], x[1], x[2], x[3], x[4]);
    writeArr(x, 5);
}