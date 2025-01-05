#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv){

    void hello();

    printf("\n");
# pragma omp parallel
    hello();
    printf("\n");
}

void hello() {
# ifdef _OPENMP
    const int my_rank = omp_get_thread_num ();
    const int actual_thread_count = omp_get_num_threads ();
# else
    const int my_rank = 0;
    const int actual_thread_count = 1;
# endif

    printf (" Hello from thread %i of %i\n", my_rank +1, actual_thread_count );
}
