//Sam Disharoon
//Various tests for the eigenvector functions
#include "matrix_lib.h"
#define limit 20
int main(int argc, char** argv){
	// set up MPI world
	MPI_Init(NULL, NULL);
	
	int worldSize, myRank;
	
	double startTime, stopTime;

	MPI_Comm world = MPI_COMM_WORLD;
	
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	
	if(argc != 3){
		if(myRank == 0){
			printf("Usage ~> ./driver *matrix file* *vector file*\n");
		}
		return 1;
	}
	
	int mSize = 0, svSize = 0, numLines = 0, i = 0, j;
	
	struct mat matrixA, sVector; // matrices
	
	// various file sizes
	FILE* big,* bigV;

	// various char sizes
	char b[2500], bV[5];

	// this section tests reading in the file
	// using fopen/fclose


	// master node reads in the file and starts off with the data
	if(myRank == 0){
		
		startTime = MPI_Wtime();
		
		// error checking
		if((big = fopen(argv[1], "r")) == NULL){
			puts("data error!");
			return 1;
		}
		if((bigV = fopen(argv[2], "r")) == NULL){
			puts("sVector error!");
			return 1;
		}
		
		// get number of lines (use sVector cause it is faster)
		while(fgets(bV, sizeof(bV), bigV)){
			numLines++;
		}
		
		// calculate number of values in file
		// find file size, subtract by the number of lines,
		// divide by two because for every number,
		// there is also a space
		fseek(big, 0, SEEK_END);
		mSize = ftell(big);
		mSize = (mSize - numLines) / 2;
		fseek(big, 0, SEEK_SET);
		
		fseek(bigV, 0, SEEK_END);
		svSize = ftell(bigV);
		svSize = (svSize - numLines) / 2;
		fseek(bigV, 0, SEEK_SET);

		printf("Matrix Size ~> %d sVector Size ~> %d\n", mSize, svSize);
		initMat(&matrixA, numLines, numLines, 0);
		initMat(&sVector, numLines, 1, 0);
		// read data and put into matrix
		// *********************************
		// NOTE ~> j is row number
		j = 0;
		while(fgets(b, sizeof(b), big) && j < numLines){
			char tmp[strlen(b)];
			sprintf(tmp, "%s", b);
			//printf("b ~> %s\n", b);
			fillFileMatSQ(&matrixA, strlen(b), j, tmp, 1);
			j++;
		}
//		puts("A:");
//		printMat(&matrixA);	
		j = 0;
		while(fgets(bV, sizeof(bV), bigV)){
			char buf[strlen(bV)];
			sprintf(buf, "%s", bV);
			fillFileMatSQ(&sVector, strlen(bV), j, buf, 0);
			j++;
		}
		//printMat(&sVector);
		
		stopTime = MPI_Wtime();
		printf("File reading took ~> %1.2f seconds\n", stopTime - startTime);
		fflush(stdout);
	}
	// this section tests the Eigenvector methods;
	//  matrices MUST be sqaure!
	
	// update solution vector (x <- Ax)
	startTime = MPI_Wtime();
	multiMat(&matrixA, &sVector, &sVector, world, worldSize, myRank);
	
	/*if(myRank == 0){
		puts("A * x\n===================");
		printMat(&sVector);
	}*/

	// normalize solution vector
	normalize(&sVector);
	stopTime = MPI_Wtime();
	if(myRank == 0){
	//	puts("1 normalization of A:");
	//	printMat(&sVector);
	//	puts("==================");
		printf("1 normaliztion took ~> %1.2f seconds\n", stopTime - startTime);
	}
	fflush(stdout);
	//copyMat(&sVector, &copy);
	//free(result.arr);
	
	// repeat
	
	startTime = MPI_Wtime();
	for(; i < limit - 1; i++){
		//initMat(&result, atoi(argv[1]), 1, 0);
		multiMat(&matrixA, &sVector, &sVector, world, worldSize, myRank);
	//	printf("Normalize %d\n", i + 2);
		normalize(&sVector);
	//	printMat(&sVector);
	//	puts("==================");
		//subMat(&sVector, &copy, &result, world, worldSize, myRank);
		//copyMat(&sVector, &copy);
		//free(result.arr);
		
		// compare method attempts to stop it when it has reached a certain limit, but I had problems getting it to work, so I scrapped it
		/*
		if(compare(&result)){
			break;
		}
		*/
	}
	stopTime = MPI_Wtime();
	if(myRank == 0){
//		puts("Largest Eigenvector of A:");
//		printMat(&sVector);
		printf("%d normaliztions took ~> %1.2f seconds\n", limit - 1, stopTime - startTime);
	}
	
	fflush(stdout);
	MPI_Finalize();
	free(matrixA.arr);
	free(sVector.arr);
	//free(copy.arr);
	fclose(big);
	fclose(bigV);

	return 0;


}


