//Sam Disharoon
//Various tests for the eigenvector functions
#include "matrix_lib.h"
#define limit 2
int main(int argc, char** argv){
	// set up MPI world
	MPI_Init(NULL, NULL);
	
	int worldSize, myRank;
	
	//double startTime, stopTime;

	MPI_Comm world = MPI_COMM_WORLD;
	
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	
	// using arguments to test our algorithms before reading in a file
	
	if(argc != 3){
		if(myRank == 0){
			printf("Usage ~> ./driver *file1* *file 2*\n");
		}
		return 1;
	}
		int mSize = 0, svSize = 0, numLines = 0, i = 0, j;
		struct mat matrixA, sVector; //, result;
		//FILE* small,* smallV;
		//FILE* med,* medV;
		FILE* big,* bigV;
		//char s[45], sV[5];
		//char m[250], mV[5];
		char b[2500], bV[5];
	if(myRank == 0){
		
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
		printMat(&matrixA);	
		j = 0;
		while(fgets(bV, sizeof(bV), bigV)){
			char buf[strlen(bV)];
			sprintf(buf, "%s", bV);
			fillFileMatSQ(&sVector, strlen(bV), j, buf, 0);
			j++;
		}
		//printMat(&sVector);
	}
	
	if(myRank == 0){
		fclose(big);
		fclose(bigV);
		free(matrixA.arr);
		free(sVector.arr);
	}
	MPI_Finalize();
	fflush(stdout);

	return 0;


}


