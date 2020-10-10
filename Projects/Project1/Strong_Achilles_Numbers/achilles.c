//This is the main function for the Strong Achilles Numbers problem
//Sam Disharoon & Jordan Welch
#include<stdio.h>
#include<unistd.h>
#include<mpi.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include"achilles.h"
#define UPPER 100000000
#define MAX 3000000
//Implement Gather and Gatherv for primes!
int main(int argc, char** argv){
        MPI_Init(&argc, &argv);
        MPI_Comm world = MPI_COMM_WORLD;

        int myRank, worldSize, x = 1, x2 = 1, found = 0, totalSANs = 0, maxPrime = 630000, totalPri = 51341,  p = 0, q, pNum = 2;
	long long unsigned int n = 4, t;
	//long long unsigned int numOps = 0; // used to calulate the number of operations per node
	
	/*
 	* x and x2 are "bools"
 	* n is first iterator
 	* p is set of prime factors (2nd iterator)
 	* pNum is value of the list at index p
 	* t is the totient of n
 	* found is number of Strong Achilles numSAN (Solution!)
 	* maxPrime is highest eligible prime factor
 	* totalPri is the number of primes under maxPrime
 	* numOps is number of operations (for data purposes)
	*/

        MPI_Comm_size(world,&worldSize);
        MPI_Comm_rank(world,&myRank);
	
	// Parallel implementation
	

	/* For checking output
	char tmp[10];
	char buf[1000000];
	*/
	long* sanCount = malloc(sizeof(long));// stores the amount of SANs each proc found
	long* numSAN = malloc(sizeof(long));// can be sent to MPI_Reduce this way
	
	//Couldn't get Gather to work, so had to let the nodes make their list of primes themselves :(
	int* localArr = malloc(sizeof(int) * totalPri);
	for(;pNum < maxPrime; pNum++){
		if(isPrime(pNum)){
			localArr[p] = pNum;
			p++;
		}
	}
	// printf("P ~> %d localArr[p] ~> %d\n", p, localArr[p - 1]);
	
	n += myRank;// Assign each node a section of UPPER to check
	
	// Use given info to find solution
	for(; n < UPPER; n += worldSize){ // Iterate each number up to the limit
		x = 1;
		//numOps += 2;
		if(isPrime(n)){ // Only works on non primes!
			x = 0;
			continue;
		}
		for(p = 0; p < totalPri; p++){ // Factors of p to determine if powerful
			pNum = localArr[p];
			if(!pNum){printf("ERROR!\n"); break;}
			if(pNum > n){ // for early numbers
				break;
			}
			if(n % pNum == 0){
				//numOps++;
				if(!powerful(pNum,n)){
					x = 0;
					break;
				}
			}
		}
		if(x) {
			//numOps++;
			if (!perfectPower(n)) { 
				// is achilles!
				t = totient(n);
				x2 = 1;
				if(isPrime(t)){
					x2 = 0;
					continue;
				}
				for(q = 0; q < totalPri; q++){
					pNum = localArr[q];
					if(!pNum){printf("ERROR!\n"); break;}
					if(pNum > t){ //for small values
						break;
					}
					if(t % pNum == 0){
						if(!powerful(pNum,t)){
							x2 = 0;
							break;
						}
					}
				}
				if(x2){
					if(!perfectPower(t)){
						// Strong achillies!
						found++;
					}
				}			
			}
		}
	}

	
  	//printf("I am node %d and my SANs are ~> %s\n", myRank, buf);
	printf("I am node %d and I found %d SANs\n", myRank, found);
		numSAN[0] = found;
	MPI_Reduce(numSAN, sanCount, 1, MPI_INT, MPI_SUM, 0, world);
	if(myRank == 0){
		totalSANs = sanCount[0];
		printf("\nThere are %d total SANs up to %d\n",  totalSANs, UPPER);
	}


	/* Serial implementation DO NOT USE!!! Dumb brute force takes a VERY long time!
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

free(sanCount);
free(numSAN);

free(localArr);
MPI_Finalize();
return 0;
}

