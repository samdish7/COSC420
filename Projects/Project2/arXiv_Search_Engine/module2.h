/* module 2 for arXiv search engine main
 * Sam Disharoon & Brock Forsythe
 * =======================================================================
 * DESCRIPTION
 *
 * This program is meant to take the graph created in module 1,
 * keep track of of the edges in the graph by updating the hub scores
 * and authorities of each page.
 * This is done using the HITS algorithm, and the rank of each page
 * is done by the PageRank algorithm
 * =======================================================================
*/
#ifndef MODULE2_H
#define MODULE2_H
#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"datatype.h"

// function to read in data
void readFile(FILE* file, char* line, int worldSize, int myRank, MPI_Comm world){
	puts("You called me");
}


#endif 
