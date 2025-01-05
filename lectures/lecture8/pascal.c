#include <stdio.h>

int factorial(int n) {
    if(n <= 1) return 1;
    return n * factorial(n-1);
}

int factorialAlt(int n) {
    int m = (n % 2) + 1;
    int ret = 1;
    for(int i = 0; i < n/2; i++) ret *= (i + m)*(n - i);
    return ret;
}

int binomial(int n, int k) {
    return factorial(n)/(factorial(k)*factorial(n - k));
}



int main() {
    int binomial(int n, int k);

    printf("\nPascal's Triangle:\n\n");
    for(int i = 0; i < 11; i++){
        for(int p = 0; p <= i; p++){
            printf("%d\t", binomial(i, p));
        }
        printf("\n");
    }
}