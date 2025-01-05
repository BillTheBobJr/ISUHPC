#include <stdio.h>
#include <time.h>

int factorialAlt(int n) {
    int m = (n % 2) + 1;
    int ret = 1;
    for(int i = 0; i < n/2; i++) ret *= (i + m)*(n - i);
    return ret;
}
int factorial(int n) {
    if(n <= 1) return 1;
    return n * factorial(n-1);
}

int main(){
    int start2 = clock();
    printf("%d\n", factorialAlt(10));
    int end2 = clock();
    int start1 = clock();
    printf("%d\n", factorial(10));
    int end1 = clock();

    printf("%d\n%d\n", end1 - start1, end2 - start2);
}