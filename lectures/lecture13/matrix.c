#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"

matrix new_matrix(const int rows, const int cols)
{
    matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    assert(rows > 0);
    assert(cols > 0);
    mat.val = (double *)malloc(sizeof(double) * rows * cols);
    for (int i = 0; i < (rows * cols); i++)
    {
        mat.val[i] = 0.0;
    }

    return mat;
}

void print_matrix_full(const matrix *mat, char *varname)
{
    assert(mat->rows > 0);
    assert(mat->cols > 0);
    printf("\n %s =\n", varname);
    for (int i = 1; i <= mat->rows; i++)
    {
        printf(" | ");
        for (int j = 1; j <= mat->cols; j++)
        {
            printf(" %10.2e", mgetp(mat, i, j));
            if (j < mat->cols)
            {
                printf(", ");
            }
            else
            {
                printf(" ");
            }
        }
        printf("|\n");
    }
    printf("\n");
}
matrix matrix_add(const matrix *A, const matrix *B)
{
    const int rows = A->rows;
    const int cols = A->cols;
    assert(rows == B->rows);
    assert(cols == B->cols);
    matrix C = new_matrix(rows, cols);

    for (int i = 1; i <= rows; i++)
        for (int j = 1; j <= cols; j++)
        {
            mget(C, i, j) = mgetp(A, i, j) + mgetp(B, i, j);
        }

    return C;
}

matrix matrix_mult(const matrix *A, const matrix *B)
{
    const int rowsA = A->rows;
    const int colsA = A->cols;
    const int rowsB = B->rows;
    const int colsB = B->cols;
    assert(colsA == rowsB);
    matrix C = new_matrix(rowsA, colsB);

    for (int i = 1; i <= rowsA; i++)
        for (int j = 1; j <= colsB; j++)
            for (int k = 1; k <= colsA; k++)
            {
                mget(C, i, j) += mgetp(A, i, k) * mgetp(B, k, j);
            }

    return C;
}
matrix matrix_dot_mult(const matrix *A, const matrix *B)
{
    const int rows = A->rows;
    const int cols = A->cols;
    assert(rows == B->rows);
    assert(cols == B->cols);
    matrix C = new_matrix(rows, cols);

    for (int i = 1; i <= rows; i++)
        for (int j = 1; j <= cols; j++)
        {
            mget(C, i, j) = mgetp(A, i, j) * mgetp(B, i, j);
        }

    return C;
}
vector new_vector(const int size)
{
    vector vec;
    vec.size = size;
    assert(size > 0);
    vec.val = (double *)malloc(sizeof(double) * size);

    for (int i = 0; i < (size); i++)
    {
        vec.val[i] = 0.0;
    }

    return vec;
}

void print_vector_full(const vector *vec, char *varname)
{
    assert(vec->size > 0);
    printf("\n");
    printf(" %s =\n", varname);
    printf(" | ");
    for (int i = 1; i <= vec->size; i++)
    {
        printf(" %10.2e", vgetp(vec, i));
        if (i < vec->size)
        {
            printf(", ");
        }
    }
    printf(" |^T\n\n");
}
vector vector_add(const vector *x, const vector *y)
{
    const int size = x->size;
    assert(size == y->size);
    vector z = new_vector(size);

    for (int i = 1; i <= size; i++)
    {
        vget(z, i) = vgetp(x, i) + vgetp(y, i);
    }

    return z;
}
double vector_dot_mult(const vector *x, const vector *y)
{
    const int size = x->size;
    assert(size == y->size);

    double z = 0.0;
    for (int i = 1; i <= size; i++)
    {
        z += vgetp(x, i) * vgetp(y, i);
    }

    return z;
}

void print_scalar_full(const double *z, char *varname)
{
    printf("\n %.1s =\n", &varname[1]);
    printf(" %10.e \n\n", *z);
}
vector matrix_vector_mult(const matrix *A, const vector *x)
{
    const int rows = A->rows;
    const int cols = A->cols;
    const int size = x->size;
    assert(cols == size);
    vector Ax = new_vector(rows);

    for (int i = 1; i <= rows; i++)
    {
        double tmp = 0.0;
        for (int j = 1; j <= size; j++)
        {
            tmp += mgetp(A, i, j) * vgetp(x, j);
        }
        vget(Ax, i) = tmp;
    }

    return Ax;
}

vector solve(const matrix *A, const vector *b)
{
    const int rows = A->rows;
    const int cols = A->cols;
    const int size = b->size;
    assert(rows == cols);
    assert(rows == size);

    vector x = new_vector(rows);

    for (int i = 1; i <= (size - 1); i++) // LOOP OVER EACH COLUMN
    {
        // Select largest pivot in current column
        int p = i;
        double maxA = -100.e0;
        for (int j = i; j <= size; j++)
        {
            double tmp = fabs(mgetp(A, j, i));
            if (tmp > maxA)
            {
                p = j;
                maxA = tmp;
            }
        }

        // See if matrix is singular
        if (maxA <= 1.0e-14)
        {
            printf(" Cannot invert system \n");
            exit(1);
        }
        // Pivot (aka interchange rows)
        if (p != i)
        {
            for (int j = 1; j <= size; j++)
            {
                double tmp = mgetp(A, i, j);
                mgetp(A, i, j) = mgetp(A, p, j);
                mgetp(A, p, j) = tmp;
            }

            double tmp = vgetp(b, i);
            vgetp(b, i) = vgetp(b, p);
            vgetp(b, p) = tmp;
        }

        // Eliminate below diagonal
        for (int j = (i + 1); j <= size; j++)
        {
            double dm = mgetp(A, j, i) / mgetp(A, i, i);
            for (int k = 1; k <= size; k++)
            {
                mgetp(A, j, k) = mgetp(A, j, k) - dm * mgetp(A, i, k);
            }
            vgetp(b, j) = vgetp(b, j) - dm * vgetp(b, i);
        }
    }
    // Backward substitution
    vget(x, size) = vgetp(b, size) / mgetp(A, size, size);
    for (int j = 1; j <= (size - 1); j++)
    {
        double sum = 0.e0;

        for (int k = (size - j + 1); k <= size; k++)
        {
            sum = sum + mgetp(A, size - j, k) * vget(x, k);
        }

        vget(x, size - j) = (vgetp(b, size - j) - sum) / mgetp(A, size - j, size - j);
    }

    return x;
}


matrix matrix_transpose(const matrix * A){
    int rows = A->cols;
    int cols = A->rows;
    matrix transpose = new_matrix(rows, cols);
    for(int i = 0; i < cols; i++) {
        for(int p = 0; p < rows; p++) {
            transpose.val[i*rows + p] = A->val[p*cols + i];
        }
    }

    return transpose;
}


// Preform the power iteration
double power_iteration(const matrix * A, const vector * v0, double tol, int max_iter) {
    // Create a copy of the input vector
    vector v = vector_copy(v0);
    vector w;

    // Get initial eigenvalue estimate
    double eigenvalue = get_eigenvalue(A, &v);

    // Preform Power Iteration
    for(int i = 0; i < max_iter; i++) {

        w = dot_product(A, &v);
        v = normalize_vector(&w);
        double prev = eigenvalue;
        eigenvalue = get_eigenvalue(A, &v);

        if(abs(prev - eigenvalue) < tol) {
            break;
        }
    }

    // Return eigenvalue
    return eigenvalue;
}

// Preform the shifted inverse power iteration
double shifted_inverse_power_iteration(const matrix * A, const vector * v0, double mu,double tol, int max_iter) {
    // Create a copy of the input vector
    vector v = vector_copy(v0);
    vector w;

    // Get initial eigenvalue guess
    double eigenvalue = get_eigenvalue(A, v0);
    // Create shifted input matrix
    matrix mu_matrix = new_matrix(v0->size, v0->size);
    for(int i = 0; i < v0->size; i++) mu_matrix.val[i*v0->size + i] = mu;
    matrix shifted_A = matrix_sub(A, &mu_matrix);


    // Preform the shifted inverse power iteration as described in lecture
    for(int i = 0; i < max_iter; i++) {
        vector v2 = vector_copy(v0);
        w  = solve(&shifted_A, &v2);

        v = normalize_vector(&w);
        
        double prev = eigenvalue;
        eigenvalue = get_eigenvalue(A, &v);

        if(abs(prev - eigenvalue) < tol) {
            break;
        }
    }

    // Return shifted eigenvalue
    return eigenvalue;
}

// Calculates product between a matrix and vector
vector dot_product(const matrix * A, const vector * b){
    vector prod = new_vector(b->size);
    for(int i = 0; i < A->rows; i ++) {
        for(int p = 0; p < A->cols; p ++) {
            prod.val[i] += A->val[i * A->rows + p] * b->val[p];
        }

    }

    
    return prod;
}

// Normalizes a vector to magnitude of 1
vector normalize_vector(const vector * b) {

    double magnitude = 0;
    vector normalized = new_vector(b->size);
    for(int i = 0; i < b->size; i ++) {
        magnitude += b->val[i]*b->val[i];
    }
    magnitude = sqrt(magnitude);

    for(int i = 0; i < normalized.size; i++) {
        normalized.val[i] = b->val[i] / magnitude; 
    }

    return normalized;
}

// Gets largest eigenvalue by solving (b.' * A * b)
double get_eigenvalue(const matrix * A, const vector * b) {
    if(!(A->cols == A->rows && A->rows == b->size)) {
        printf("Incorrect dimesions");
        return -1;
    }

    matrix inter = new_matrix(1, A->cols);
// Solves b.' * A
    for(int i = 0; i < A->cols; i++) {
        double temp = 0;
        for(int p = 0; p < b->size; p++) {
            temp += A->val[i * A->rows + p] * b->val[p];
        }
        inter.val[i] = temp;
    }
// Solves (b.' * A) * b
    vector temp = dot_product(&inter, b);
    double val = -2147483648;
    // Gets largest eigenvalue
    for(int i = 0; i < temp.size; i++){
        if(temp.val[i] > val) val = temp.val[i];
    }
    return val;
}

// Finds sqrt of a number
double sqrt(double val) {
    int temp = (int) val;
    int count = 0;
    if(temp == 0) count = 1;
    else while(temp >>= 1) count++;
    double s = (double)count;

    if(val < 0){
        printf("Input is negative");
        return -1;
    }
    
    if(val == 0){
        return 0;
    }
    
    double sDelta;
    for(int k = 0; k < 100; k++){
        sDelta = -.5*(s - val/s);
        s += sDelta;

        if(sDelta < 1e-14 && sDelta > -1e-14){
            break;
        }
    }

    return s;
}

// Preforms a deep copy of a vector
vector vector_copy(const vector * v) {
    vector temp = new_vector(v->size);
    for(int i = 0; i < v->size; i++){
        temp.val[i] = v->val[i];
    }
    return temp;
}

// Subtracts 2 matrices
matrix matrix_sub(const matrix * A, const matrix * B) {
    if(!(A->rows == B->rows && A->cols == B->cols)) {
        printf("Invalid dimesions");
        return *A;
    }

    matrix temp = new_matrix(A->rows, A->cols);
    for(int i = 0; i < A->rows; i++){
        for(int p = 0; p < A->cols; p++){
            temp.val[i*A->rows + p] = A->val[i*A->rows + p] - B->val[i*A->rows + p];
        }
    }

    return temp;
}
