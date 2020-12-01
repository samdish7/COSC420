// Sam Disharoon & Brock Forsythe
#include"mat_lib.h"
int main(int argc, char** argv){
	// MPI STUFF
	MPI_Init(&argc, &argv);
	MPI_Comm world = MPI_COMM_WORLD;
	int myRank, worldSize;
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);

	struct mat A, vec;
	FILE* file;
	char x[100];
	int r = 0;
	

	if(!myRank){
		file = fopen("A.txt", "r"); // read in file
		initMat(&A, 8, 8, 0);
		initMat(&vec, 8, 1, 2);
		while(fgets(x, sizeof(x), file) && r < 8){
			char tmp[strlen(x)];
			sprintf(tmp, "%s", x);
			//printf("%s\n", tmp);
			fillFileMatSQ(&A, strlen(tmp), r, tmp, 1);
			r++;
		}
		puts("A:");
		printMat(&A); // sketch of A (1)
		puts("Vec:");
		printMat(&vec);
		
		//This is the next step to getting A normalized so it can display the ideal eigenvector. Couldn't type fast enough and fgets was giving me issues at the start :/
		//multiMat();
		//normalize();
	}

if(!myRank){
	free(A.arr);
	fclose(file);
}
MPI_Finalize();
return 0;
}
// We have A in a seperate file and it imports A and displays it, then performs the calculations on it.
// The walk simulation is in a seperate file called task3.c
