#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// I decided to used nested parallelization on the same problem
// as lecture 18 and, when running the code, I found that nested parallelization
// only provided a time save over the single parallelization code from lecture 18
// once I had high thread counts and large summations.

// For example with 16 thread count for N = 20000 and K = 20000, the nested
// parallelization code outpreformed the single parallelization from lecture 18,
// and with further testing, it appeared that this trend continued with both high
// thread counts and large N/K.
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

    omp_set_nested(1); omp_set_dynamic(0);


    float *solu = (float*)malloc(N * sizeof(float));

    const double time1 = omp_get_wtime();
#   pragma omp parallel for num_threads(thread_count)
    for (int i = 1; i <= N; i++)
    {
        float sum = 0;
        # pragma omp prallel for reduction(+:sum)
        for (int j = 1; j <= K; j++)
        {
            sum += 1.0 / ((i + j - 1) * j);
        }

        # pragma omp critical
        {
            solu[i - 1] = sum;
        }
    }
    const double time2 = omp_get_wtime();

    printf("Parallelization Time = %12.5e\n\n", time2 - time1);

    free(solu);

    return 0;
}