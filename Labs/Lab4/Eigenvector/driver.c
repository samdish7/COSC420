//Sam Disharoon & Jordan Welch
//Various tests for the eigenvector functions
#include "matrix_lib.h"
#define tiny 0.0000000001
#define limit 100000
int main(int argc, char** argv){
	// set up MPI world
	MPI_Init(NULL, NULL);
	
	int worldSize, myRank;
	
	double startTime, stopTime;

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
	
	int i = 0;
	struct mat matrixA, sVector;
	
	initMat(&matrixA, atoi(argv[1]), atoi(argv[1]), 1);
	initMat(&sVector, atoi(argv[1]), 1, 2);
	
	
	if(myRank == 0){
		puts("Matrix A");
		printMat(&matrixA);
		/*		
 		puts("Matrix B");
		printMat(&sVector);
		*/
	}
	
	
	// this section tests the Eigenvector methods, matrices MUST be sqaure!
	// update solution vector (x <- Ax)
	multiMat(&matrixA, &sVector, &sVector, world, worldSize, myRank);
	
	// normalize solution vector
	normalize(&sVector);
	
	
	if(myRank == 0){
		puts("Largest Eigenvector of A:");
		printMat(&sVector);
		
		puts("After normalizing 1000 times:");
		printMat(&sVector);
	}
	
	MPI_Finalize();
	free(matrixA.arr);
	free(sVector.arr);
	fflush(stdout);

	return 0;


}


