#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "matrix.h"

int main() {
    srand(time(NULL));
    int size;
    printf("Size of Matrix:");
    scanf("%d", &size);
    matrix L = new_matrix(size, size);
    vector b = new_vector(size);


    for(int i = 1; i < size; i++){
        for(int p = 0; p < i; ++p){
            L.val[i*size + p] = (double)(rand()) / (double)RAND_MAX;
        }
    }
    for(int i = 0; i < size; i++) {
        L.val[i*size + i] = 1;
        b.val[i] = (double)(rand()) / (double)RAND_MAX;
    }

    matrix transpose = matrix_transpose(&L);
    matrix A = matrix_mult(&L, &transpose);

    print_matrix_full(&A, "A");
    print_vector_full(&b, "b");
    double eigenvalue = power_iteration(&A, &b, 1e-14, 10);
    double shifted_eigenvalue = shifted_inverse_power_iteration(&A, &b, 1, 1e-10,10);
    
    vector solu = solve(&A, &b);
    print_vector_full(&solu, "Solution");
    printf("Max Eigenvalue of the Matrix: %lf\n", eigenvalue);
    printf("Max Eigenvalue of the Matrix Shifted by mu = 1: %lf\n", shifted_eigenvalue);    

    return 0;
}

