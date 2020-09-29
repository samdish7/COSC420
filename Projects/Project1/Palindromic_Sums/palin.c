//This is the main function for the Palindromic Sums problem
//Sam Disharoon & Jordan Welch
#include<stdio.h>
#include<unistd.h>
#include<mpi.h>
#include<math.h>
#include"palin.h"

int main(int argc, char** argv){
        MPI_Init(&argc, &argv);
        MPI_Comm world = MPI_COMM_WORLD;

        int myRank, worldSize;
	unsigned long long int i, sum = 0;

        MPI_Comm_size(world,&worldSize);
        MPI_Comm_rank(world,&myRank);
	
	/* Serial Implementaion
 	* for(i = 2; i < 100000000; i++){
		if(isPalin(i)){
			if(conSquares(i)){
				//printf("%d\n",i);
				sum += i;
			}
		}
	}
	printf("The sums of all the palindomic numbers below 10^8 is ~> %llu\n",sum);
	*/
	MPI_Finalize();
	return 0;
}

