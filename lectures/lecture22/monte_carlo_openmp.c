#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(int argc, char **argv)
{
    srand(time(NULL));
    const int thread_count = 4;
    const int size = 1000000;
    omp_set_num_threads(thread_count);
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < size; i++)
    {
        double x = (double)rand()/((double)RAND_MAX);
        double y = (double)rand()/((double)RAND_MAX);
        double s = x*x + y*y;
        sum += (s < 1) ? 1.0f : 0.0f;
    }

    printf("An approximation for pi is %lf\n", 4 * sum / size);

    return 0;
}