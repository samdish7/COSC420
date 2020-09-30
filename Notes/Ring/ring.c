#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

int main(int argc, char** argv){
	MPI_Init(NULL,NULL); // pass through cli args
	MPI_Comm world = MPI_COMM_WORLD;
	
	int worldSize, myRank, dest, from, secs;
	int token = 0; // gets passed between procs
	int limit = 12; // how many times thie proc has pingponged
	
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	
	srand(time(0) + myRank);
	
	//while (token <= limit
	return 0;
}
