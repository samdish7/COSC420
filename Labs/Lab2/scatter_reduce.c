//This program gives a good example of using the scatter and reduce MPI functions
//Sam Disharoon & Jordan Welch
//Lab 2
#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<string.h>

int main(int argc, char** argv){
	MPI_Init(&argc, &argv);
	MPI_Comm world = MPI_COMM_WORLD;
	
	int worldSize, myRank, i;
	
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);

	if(argc < 2){
		printf("Usage: ./scatter_reduce N\n");
		MPI_Finalize();
		return 0;
	}
	
MPI_Finalize();
return 0;
}
