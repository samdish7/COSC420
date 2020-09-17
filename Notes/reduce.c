#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>
#include<string.h>

//take a command-line arg, N, to denote
//a positive int
// ./reduce N
// has args
int main(int argc, char** argv){
	MPI_Init(&argc, &argv);
	
	MPI_Comm world = MPI_COMM_WORLD;
	
	int worldSize, myRank;

	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);

	if(argc < 2){
		printf("Usage ~> ./reduce N\n");
		MPI_Finalize();
		return 1;
	}
	int N = atoi(argv[1]);
	
	srand(time(NULL) + myRank);

	int* numbers = (int*) malloc(N*sizeof(int));
	int i;

	char buf[256];
	char tmp[3];
	
	for(i = 0; i < N; i++){
		numbers[i] = rand() % 10;
		sprintf(tmp, "%d ", numbers[i]);
		strcat(buf, tmp);
	}
	
	printf("I am node %d and my numbers are %s\n", myRank, buf);

	/*int MPI_Reduce(const void *sendbuf,
 * 		void *recvbuf,
 * 		int count;
 * 		MPI_Datatype datatype,
 * 		MPI_Op op,
 * 		int root,
 * 		MPI_Comm comm) */
	int* result = NULL;
	
	if(myRank == 0){
		result = (int*) malloc(N*sizeof(int));
	}
	
	MPI_Reduce(number, result, N, MPI_INT, MPI_SUM, 0, world);
	
	if(myRank == 0){
		for(i=0; i<N; i++){
			printf("%d ", result[i]);
		}
		puts("");
	}
	
	free(numbers);
	free(result);
}
