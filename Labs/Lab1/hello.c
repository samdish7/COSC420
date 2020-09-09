//Lab 1
//This program takes hello world and uses mpi to output it using n nodes
#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv){
	MPI_Init(NULL,NULL);
	MPI_Comm world = MPI_COMM_WORLD;

	int worldSize, myRank,len;
	char name[MPI_MAX_PROCESSOR_NAME];

	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	if( myRank == 0 ){
		MPI_Get_processor_name(name,&len);
		printf("Hello from the master node! My name is %s\n",name);
		printf("There are %d  total nodes.\n", worldSize);
	}
	else {
		MPI_Get_processor_name(name,&len);
		printf("Hello, from worker node %d! My name is %s\n", myRank,name);
	}
	
	MPI_Finalize();
	return 0;
}
