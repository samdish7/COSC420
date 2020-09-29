//Sam Disharoon & Jordan Welch
//Various tests for the matrix library
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include "matrix_lib.h"

int main(int argc, char** argv){
	MPI_Init(NULL, NULL);
	srand(time(NULL));
	
	int worldSize, myRank;
	
	MPI_Comm world = MPI_COMM_WORLD;
	
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	
	struct mat matrixA, matrixB, /*solution,*/ result;
	
	initMat(&matrixA, atoi(argv[1]), atoi(argv[2]), 1);
	initMat(&matrixB, atoi(argv[3]), atoi(argv[4]), 1);
		
	//Used to print out given matrices
	/*if(myRank == 0){
		puts("\033c");
		puts("Matrix A\n");
		printMat(&matrixA);
		puts("\nMatrix B\n");
		printMat(&matrixB);
	}*/	
		//This is o call serial addition (Breaks for more than 1000x1000 matrices!
		/*initMat(&solution, matrixA.rows, matrixB.cols, 0);
		addMatS(&matrixA, &matrixB, &solution);
		
		//Output for Addition
		if(myRank == 0){
			puts("Matrices have been made, starting various operations:");
			puts("\nSerial of A + B Done");
			//printMat(&solution);
		}*/
		
		initMat(&result, matrixA.rows, matrixB.cols, 0);
		addMatP(&matrixA, &matrixB, &result, world, worldSize, myRank);
		
		if(myRank == 0){
			puts("\nResult of A + B Done");
			//printMat(&result);
			free(result.arr);
			//free(solution.arr);
		}
		//This is for serial of subtraction (Breaks for more thand 1000x1000 matrices!)
		/*initMat(&solution, matrixA.rows, matrixB.cols, 0);
		subMatS(&matrixA, &matrixB, &solution);
	
		//Output for Subtraction	
		if(myRank == 0){
			puts("\nSerial of A - B Done");
			//printMat(&solution);
		}
		*/
		initMat(&result, matrixA.rows, matrixB.cols, 0);
		subMatP(&matrixA, &matrixB, &result, world, worldSize, myRank);
		
		if(myRank == 0){
			puts("\nResult of A - B Done");
			//printMat(&result);
			free(result.arr);
			//free(solution.arr);
		}

		//This is serial for subtraction (Breaks for more than 1000x1000 matrices!)
		/*initMat(&solution, matrixA.rows, matrixB.cols, 0);
		subMatS(&matrixB, &matrixA, &solution);
		
		if(myRank == 0){
			puts("\nSerial of B - A Done");
			//printMat(&solution);
		}*/

		initMat(&result, matrixA.rows, matrixB.cols, 0);
		subMatP(&matrixB, &matrixA, &result, world, worldSize, myRank);
		
		if(myRank == 0){
			puts("\nResult of B - A Done");
			//printMat(&result);
			free(result.arr);
			//free(solution.arr);
		}

		//This is serial for multiplication (Breaks for more thand 1000x1000 matrices!)
		/*initMat(&solution, matrixA.rows, matrixB.cols, 0);
		multiMatS(&matrixA, &matrixB, &solution);
		
		//Output for Multiplication
		if(myRank == 0){
			puts("\nSerial of A * B Done");
			//printMat(&solution);
		}*/
		
		initMat(&result, matrixA.rows, matrixB.cols, 0);
		multiMatP(&matrixA, &matrixB, &result, world, worldSize, myRank);
		
		if(myRank == 0){
			puts("\nResult of A * B Done");
			//printMat(&result);
			free(result.arr);
			//free(solution.arr);
		}
		//This is serial for multiplication (Breaks for more than 1000x1000 matrices!)
		/*initMat(&solution, matrixA.rows, matrixB.cols, 0);
		multiMatS(&matrixB, &matrixA, &solution);
		
		if(myRank == 0){
			puts("\nSerial of B * A Done");
			//printMat(&solution);
		}*/

		initMat(&result, matrixA.rows, matrixB.cols, 0);
		multiMatP(&matrixB, &matrixA, &result, world, worldSize, myRank);
		if(myRank == 0){
			puts("\nResult of B * A Done");
			//printMat(&result);
			free(result.arr);
			//free(solution.arr);
		}
	
	initMat(&result, matrixA.cols, matrixA.rows, 0);
	transpose(&matrixA, &result);
	
	//Output of transpose
	if(myRank == 0){
		puts("\nResult of A^(T) Done");
		//printMat(&result);
		free(result.arr);
	}

	initMat(&result, matrixB.cols, matrixB.rows, 0);
	transpose(&matrixB, &result);
	if(myRank == 0){
		puts("\nResult of B^(T) Done");
		//printMat(&result);
		free(result.arr);
	}

	MPI_Finalize();
	free(matrixA.arr);
	free(matrixB.arr);

	return 0;


}

