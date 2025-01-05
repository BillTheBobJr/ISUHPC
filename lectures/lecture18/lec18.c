#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


void usage(const char *prog_name)
{
    fprintf(stderr, " usage : %s <num_threads > <num_intervals >\n", prog_name);
    fprintf(stderr, " num_threads should be positive \n");
    fprintf(stderr, " num_intervals should be positive \n");
    fprintf(stderr, " mod( num_intervals , num_threads ) != 0\n");
    exit(1);
}

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        usage(argv[0]);
    }
    const int thread_count = strtol(argv[1], NULL, 10);
    const int N = strtol(argv[2], NULL, 10);
    const int K = strtol(argv[3], NULL, 10);
    if (thread_count < 1 || N < 1 || K < 1 || N % thread_count != 0)
    {
        usage(argv[0]);
    }

    // Version 1: Parallelizing the inner loop, is significatly slower to due theard initialization overhead
    const double v1Time1 = omp_get_wtime();

    for (int i = 1; i <= N; i++)
    {
        double sum = 0;

    #   pragma omp parallel for num_threads(thread_count) \
        reduction(+ : sum)
        for (int j = 1; j <= K; j++)
        {
            sum += 1.0 / ((i + j - 1) * j);
        }
    }

    const double v1Time2 = omp_get_wtime();
    printf("Inner Loop Parallelization Time = %12.5e\n\n", v1Time2 - v1Time1);

    // Version 2: Parallelizing the outer loop, has limitation due to storage constaints
    float *solu = (float*)malloc(N * sizeof(float));

    const double v2Time1 = omp_get_wtime();
#   pragma omp parallel for num_threads(thread_count)
    for (int i = 1; i <= N; i++)
    {
        float sum = 0;
        for (int j = 1; j <= K; j++)
        {
            sum += 1.0 / ((i + j - 1) * j);
        }
        # pragma omp critical
        {
            solu[i - 1] = sum;
        }
    }
    const double v2Time2 = omp_get_wtime();

    printf("Outer Loop Parallelization Time = %12.5e\n\n", v2Time2 - v2Time1);

    free(solu);

    return 0;
}
