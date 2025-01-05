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

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        usage(argv[0]);
    }
    const int thread_count = strtol(argv[1], NULL, 10);
    const int N = strtol(argv[2], NULL, 10);
    const int K = strtol(argv[3], NULL, 10);

    if (thread_count < 1 || N < 1 || K < 1 || K % thread_count != 0)
    {
        usage(argv[0]);
    }
    omp_set_num_threads(thread_count);

    const double time1 = omp_get_wtime();

    int i = 1;
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (int j = 1; j <= K; j++)
    {
        sum += 1.0;
    }

    printf("%lf\n", sum);

    const double time2 = omp_get_wtime();
    printf("time = %12.5e\n\n", time2 - time1);

    return 0;
}

// This appears to run slower for more threads because the overhead for
// making more parallel process is more expensive than the time saved by running in parallel
// if we could somehow run the outer loop in parallel instead of the inner loop
// this should save time, however because order matters with the final calculation of
// the sum, we can not do that