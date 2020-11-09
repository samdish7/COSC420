//Sam Disharoon & Jordan Welch
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
		FILE* med,* medV;
		//FILE* big,* bigV;
		//char s[20], sV[5];
		char m[200], mV[5];
		//char b[1500], bv[5];
	if(myRank == 0){
		
		// error checking
		if((med = fopen(argv[1], "r")) == NULL){
			puts("data error!");
			return 1;
		}
		if((medV = fopen(argv[2], "r")) == NULL){
			puts("sVector error!");
			return 1;
		}
		
		// get number of lines (use sVector cause it is faster)
		while(fgets(mV, sizeof(mV), medV)){
			numLines++;
		}
		
		// calculate number of values in file
		// find file size, subtract by the number of lines,
		// divide by two because for every number,
		// there is also a space
		fseek(med, 0, SEEK_END);
		mSize = ftell(med);
		mSize = (mSize - numLines) / 2;
		fseek(med, 0, SEEK_SET);
		
		fseek(medV, 0, SEEK_END);
		svSize = ftell(medV);
		svSize = (svSize - numLines) / 2;
		fseek(medV, 0, SEEK_SET);
		printf("Matrix Size ~> %d sVector Size ~> %d\n", mSize, svSize);

		initMat(&matrixA, numLines, numLines, 0);
		initMat(&sVector, numLines, 1, 0);
		// read data and put into matrix
		// **********************************
		// NOTE ~> j is row number, i is column number,
		// it looks very weird in the .h file, but it works,
		// so we are rolling with it
		j = 0;
		while(fgets(m, sizeof(m), med) && j < numLines){
			char tmp[strlen(m)];
			sprintf(tmp, "%s", m);
			fillFileMatSQ(&matrixA, strlen(m), j, i, tmp, 1);
			i++;
			j++;
		}
		printMat(&matrixA);	
		j = 0;
		i = 0;
		while(fgets(mV, sizeof(mV), medV)){
			char buf[strlen(mV)];
			sprintf(buf, "%s", mV);
			fillFileMatSQ(&sVector, strlen(mV), j, 0, buf, 0);
			j++;
		}
		printMat(&sVector);
	}
	
	if(myRank == 0){
		fclose(med);
		fclose(medV);
		free(matrixA.arr);
		free(sVector.arr);
	}
	MPI_Finalize();
	fflush(stdout);

	return 0;


}


