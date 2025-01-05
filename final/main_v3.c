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

// int main(int argc , char* argv [])
int main()
{
    // Matrix Def
    int row_ptr[] = {0,2,5,6,7};
    int values[] = {1,8,5,6,9,4,6};
    int col_index[] = {1,4,0,3,4,1,1};
    int x[] = {2,7,8,4,3};
    int rows = 4;
    int cols = 5;
    int size = row_ptr[rows];

    int comm_sz;
    int my_rank;
    int *elements_computed;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int N = 2;
    // // get_input();
    const int thread_count = N;

    int iM = (size - 1) / (comm_sz - 2) + 1;

    
    int iR = iM / N;


    int R = iR;
    int M = iM;
    if(iR > 32) {
        R = 16;
        M = N * R;
    } else {
        R = iR;
        M = iM;
    }

    int total = (size - 1)/M + 1;


    int local_bp_start[1];
    int local_bp_end[1];
    int local_total[1];
    int local_rows[1];
    int local_cols[1];
    int rows_comp[1];

    if (my_rank > 1)
    {
        int local_size[1];
        MPI_Recv(local_total, 1, MPI_INTEGER, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(local_rows, 1, MPI_INTEGER, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(local_cols, 1, MPI_INTEGER, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);


        
        int local_row_ptr[local_rows[0]];
        int local_x[local_cols[0]];
        MPI_Recv(local_row_ptr, local_rows[0] + 1, MPI_INTEGER, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(local_x,  local_cols[0], MPI_INTEGER, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("open done\n");
        for(int k = my_rank - 2; k < local_total[0]; k += comm_sz - 2) {
            MPI_Recv(local_size, 1, MPI_INTEGER, 0, 0,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(local_bp_start, 1, MPI_INTEGER, 0, 0,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(local_bp_end, 1, MPI_INTEGER, 0, 0,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);


            int local_nnz[local_size[0]];
            int local_col[local_size[0]];
            printf("%d\n", local_size[0]);
            printf("Hasdfa;klsfd\n");

            MPI_Recv(local_nnz, local_size[0], MPI_INTEGER, 0, 0,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(local_col, local_size[0], MPI_INTEGER, 0, 0,
                    MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            int *local_mem = (int *)malloc(local_size[0] * sizeof(int));
            // for(int i = 0; i < local_cols[0]; i++){
            //     printf("X %d : %d\n", i, local_x[i]);
            // }
            // for(int i = 0; i < local_size[0]; i++){
            //     printf("Val %d %d : %d\n", my_rank, i, local_nnz[i]);
            //     printf("Col %d %d : %d\n", my_rank, i, local_col[i]);
            //     printf("X %d %d : %d\n", my_rank, i, local_x[local_col[i]]);
            // }
            printf("%d all BP recieved\n", my_rank);


            for(int i = 0; i < R; i++) local_mem[i] = 0;
            #pragma omp parallel num_threads(thread_count)
            {
                int thread_num = omp_get_thread_num();
                for (int i = thread_num; i < local_size[0]; i += thread_count)
                {
                    local_mem[i] = local_nnz[i] * local_x[local_col[i]];
                }
            }

            printf("D%d comp done\n", my_rank);

            int row_start = min(local_bp_start[0], local_rows[0]);
            int row_end = min(local_bp_end[0], local_rows[0]);
            if (row_end == 0)
                row_end = local_rows[0];
            if (local_row_ptr[row_end] % M != 0 || row_start == row_end)
                row_end = min(row_end + 1, local_rows[0]);
            int bp_id = (my_rank - 2) * M;
            int ele_comp_size = row_end - row_start;
            int *final_sum = (int *)malloc(ele_comp_size * sizeof(int));
            printf("Rank:%d  Start:%d  End:%d\n", my_rank, row_start, row_end);
            #pragma omp parallel
            {
                for(int i = 0;i < ele_comp_size; i++) final_sum[i] = 0;
            }

            printf("final prpe deone\n");
            #pragma omp parallel num_threads(thread_count)
            {
                int thread_num = omp_get_thread_num();
                int row_id = row_start + thread_num;
                while (row_id < row_end)
                {
                    int sum = 0;
                    int reduce_start = max(0, local_row_ptr[row_id] - bp_id);
                    int reduce_end = min(M, local_row_ptr[row_id + 1] - bp_id);

                    for (int i = reduce_start; i < reduce_end; i++)
                    {
                        sum += local_mem[i];
                    }

                    final_sum[row_id - row_start] = sum;
                    printf("Rank:%d  id:%d   val%d", my_rank, row_id - row_start, sum);
                    row_id = row_id + thread_count;

                }
            }

            elements_computed = final_sum;

            rows_comp[0] = ele_comp_size;
            MPI_Send(rows_comp, 1, MPI_INTEGER, 1, 0, MPI_COMM_WORLD);
            MPI_Send(elements_computed, ele_comp_size, MPI_INTEGER, 1, 0, MPI_COMM_WORLD);
            free(local_mem);
            free(final_sum);
        }
        printf("Woo");
    }
    else if(my_rank == 0)
    {
        int bp_array[total + 1];
        local_total[0] = total;
        local_rows[0] = rows;
        local_cols[0] = cols;
        
        #pragma omp parallel num_threads(thread_count)
        {
            int thread_num = omp_get_thread_num();

            for(int j = thread_num; j < comm_sz - 2; j += thread_count){
                MPI_Send(local_total, 1, MPI_INTEGER, j + 2, 0, MPI_COMM_WORLD);
                MPI_Send(local_rows,  1, MPI_INTEGER, j + 2, 0, MPI_COMM_WORLD);
                MPI_Send(local_cols,  1, MPI_INTEGER, j + 2, 0, MPI_COMM_WORLD);
                MPI_Send(row_ptr, rows + 1, MPI_INTEGER, j + 2, 0, MPI_COMM_WORLD);
                MPI_Send(x, cols, MPI_INTEGER, j + 2, 0, MPI_COMM_WORLD);
            }

            for(int i = thread_num; i < total + 1; i += thread_count){
                bp_array[i] = 0;
            }

            for (int i = thread_num; i < rows; i += N)
            {
                int crbpid = (row_ptr[i]) / M;
                int nrbpid = (row_ptr[i + 1]) / M;
                if (crbpid != nrbpid)
                {
                    for (int j = crbpid + 1; j < nrbpid + 1; j++)
                    {
                        bp_array[j] = i;
                    }
                    if (row_ptr[i + 1] % M == 0) {
                        bp_array[nrbpid] = bp_array[nrbpid] + 1;

                    }
                }
            }
        }

        const int local_thread_count = (N > comm_sz - 2) ? comm_sz - 2 : N;

        MPI_Send(local_total, 1, MPI_INTEGER, 1, 0, MPI_COMM_WORLD);
        MPI_Send(local_rows,  1, MPI_INTEGER, 1, 0, MPI_COMM_WORLD);
        MPI_Send(bp_array, total + 1, MPI_INTEGER, 1, 0, MPI_COMM_WORLD);

        #pragma omp parallel num_threads(local_thread_count)
        {
            int thread_num = omp_get_thread_num();

            for(int j = thread_num; j < total; j += local_thread_count){
                int local_size[1] = {0};
                if(j == total - 1) local_size[0] = size % M;
                if(local_size[0] == 0) local_size[0] = M;
                local_bp_start[0] = bp_array[j];
                local_bp_end[0] = bp_array[j + 1];

                int offset = j * M;
                int local_nnz[local_size[0]];
                int local_col[local_size[0]];
                memcpy(local_nnz, &values[offset], local_size[0]*sizeof(int));
                memcpy(local_col, &col_index[offset], local_size[0]*sizeof(int));

                int device = (j % (comm_sz - 2)) + 2;
                MPI_Send(local_size, 1, MPI_INTEGER, device, 0, MPI_COMM_WORLD);
                MPI_Send(local_bp_start, 1, MPI_INTEGER, device, 0, MPI_COMM_WORLD);
                MPI_Send(local_bp_end, 1, MPI_INTEGER, device, 0, MPI_COMM_WORLD);
                MPI_Send(local_nnz, local_size[0], MPI_INTEGER, device, 0, MPI_COMM_WORLD);
                MPI_Send(local_col, local_size[0], MPI_INTEGER, device, 0, MPI_COMM_WORLD);
            }
        }
    } else {
        MPI_Recv(local_total, 1, MPI_INTEGER, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(local_rows,  1, MPI_INTEGER, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int bp_array[local_total[0] + 1];
        MPI_Recv(bp_array, local_total[0] + 1, MPI_INTEGER, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for(int i = 0; i < local_total[0] + 1; i ++){
            printf("%d: %d\n",i, bp_array[i]);
        }

        const int local_thread_count = (N > comm_sz - 2) ? comm_sz - 2 : N;

        int *final_vector = (int *)malloc(local_rows[0] * sizeof(int));
        for(int i = 0; i < local_rows[0]; i++) final_vector[i] = 0;

        #pragma omp parallel num_threads(local_thread_count)
        {
            int thread_num = omp_get_thread_num();

            for(int j = thread_num; j < local_total[0]; j += local_thread_count){
                int device = (j % (comm_sz - 2)) + 2;

                MPI_Recv(rows_comp, 1, MPI_INTEGER, device, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                elements_computed = (int *)malloc((rows_comp[0]) * sizeof(int));
                MPI_Recv(elements_computed, rows_comp[0], MPI_INTEGER, device, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                printf("Rank: %d Num:%d", j, rows_comp[0]);
                for(int i = 0; i < rows_comp[0]; i++){
                    printf("Pos:%d  Val:%d\n", i, elements_computed[i]);
                }
            
                for (int i = 0; i < rows_comp[0]; i++)
                {
                    final_vector[bp_array[j] + i] += elements_computed[i];
                }
                free(elements_computed);
            }
        }

        printf("Final Vector:\n");
        for (int i = 0; i < local_rows[0]; i++)
        {
            printf("%d\n", final_vector[i]);
        }
        free(final_vector);

        printf("rip");

    }
    MPI_Finalize();
    return 0;
}