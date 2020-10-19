//Sam Disharoon & Jordan Welch
//Various tests for the gauss jordan algorithm and fixed multiplication
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include "matrix_lib.h"

int main(int argc, char** argv){
	MPI_Init(NULL, NULL);
	srand(time(NULL));
	
	int worldSize, myRank;
	
	double startTime, stopTime;
	startTime = MPI_Wtime();

	MPI_Comm world = MPI_COMM_WORLD;
	
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	
	struct mat matrixA, matrixB, result;
	
	if(argc != 5){
		if(myRank == 0){
			printf("Usage ~> ./gauss a b c d\n");
		}
		return 1;
	}
		
	initMat(&matrixA, atoi(argv[1]), atoi(argv[2]), 1);
	initMat(&matrixB, atoi(argv[3]), atoi(argv[4]), 1);
	
	
	if(myRank == 0){
		puts("Matrix A");
		printMat(&matrixA);
		puts("Matrix B");
		printMat(&matrixB);
	}
	

	if(matrixA.cols != matrixB.rows){
		if(myRank == 0){
			puts("Error!!!!");
			puts("matrix A's row must match matrix B's columns!");
		}
	} else {
	
	// this section tests the matric multiplication function that we fixed from Lab 2
		
	initMat(&result, matrixA.rows, matrixB.cols, 0);
	multiMat(&matrixA, &matrixB, &result, world, worldSize, myRank);
		
		if(myRank == 0){
			puts("\nResult of A * B Done");
			//printMat(&result);
			free(result.arr);
		}
	}
	if(matrixB.cols != matrixA.rows){
		if(myRank == 0){
			puts("Error!!!");
			puts("matrix B's row must match matrix A's columns!");
		}
	} else {
	
		initMat(&result, matrixA.rows, matrixB.cols, 0);
		multiMat(&matrixB, &matrixA, &result, world, worldSize, myRank);
		if(myRank == 0){
			puts("\nResult of B * A Done");
			//printMat(&result);
			free(result.arr);
		}
	}
	
	// this section tests the gauss-jordan algorithm, matrices MUST be sqaure!
	if(matrixA.cols != matrixA.rows || matrixB.cols != matrixB.rows){
		if(myRank == 0){
			puts("Can't do Gauss-Jordan unless matrices are Square!");
		}
	} else {
		// testing serial of Gauss-Jordan
		initMat(&result, matrixA.cols, 1, 1);
		gauss_jordanS(&matrixA, &result);
		if(myRank == 0){
			puts("Answer to Gauss-Jordan Elimination of Matrix A:");
			printMat(&result);
			free(result.arr);
		}
		
	}

	stopTime = MPI_Wtime();
        printf("MPI_Wtime measured %1.2f seconds\n", stopTime-startTime);
	MPI_Finalize();
	free(matrixA.arr);
	free(matrixB.arr);
	fflush(stdout);

	return 0;


}


