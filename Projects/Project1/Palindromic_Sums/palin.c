//This is the main function for the Palindromic Sums problem
//Sam Disharoon & Jordan Welch
#include<stdio.h>
#include<unistd.h>
#include<mpi.h>
#include<math.h>
#include"palin.h"
#define UPPER 1000
int main(int argc, char** argv){
        MPI_Init(&argc, &argv);
        MPI_Comm world = MPI_COMM_WORLD;

        int myRank, worldSize;
	unsigned long long int i, sum = 0;
	int* arr = NULL;
        char tmp[10];
	char buf[10000000000];
	MPI_Comm_size(world,&worldSize);
        MPI_Comm_rank(world,&myRank);
	
	//Parallel implementation
	i = myRank + 1;
	for(;i < UPPER; i++){
	
	}
	if (myRank == 0){
		printf("The sums of all the palindromic numbers below 10^8 is ~> %llu\n",sum);	
	}
	MPI_Finalize();
	/* Serial Implementaion
 	* for(i = 2; i < UPPER; i++){
		if(isPalin(i)){
			if(conSquares(i)){
				//printf("%d\n",i);
				sum += i;
			}
		}
	}
	printf("The sums of all the palindomic numbers below 10^8 is ~> %llu\n",sum);
	*/
	
	return 0;
}

