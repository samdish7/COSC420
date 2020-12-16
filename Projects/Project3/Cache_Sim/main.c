#include "matrix.h"

int main(int argc, char **argv)
{
	//Initialize MPI
	MPI_Init(&argc,&argv);
	MPI_Comm world = MPI_COMM_WORLD;
	int myRank, worldSize;
	MPI_Comm_rank(world,&myRank);	
	MPI_Comm_size(world,&worldSize);
	//Allows for random numbers
	srand(time(NULL) + myRank);
	//Initialze the matrices from struct matrix
	matrix A, B, C;
	A.rows = B.rows = C.rows = atoi(argv[1]);
	A.cols = B.cols = C.cols = atoi(argv[2]);
	//Fills A and B with random nums and C with an empty arra

	createMatrix(&A);
	createMatrix(&B);
	AllocateMatrix(&C);

	/*if(myRank == 0)
	{
		printf("Matrix A: \n");
		printMatrix(&A);
		printf("Matrix B: \n");
		printMatrix(&B);
	}
*/	//int blockSize = A.rows / worldSize; //Makes even blocks based on number of nodes
	//int n = A.rows;
	double startTime, stopTime;
	startTime = MPI_Wtime();

	SerialMult(&A,&B,&C, myRank);
	stopTime = MPI_Wtime();
	if(myRank == 0)
	{
		//printMatrix(&C);
		printf("Time taken: %9.7f seconds\n", stopTime - startTime);
	}

	AllocateMatrix(&C);

	startTime = MPI_Wtime();
	BestSerialMult(&A,&B,&C,myRank);
	stopTime = MPI_Wtime();
	
	//MatrixMult(&A,&B,&C);
	if(myRank == 0)
	{
		//printMatrix(&C);
		printf("Time taken: %9.7f seconds\n", stopTime - startTime);
		puts("-------------------------------------------");
	}
	
	AllocateMatrix(&C);

	int blockSize = A.rows / 2;
	startTime = MPI_Wtime();
	BlockedSerialMatrixMult(&A,&B,&C,blockSize,myRank);
	stopTime = MPI_Wtime();
	
	if(myRank == 0)
	{
		//printMatrix(&C);
		printf("Time taken: %9.7f seconds\n", stopTime - startTime);
		puts("-------------------------------------------");
	}

	matrix G;
	matrix H;
	matrix I;

	G.rows = H.rows = I.rows = atoi(argv[1]);
	G.cols = H.cols = I.cols = atoi(argv[2]);
	if(myRank == 0)
	{
		initMatrix(&G,G.rows,G.cols);
		//printf("G matrix\n");
		//printMatrix(&G);
		initMatrix(&H,H.rows,H.cols);
		//printf("H matrix\n");
		//printMatrix(&H);
		AllocateMatrix(&I);
	}
	
		startTime = MPI_Wtime();
		classicMultMatrix(&G,&H,&I,&world,worldSize,myRank);
		stopTime = MPI_Wtime();
		

	if(myRank == 0)
	{
		printf("Classic Parallel Mult Matrix:\n");
		//printMatrix(&I);
		printf("Time taken: %9.7f seconds\n", stopTime - startTime);
		puts("-------------------------------------------");
	}
	
		startTime = MPI_Wtime();
		FasterMultMatrix(&G,&H,&I,&world,worldSize,myRank);
		stopTime = MPI_Wtime();
	
	if(myRank == 0)
	{
		printf("Faster Parallel Mult Matrix:\n");
		//printMatrix(&I);
		printf("Time taken: %9.7f seconds\n", stopTime - startTime);
		puts("-------------------------------------------");
	}

	//printf("MPI_time measured: %1.6f seconds\n", stopTime-startTime);
	fflush(stdout);
	free(A.data);
	free(B.data);
	free(C.data);
	MPI_Finalize();
	return 0;
}
