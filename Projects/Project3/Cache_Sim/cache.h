#ifndef CACHE_H
#define CACHE_H
#define INDEX(A,i,j) A->cols*i+j
#define ACCESS(A,i,j) A->data[INDEX(A,i,j)]
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

static int cache = 32000;

typedef struct 
{
	int rows, cols;
	double* data;	
} matrix;

void initMatrix(matrix *A, int rows, int cols)
{	
	int i,j;
	A->rows = rows;
	A->cols = cols;
	A->data = malloc(A->rows*A->cols*sizeof(double));
	for(i=0; i < A->rows; i++)
	{
		for(j = 0; j < A->cols; j++)
		{
			ACCESS(A,i,j) = 0;
		}
	}
}

void createMatrix(matrix *A)
{
	int i,j;
	A->data = malloc(A->rows*A->cols*sizeof(double));
	for(i=0;i < A->rows;i++)
	{	
		for(j=0;j < A->cols;j++)
		{
			ACCESS(A,i,j) = rand() % 10 + 1;
		}
	}
}

void allocateMatrix(matrix *A)
{
	int i,j;
	A->data = malloc(A->rows*A->cols*sizeof(double));
	for(i=0;i < A->rows;i++)
	{	
		for(j=0;j < A->cols;j++)
		{
			ACCESS(A,i,j) = 0;
		}
	}
}

void createIdentityMatrix(matrix *A)
{
	int i,j;
	A->data = malloc(A->rows*A->cols*sizeof(double));
	for(i=0; i < A->rows; i++)
	{
		for(j=0; j < A->cols; j++)
		{
			if(i == j)
			{
				ACCESS(A,i,j) = 1;
			}
			else
			{
				ACCESS(A,i,j) = 0;
			}
		}
		puts("");
	}
}

void printMatrix(matrix *A)
{
	int i,j;
	for(i=0;i < A->rows;i++)
	{	
		for(j=0;j < A->cols;j++)
		{
			printf("%0.2f ", ACCESS(A,i,j));
		}
		puts("");
	}
}

void MPIAddMatrix(matrix *A, matrix *B, matrix *C, MPI_Comm* world, int worldSize, int myRank)
{
	int N = A->rows * A->cols; //Area of amtrix
	int localLen = N/worldSize; //Length of each partition
	double *localArrA = malloc(localLen*sizeof(double));
	double *localArrB = malloc(localLen*sizeof(double));
	double *sol = malloc(localLen*sizeof(double)); // solution
	//Scatters both Matrices to be operated on in parts.
	MPI_Scatter(A->data, localLen, MPI_DOUBLE, localArrA, localLen, MPI_DOUBLE, 0, *world);
	MPI_Scatter(B->data, localLen, MPI_DOUBLE, localArrB, localLen, MPI_DOUBLE, 0, *world);
	int i;
	//Cretaes the array of solutions. The actual addition part
	//puts("Matrix A: ");
	for(i=0; i < localLen; i++)
	{
		sol[i] = localArrA[i] + localArrB[i]; 
		//printf("%0.2f ",sol[i]); 
	}
	// Puts all data into fin to be transfered to C->dataMPI_Gather(sol, localLen, MPI_DOUBLE, C->data, localLocal, MPI_DOUBLE, 0, *world);
	MPI_Gather(sol, localLen, MPI_DOUBLE, C->data, localLen, MPI_DOUBLE, 0, *world);

	free(localArrA);
	free(localArrB);
	free(sol);
}

void MPISubMatrix(matrix *A, matrix *B, matrix *C, MPI_Comm* world, int worldSize, int myRank)
{
	int N = A->rows * A->cols; //Area of amtrix
	int localLen = N/worldSize; //Length of each partition
	double *localArrA = malloc(localLen*sizeof(double));
	double *localArrB = malloc(localLen*sizeof(double));
	double *sol = malloc(localLen*sizeof(double)); // solution
	//Scatters both Matrices to be operated on in parts.
	MPI_Scatter(A->data, localLen, MPI_DOUBLE, localArrA, localLen, MPI_DOUBLE, 0, *world);
	MPI_Scatter(B->data, localLen, MPI_DOUBLE, localArrB, localLen, MPI_DOUBLE, 0, *world);
	int i;
	//Cretaes the array of solutions. The actual addition part


	for(i=0; i < localLen; i++)
	{
		sol[i] = localArrA[i] - localArrB[i];  
	}
	// Puts all data into fin to be transfered to C->data
	MPI_Gather(sol, localLen, MPI_DOUBLE, C->data, localLen, MPI_DOUBLE, 0, *world);	
	free(localArrA);
	free(localArrB);
	free(sol);
}

//B is accessed by cols which only provides part of a row for each cache loaded.
void SerialMult(matrix *A, matrix *B, matrix *C)
{
	int i,j,k;
	for(i=0; i < A->rows; i++)
	{
		for(j=0;j < B->cols; j++)
		{
			for(k = 0; k < A->cols; k++)
			{
				ACCESS(C,i,j) += ACCESS(A,i,k) * ACCESS(B,k,j);
			}
		}
	}
}

//A is loaded once as opposed to n times in SerialMult
//B is accessed by rows which fully utilizes caches
void BestSerialMult(matrix *A, matrix *B, matrix *C/*int n, int blockSize*/)
{
	//n is Array Size
	int i,j,k;
	//int slots = blockSize * (n/blockSize); //Amount that fits in blocks evenly
	for(i = 0; i < A->rows; i++)
	{
		for(k = 0; k < B->cols; k++)
		{
			for(j = 0; j < A->cols ; j++)
			{
				ACCESS(C,i,j) += ACCESS(A,i,k) * ACCESS(B,k,j);
			}
		}
	}
}

double InnerProd(matrix *A, matrix *B, MPI_Comm *world, int worldSize, int myRank)
{
	if(A->rows != 1 && A->cols != 1)
	{
		puts("A is not a vector\n");
		return -1;
	}
	if(B->rows != 1 && B->cols != 1)
	{
		puts("B is not a vector\n");
		return -1;
	}
	if(A->rows*A->cols != B->rows*B->cols)
	{
		puts("Matrices aren't same size\n");
		return -1;
	}

	int length = A->cols;
	int* VectorArray = malloc(worldSize * sizeof(int));
	int* displacement = malloc(worldSize * sizeof(int));
	int j;

	for(j = 0; j < worldSize; j++)
	{
		VectorArray[j] = length / worldSize;
		displacement[j] = j * (length / worldSize);
	}
	if(length % worldSize > 0){
		int extra = length % worldSize;
		VectorArray[worldSize - 1] += extra;
	}



	int matrixLen = VectorArray[myRank]; // Nodes divide array size
	//printf("Node %d ~> Matrix Len ~> %d\n", myRank, matrixLen);
	double result = 0; //Final prod
	
	double *localMatA = (double*)malloc(matrixLen*sizeof(double));
	double *localMatB = (double*)malloc(matrixLen*sizeof(double));
	
	MPI_Scatterv(A->data, VectorArray, displacement, MPI_DOUBLE, localMatA, matrixLen, MPI_DOUBLE, 0, *world);
	MPI_Scatterv(B->data, VectorArray, displacement, MPI_DOUBLE, localMatB, matrixLen, MPI_DOUBLE, 0, *world);

	double sum = 0;
	int i;
	int matrixLenByte = matrixLen*sizeof(double);
	int localcache = (matrixLenByte / cache);
	if(matrixLenByte < cache)
	{
		for(i = 0; i < matrixLen; i++)
		{
			sum += localMatA[i] * localMatB[i];
		}
	}
	else
	{
		for(i = 0; i < matrixLenByte * localcache; i+= localcache)
		{
			for(j = 0; j < i+cache && j < matrixLen; j++)
			{
				sum += localMatA[i] * localMatB[i];	
			}	
		}
	}

	MPI_Reduce(&sum, &result, 1, MPI_DOUBLE, MPI_SUM, 0, *world);
	
	free(localMatA);
	free(localMatB);
	free(displacement);
	free(VectorArray);
	if(myRank == 0)
	{
		return result;
	}
	return -1;
}

//Altered matrix Mult
double* classicMultMatrix(matrix *A, matrix *B, MPI_Comm *world, int worldSize, int myRank) {
	int len;
	if(A->cols != B->rows)
	{
		puts("Wrong dimensions, need square matrices\n");
	}

	len = A->rows * B->rows;
	double* result = malloc(len*sizeof(double));
	matrix Atemp;
	matrix Btemp;
	initMatrix(&Atemp, 1, A->cols);
	initMatrix(&Btemp, B->cols, 1);

	int i,j,k;
	for(i = 0; i < A->rows; i++){
		for(j = 0; j < B->cols; j++){
			//Copies temp A data over
			for(k = 0; k < A->cols; k++){
				Atemp.data[k] = ACCESS(A,i,k);
				Btemp.data[k] = ACCESS(B,k,j);
			}


			double InnerProduct = InnerProd(&Atemp, &Btemp, world, worldSize, myRank);
			result[INDEX(B,i,j)] = InnerProduct;
			
		}
	}

	free(Atemp.data);
	free(Btemp.data);
	return result;
}

void FasterMultMatrix(matrix *A, matrix *B, matrix *C, MPI_Comm *world, int worldSize, int myRank)
{
	if(A->cols != B->rows)
	{
		puts("Wrong dimensions, need square matrices\n");
	}

	matrix Atemp;
	matrix Btemp;
	initMatrix(&Atemp, 1, A->cols);
	initMatrix(&Btemp, B->cols, 1);

	int i,j,k;
	for(i = 0; i < A->rows; i++){
		for(k = 0; k < B->cols; k++){
			//Copies temp A data over
			for(j = 0; j < A->cols; j++){
				Atemp.data[k] = ACCESS(A,i,k);
				Btemp.data[k] = ACCESS(B,k,j);
			}


			double InnerProduct = InnerProd(&Atemp, &Btemp, world, worldSize, myRank);

				ACCESS(C,i,j) = InnerProduct;
		}
	}

	free(Atemp.data);
	free(Btemp.data);
}
#endif
