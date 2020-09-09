//Lab 1 prime.c
//This takes a number from the command line, and uses parralism to determine if it is prime or not
#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){
	MPI_Init(NULL,NULL);
	
	MPI_Comm world = MPI_COMM_WORLD;
	
	int num = atoi(argv[1]);
	int worldSize, myRank;
	int counter=0;
	printf("Number passed is ~> %d",num);
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	
	

	MPI_Finalize();
	return 0;
}
