#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <mpi.h>
#include <omp.h>

int max(int i1, int i2)
{
    int largest = i2;
    if (i1 > i2)
    {
        largest = i1;
    }
    return largest;
}

int min(int i1, int i2)
{
    int smallest = i2;
    if (i1 < i2)
    {
        smallest = i1;
    }
    return smallest;
}

int get_mv_input(int rows, int cols, int size, int *row_ptr, int *col_idx, int *values, int *x, const int my_rank){
    if(my_rank == 0) {
        FILE* fptr;

        fptr = fopen('mv_def.txt', 'r');

        fscanf(fptr, "%d ", row_ptr);
        fscanf(fptr, "%d ", col_idx);
        fscanf(fptr, "%d ", values);
        fscanf(fptr, "%d ", x);
    }
}

// int main(int argc , char* argv [])
int main()
{
    // Matrix Def
    int rows = 5;
    int cols = 5;
    int size = 5;
    int N;
    int *row_ptr = (int*)malloc((rows + 1) * sizeof(int));
    int *values = (int*)malloc(size * sizeof(int));
    int *col_index = (int*)malloc(size * sizeof(int));
    int *x = (int*)malloc(cols * sizeof(int));

    int comm_sz;
    int my_rank;


    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    printf("Here");

    get_mv_input(rows, cols, size, row_ptr, col_index, values, x, my_rank);


    return 0;
    int *elements_computed;
    int *final_vector;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    // get_input();
    const int thread_count = N;

    int iM = (size - 1) / (comm_sz - 1) + 1;

    
    int iR = (iM + N - 1)/ N;


    int R = iR;
    int M = iM;
    // if(iR > 16) {
    //     R = 16;
    //     M = N * R;
    // } else {
    //     R = iR;
    //     M = iM;
    // }

    int iter = size / (R * (comm_sz - 1));

    int local_bp_start[1];
    int local_bp_end[1];
    int len[1];
    if (my_rank != 0)
    {
        int last_idx = row_ptr[rows];
        int start_idx = (my_rank - 1) * M;
        int bp_idx = my_rank - 1;
        for(int k = start_idx; k < last_idx; k += (comm_sz - 1) * M) {
            int *local_mem = (int *)malloc(R * sizeof(int));
            for(int i = 0; i < R; i++) local_mem[i] = 0;
            #pragma omp parallel num_threads(thread_count)
            {
                int thread_num = omp_get_thread_num();
                for (int i = 0; i < R; i++)
                {
                    int local_idx = thread_num + i * N;
                    int idx = min(local_idx + k, last_idx - 1);
                    local_mem[local_idx] = values[idx] * x[col_index[idx]];
                }
            }

            MPI_Recv(local_bp_start, 1, MPI_INTEGER, 0, 0,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(local_bp_end, 1, MPI_INTEGER, 0, 0,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            int row_start = min(local_bp_start[0], rows);
            int row_end = min(local_bp_end[0], rows);
            if (row_end == 0)
                row_end = rows;
            if (row_ptr[row_end] % M != 0 || row_start == row_end)
                row_end = min(row_end + 1, rows);
            int bp_id = (my_rank - 1) * M;
            int ele_comp_size = row_end - row_start;
            int *final_sum = (int *)malloc(ele_comp_size * sizeof(int));
            #pragma omp parallel
            {
                for(int i = 0;i < ele_comp_size; i++) final_sum[i] = 0;
            }
            #pragma omp parallel num_threads(thread_count)

            {
                int thread_num = omp_get_thread_num();
                int row_id = row_start + thread_num;
                while (row_id < row_end)
                {
                    int sum = 0;
                    int reduce_start = max(0, row_ptr[row_id] - bp_id);
                    int reduce_end = min(M, row_ptr[row_id + 1] - bp_id);

                    for (int i = reduce_start; i < reduce_end; i++)
                    {
                        // printf("Rank:%d  I:%d  Val:%d\n", my_rank, i, local_mem[i]);
                        sum += local_mem[i];
                    }

                    // printf("Rank:%d  Pos:%d\n", my_rank, row_id - row_start);

                    final_sum[row_id - row_start] = sum;
                    row_id = row_id + thread_count;
                }
            }

            elements_computed = final_sum;

            len[0] = ele_comp_size;
            MPI_Send(len, 1, MPI_INTEGER, 0, 0, MPI_COMM_WORLD);
            MPI_Send(elements_computed, ele_comp_size, MPI_INTEGER, 0, 0, MPI_COMM_WORLD);
            free(local_mem);
            free(final_sum);
            bp_idx += comm_sz - 1;
        }
    }
    else
    {
        // printf("M:%d  R:%d\n", M, R);
        // Because each thread does not compute the same number of elements in bp
        // This has to be computed in shared memory, thus has to be done in machine 0

        // Size of bp is number of machines
        int *bp = (int *)malloc((iter * (comm_sz - 1) + 1) * sizeof(int));
        
        #pragma omp parallel num_threads(thread_count)
        {
            for(int i = 0; i < iter * (comm_sz - 1) + 1; i++){
                bp[i] = 0;
            }
        }
        #pragma omp parallel num_threads(thread_count)
        {
            int thread_num = omp_get_thread_num();
            for (int i = thread_num; i < rows; i += N)
            {
                int crbpid = (row_ptr[i]) / M;
                int nrbpid = (row_ptr[i + 1]) / M;
                if (crbpid != nrbpid)
                {
                    for (int j = crbpid + 1; j < nrbpid + 1; j++)
                    {
                        bp[j] = i;
                    }
                    if (row_ptr[i + 1] % M == 0) {
                        bp[nrbpid] = bp[nrbpid] + 1;

                    }
                }
            }
        }

        // for(int i = 0; i < comm_sz; i++){
        //     printf("Rank:%d  val:%d\n", i, bp[i]);
        // }

        for (int j = 1; j < comm_sz; j++)
        {
            local_bp_start[0] = bp[j - 1];
            local_bp_end[0] = bp[j];
            MPI_Send(local_bp_start, 1, MPI_INTEGER, j, 0,
                     MPI_COMM_WORLD);
            MPI_Send(local_bp_end, 1, MPI_INTEGER, j, 0,
                     MPI_COMM_WORLD);
        }


        final_vector = (int *)malloc(rows * sizeof(int));
        for(int i = 0; i < rows; i++) final_vector[i] = 0;

        for (int j = 1; j < comm_sz; j++)
        {
            MPI_Recv(len, 1, MPI_INTEGER, j, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            elements_computed = (int *)malloc((len[0]) * sizeof(int));
            MPI_Recv(elements_computed, len[0], MPI_INTEGER, j, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // printf("Rank: %d Num:%d", j, len[0]);
            // for(int i = 0; i < len[0]; i++){
            //     printf("Pos:%d  Val:%d\n", i, elements_computed[i]);
            // }
            
            for (int i = 0; i < len[0]; i++)
            {
                final_vector[bp[j - 1] + i] += elements_computed[i];
            }
            free(elements_computed);

        }

        free(bp);
        printf("Final Vector:\n");
        for (int i = 0; i < rows; i++)
        {
            printf("%d\n", final_vector[i]);
        }
        free(final_vector);
    }
    MPI_Finalize();
    return 0;
}

