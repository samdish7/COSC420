#ifndef MATRIX_H
#define MATRIX_H
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
			ACCESS(A,i,j) = rand() % 10 + 1;
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
			ACCESS(A,i,j) = rand() % 10;
		}
	}
}

void AllocateMatrix(matrix *A)
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
	int i,j,k,count = 0;
	for(i=0; i < A->rows; i++)
	{
		for(j=0;j < B->cols; j++)
		{
			count += 1;
			for(k = 0; k < A->cols; k++)
			{
				ACCESS(C,i,j) += ACCESS(A,i,k) * ACCESS(B,k,j);
			}
		}
	}
	//printf("Count: %d\n", count);
}

//A is loaded once as opposed to n times in SerialMult
//B is accessed by rows which fully utilizes caches
void BestSerialMult(matrix *A, matrix *B, matrix *C/*int n, int blockSize*/)
{
	int i,j,k,count = 0;
	for(i = 0; i < A->rows; i++)
	{
		for(k = 0; k < B->cols; k++)
		{
			count += B->cols;
			for(j = 0; j < A->cols ; j++)
			{
				ACCESS(C,i,j) += ACCESS(A,i,k) * ACCESS(B,k,j);
			}
		}
	}
	//printf("Count: %d\n", count);
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

	int length = A->rows * A->cols;
	int VectorArray[worldSize];
	int displacement[worldSize];
	int j;

	for(j = 0; j < worldSize; j++)
	{
		VectorArray[j] = length / worldSize;
	}

	for(j = 0; j < (length % worldSize); j++)
	{
		VectorArray[j] += 1;
	}

	int nextLength = 0;
	for(j = 0; j < worldSize; j++)
	{
		if(j == 0)
		{
			displacement[j] = 0;
			nextLength = VectorArray[j];
			continue;
		}
		displacement[j] = displacement[j - 1] + nextLength;
		nextLength = VectorArray[j];
	}

	int matrixLen = VectorArray[myRank]; // Nodes divide array size
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
	if(myRank == 0)
	{
		return result;
	}
	return -1;
}

//Altered matrix Mult
void classicMultMatrix(matrix *A, matrix *B, matrix *C, MPI_Comm *world, int worldSize, int myRank)
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
	for(i = 0; i < A->rows; i++)
	{
		for(j = 0; j < B->cols; j++)
		{
			if(myRank == 0)
			{
				//Copies temp A data over
				for(k = 0; k < A->cols; k++)
				{
					Atemp.data[k] = ACCESS(A,i,k);
				}
			}

			if(myRank == 0)
			{
				//Copies temp A data over
				for(k = 0; k < A->cols; k++)
				{
					Btemp.data[k] = ACCESS(B,k,j);
				}
			}

			double InnerProduct = InnerProd(&Atemp, &Btemp, world, worldSize, myRank);

			if(myRank == 0)
			{
				ACCESS(C,i,j) = InnerProduct;
			}
		}
	}

	free(Atemp.data);
	free(Btemp.data);
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
	for(i = 0; i < A->rows; i++)
	{
		for(k = 0; k < B->cols; k++)
		{
			if(myRank == 0)
			{
				//Copies temp A data over
				for(j = 0; j < A->cols; j++)
				{
					Atemp.data[k] = ACCESS(A,i,k);
				}
			}

			if(myRank == 0)
			{
				//Copies temp A data over
				for(j = 0; j < A->cols; j++)
				{
					Btemp.data[k] = ACCESS(B,k,j);
				}
			}

			double InnerProduct = InnerProd(&Atemp, &Btemp, world, worldSize, myRank);

			if(myRank == 0)
			{
				ACCESS(C,i,j) = InnerProduct;
			}
		}
	}

	free(Atemp.data);
	free(Btemp.data);
}


//Math for Inner Mult
double DotProduct(double *A, double *B, int c)
{
	int arraySize = c;
	int i,myRank,worldSize;
	int sum = 0;
	int world = MPI_COMM_WORLD;
	MPI_Comm_rank(world,&myRank);
	MPI_Comm_size(world, &worldSize);
	int *sendcounts = malloc(worldSize * sizeof(double));
	int *displs = malloc(worldSize * sizeof(double));
	double load = arraySize / worldSize;
	int extra = (arraySize % worldSize) + load;
	double rem = arraySize % worldSize;
	for(i=0; i < worldSize; i++)
	{
		sendcounts[i] = arraySize/worldSize;
		if(rem > 0)
		{
			sendcounts[i]++;
			rem--;
		}
		displs[i] = sum;
		sum+= sendcounts[i];
	}
	double *localArrayOne = malloc(extra * sizeof(double));
	double *localArrayTwo = malloc(extra * sizeof(double));

	MPI_Scatterv(A,sendcounts,displs,MPI_DOUBLE,localArrayOne,sendcounts[myRank],MPI_DOUBLE,0,world);
	MPI_Scatterv(B,sendcounts,displs,MPI_DOUBLE,localArrayTwo,sendcounts[myRank],MPI_DOUBLE,0,world);

	double partialInnerProduct = 0;
	for(i=0;i<sendcounts[myRank];i++)
	{
		partialInnerProduct += localArrayOne[i] * localArrayTwo[i];
	}

	double fullInnerProduct = 0;
	MPI_Reduce(&partialInnerProduct,&fullInnerProduct,1,MPI_DOUBLE,MPI_SUM,0,world);
	free(localArrayOne);
	free(localArrayTwo);
	free(displs);
	free(sendcounts);
	return fullInnerProduct;
}

void MatrixMult(matrix *A, matrix *B, matrix *C)
{
	int i,j,k;
	for(i=0;i<C->rows; i++)
	{
		for(j=0;j<C->cols;j++)
		{
			int arraySize = A->cols;
			double *arrayOne = malloc(arraySize*sizeof(double));
			double *arrayTwo = malloc(arraySize*sizeof(double));
			for(k=0;k<A->cols;k++)
			{
				arrayOne[k] = A->data[(i*A->cols)+1];
				arrayTwo[k] = B->data[(k*B->cols)+j];
			}
			double q = DotProduct(arrayOne, arrayTwo, arraySize);
			ACCESS(C,i,j) = q;
			free(arrayOne);
			free(arrayTwo);
		}
	}
}


//Row reduction formula
//Can compute inverse of a matrix
void MPIGaussJordan(matrix *A, matrix *B, matrix *D, MPI_Comm *world, int worldSize, int myRank)
{
	//puts("Hi");
	int n = A->rows * A->cols; //Area of amtrix
	int i,j,k;
	char L[n];	
	int localLen = n/worldSize; //Length of each partition
	double *localArrA = malloc(localLen*sizeof(double));
	double *localArrB = malloc(localLen*sizeof(double));
	double *sol = malloc(localLen*sizeof(double));
	//Scatters both Matrices to be operated on in parts.

	for(i=0; i < n; i++)
	{
		L[i] = i % worldSize;
	}
	
	MPI_Scatter(A->data, localLen, MPI_DOUBLE, localArrA, localLen, MPI_DOUBLE, 0, *world);
	MPI_Scatter(B->data, localLen, MPI_DOUBLE, localArrB, localLen, MPI_DOUBLE, 0, *world);
	//K is the pivot row
	for(k=0;k<localLen;k++)
	{
		for(i=k+1; i<localLen; i++)
		{	
			if(L[k] == myRank)
			{
				sol[i] = localArrA[i] / localArrB[i];
			}
		}

		for(j=k+1; j<localLen; j++)
		{
			if(L[i] == myRank)
			{
				ACCESS(A,i,j) = ACCESS(A,i,j) - (sol[i] * ACCESS(A,j,k));
			}
		 	ACCESS(B,i,j) = ACCESS(D,i,j) - (sol[i] * ACCESS(B,j,k));
		}	
	}
	MPI_Gather(sol, localLen, MPI_DOUBLE, D->data, localLen, MPI_DOUBLE, 0, *world);	
	free(localArrA);
	free(localArrB);
	free(sol);
}

void Equalize(matrix* A, matrix* B)
{
	int i,j;
	//Sets values of input matrices equal to each other
	for(i=0; i < A->rows; i++)
	{
		for(j=0;j < A->cols; j++)
		{
			ACCESS(A,i,j) = ACCESS(B,i,j);
		}
	}
}

//Does the x/||X||2 process
double Normalize(matrix* A, int normalize)
{
	int i,j;
	double total = 0;
	double temp = 0;
	//Loop computes x
	for(i=0; i < A->rows; i++)
	{
		for(j=0; j < A->cols; j++)
		{
			temp = (double)(ACCESS(A,i,j) * ACCESS(A,i,j));
		}
		total += temp;
	}
	
	//Takes a smaller value of the total from aboce (||x||2)
	double newTotal = sqrt(total);
	if(normalize == 1)
	{
		for(i = 0; i < A->rows; i++)
		{
			for(j=0; j < A->cols; j++)
			{
				//x/||x||2
				ACCESS(A,i,j) = ((double)ACCESS(A,i,j)/newTotal);
			}
		}
	}
	//returns even smaller value of the new total
	return sqrt(newTotal);
}

//A must be square matrix
void EigenVector(matrix *A, matrix *B, matrix *C, MPI_Comm *world, int myRank)
{
	//Checks if the matrix is square
	if(A->rows == B->cols)
	{
		double temp = 0;
		double smallestVal = 1000000000;
		//Runs while x is converging by .000001
		do
		{
			MatrixMult(A,B,C);
			//Sets temp to smallest value then reassigns smallest value
			if(myRank == 0)
			{
				temp = smallestVal;
				Equalize(B,C);
				smallestVal = Normalize(B,1);
			}
		}while((fabs(temp - smallestVal)) > .000001);
		printMatrix(B);
		MatrixMult(A,B,C);
	}
}
#endif
