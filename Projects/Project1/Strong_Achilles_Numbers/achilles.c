//This is the main function for the Strong Achilles Numbers problem
//Sam Disharoon & Jordan Welch
#include<stdio.h>
#include<unistd.h>
#include<mpi.h>
#include<math.h>
#include"achilles.h"
#define UPPER 1000
int main(int argc, char** argv){
        MPI_Init(&argc, &argv);
        MPI_Comm world = MPI_COMM_WORLD;

        int myRank, worldSize, x = 1, x2 = 1, n = 4, p, t, q, total = 0;
	/*
 	* x and x2 are "bools"
 	* n is first iterator
 	* p is first set of factors (2nd iterator)
 	* t is the totient of n
 	* q is second set of factors (3rd iterator)
 	* total is number of Strong Achilles numbers (Solution!)
	*/
	
        MPI_Comm_size(world,&worldSize);
        MPI_Comm_rank(world,&myRank);
	
	for(; n < UPPER; n++){ // Iterate each number up to the limit
		x = 1;
		if(isPrime(n)){ // Only works on non primes!
			x = 0;
			continue;
		}
		for(p = 2; p < n; p++){
			if(x){
				if(n % p == 0){
					if(isPrime(p)){
						if(!powerful(p,n)){
							x = 0;
							break;
						}
					}
				}
			}
		}
		//if(x){total++; printf("%d ",n);} //Test to see if powerful worked... it does :)
	}


	printf("Total powerful nums ~> %d\n",total);
MPI_Finalize();
return 0;
}

