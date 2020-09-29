#include<stdio.h>
#include<mpi.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char** argv){
	MPI_Init(&argc, &argv);
	
	MPI_Comm world = MPI_COMM_WORLD;
	
	int worldSize, myRank, i;
	
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &worldSize);
	
	if(argc < 2){
		printf("Usage: ./scatterv N\n");
		MPI_Finalize();
		return 0;
	}
	srand(time(NULL) + myRank);
	
	int N = atoi(argv[1]);
	
	int *sendcts = (int*) malloc(worldSize * sizeof(int));
	int *displcmts = (int*) malloc(worldSize * sizeof(int));
	
	for(i = 0; i < worldSize; i++){
		sendcts[i] = N/worldSize; // number each gets
		displcmts[i] = i * (N/worldSize)l // start indicies
	}
	
	if(N % worldSize > 0){
		//printf("N is not divisible by %d\n", worldSize);
		int extra = N % worldSize;
		sendcts[worldSize - 1] += extra; //small brain, easy
		/* "medium brain way"
 		* -remember OG array, but move the pointer "forward" so that there is a divisible amount
 		*  to scatter, just leave the "extra" on the root
 		*  -then just us regular scatter
 		*  -root will give as recvbuf a pointer to the "middle" of an actual recvbuf,
 		*  where the front has the extra data that got ignored
 		*
 		*  int offset = rank == root ? extra : 0;
 		*  recvbuf = malloc((len + offset) * sizeof(double));
 		*  MPI_Scatter(sendbuf + offset, recvbuf+offset, ..);
 		*  for(i = 0; i < offset; i++){
 		*  	recvbuf[i] = arr[i]; // only happens on root
 		*  }
 		*
 		*  "big brain way" ~Grant 2020
 		*  for(i = 0; i < extra; i++){
 		*  	
 		*  }
 		
		*/
	}


MPI_Finalize();
return 0;
}
