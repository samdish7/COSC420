//Main function for primality of 2n^2 problem
//Sam Disharoon and Jordan Welch

#include<stdio.h>
#include<unistd.h>
#include<mpi.h>
#include<math.h>
#include<stdlib.h>
#include"primality.h"
#define MAX 30000000
int main(int argc, char** argv){
	MPI_Init(&argc, &argv);
	MPI_Comm world = MPI_COMM_WORLD;

	int myRank, worldSize;
	
	MPI_Comm_size(world,&worldSize);
	MPI_Comm_rank(world,&myRank);

	long int found = 0, total = 0;
	long long unsigned int n = 29900000, t, numOps = 0;
	
	long int* localCou = malloc(sizeof(long));
	long int* totalCou = malloc(sizeof(long));

	n += myRank;
	numOps += 5;
	for(; n <= MAX; n += worldSize) {
		t = 2 * (n * n) - 1;
		numOps += 3;
		if(isPrime(t)) {
			printf("%llu ", n);
			numOps += (sqrt(t) + 3);
			found++;
		}
		else{
			numOps += 2;
		}
	}
	
	localCou[0] = found;
	numOps++;
	printf("I am node %d and I found ~> %li in ~%llu operations\n", myRank, localCou[0], numOps);
	MPI_Reduce(localCou, totalCou, 1, MPI_LONG, MPI_SUM, 0, world);
	if(myRank == 0){
		total = totalCou[0];
		printf("Answer: %li\n", total);
	}
	
	free(localCou);
	free(totalCou);
	MPI_Finalize();
	return 0;
}
