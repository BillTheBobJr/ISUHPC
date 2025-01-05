#include <stdio.h>
#include <stdlib.h>

struct fraction {
    int numerator;
    int denominator;
};

int findPrimeFactors(int number, int *primes, int len) {
    int count = 0;
    int curr = 3;
    while(curr * curr < number) {
        if(count == len){
            printf("Buffer length met");
            break;
        }

        if(!(number && 1)) {
            primes[count++] = 2;
            number /= 2;
            continue;
        }

        if(((number / curr) * curr ) == number) {
            primes[count++] = curr;
            number /= curr;
            curr = 3;
            continue;
        }

        curr += 2;
    }

    primes[count] = number;
    return count + 1;
}

int main(int argc, char *argv[]) {
    int *primes = (int *)malloc(10 * sizeof(int));

    printf("%d", atoi(argv[1]));
    int count = findPrimeFactors(atoi(argv[1]), primes, 10);
    for(int i = 0; i < count; i ++) {
        if(i) {
            printf(", ");
        }
        printf("%d", primes[i]);
    }
    
    return 0;
}