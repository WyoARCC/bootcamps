#include <stdio.h>
#include <omp.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int thd_lvl;
    int thd_req = MPI_THREAD_FUNNELED;
    int size,rank;
    int thd_id,thd_sz;

    MPI_Init_thread(&argc, &argv, thd_req, &thd_lvl);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    #pragma omp parallel private(thd_id,thd_sz)
    {
        thd_id = omp_get_thread_num();
        thd_sz = omp_get_num_threads();
        printf("Hello from process %d / %d, thread %d / %d\n",
            rank,size,
            thd_id,thd_sz
        );
    }

    MPI_Finalize();

    return 0;
}
