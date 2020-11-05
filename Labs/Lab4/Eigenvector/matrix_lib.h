//Matrix Library File
//Sam Disharoon & Jordan Welch
#ifndef MATRIX_LIB_H
#define MATRIX_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
//These make accessing elements in the matrices easier
#define INDEX(n, m, i, j) m * i + j
#define ACCESS(A, i, j) A -> arr [INDEX(A -> rows, A -> cols, i, j)]

// how our matrix is implemented
struct mat {
	int rows, cols;
	double *arr;
};
// initiate a new matrix
void initMat(struct mat* A, int r, int c, int fill) {
	A -> rows = r;
	A -> cols = c;
	A -> arr = malloc(r * c * sizeof(double));
	int i, k;
	// this fills the matrix with values
	if(fill == 1) {
		for(i = 0; i < r; i++) {
			for(k = 0; k < c; k++) {
				ACCESS(A, i, k) = rand() % 20 + 1;
			}
		}		
	} else if(fill == 2){
	// this creates a vector of all 1s
		for(i = 0; i < r; i++) {
			for(k = 0; k < c; k++) {
				ACCESS(A, i, k) = 1;
			}
		}
	} else {
	// this acts as a memset to clear a matrix of all values
		for(i = 0; i < r; i++) {
			for(k = 0; k < c; k++) {
				ACCESS(A, i, k) = 0;
			}
		}
	}
}
// copy matrix
void copyMat(struct mat* A, struct mat* copyA){
	copyA -> rows = A -> rows;
	copyA -> cols = A -> cols;
	copyA -> arr = malloc(copyA -> rows * copyA -> cols * sizeof(double));
	
	int i, k;
	for(i = 0; i < copyA -> rows; i++){
		for(k = 0; k < copyA -> cols; k++){
			ACCESS(copyA, i, k) = ACCESS(A, i, k);
		}
	}
}
// print the matrix
void printMat(struct mat* A) {
	int i, k;
	for(i = 0; i < A -> rows; i++) {
		for(k = 0; k < A -> cols; k++) {
			printf("%8.11f ", ACCESS(A, i, k));
		}
		puts("");
	}
}
// method to test when the normalization is complete
int compare(struct mat *A){
	int i, k;
	double tiny = 0.00000000001;
	printf("Compare\n");
	printMat(A);
	for(i = 0; i < A -> rows; i++){
		for(k = 0; k < A -> cols; k++){
			if(tiny > abs(ACCESS(A, i, k))){
				puts("Limit Reached!");
				return 1;
			}
		}
	}
	return 0;

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
	double arrA[counter[myRank]];
	double arrB[counter[myRank]];
	double finalArr[counter[myRank]];
	
	// clear the blocks
	for(i = 0; i < counter[myRank]; i++) {
		arrA[i] = 0;
	}
	for(i = 0; i < counter[myRank]; i++) {
		arrB[i] = 0;
	}
	// calling scatter functions to distribute to the processors
	MPI_Scatterv(A -> arr, counter, displs, MPI_DOUBLE, arrA, counter[myRank], MPI_DOUBLE, 0, world);
	MPI_Scatterv(B -> arr, counter, displs, MPI_DOUBLE, arrB, counter[myRank], MPI_DOUBLE, 0, world);
	
	for(i = 0; i < counter[myRank]; i++) {
		finalArr[i] = arrA[i] + arrB[i];
	}
	// gathering all the data collected from the processors
	MPI_Gatherv(finalArr, counter[myRank], MPI_DOUBLE, F -> arr, counter, displs, MPI_DOUBLE, 0, world);
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
	double arrA[counter[myRank]];
	double arrB[counter[myRank]];
	double finalArr[counter[myRank]];
	// clears the blocks
	for(i = 0; i < counter[myRank]; i++) {
		arrA[i] = 0;
	}
	for(i = 0; i < counter[myRank]; i++) {
		arrB[i] = 0;
	}
	// call scatter to distribute the data to processors
	MPI_Scatterv(A -> arr, counter, displs, MPI_DOUBLE, arrA, counter[myRank], MPI_DOUBLE, 0, world);
	MPI_Scatterv(B -> arr, counter, displs, MPI_DOUBLE, arrB, counter[myRank], MPI_DOUBLE, 0, world);
	for(i = 0; i < counter[myRank]; i++) {
		finalArr[i] = arrA[i] - arrB[i];
	}
	// gather all data from processors
	MPI_Gatherv(finalArr, counter[myRank], MPI_DOUBLE, F -> arr, counter, displs, MPI_DOUBLE, 0, world);
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
double innerProd(double *arr1, double *arr2, int arrSize, MPI_Comm world, int worldSize, int myRank) {
	double blockTotal = 0, total = 0;
	
	int blockSize = arrSize / worldSize;
	int overflow = arrSize % worldSize + blockSize;
	int i;
	
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
	
	double* arrB = malloc(sizeof(double) * counter[myRank]);
	double* arrA = malloc(sizeof(double) * counter[myRank]);

	for(i = 0; i < counter[myRank]; i++) {
		arrA[i] = 0;
	}
	for(i = 0; i < counter[myRank]; i++) {
		arrB[i] = 0;
	}
	
	MPI_Scatterv(arr1, counter, displs, MPI_DOUBLE, arrA, counter[myRank], MPI_DOUBLE, 0, world);
	MPI_Scatterv(arr2, counter, displs, MPI_DOUBLE, arrB, counter[myRank], MPI_DOUBLE, 0, world);
	
	for(i = 0; i < counter[myRank]; i++) {
		blockTotal += arrA[i] * arrB[i];
	}
	MPI_Reduce(&blockTotal, &total, 1, MPI_DOUBLE, MPI_SUM, 0, world);
	
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
	
	int i, k, n;
	double blockTotal;
	double *arrA = malloc(A -> rows * sizeof(double));
	double *arrB = malloc(B -> rows * sizeof(double));
	
	for(i = 0; i < F -> rows; i++) {
		for(k = 0; k < F -> cols; k++) {
			for(n = 0; n < A -> rows; n++) {
				arrA[n] = ACCESS(A, i, n);
				arrB[n] = T.arr[k * B -> rows + n];
			}
			blockTotal = innerProd(arrA, arrB, A -> cols, world, worldSize, myRank);
			ACCESS(F, i, k) = blockTotal;
		}
	}
	free(arrA);
	free(arrB);
	free(T.arr);
}
// serial method of Gauss-Jordan Elimination
// Doesn't work :(
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
// method for calculating the euclidean norm
double euclidean_norm(struct mat* A){
	int i;
	double x, norm = 0.0;
	
	for(i = 0; i < A -> rows; i++){
		x = ACCESS(A, i, 0);
		norm += x * x;
		//printf("X ~> %8.11f\n",x);
	}
	return sqrt(norm);
}
// method for normalizing a matrix
void normalize(struct mat* A){
	int i;
	//printMat(A);
	double x, enorm = euclidean_norm(A);
	for(i = 0; i < A -> rows; i++){
		x = ACCESS(A, i, 0);
		ACCESS(A, i, 0) = x / enorm;
		//printf("%8.11f\n", ACCESS(A, i, 0));
	}
}
#endif
