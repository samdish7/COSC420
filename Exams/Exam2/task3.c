#include<stdlib.h>
#include<stdio.h>
//#include<mpi.h>
#define INDEX(A,i,j) A.cols*i+j
#define ACCESS(A,i,j) A.data[INDEX(A,i,j)]
#include<string.h>
#include<math.h>
typedef struct 
{
	int rows, cols;
	double* data;	
} matrix;

void printMatrix(matrix A)
{
	int i,j;
	for(i=0;i < 1;i++)
	{	
		for(j=0;j < 8;j++)
		{
			printf("%0.2f ", ACCESS(A,i,j));
		}
		puts("");
	}
}

double Normalize(matrix A, int normalize)
{
	int i,j;
	double total = 0;
	double temp = 0;
	//Loop computes x
	for(i=0; i < A.rows; i++)
	{
		for(j=0; j < A.cols; j++)
		{
			temp = (double)(ACCESS(A,i,j) * ACCESS(A,i,j));
		}
		total += temp;
	}
	
	//Takes a smaller value of the total from aboce (||x||2)
	double newTotal = sqrt(total);
	if(normalize == 1)
	{
		for(i = 0; i < A.rows; i++)
		{
			for(j=0; j < A.cols; j++)
			{
				//x/||x||2
				ACCESS(A,i,j) = ((double)ACCESS(A,i,j)/newTotal);
			}
		}
	}
	//returns even smaller value of the new total
	return sqrt(newTotal);
}

int main()
{
/*	MPI_Init(&argc,&argv);
	MPI_Comm world = MPI_COMM_WORLD;
	int myRank, worldSize;
	MPI_Comm_rank(world,&myRank);	
	MPI_Comm_size(world,&worldSize);
*/	srand(time(NULL));
	
	matrix A;
	A.rows = 1;
	A.cols = 8;
	ACCESS(A,0,0) = 0;
	ACCESS(A,0,1) = 1;
	ACCESS(A,0,2) = 0;
	ACCESS(A,0,3) = 1;
	ACCESS(A,0,4) = 0;
	ACCESS(A,0,5) = 0;
	ACCESS(A,0,6) = 1;
	ACCESS(A,0,7) = 1;
	int i, s, k;

	for(i = 0; i < A.rows; i++)
	{
		for(j = 0; j < A.cols; j++)
		{
			printf("%0.2f ", ACCESS(A,i,j);
		}
	}
	
	for(i=0; i < 1000; i++)
	{
		s = rand() % 8;
		for(k = 0; k < 20; k++)
		{
			if(k = '\n')
			{
				s++;
				continue;
			}
			if(k = '\0')
			{
				printf("Reached end of matrix\n");
				continue;	
			}
		}	
	}
	
	return 0;
}
//Clearly still need to parallelize it
//Need to determine v[i] vector to be able to count number of times a walk ended on each node
//	Primarily using a counter in order to document this.
//Need to normalize v[i] vector using Normailze Function above.
//Still need to do tests to determine difference in eigenvalues and eigenvectors 
