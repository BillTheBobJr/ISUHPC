#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "vector.h"

vector fine_grain_parallel(const vector vec, const int thread_count)
{
    vector local_vec = copy_vector(vec);

    float norm = 0.0f;
    const double time1 = omp_get_wtime();
#pragma omp parallel num_threads(thread_count)
    {
#pragma omp for reduction(+ : norm)
        for (int i = 0; i < local_vec.len; i++)
        {
            norm += local_vec.val[i] * local_vec.val[i];
        }

#pragma omp barrier // not needed ( implicit )

#pragma omp single
        norm = f_sqrt(norm);

#pragma omp for
        for (int i = 0; i < local_vec.len; i++)
        {
            local_vec.val[i] = local_vec.val[i] / norm;
        }
    }
    const double time2 = omp_get_wtime();

    printf("Fine-Grain Approach Runtime: %lf\n", time2 - time1);
    return local_vec;
}

vector coarse_grain_parallel(const vector vec, const int thread_count)
{
    vector local_vec = copy_vector(vec);

    float norm = 0.0f;
    const double time1 = omp_get_wtime();
#pragma omp parallel num_threads(thread_count)
    {
        const int my_rank = omp_get_thread_num();

        const int N_per_thread = local_vec.len / thread_count;
        const int istart = my_rank * N_per_thread;
        const int iend = (my_rank + 1) * (N_per_thread);

        double norm_thread = 0.0;
        for (int i = istart; i < iend; i++)
        {
            norm_thread += (local_vec.val[i] * local_vec.val[i]);
        }

#pragma omp critical
        norm += norm_thread;

#pragma omp barrier

#pragma omp single
        norm = f_sqrt(norm);

        for (int i = istart; i < iend; i++)
        {
            local_vec.val[i] = local_vec.val[i] / norm;
        }
    }
    const double time2 = omp_get_wtime();

    printf("Coarse-Grain Approach Runtime: %lf\n", time2 - time1);
    return local_vec;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return 0;
    }
    const int thread_count = strtol(argv[1], NULL, 10);
    const int N = strtol(argv[2], NULL, 10);
    if (thread_count < 1 || N < 1 || N % thread_count != 0)
    {
        return 0;
    }

    vector vec = new_vector(N, 1.0f);

    vector fvec = fine_grain_parallel(vec, thread_count);
    printf("First element of Fine-Grain Generated Vector: %f\n", fvec.val[0]);
    // print_vector_full(&fvec, "Fine-Grain Generated");
    vector cvec = coarse_grain_parallel(vec, thread_count);
    printf("First element of Coarse-Grain Generated Vector: %f\n", cvec.val[0]);
    // print_vector_full(&cvec, "Coarse-Grain Generated");

    return 1;
}
