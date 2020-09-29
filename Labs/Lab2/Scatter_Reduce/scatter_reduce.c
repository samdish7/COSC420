//This program gives a good example of using the scatter and reduce MPI functions
//Sam Disharoon & Jordan Welch
//Lab 2
#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<string.h>

int main(int argc, char** argv){
	MPI_Init(NULL,NULL);
	MPI_Comm world = MPI_COMM_WORLD;
	
	if(argc != 2){
		printf("Usage ~> mpiexec -n *num nodes* ./scat N\n");
		MPI_Finalize();
		return 1;
	}
	srand(time(NULL));
	
	int vecSize = atoi(argv[1]);
	int worldSize, myRank, i, total = 0, blockTotal = 0;
	
	int* arr1 = malloc(vecSize * sizeof(int));
	int* arr2 = malloc(vecSize * sizeof(int));
	
	
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
	
	int blockSize = vecSize / worldSize;
	int over = vecSize % worldSize + blockSize;
	int counter[worldSize];
	int displacement[worldSize];
	
	if (myRank == 0){
		printf("Vector Size ~> %d\n",vecSize);
		for(i = 0; i < vecSize; i++){
			arr1[i] = rand() % 10 + 1;
			arr2[i] = rand() % 10 + 1;
		}
		/*printf("Vector A:\n(");
		for(i = 0; i < vecSize; i++){
			if(i == vecSize - 1){
				printf("%d)\n",arr1[i]);
			}
			else{
				printf("%d, ",arr1[i]);
			}
		}
		printf("Vector B:\n(");
		for(i = 0; i < vecSize; i++){
			if(i == vecSize - 1){
				printf("%d)\n",arr2[i]);
			}
			else {
				printf("%d, ",arr2[i]);
			}
		}*/
	}
	for(i = 0;i < worldSize; i++){
		displacement[i]= i * blockSize;
		if (i == worldSize - 1){
			counter[i] = over;
		}
		else{
			counter[i] = blockSize;
		}
	}
	
	int split1[counter[myRank]];
	int split2[counter[myRank]];
	
	for(i = 0; i < counter[myRank]; i++){
		split1[i] = 0;
		split2[i] = 0;
	}
	
	MPI_Scatterv(arr1, counter, displacement, MPI_INT, split1, counter[myRank], MPI_INT, 0, world);
	
	MPI_Scatterv(arr2, counter, displacement, MPI_INT, split2, counter[myRank], MPI_INT, 0, world);
	
	for (i = 0; i < counter[myRank]; i++){
		blockTotal += split1[i] * split2[i];
	}
	
	MPI_Reduce(&blockTotal, &total, 1,  MPI_INT, MPI_SUM, 0, world);
	if( myRank == 0 ){
		printf("\nInner product of the two vectors is ~> %d\n",total);
	}
free(arr1);
free(arr2);
MPI_Finalize();
return 0;
}
