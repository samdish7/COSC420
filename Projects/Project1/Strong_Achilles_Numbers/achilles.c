//This is the main function for the Strong Achilles Numbers problem
//Sam Disharoon & Jordan Welch
#include<stdio.h>
#include<unistd.h>
#include<mpi.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include"achilles.h"
#define UPPER 10000
#define MAX 2000000
int main(int argc, char** argv){
        MPI_Init(&argc, &argv);
        MPI_Comm world = MPI_COMM_WORLD;

        int myRank, worldSize, x = 1, x2 = 1, found = 0, total = 0; 
	long long unsigned int numOps = 0, n = 4, t, p, q;
	/*
 	* x and x2 are "bools"
 	* n is first iterator
 	* p is first set of factors (2nd iterator)
 	* t is the totient of n
 	* q is second set of factors (3rd iterator)
 	* found is number of Strong Achilles numbers (Solution!)
 	* numOps is number of operations (for data purposes)
	*/
        MPI_Comm_size(world,&worldSize);
        MPI_Comm_rank(world,&myRank);
	
	// Parallel implementation
	
	/*
	char tmp[10];
	char buf[1000000];
	*/

	int* arr = NULL;// stores the amount of SANs each proc found
	int* numbers = malloc(sizeof(int) * (MAX/worldSize));// can be sent to MPI_Reduce this way
	
	if (myRank == 0){
		arr = malloc (sizeof(int) * (MAX/worldSize)); 
	}
	
	n += myRank;// Assign each node a section to check
	
	for(; n < UPPER; n += worldSize){ // Iterate each number up to the limit
		x = 1;
		numOps += 2;
		if(isPrime(n)){ // Only works on non primes!
			x = 0;
			continue;
		}
		for(p = 2; p <= n/2; p++){
			numOps++;
			if(x){
				numOps++;
				if(n % p == 0){
					numOps++;
					if(isPrime(p)){
						numOps++;
						if(!powerful(p,n)){
							x = 0;
							break;
						}
					}
				}
			}
		}
		if(x) {
			numOps++;
			if (!perfectPower(n)) {
				t = totient(n);
				x2 = 1;
				numOps += 3;
				if(isPrime(t)){ // Only works on non primes!
					x2 = 0;
					continue;
				}
				for(q = 2; q <= t/2; q++) {
					numOps++;
					if(x2) {
						numOps++;
						if(t % q == 0) {
							numOps++;
							if(isPrime(q)) {
								numOps++;
								if(!powerful(q,t)) {
									x2 = 0;
									break;
								}
							}
						}
					}
				}
				if(x2) {
					numOps++;
					if(!perfectPower(t)) {
						//sprintf(tmp, "%llu ", n);
						//strcat(buf, tmp);
						numbers[found] = 1;
						found++;
					}
				}
			}
		}
	}

	
	/*
  	printf("I am node %d and my SANs are ~> %s\n", myRank, buf);
	printf("I am node %d and I found %d SANs\n", myRank, found);
	printf("I am node %d and did %llu calculations\n", myRank, numOps);
	*/
	MPI_Reduce(numbers, arr, worldSize, MPI_INT, MPI_SUM, 0, world);
	if(myRank == 0){
		int j = 0;
		for(;j < worldSize; j++){
			total += arr[j];
		}
		printf("There are %d total SANs up to %d\n", total, UPPER);
	}


	/* Serial implementation
	for(; n < UPPER; n++){ // Iterate each number up to the limit
		x = 1;
		numOps += 2;
		if(isPrime(n)){ // Only works on non primes!
			x = 0;
			continue;
		}
		for(p = 2; p <= n/2; p++){
			numOps++;
			if(x){
				numOps++;
				if(n % p == 0){
					numOps++;
					if(isPrime(p)){
						numOps++;
						if(!powerful(p,n)){
							x = 0;
							break;
						}
					}
				}
			}
		}
		if(x) {
			numOps++;
			if (!perfectPower(n)) {
				t = totient(n);
				x2 = 1;
				numOps += 3;
				if(isPrime(t)){ // Only works on non primes!
					x2 = 0;
					continue;
				}
				for(q = 2; q <= t/2; q++) {
					numOps++;
					if(x2) {
						numOps++;
						if(t % q == 0) {
							numOps++;
							if(isPrime(q)) {
								numOps++;
								if(!powerful(q,t)) {
									x2 = 0;
									break;
								}
							}
						}
					}
				}
				if(x2) {
					numOps++;
					if(!perfectPower(t)) {
						//printf("%d ", n); // Found one!
						found++;
					}
				}
			}
		}
	}
	*/
	
free(arr);
free(numbers);
MPI_Finalize();
return 0;
}

