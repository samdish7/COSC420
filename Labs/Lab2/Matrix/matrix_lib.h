//Matrix Library File
//Sam Disharoon & Jordan Welch
#ifndef MATRIX_LIB_H
#define MATRIX_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

//These make accessing elements in the matrices easier
#define INDEX(n, m, i, j) m * i + j
#define ACCESS(A, i, j) A -> arr [INDEX(A -> rows, A -> cols, i, j)]

//How our matrix is implemented
struct mat {
	int rows, cols;
	int *arr;
};
//Initiate a new matrix
void initMat(struct mat* A, int r, int c, int fill) {
	A -> rows = r;
	A -> cols = c;
	A -> arr = malloc(r * c * sizeof(int));
	//This fills the matrix with values
	if(fill) {
		int i, k;
		for(i = 0; i < r; i++) {
			for(k = 0; k < c; k++) {
				ACCESS(A, i, k) = rand() % 10 + 1;
			}
		}		
	}
	//This acts as a memset by removing all values
	else {
		int i, k;
		for(i = 0; i < r; i++) {
			for(k = 0; k < c; k++) {
				ACCESS(A, i, k) = 0;
			}
		}
	}
}
//Print the matrix
void printMat(struct mat* A) {
	int i, k;
	for(i = 0; i < A -> rows; i++) {
		for(k = 0; k < A -> cols; k++) {
			printf("%d ", ACCESS(A, i, k));
		}
		printf("\n");
	}
}
//Parralel method to Matrix Addition
void addMatP(struct mat *A, struct mat *B, struct mat *F, MPI_Comm world, int worldSize, int myRank) {
	//Helper ints
	int arrSize = A -> rows * A -> cols;
	int blockSize = arrSize / worldSize;
	int overflow = arrSize % worldSize + blockSize;
	//Helper arrays
	int counter[worldSize];
	int displacement[worldSize];
	//Counter
	int i;
	
	for(i = 0; i < worldSize; i++) {
		displacement[i] = i * (blockSize);
		if(i == worldSize - 1) {
			counter[i] = overflow;
		}
		else {
			counter[i] = blockSize;
		}
	}
	//Smaller matrices
	int arrA[counter[myRank]];
	int arrB[counter[myRank]];
	int finalArr[counter[myRank]];
	
	//Clear the blocks
	for(i = 0; i < counter[myRank]; i++) {
		arrA[i] = 0;
	}
	for(i = 0; i < counter[myRank]; i++) {
		arrB[i] = 0;
	}
	//Calling scatter functions to distribute to the processors
	MPI_Scatterv(A -> arr, counter, displacement, MPI_INT, arrA, counter[myRank], MPI_INT, 0, world);
	MPI_Scatterv(B -> arr, counter, displacement, MPI_INT, arrB, counter[myRank], MPI_INT, 0, world);
	
	for(i = 0; i < counter[myRank]; i++) {
		finalArr[i] = arrA[i] + arrB[i];
	}
	//Gathering all the data collected from the processors
	MPI_Gatherv(finalArr, counter[myRank], MPI_INT, F -> arr, counter, displacement, MPI_INT, 0, world);
}
//Parralel method for Matrix Subtraction
void subMatP(struct mat *A, struct mat *B, struct mat *F, MPI_Comm world, int worldSize, int myRank) {
	//Helper ints
	int arrSize = A -> rows * A -> cols;
	int blockSize = arrSize / worldSize;
	int overflow = arrSize % worldSize + blockSize;
	//Helper arrays
	int counter[worldSize];
	int displacement[worldSize];
	//Counter
	int i;
	
	for(i = 0; i < worldSize; i++) {
		displacement[i] = i * blockSize;
		if(i == worldSize - 1) {
			counter[i] = overflow;
		}
		else {
			counter[i] = blockSize;
		}
	}
	//Smaller matrices
	int arrA[counter[myRank]];
	int arrB[counter[myRank]];
	int finalArr[counter[myRank]];
	//Clears the blocks
	for(i = 0; i < counter[myRank]; i++) {
		arrA[i] = 0;
	}
	for(i = 0; i < counter[myRank]; i++) {
		arrB[i] = 0;
	}
	//Call scatter to distribute the data to processors
	MPI_Scatterv(A -> arr, counter, displacement, MPI_INT, arrA, counter[myRank], MPI_INT, 0, world);
	MPI_Scatterv(B -> arr, counter, displacement, MPI_INT, arrB, counter[myRank], MPI_INT, 0, world);
	for(i = 0; i < counter[myRank]; i++) {
		finalArr[i] = arrA[i] - arrB[i];
	}
	//Gather all data from processors
	MPI_Gatherv(finalArr, counter[myRank], MPI_INT, F -> arr, counter, displacement, MPI_INT, 0, world);
}
//Serial method to Transpose of a Matrix
void transpose(struct mat *A, struct mat *F) {
	int i, k;
	for(i = 0; i < A -> rows; i++) {
		for(k = 0; k < A -> cols; k++) {
			ACCESS(F, k, i) = ACCESS(A, i, k);
		}
	}
}
//Inner Product method (Parralel)
int innerProd(int *arr1, int *arr2, int arrSize, MPI_Comm world, int worldSize, int myRank) {
	int blockTotal = 0, i = 0, total = 0;
	
	if(myRank == 0) {
		for(; i < arrSize; i++) {
			arr1[i] = rand() % 5 + 1;
			arr2[i] = rand() % 5 + 1;
		}
	}
	
	int blockSize = arrSize / worldSize;
	int overflow = arrSize % worldSize + blockSize;
	
	int counter[worldSize];
	int displacement[worldSize];
	
	for(i = 0; i < worldSize; i++) {
		displacement[i] = i * blockSize;
		if(i == worldSize - 1) {
			counter[i] = overflow;
		}
		else {
			counter[i] = blockSize;
		}
	}
	
	int arrB[counter[myRank]];
	int arrA[counter[myRank]];
	for(i = 0; i < counter[myRank]; i++) {
		arrA[i] = 0;
	}
	for(i = 0; i < counter[myRank]; i++) {
		arrB[i] = 0;
	}
	MPI_Scatterv(arr1, counter, displacement, MPI_INT, arrA, counter[myRank], MPI_INT, 0, world);
	MPI_Scatterv(arr2, counter, displacement, MPI_INT, arrB, counter[myRank], MPI_INT, 0, world);
	for(i = 0; i < counter[myRank]; i++) {
		blockTotal += arrA[i] * arrB[i];
	}
	MPI_Reduce(&blockTotal, &total, 1, MPI_INT, MPI_SUM, 0, world);
		return total;
}
//Parralel method for Matrix Multiplication
void multiMatP(struct mat *A, struct mat *B, struct mat *F, MPI_Comm world, int worldSize, int myRank) {
	struct mat T;
	
	if(A -> cols != B -> rows){
		printf("Can't multiply!\n");
		return;
	}
	
	initMat(&T, B -> rows, B -> cols, 0);
	transpose(B, &T);
	
	int i, k, n, blockTotal;
	int *arrA = malloc(A -> cols * sizeof(int));
	int *arrB = malloc(B -> cols * sizeof(int));
	for(i = 0; i < F -> rows; i++) {
		for(k = 0; k < F -> cols; k++) {
			for(n = 0; n < A -> rows; n++) {
				arrA[n] = A -> arr[i * A -> rows + n];
				arrB[n] = T.arr[k * B -> rows + n];
			}
			blockTotal = innerProd(arrA, arrB, A -> cols, world, worldSize, myRank);
			ACCESS(F, i, k) = blockTotal;
		}
	}
}
#endif
