//Main function for primality of 2n^2 problem
//Sam Disharoon and Jordan Welch

#include<stdio.h>
#include<unistd.h>
#include<mpi.h>
#include<math.h>
#include"primality.h"
#define MAX 50000000
int main(int argc, char** argv){
	MPI_Init(&argc, &argv);
	MPI_Comm world = MPI_COMM_WORLD;

	int myRank, worldSize;
	
	MPI_Comm_size(world,&worldSize);
	MPI_Comm_rank(world,&myRank);

	int total = 0;
	long long unsigned int n, t;
	for(n = 2; n <= MAX; n++) {
		t = 2 * (n * n) - 1;
		if(isPrime(t)) {
			//printf("%llu ", n);
			total++;
		}
	}
	
	printf("Answer: %d\n", total);

	MPI_Finalize();
	return 0;
}
