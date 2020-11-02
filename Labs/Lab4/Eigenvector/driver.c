//Sam Disharoon & Jordan Welch
//Various tests for the eigenvector functions
#include "matrix_lib.h"
#define tiny 0.0000000001
#define limit 100000
int main(int argc, char** argv){
	// set up MPI world
	MPI_Init(NULL, NULL);
	
	int worldSize, myRank;
	
	//double startTime, stopTime;

	MPI_Comm world = MPI_COMM_WORLD;
	
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	
	// using arguments to test our algorithms before reading in a file
	
	srand(time(NULL));
	if(argc != 2){
		if(myRank == 0){
			printf("Usage ~> ./driver a\n");
		}
		return 1;
	}
	
	//FILE* file;
	int i = 0;
	struct mat matrixA, sVector, copy;
	
	initMat(&matrixA, atoi(argv[1]), atoi(argv[1]), 1);
	initMat(&sVector, atoi(argv[1]), 1, 2);
	initMat(&copy, atoi(argv[1]), 1, 0);
	
	if(myRank == 0){
		puts("Matrix A");
		printMat(&matrixA);
	}
	
	// this section tests the Eigenvector methods, matrices MUST be sqaure!
	// update solution vector (x <- Ax)
	multiMat(&matrixA, &sVector, &sVector, world, worldSize, myRank);
	/*if(myRank == 0){
		puts("A * x\n===================");
		printMat(&sVector);
	}*/

	// normalize solution vector
	normalize(&sVector);
	if(myRank == 0){
		puts("1 normalization of A:");
		printMat(&sVector);
		puts("==================");
	}
	
	// repeat (This is where the problem lies)
	for(; i < 3; i++){
		printf("Ax -> x %d\n", i);
		multiMat(&matrixA, &sVector, &sVector, world, worldSize, myRank);
		printMat(&sVector);
		puts("==================");
		printf("Normalize %d\n", i);
		normalize(&sVector);
		printMat(&sVector);
		puts("==================");
	}
		copyMat(&sVector, &copy);
	if(myRank == 0){
		puts("Largest Eigenvector of A:");
		printMat(&sVector);
	}
	
	MPI_Finalize();
	free(matrixA.arr);
	free(sVector.arr);
	free(copy.arr);
	fflush(stdout);

	return 0;


}


