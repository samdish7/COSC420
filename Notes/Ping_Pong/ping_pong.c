#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){
	MPI_Init(NULL,NULL);
	
	MPI_Comm world = MPI_COMM_WORLD;



	int worldSize, myRank;
	int token = 0;
	int counter = 0;
	
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	
	if(worldSize != 2){
		fprintf(stderr,"ONLY RUN WITH 2 PROCESSORS\n");
		MPI_Finalize();
		return 0;
	}

	while(token < 10){
		if(myRank % 2 == token % 2){
			token++;
			printf("Proc %d sent %d to %d\n", myRank, token, (myRank + 1) % 2);
			MPI_Send(&token, 1, MPI_INT, (myRank + 1) % 2, 0, world);
		} else {
			MPI_Recv(&token, 1, MPI_INT, (myRank + 1) % 2, 0, world, MPI_STATUS_IGNORE);
			printf("Proc %d recieved %d to %d\n", myRank, token, (myRank + 1) % 2);
		}
	}	
MPI_Finalize();
return 0;
}
