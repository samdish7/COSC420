//Lab 1 prime.c
//This takes a number from the command line, and uses parralism to determine if it is prime or not
#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>
#include<math.h>
int main(int argc, char** argv){
	MPI_Init(NULL,NULL);
	
	MPI_Comm world = MPI_COMM_WORLD;
	if(argc !=2){
		printf("Argument Error!\n");
		MPI_Finalize();
		return 1;
	}
	int num = atoi(argv[1]);
	int worldSize, myRank,i,split;

	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	
	split = num / worldSize;

	if (myRank == 0){
		printf("The number passed is ~> %d\n",num);
	}
	i = myRank + 2;

	MPI_Finalize();
	return 0;
}
