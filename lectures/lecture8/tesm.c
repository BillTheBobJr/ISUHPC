#include <stdio.h>

int main(){
    FILE* infile = fopen('out1.data', 'r');

    double B[2][3];
    for (int i =0; i <2; i++){
        for(int j = 0; j < 3; j++){
            double z;
            fscanf(infile, '%lf', &z);
            B[i][j] = z;
            printf("B[%d][%d] = %8.4f\n", i, j, B[i][j]);
        }
    }

    fclose(infile);
    return 0;
}