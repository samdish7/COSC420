// Test2.c
// Sam Disharoon
#include"datatype.h"
#include"module2.h"

int main(int argc, char** argv){
	
	// set up MPI world
	int myRank, worldSize;
	MPI_Comm world = MPI_COMM_WORLD;
	
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	
	// create variables
	//double start, end; // timing
	MPI_File in;
	char* str = NULL;
	int fSize = 0, numLines = 0;
	long int numChar = 0; 
	
	MPI_

MPI_Finalize();
return 0;
}
