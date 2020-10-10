//Main function for chip defects problem
//Sam Disharoon & Jordan Welch
#include<stdio.h>
#include<unistd.h>
#include<mpi.h>
#include<math.h>
#define k 20000
#define n 1000000
int main(int argc, char** argv){
	MPI_Init(&argc, &argv);
	MPI_Comm world = MPI_COMM_WORLD;

	int myRank, worldSize;
	
	MPI_Comm_size(world,&worldSize);
	MPI_Comm_rank(world,&myRank);

	long double prob, localS = 0;
	long double* total = malloc(sizeof(long double));


	
	if(myRank == 0){
		printf("Answer ~> %.10f\n", (1-prob));
	}
	MPI_Finalize();
	return 0;
}
