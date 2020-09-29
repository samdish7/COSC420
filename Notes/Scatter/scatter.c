#include<stdio.h>
#include<mpi.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main(int argc, char** argv){
	MPI_Init(NULL, NULL);

	int worldSize, myRank, i;
	
	MPI_Comm world = MPI_COMM_WORLD;
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);


	if(argc < 2){
		printf("Usage: ./scatter N\n");
		return 0;
	}
	int N = atoi(argv[1]);
	double* arr = NULL;
	//only the root starts with all the data
	if(myRank == 0){
	//more realistically, would read in an
	//array from a large datafile, or something
		arr = malloc(N*sizeof(double));
		for(i=0; i<N; i++){
			arr[i] = (double)rand() / RAND_MAX; // 0 to 1
		}
	}
	//the chunk of the array that will be scattered to me 
	//NB: beware of rounding issues!
	int local_len = N / worldSize;
	double* local_arr = malloc(local_len * sizeof(double));
	
	MPI_Scatter(arr, local_len, MPI_DOUBLE, local_arr, local_len, MPI_DOUBLE, 0, world);
	
	char* buf = malloc(5*local_len+1);
	memset(buf, 0, 5*local_len + 1);

	/*long way of doing memset
 * 	for(i=0; i < 5*local_len+1; i++){
		buf[i]=0;
	}*/
	char tmp[6];
	for(i=0; i<local_len; i++){
		sprintf(tmp, "%0.2f ", local_arr[i]);
		strcat(buf, tmp);
	}
	printf("I am node %d and my numbers are %s\n",myRank, buf);

	MPI_Finalize();
	free(local_arr);
	free(buf);
	if(myRank == 0){
		free(arr);
	}
return 0;
}
