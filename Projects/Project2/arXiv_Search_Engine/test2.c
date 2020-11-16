// Test2.c
// Sam Disharoon
#include"module2.h"

int main(int argc, char** argv){
	
	// set up MPI world
	MPI_Init(&argc, &argv);
	
	int myRank, worldSize;
	MPI_Comm world = MPI_COMM_WORLD;
	
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	MPI_Status status;
	
	// create variables
	//double start, end; // timing
	FILE* in;
	long int fSize;
	
	// opening files 
	if((in = fopen("data/arxiv-citations.txt", "r")) == NULL){
		puts("File open error!");
		MPI_Finalize();
		return 1;
	}

	// read file and get file size
	fSize = readCit(in, myRank, worldSize, world);
	if(!myRank){
		printf("Size of test.txt is ~> %li\n", fSize);
	}
fclose(in);
MPI_Finalize();
return 0;
}
