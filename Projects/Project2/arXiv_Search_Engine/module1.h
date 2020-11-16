/* module 1 for arXiv search engine
*  Sam Disharoon & Brock Forsythe 
* =========================================================================
* DESCRIPTION
*
* This module uses module 2 to maintain the document search index.
* A Binary Seatch Tree is used for storing the keys for each word in the file to 
* create a backwards index that maps each word to a document that has 
* the word in the abstract
*/
#ifndef MODULE1_H
#define MODULE1_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
//#include<mpi.h>
#include"datatype.h"

//Struct for each specific article

//Makes a root for the BST based on the ID of articles
void createRoot(WordNode** root)
{
	(*root) = (WordNode*) malloc(sizeof(WordNode));
	(*root)->word = (char*) calloc(16, sizeof(char));
	strcpy((*root)->word, "merosymmetrical"); //Pre found root word in nodes
	(*root)->IDList = NULL;
	(*root)->left = NULL;
	(*root)->right = NULL;
}

WordNode* checkWord(WordNode** root, char* word, int* pos)
{
	WordNode* current = *root;
	WordNode* prev = NULL;

	//Do until there arent any words left in index
	while(current != NULL)
	{
		//Check with other words to find if the word matches any others
		prev = current;
		if(strcmp(current->word, word) == 0)
		{
			(*pos) = 0;
			return current;
		}
		else if(strcmp(word, current->word) > 0)
		{
			(*pos) = 1;
			current = current->right;
		}
		
		else if(strcmp(word, current->word) < 0)
		{
			(*pos) = -1;
			current = current->left;
		}
	}
	return prev;
}

void InsertWord(WordNode** root, Article* data, char* word, int wordSize)
{
	//Checks if word is in tree.
	int pos;
	WordNode* newNode;
	WordNode* temp = checkWord(root, word, &pos);
	if(pos != 0)
	{
		WordNode* prev = temp;
		newNode = (WordNode*) malloc(sizeof(WordNode));
		newNode->word = (char*) calloc(wordSize, sizeof(int));
		strcpy(newNode->word, word);
		newNode->right = NULL;
		newNode->left = NULL;

		//Look for new wordNode's position
		if(pos == -1)
		{
			prev->left = newNode;
		}
		else if(pos == 1)
		{
			prev->right = newNode;
		}
	}
	else
	{
		newNode = temp;
	}
	
	//Creates List node for the ID of the article
	IDNode* newListNode = (IDNode*) malloc(sizeof(IDNode));
	newListNode->next = NULL;
	newListNode->ID = (char*) calloc(data->IDSize, sizeof(char));
	strcpy(newListNode->ID, data->ID);

	IDNode* current = newNode->IDList;
	if(current == NULL)
	{
		newNode->IDList = newListNode;
	}
	else
	{
		while(current->next != NULL && strcmp(current->ID, newListNode->ID) != 0)
		{
			current = current->next;
		}
		if(strcmp(current->ID, newListNode->ID) == 0)
		{
			free(newListNode);
			return;
		}
		else
		{
			current->next = newListNode;
		}
	}
}


void printInfoSearch(ArticleNode** root, char* ID)
{
	ArticleNode* current = (*root);
	while(current != NULL)
	{
		if(strcmp(ID, current->article->ID) == 0)
		{
			printf("%s \n", current->article->title);
			return;
		}
		else if(strcmp(ID, current->article->ID) < 0)
		{
			current = current->left;
		}
		else if(strcmp(ID, current->article->ID) > 0)
		{
			current = current->right;
		}
	}
}

void wordSearch(WordNode** root, char* word, ArticleNode** wordRoot)
{
	WordNode* current = (*root);
	int found = 0;
	while(current != NULL && found == 0)
	{
		if(strcmp(word, current->word) == 0)
		{
			found = 1;
		}
		else if(strcmp(word, current->word) < 0)
		{
			current = current->left;
		}
		else if(strcmp(word, current->word) > 0)
		{
			current = current->right;
		}
	}
	
	if(found == 1)
	{
		IDNode* currentID = current->IDList;
		while(currentID != NULL)
		{
			printf("%s \n", currentID->ID);
			printInfoSearch(wordRoot, currentID->ID);
			puts("");
			currentID = currentID->next;
		}
	}
	
	else
	{
		puts("This word does not exist in any articles in the metadata.\n");
	}
}

void ArticleInsert(ArticleNode** root, Article* data)
{
	//Allocates room for all the data inside Article struct
	ArticleNode* newNode;
	newNode = (ArticleNode*) malloc(sizeof(ArticleNode));
	newNode->article = (Article*) malloc(sizeof(data));
	newNode->article->ID = (char*) calloc(data->IDSize, sizeof(char));
	newNode->article->title = (char*) calloc(data->titleSize, sizeof(char));
	newNode->article->author = (char*) calloc(data->authorSize, sizeof(char));
	strcpy(newNode->article->ID, data->ID);
	strcpy(newNode->article->title, data->title);
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;

	if(*root == NULL)
	{
		(*root) = newNode;
	}
	else
	{
		ArticleNode* pointer = NULL;
		ArticleNode* cursor = (*root);

		while(cursor != NULL)
		{
			pointer = cursor;
			if(strcmp(newNode->article->ID, cursor->article->ID) < 0)
			{
				cursor = cursor->left;
			}
			else
			{
				cursor = cursor->right;
			}
		}

		newNode->parent = pointer;
		if(strcmp(newNode->article->ID, pointer->article->ID) > 0)
		{
			pointer->left = newNode;
		}
		else if(strcmp(newNode->article->ID, pointer->article->ID) > 0)
		{
			pointer->right = newNode;
		}

		newNode->left = NULL;
		newNode->right = NULL;
		free(cursor);
	}
}

void inOrder(ArticleNode* root)
{
	if(root != NULL)
	{
		inOrder(root->left);
		printf("%s \n", root->article->ID);
		inOrder(root->right);
	}
}
#endif
