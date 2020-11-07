//Sam Disharoon & Jordan Welch
//Various tests for the eigenvector functions
#include "matrix_lib.h"
#define limit 20
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
	struct mat matrixA, sVector; //, result;

	initMat(&matrixA, atoi(argv[1]), atoi(argv[1]), 1);
	initMat(&sVector, atoi(argv[1]), 1, 2);
	//initMat(&result, atoi(argv[1]), 1, 0);
	
	/*
	if(myRank == 0){
		puts("Matrix A");
		printMat(&matrixA);
		puts("sVector");
		printMat(&sVector);
	}
	*/

	// this section tests the Eigenvector methods;
	//  matrices MUST be sqaure!
	
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
		//copyMat(&sVector, &copy);
		//free(result.arr);
	// repeat
	for(; i < limit - 1; i++){
		//initMat(&result, atoi(argv[1]), 1, 0);
		multiMat(&matrixA, &sVector, &sVector, world, worldSize, myRank);
		printf("Normalize %d\n", i + 2);
		normalize(&sVector);
		printMat(&sVector);
		puts("==================");
		//subMat(&sVector, &copy, &result, world, worldSize, myRank);
		//copyMat(&sVector, &copy);
		//free(result.arr);
		
		// compare method attempts to stop it when it has reached a certain limit, but we had problems getting it to work, so we scrapped it
		/*
		if(compare(&result)){
			break;
		}
		*/
	}
	if(myRank == 0){
		puts("Largest Eigenvector of A:");
		printMat(&sVector);
	}
	
	MPI_Finalize();
	free(matrixA.arr);
	free(sVector.arr);
	//free(copy.arr);
	fflush(stdout);

	return 0;


}


