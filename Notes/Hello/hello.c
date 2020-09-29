#include<stdio.h> //printf
#include<mpi.h> //mpi


int main(int argc, char** argv){
	MPI_Init(NULL,NULL); //pass through arguments
	
	//this constant gets set by the MPI lib
	MPI_Comm world = MPI_COMM_WORLD;

	//Worldsize will be total number of nodes in the communicator
	//myRank will be the nodes id within that communicator
	int worldSize, myRank;
	
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	
	//only execute on the "master" node
	if( myRank==0 ){
		printf("Hello from master node!\n");
		printf("There are %d total nodes.\n",worldSize);
	} else{
		// executes in worker nodes
		printf("Hello from node %d!\n", myRank);
	}
	
	MPI_Finalize();
	return 0;
}
