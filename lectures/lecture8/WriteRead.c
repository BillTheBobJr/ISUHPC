#include <stdio.h>

int main() {
    double A[2][3] = {{10, -20, 30}, {-40, 50, -60}};

    FILE* outfile = fopen("output.data", "w");

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 3; j++){
            fprintf(outfile, "%23.16e\n", A[i][j]);
        }
    }

    fclose(outfile);
    return 0;
}