#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

int main()
{
    srand(time(NULL));
    int size = 1000000;
    int count[1];
    double val[1];
    int comm_sz;
    int my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank != 0)
    {
        MPI_Recv(count, 1, MPI_INTEGER, 0, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        val[0] = 0.0f;
        for(int i = 0; i < count[0]; i++){
            double x = (double)rand()/((double)RAND_MAX);
            double y = (double)rand()/((double)RAND_MAX);
            double s = x*x + y*y;
            val[0] += (s < 1) ? 1.0f : 0.0f;
        }
        val[0] /= size;
        MPI_Send(val, 1, MPI_DOUBLE, 0, 0,
                 MPI_COMM_WORLD);
    }
    else
    {
        for (int j = 1; j < comm_sz; j++)
        {
            count[0] = size/(comm_sz - 1);
            MPI_Send(count, 1, MPI_INTEGER, j, 0,
                     MPI_COMM_WORLD);
        }
        double sum = 0.0f;
        for (int j = 1; j < comm_sz; j++)
        {
            MPI_Recv(val, 1, MPI_DOUBLE, j, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            sum += val[0];
        }

        printf("An approximation for pi is %lf\n", 4 * sum);
    }
    MPI_Finalize();
    return 0;
}