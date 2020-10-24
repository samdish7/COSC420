// arXiv search engine main
// Sam Disharoon & Jordan Welch
#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<unistd.h>
#include<math.h>
#include<string.h>
#include"module1.h"
#include"module2.h"
int main(int argc, char** argv){
	
	// All MPI related start up functions
	MPI_Init(&argc, &argv);
	MPI_Comm world = MPI_COMM_WORLD;
	int myRank, worldSize;
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	MPI_Status status;
	MPI_File file;
	
	if(myRank == 0){
		puts("Welcome to the arXiv search engine!\nWhat word(s) do you want to search for?");
		puts("Character limit ~> 100:");
		puts("======================================");
	}
	
	int menu = 1, i;
	long long int file_size = 0; 
	char* choice = malloc(sizeof(char) * 100);
	while(menu){
	
		if(myRank == 0){
			puts("Word:");
			scanf("%s", choice);
			printf("You chose %s\n", choice);
			for(i = 1;i < worldSize; i++){
				MPI_Send(choice, 100, MPI_CHAR, i, 0, world);
			}
			MPI_Barrier(world);
		} else {
			MPI_Recv(choice, 100, MPI_CHAR, 0, 0, world, &status);
			MPI_Barrier(world);
		}
		if(strcmp(choice, "-1") == 0){
			menu = 0;
			continue;
		}
		printf("Rank %d Choice ~> %s\n", myRank, choice);
	}
	if(myRank == 0){
		puts("Goodbye!");
	}
free(choice);
MPI_Finalize();
return 0;
}
