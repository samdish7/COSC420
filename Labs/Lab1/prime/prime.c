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
	long unsigned int num = atoi(argv[1]);
	int worldSize, myRank,i;
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	i = 2 + myRank;

	while(i <= sqrt(num)){
		// printf("I am node %d, so my i ~> %d\n",myRank,i);
		if(num % i == 0){
			printf("I am node %d and I found a factor! ~> %d\n",myRank,i);
			MPI_Abort(world,1);
		}
		i += worldSize;
	}
	MPI_Finalize();
	return 0;
}
