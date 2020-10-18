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

// how our matrix is implemented
struct mat {
	int rows, cols;
	int *arr;
};
// initiate a new matrix
void initMat(struct mat* A, int r, int c, int fill) {
	A -> rows = r;
	A -> cols = c;
	A -> arr = malloc(r * c * sizeof(int));
	// this fills the matrix with values
	if(fill) {
		int i, k;
		for(i = 0; i < r; i++) {
			for(k = 0; k < c; k++) {
				ACCESS(A, i, k) = rand() % 10 + 1;
			}
		}		
	}
	// this acts as a memset by removing all values
	else {
		int i, k;
		for(i = 0; i < r; i++) {
			for(k = 0; k < c; k++) {
				ACCESS(A, i, k) = 0;
			}
		}
	}
}
// print the matrix
void printMat(struct mat* A) {
	int i, k;
	for(i = 0; i < A -> rows; i++) {
		for(k = 0; k < A -> cols; k++) {
			printf("%d ", ACCESS(A, i, k));
		}
		printf("\n");
	}
}
// method to Matrix Addition (parallel)
void addMat(struct mat *A, struct mat *B, struct mat *F, MPI_Comm world, int worldSize, int myRank) {
	// helper ints
	int arrSize = A -> rows * A -> cols;
	int blockSize = arrSize / worldSize;
	int overflow = arrSize % worldSize + blockSize;
	// helper arrays
	int counter[worldSize];
	int displs[worldSize];
	// counter
	int i;
	
	for(i = 0; i < worldSize; i++) {
		displs[i] = i * (blockSize);
		if(i == worldSize - 1) {
			counter[i] = overflow;
		}
		else {
			counter[i] = blockSize;
		}
	}
	// smaller matrices
	int arrA[counter[myRank]];
	int arrB[counter[myRank]];
	int finalArr[counter[myRank]];
	
	// clear the blocks
	for(i = 0; i < counter[myRank]; i++) {
		arrA[i] = 0;
	}
	for(i = 0; i < counter[myRank]; i++) {
		arrB[i] = 0;
	}
	// calling scatter functions to distribute to the processors
	MPI_Scatterv(A -> arr, counter, displs, MPI_INT, arrA, counter[myRank], MPI_INT, 0, world);
	MPI_Scatterv(B -> arr, counter, displs, MPI_INT, arrB, counter[myRank], MPI_INT, 0, world);
	
	for(i = 0; i < counter[myRank]; i++) {
		finalArr[i] = arrA[i] + arrB[i];
	}
	// gathering all the data collected from the processors
	MPI_Gatherv(finalArr, counter[myRank], MPI_INT, F -> arr, counter, displs, MPI_INT, 0, world);
}
// method for Matrix Subtraction (parallel)
void subMat(struct mat *A, struct mat *B, struct mat *F, MPI_Comm world, int worldSize, int myRank) {
	// helper ints
	int arrSize = A -> rows * A -> cols;
	int blockSize = arrSize / worldSize;
	int overflow = arrSize % worldSize + blockSize;
	// helper arrays
	int counter[worldSize];
	int displs[worldSize];
	// counter
	int i;
	
	for(i = 0; i < worldSize; i++) {
		displs[i] = i * blockSize;
		if(i == worldSize - 1) {
			counter[i] = overflow;
		}
		else {
			counter[i] = blockSize;
		}
	}
	// smaller matrices
	int arrA[counter[myRank]];
	int arrB[counter[myRank]];
	int finalArr[counter[myRank]];
	// clears the blocks
	for(i = 0; i < counter[myRank]; i++) {
		arrA[i] = 0;
	}
	for(i = 0; i < counter[myRank]; i++) {
		arrB[i] = 0;
	}
	// call scatter to distribute the data to processors
	MPI_Scatterv(A -> arr, counter, displs, MPI_INT, arrA, counter[myRank], MPI_INT, 0, world);
	MPI_Scatterv(B -> arr, counter, displs, MPI_INT, arrB, counter[myRank], MPI_INT, 0, world);
	for(i = 0; i < counter[myRank]; i++) {
		finalArr[i] = arrA[i] - arrB[i];
	}
	// gather all data from processors
	MPI_Gatherv(finalArr, counter[myRank], MPI_INT, F -> arr, counter, displs, MPI_INT, 0, world);
}
// method to find Transpose of a Matrix
void transpose(struct mat *A, struct mat *F) {
	int i, k; // iterators for accessing elements of matrix
	for(i = 0; i < A -> rows; i++) {
		for(k = 0; k < A -> cols; k++) {
			ACCESS(F, k, i) = ACCESS(A, i, k);
		}
	}
}
// inner Product method (parallel)
int innerProd(int *arr1, int *arr2, int arrSize, MPI_Comm world, int worldSize, int myRank) {
	int blockTotal = 0, i = 0, total = 0;
	
	int blockSize = arrSize / worldSize;
	int overflow = arrSize % worldSize + blockSize;
	
	int counter[worldSize];
	int displs[worldSize];
	
	// to solve for if !(n % worldSize == 0)
	for(i = 0; i < worldSize; i++) {
		displs[i] = i * blockSize;
		if(i == worldSize - 1) {
			counter[i] = overflow;
		}
		else {
			counter[i] = blockSize;
		}
	}
	
	int* arrB = malloc(sizeof(int) * counter[myRank]);
	int* arrA = malloc(sizeof(int) * counter[myRank]);

	for(i = 0; i < counter[myRank]; i++) {
		arrA[i] = 0;
	}
	for(i = 0; i < counter[myRank]; i++) {
		arrB[i] = 0;
	}
	
	MPI_Scatterv(arr1, counter, displs, MPI_INT, arrA, counter[myRank], MPI_INT, 0, world);
	MPI_Scatterv(arr2, counter, displs, MPI_INT, arrB, counter[myRank], MPI_INT, 0, world);
	
	for(i = 0; i < counter[myRank]; i++) {
		blockTotal += arrA[i] * arrB[i];
	}
	MPI_Reduce(&blockTotal, &total, 1, MPI_INT, MPI_SUM, 0, world);
	
	free(arrA);
	free(arrB);
	if(myRank == 0){
		return total;
	}
}
// method for Matrix Multiplication (Parallel)
void multiMat(struct mat *A, struct mat *B, struct mat *F, MPI_Comm world, int worldSize, int myRank) {
	struct mat T;
	
	initMat(&T, B -> rows, B -> cols, 0);
	transpose(B, &T);
	
	int i, k, n, blockTotal;
	int *arrA = malloc(A -> cols * sizeof(int));
	int *arrB = malloc(B -> cols * sizeof(int));
	
	for(i = 0; i < F -> rows; i++) {
		for(k = 0; k < F -> cols; k++) {
			for(n = 0; n < A -> rows; n++) {
				arrA[n] = ACCESS(A, i, n);
				arrB[n] = T.arr[k * B -> rows + n];
			}
			blockTotal = innerProd(arrA, arrB, A -> cols, world, worldSize, myRank);
			ACCESS(F, i, k) = blockTotal;
			//printf("Rank %d ~> =%d=\n", myRank, blockTotal);
		}
	}
	free(T.arr);
	free(arrA);
	free(arrB);
}
// serial method of Gauss-Jordan Elimination
void gauss_jordanS(struct mat *A, struct mat* B){
	int i, j, r, c;
	double* local = malloc(sizeof(double) * A -> rows);
	for(i = 0; i < A -> rows; i++){
		for(j = 0; j < A -> rows; j++){
			local[j] = ACCESS(A, j, i) / ACCESS(A, i, i);
		}
		for(r = 0; r < A -> rows; r++){
			if(r != i){
				for(c = 0; c < A -> cols; c++){
					ACCESS(A, r, c) -= (ACCESS(A, i, c) * local[r]);
				}
				for(c = 0; c < B -> cols; c++){
					ACCESS(B, r, c) -= (ACCESS(B, i, c) * local[r]);
				}
			}
		}
	}
	for(r = 0; r < A -> rows; r++){
		for(c = 0; c < B -> cols; c++){
			ACCESS(B, r, c) /= ACCESS(A, r, r);
		}
		ACCESS(A, r, r) /= ACCESS(A, r, r);
	}
}

#endif
