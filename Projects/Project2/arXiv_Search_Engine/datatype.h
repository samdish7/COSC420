/* file to define the datatypes used for the arXiv search engine
 * Sam Disharoon & Brock Forsythe
 * ========================================================================
 * DESCRIPTION
 *
 * This file defines the various structs needed for the search engine
 */
#ifndef DATATYPE_H
#define DATATYPE_H

// struct for articles
typedef struct{

	char* id = NULL;
	char* title = NULL;
	char* authors = NULL;
	char* abstract = NULL;
	int rank;

} article;
// struct for adjacency matrix
typedef struct{

	int rows;
	int cols;
	int* arr = NULL;

} adjMat;


#endif
