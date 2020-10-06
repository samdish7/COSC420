//Main function for chip defects problem
//Sam Disharoon & Jordan Welch
#include<stdio.h>
#include<unistd.h>
#include<mpi.h>
#include<math.h>

int main(int argc, char** argv){
	MPI_Init(&argc, &argv);
	MPI_Comm world = MPI_COMM_WORLD;

	int myRank, worldSize;
	
	MPI_Comm_size(world,&worldSize);
	MPI_Comm_rank(world,&myRank);

	int k, n, p;

	k = 3;
	n = 7;

	

	MPI_Finalize();
	return 0;
}
