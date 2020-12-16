// Driver for cache hit/miss simulation
// Sam Disharoon & Brock Forsythe
// 
// NOTES
// =============================
// Three types of single-core cache misses:
//
// 1 ~> First-time referencing data
// is always a cache miss,
// this is called COMPULSORY CACHE MISS
//
// 2 ~> If data is overwritten because 
// cache wasn't large enough, 
// this is called CAPACITY CACHE MISS
//
// 3 ~> If one data item is mapped 
// to the same cache location as another item,
// this is called CONFLICT CACHE MISS
// ====================================
// Mult-core cache misses:
//
// Same as the three above, as well as 
// if an item is invalid due to another core
// changing its value,
// this is called INVALIDATION CACHE MISS
// ************************************
// TYPICAL MEMORY HEIRARCHY
// ===========================
// the lower the cache level, 
// the harder it is to transfer data to procs
//
// LAYOUT and AVERAGE SIZE/LATENCY in time cycles
//
// Registers	~> 192 bytes	
// L1 cache	~> 32 KB	4
// L2 cache	~> 256 KB	12
// L3 cache	~> 2 MB		26
// Main Memory	~> 2 GB		230-360
// ************************************
// TWO DIFFERENT REPLACEMENT ALGS
// =================================
// 1 ~> Least-Recently Used (LRU)
// Overwrites data that is used least recently
// 
// 2 ~> First in First out (FIFO)
// Overwrites data that came in first
// ************************************
// PEAK-PERFORMANCE 
// ================================
// The quickest time for a proc to compute an equation
// this is timed by OPERATIONS/SECOND
#include"cache.h"
int main(int argc, char** argv){
	// Intiate MPI
	MPI_Init(&argc, &argv);
	MPI_Comm world = MPI_COMM_WORLD;
	int myRank, worldSize;
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);

	srand(time(NULL) + myRank);
	matrix A, B, result;// Matrices
	double start, end;// Timing
	A.rows = A.cols = B.rows = B.cols = result.rows = result.cols = atoi(argv[1]);
		
		createMatrix(&A);
		createMatrix(&B);
		allocateMatrix(&result);
	
	/*if(myRank == 0){
		puts("Matrix A");
		printMatrix(&A);
		puts("Matrix B");
		printMatrix(&B);
		puts("====================");
	}*/
	
	start = MPI_Wtime();
	SerialMult(&A, &B, &result);
	end = MPI_Wtime();
	
	if(myRank == 0){
		printf("Normal Serial Mult took %9.7f seconds\n", end - start);
		//puts("Result Matrix 1");
		//printMatrix(&result);
		puts("====================");
		allocateMatrix(&result);
	}
	
	start = MPI_Wtime();
	BestSerialMult(&A, &B, &result);
	end = MPI_Wtime();
	
	if(myRank == 0){
		printf("Best Serial Mult took %9.7f seconds\n", end - start);
		//puts("Result Matrix 2");
		//printMatrix(&result);
		puts("====================");
		allocateMatrix(&result);
	}
	
	// new set of matrices
	matrix C, D;
	C.rows = C.cols = D.rows = D.cols = atoi(argv[1]);
	if(myRank == 0){
		createMatrix(&C);
		createMatrix(&D);
		/*
 		puts("Matrix C");
		printMatrix(&C);
		puts("Matrix D");
		printMatrix(&D);
		puts("====================");
		*/
	}

	start = MPI_Wtime();
	classicMultMatrix(&A, &B, &result, &world, worldSize, myRank);
	end = MPI_Wtime();

	if(myRank == 0){
		printf("Classic Parallel Mult took %9.7f seconds\n", end - start);
		//puts("Result Matrix 3");
		//printMatrix(&result);
		puts("====================");
		allocateMatrix(&result);
	}
fflush(stdout);	
if(myRank == 0){
	free(A.data);
	free(B.data);
	free(result.data);
}
MPI_Finalize();
return 0;
}
