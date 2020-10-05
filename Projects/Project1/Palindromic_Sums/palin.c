//This is the main function for the Palindromic Sums problem
//Sam Disharoon & Jordan Welch
#include<stdio.h>
#include<unistd.h>
#include<mpi.h>
#include<math.h>
#include<string.h>
#include"palin.h"
#define UPPER 100000000
int main(int argc, char** argv){
        MPI_Init(&argc, &argv);
        MPI_Comm world = MPI_COMM_WORLD;

        int myRank, worldSize;
	unsigned long long int i, sum = 0, totalP = 0, numOps = 0;
	//totalP ~> number of palindromes each node finds
	//numOps ~> number of total operations performed
	
	int* arr = NULL;

	/*//Used for output purposes to see if numbers were being distributed properly
	char tmp[10];
	char buf[100000];
	*/

	MPI_Comm_size(world,&worldSize);
        MPI_Comm_rank(world,&myRank);
	
	//we found there are 166 total palindromes that fit the conditions, so we used that number to allocate memory for our arrays
	
	int* numbers = (int*) malloc(166 * sizeof(int)); //get each palindrome and store it in an array
	
	//Parallel implementation
	i = myRank + 2;
	for(;i < UPPER; i += worldSize){
		numOps++;
		if(isPalin(i)){
			numOps++;
			if(conSquares(i)){
				numOps++;
				numbers[totalP] = i;
				//sprintf(tmp,"%d ", numbers[totalP]);
				//strcat(buf, tmp);
				totalP++;
			}
		}
	}
	if(myRank == 0){
		arr = malloc(166 * sizeof(int));
	}
	MPI_Reduce(numbers, arr, 166, MPI_INT, MPI_SUM, 0, world);
		numOps++;
	//printf("My numbers are ~> %s and I found %llu Palindromes\n", buf, totalP);
	
	//Master node finds and displays the sum
	if (myRank == 0){
 		for(i = 0; i < 166; i++){
			numOps++;
 			sum += arr[i];
		}
		printf("The sums of all the palindromic numbers below 10^8 is ~> %llu\n", sum);	
	}
	printf("I am proc %d and I did %llu calculations\n", myRank, numOps);
	
	 /*Serial Implementaion
 	for(i = 2; i < UPPER; i++){
		numOps++;
		if(isPalin(i)){
			numOps++;
			if(conSquares(i)){
				numOps++;
				//printf("%d\n",i);
				sum += i;
			}
		}
	}
	printf("The sums of all the palindomic numbers below 10^8 is ~> %llu\n",sum);
	printf("Total number of operations ~> %d", numOps);
	*/

	MPI_Finalize();
	free(arr);
	free(numbers);
	return 0;
}

