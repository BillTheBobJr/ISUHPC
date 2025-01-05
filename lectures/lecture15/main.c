#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "trimatrix.h"

int main(){
    // Makes random actually random
    srand(time(NULL));

    // Create 6x6 lower matrix
    int size = 6;
    matrix L = new_matrix(size, size);

    // Populate lower matrix
    for(int i = 1; i < size; i++){
        for(int p = 0; p < i; ++p){
            L.val[i*size + p] = (double)(rand()) / (double)RAND_MAX;
        }
    }
    for(int i = 0; i < size; i++) {
        L.val[i*size + i] = 1;
    }
    
    // Create symmetric matrix using lower matrix
    matrix transpose = matrix_transpose(&L);
    matrix A = matrix_mult(&L, &transpose);

    // Create empty tridiagonal matrix
    trimatrix T = new_trimatrix(size);

    // Populate tridiagonal matrix
    Hessenberg(&A ,&T);
    printf("\n");
    printf("Original Matrix :\n");
    print_matrix(&A);
    printf("Reduction to Tridiagonal Form :\n");
    print_trimatrix(&T);

    // Solve for A using QRA and the tridiagonal matrix
    QRA(&T);
    printf("After QR Algorithm :\n");
    print_trimatrix(&T);

    return 0;
}