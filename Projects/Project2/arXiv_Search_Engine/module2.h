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
 *
 * Book keeping notes:
 * Longest line in arxiv-citations ~> 16
 * =======================================================================
*/
#ifndef MODULE2_H
#define MODULE2_H
#include"datatype.h"
#include"matrix_lib.h"

// function to read in data
long int readCit(FILE* file, const int myRank, const int worldSize, MPI_Comm world){
	long int fSize;
	int i = 0, numIDs = 0, max = 19, numArt = 0;
	char str[max];
	char* plus = "+++++", *minus = "-----";
	char* prevStr = malloc(max);
	char* currID = malloc(max);
	
	// empty both strings
	currID[0] = '\0';
	prevStr[0] = '\0';
	
	// get file size
	fseek(file, 0, SEEK_END);
	fSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	// go through the file
	while(fgets(str, sizeof(str), file)){
		if(!i){ // for first iteration
			strcpy(currID, str);
			strcpy(prevStr, str);
			printf("First! ~> %s\n", currID);
			i++;
			continue;
		}
		//printf("prev ~> %s\n", prevStr);
		str[strlen(str)-1] = '\0';
		//printf("str ~> %s ~> %zu\n", str, strlen(str));
		if(!strcmp(str, minus)){ // begin counting pages cited
			strcpy(currID, prevStr); // set currID to prevStr because prevStr is the start of the new paper
			numIDs = 0;
		} else if(!strcmp(str, plus)){ // end of block
			numArt++;
			//printf("%s cited %d pages\n", currID, numIDs);
			strcpy(currID, str); // sets currID to +++++ (signifies the end of block)
		} else {
			numIDs++;
		}

		strcpy(prevStr, str); // save the string as previous
	}
	printf("Number of articles ~> %d\n", numArt);
	free(prevStr);
	free(currID);
	return fSize;
}


#endif 
