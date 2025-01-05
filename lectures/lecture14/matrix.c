#include "matrix.h"
#include <math.h>
double power_iteration(const vector * v0, double tol, int max_iter, const matrix * A) {
    vector v = v0;
    vector w;
    double eigenvalue = get_eigenvalue(A, v0);
    for(int i = 0; i < max_iter; i++) {
        w  = dot_product(A, &v);
        v = normalize_vector(&v);
        double prev = eigenvalue;
        eigenvalue = get_eigenvalue(A, &v);
        
        
        if(abs(prev - eigenvalue) < tol) {
            break;
        }
    }

    return eigenvalue;
}

double inverse_power_iteration(const vector * v0, double tol, int max_iter, const matrix * A) {
    vector v = v0;
    vector w;
    double eigenvalue = get_eigenvalue(A, v0);
    for(int i = 0; i < max_iter; i++) {
        w  = dot_product(A, &v);
        v = normalize_vector(&v);
        double prev = eigenvalue;
        eigenvalue = get_eigenvalue(A, &v);
        
        
        if(abs(prev - eigenvalue) < tol) {
            break;
        }
    }

    return eigenvalue;
}

vector dot_product(const matrix * A, const vector * b){
    vector prod = new_vector(b->size);
    for(int i = 0; i < A->rows; i ++) {
        for(int p = 0; p < A->cols; p ++) {
            prod.val[i * A->rows + p] = A->val[i * A->rows + p] * b->val[p];
        }
    }

    return prod;
}

vector normalize_vector(const vector * b) {
    double magnitude = 0;
    vector normalized = new_vector(b->size);
    for(int i = 0; i < b->size; i ++) {
        magnitude += b->val[i]*b->val[i];
    }
    magnitude = sqrt(magnitude);

    for(int i = 0; i < v.size; i++) {
        normalized.val[i] = b->val[i] / magnitude; 
    }

    return normalized;
}

double get_eigenvalue(const matrix * A, const vector * b) {
    if(!(A->cols == A->rows && A->rows == b->size)) {
        printf("Incorrect dimesions");
        return NULL;
    }

    matrix inter = new_matrix(A->rows, 1);

    for(int i = 0; i < A->rows; i++) {
        double temp = 0;
        for(int p = 0; p < b->size; p++) {
            temp += A->val[i * A->rows + p] * b->val[p];
        }
        inter.val[i] = temp;
    }

    vector temp = dot_product(&inter, b);
    print(temp.size);
    return temp.val[0];
}