//File: matrix.c

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//NB: the A here needs to be a struct, not a pointer!
#define INDEX(A,i,j) A->cols*i + j
//now can do A.data[INDEX(A,i,j)]

//use the above to shortcut accessing the array
#define ACCESS(A,i,j) A->data[INDEX(A,i,j)]

//C needs the "typedef"
typedef struct{
	int rows, cols; //dimensions
	double* data;	//pointer to the data, a flat array
} matrix;

void initMatrix(matrix *A){
	int i,j;
	A->data = malloc(A->rows * A->cols * sizeof(double));
	for(i=0; i < A->rows; i++){
		for(j=0; j < A->cols; j++){
			//ACCESS(A,i,j) = rand() / RAND_MAX;
			A->data[INDEX(A,i,j)] = (double) rand() / (double) RAND_MAX;
			//printf("Macro for INDEX(A,%d,%d) gives %d\n", i, j, INDEX(A,i,j));
			//printf("Setting A[%d,%d] to %0.2f\n", i, j, A->data[INDEX(A,i,j)]);
		}
	}
}

void printMatrix(matrix* A){
	int i,j;
	for(i=0; i < A->rows; i++){
		for(j=0; j < A->cols; j++){
			printf("%0.2f ", ACCESS(A,i,j));
		}
		puts("");
	}
}

int main(){
	srand(time(0));
	matrix A;
	A.rows = 3;
	A.cols = 4;
	

	initMatrix(&A);
	printMatrix(&A);
}
