#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main()
{
    char greeting[MAX_STRING];
    double val[1];
    int comm_sz;
    int my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    // printf (" Hello from Processor %2d of %2d\n",my_rank , comm_sz );

    if (my_rank != 0)
    {
        
        MPI_Recv(val, 1, MPI_DOUBLE, 0, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        sprintf(greeting, "Greetings from process %2i of %2i! Process 0 sent me %lf!",
                my_rank, comm_sz, val[0]);
        MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR, 0, 0,
                 MPI_COMM_WORLD);
    }
    else
    {
        printf("Greetings from process %2i of %2i! I am sending each process a special number!\n",
               my_rank, comm_sz);
        for (int j = 1; j < comm_sz; j++)
        {
            val[0] = rand();
            MPI_Send(val, 1, MPI_DOUBLE, j, 0,
                     MPI_COMM_WORLD);
        }
        for (int j = 1; j < comm_sz; j++)
        {
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, j, 0,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", greeting);
        }
    }
    MPI_Finalize();
    return 0;
}