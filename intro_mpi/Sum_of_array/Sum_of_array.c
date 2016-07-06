#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
 
/************************************************************
 * This is a simple broadcast program in MPI
 * ************************************************************/

int main(int argc,char *argv[]){
	
    int i,myid, numprocs;
    int source,count;
    int buffer[100]; 
    int Total_Sum;
    int thd_lvl;
    MPI_Status status;
 
    MPI_Init_thread(&argc,&argv, MPI_THREAD_SINGLE, &thd_lvl);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    source=0;
    count=100;
    if(myid == source){
    	for(i=0;i<count;i++)
        	buffer[i]=i;
    }
    
    int sum = 0;
    MPI_Bcast(buffer,count,MPI_INT,source,MPI_COMM_WORLD);
    for(i=myid;i<count;i+=numprocs){
    	sum = sum + buffer[i]; 
    }
    if(myid != source){
    	printf("The sum computed by process %d = %d\n",myid, sum);
	MPI_Send(&sum,1, MPI_INT, source, 1 , MPI_COMM_WORLD);
    }
    else{
        printf("The sum computed by process %d = %d\n",myid, sum);
	Total_Sum = sum;
	for(i = 1; i < numprocs; i++){
		MPI_Recv ( &sum, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
	   	Total_Sum = Total_Sum + sum;
	}
    }
	
    if (myid == source){
 	    printf ("\n");
	    printf ("The total sum of the array is %d\n", Total_Sum);
    }	 			 
   
    MPI_Finalize();
}
