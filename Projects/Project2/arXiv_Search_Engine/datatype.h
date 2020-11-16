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

typedef struct ARTICLE
{
    //key represents the searched word
    int key;
    //data that holds list of document ids that contain search term
	//want to put the data into a second struct 
  	char* ID;
		int IDSize;
	char* title;
		int titleSize;
	char* author;
		int authorSize;
	char* abstract;
}Article;

//struct for the bst of articles
typedef struct ANODE
{
	Article* article;
	struct ANODE *left, *right, *parent;
}ArticleNode;

//struct for each id 
typedef struct IDNODE
{
	struct IDNODE* next;
	char* ID;
}IDNode;

//struct for each word in the articles
typedef struct WORDNODE
{
	char* word;
	IDNode* IDList;
	struct WORDNODE* left;
	struct WORDNODE* right;
}WordNode;

#endif
