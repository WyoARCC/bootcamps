
# include <stdio.h>
# include <stdlib.h>
#include "mpi.h"

int main ( int argc, char *argv[] )
{
  int N = 100;
  int i;
  int master = 0;
  int my_id;
  int numprocs;
  MPI_Status status;
  int sum;
  int Total_Sum;
  MPI_Init ( &argc, &argv );
  MPI_Comm_size ( MPI_COMM_WORLD, &numprocs );
  MPI_Comm_rank ( MPI_COMM_WORLD, &my_id );

  sum = 0;
 	
  for ( i = my_id; i < N; i+=numprocs )
  { 
    sum = sum + i;
  }

  printf ( "\n" );
  printf ( "SUM as computed by Process %d: %d\n", my_id, sum );

  if ( my_id != master ) 
  {
    MPI_Send ( &sum, 1, MPI_INT, master, 1, MPI_COMM_WORLD );
  }
  else 
  {
    Total_Sum = sum;
    for ( i = 1; i < numprocs; i++ ) 
    {
      MPI_Recv ( &sum, 1, MPI_INT, MPI_ANY_SOURCE, 1, 
        MPI_COMM_WORLD, &status );

      Total_Sum = Total_Sum + sum;
    }
  }

  if ( my_id == master )
  {
    printf ( "\n");         
    printf ( "SUM - Master process:\n");         
    printf ( "  The total sum of first N integers is %d\n", Total_Sum );
  }
  MPI_Finalize ( );
 
  return 0;
}



