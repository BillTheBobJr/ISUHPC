#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"

vector new_vector(const int len, const float val) {
    vector vec;
    vec.len = len;

    assert(len > 0);
    vec.val = (float *)malloc(sizeof(float) * len);
    for(int i = 0; i < len; i++) {
        vec.val[i] = val;
    }

    return vec;


}
vector copy_vector(const vector vec) {
    vector new_vec = new_vector(vec.len, 0.0f);
    for(int i = 0; i < vec.len; i++) {
        new_vec.val[i] = vec.val[i];
    }

    return new_vec;
}

void print_vector_full( const vector * vec , char* varname ){
        assert(vec->len > 0);
    printf("\n");
    printf(" %s =\n", varname);
    printf(" | ");
    for (int i = 0; i < vec->len; i++)
    {
        printf(" %10.2e", vec->val[i]);
        if (i < vec->len)
        {
            printf(", ");
        }
    }
    printf(" |^T\n\n");
}

void delete_vector(vector * vec) {
    free(vec->val);
}

// Finds sqrt of a number
float f_sqrt(float val) {
    int temp = (int) val;
    int count = 0;
    if(temp < 2) count = 1;
    else while(temp >>= 1) count++;
    float s = (float)count;

    if(val < 0){
        printf("Input is negative");
        return -1;
    }
    
    if(val == 0){
        return 0;
    }
    
    float sDelta;
    for(int k = 0; k < 100; k++){
        sDelta = -.5*(s - val/s);
        s += sDelta;

        if(sDelta < 1e-14 && sDelta > -1e-14){
            break;
        }
    }

    return s;
}