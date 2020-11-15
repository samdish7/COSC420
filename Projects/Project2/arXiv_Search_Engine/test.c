#include "module1.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<string.h>

//IMPORTANT Run using ./test <N> where N = number of articles to read in

/*arxiv-metadata.txt
 * Lines:          8,073,560
 * Words:          229,414,035
 * Chars:          1,652,562,265
 * Bytes:          1,652,562,299
 * Articles:       1,614,712
 * Middle Article: 1701.01948
 * Longest Line:   36,182
 */

/*
long long findOffset(int file, long long displ, long long sendCount)
{
    char buf;
    int k, n;
    int found = 0;
    for(k = 0; found == 0; k++)
    {
        lseek(file, (displ + sendCount - k), SEEK_SET);
        read(file, &buf, 1);
        if(buf == '\n')
        {
            for(n = 1; n <= 6; n++)
            {
                lseek(file, (displ + sendCount - k) - n, SEEK_SET);
                read(file, &buf, 1);
		//checks if the line is +'s
                if(buf != '+')
                {
                    n = 6;
                    found = 0;
                }
                else
                {
                    found = 1;
                }
            }
        }
    }
    return (sendCount - (k -3));
}

*/
int main(int argc, char* argv[])
{

/*	int myRank, worldSize;
	MPI_Init(NULL,NULL);
	MPI_Comm world = MPI_COMM_WORLD;
	MPI_Comm_size(world, &worldSize);
	MPI_Comm_rank(world, &myRank);
*/
/*	long long i;
	long long biteSize = 1652562265;
 	long long block = biteSize / world;
   	long long overflow = biteSize % world + block;

    	long long sendCounts[world];
    	long long displs[world];
*/
	Article arxiv;
	arxiv.IDSize = 11;
	arxiv.ID = (char*) calloc(arxiv.IDSize, sizeof(char));
	//Sets root to the previously found median ID
	strcpy(arxiv.ID, "1701.01948");
	arxiv.authorSize = 2;
	arxiv.author = (char*) calloc(arxiv.authorSize, sizeof(char));
	arxiv.titleSize = 1;
	arxiv.title = (char*) calloc(arxiv.titleSize, sizeof(char));

	ArticleNode *root = NULL;
	ArticleInsert(&root, &arxiv);
	WordNode* wordRoot;
	createRoot(&wordRoot);

	int file;
	long long i, count = 0;
	long long input;

	if(argc < 1 || argc > 2)
	{
		puts("Invalid input\n");
		exit(1);
	}
	if(argc == 1)
	{
		input = 1614712;
	}
	else if(argc == 2)
	{
		input = (long long) atoi(argv[1]);
	}

	char buf;
	char info[37000];
	memset(info, '\0', sizeof(info));

	int pos = 0; // Determines if line is Id, authoer, etc...
	int size[5];
	for(i = 0; i < 5; i++)
	{
		size[i] = 0;
	}
	
	file = open("arxiv-metadata.txt", O_RDONLY);
	if(file < 0)
	{
		puts("Input file error\n");
		exit(1);
	}
	/*if(myRank == 0)
	{
		file = open("arxiv-metadata.txt", O_RDONLY);
		if(file < 0)
		{
			printf("Error opening file\n");
			exit(1);
		}	
	}*/

	 //read file contents till end of file 

/*	if(myRank == 0)
	{
    		for(i = 0; i < world; i++)
		{
        		if(i == 0)
        		{
            			displs[i] = 0;
      		 	}
        		else
        		{
            			displs[i] = displs[i - 1] + sendCounts[i - 1];
        		}
        		if(i == world - 1)
        		{
            			sendCounts[i] = biteSize - displs[i];
        		}
        		else
        		{
            			sendCounts[i] = findOffset(file, displs[i], block);
        		}
        		//printf("%lld - %lld (%lld)\n", displs[i], displs[i] + sendCounts[i], sendCounts[i]);
     		}
	}
*/
	// if(myRank != 0)
		//sleep(5);
	 //lseek(file, displs[i], SEEK_SET);
   	 //for(i = 0; i < sendCounts[myRank]; i++)
    	 //{
       	//	read(file, &buf, 1);
       	//	}
       		printf("Reading in arxiv-metadata.txt...\n");
       		while(read(file, &buf, 1) > 0 && count != input)
		{
        		if(pos == 3)
        		{
        		        info[size[pos]] = tolower(buf);
        		}
       			else
       			{
            			info[size[pos]] = buf;
        		}
        		size[pos]++;
        		if((buf == ' ' || buf == '\n') && pos == 3)
       	 		{
            			//printf("%s ", info);
            			info[size[pos] - 1] = '\0';
           			InsertWord(&wordRoot, &arxiv, info, size[pos]);
           			memset(info, '\0', sizeof(info));
            			size[pos] = 0;
            			if(buf == '\n')
            			{
            				pos++;
            			}
        		}
			else if(buf == '\n')
			{
				if(pos == 0)
				{
					//Insert into ID
					printf("%s", info);
					info[size[pos] - 1] = '\0';
					arxiv.IDSize = size[pos];
					size[pos] = 0;
					arxiv.ID = (char*) calloc(arxiv.IDSize, sizeof(char));
					strcpy(arxiv.ID,info);
				}
				else if(pos == 1)
				{
					//Insert into Title
					//printf("%d - %s\n", size[pos], info);
					info[size[pos] - 1] = '\0';
					arxiv.titleSize = size[pos];
					size[pos] = 0;

					arxiv.title = (char*) calloc(arxiv.titleSize, sizeof(char));
					strcpy(arxiv.title, info);
				}
				else if(pos == 2)
				{
					//Insert into Author
					printf("%d - %s\n", size[pos], info);
					info[size[pos] - 1] = '\0';
					arxiv.authorSize = size[pos];
					size[pos] = 0;
	
					arxiv.author = (char*) calloc(arxiv.authorSize, sizeof(char));
					strcpy(arxiv.author, info);
	
					read(file, &buf, 1);
					read(file, &buf, 1);
				}
				else if(pos == 4)
				{
					//Insert into BST
				
					ArticleInsert(&root, &arxiv);
					memset(arxiv.ID, '\0', sizeof(size[0]));
					memset(arxiv.title, '\0', sizeof(size[1]));
					memset(arxiv.author, '\0', sizeof(size[2]));
				
					size[pos] = 0;
					pos = -1;
					count++;
				}
				pos++;
				memset(info, '\0', sizeof(info));
			}
		}
		//if(myRank == 0)
 		//{
        	int running = 1;
        	while(running)
		{
            		char str[128];
            		printf("Enter a word to search for (enter EXIT to quit): ");
            		scanf("%s",str);
            		if(strcmp(str, "EXIT") == 0)
            		{
                		running = 0;
           	 	}
            		else
            		{
                		printf("\nArticles with word '%s' include (but are not limited to): \n\n", str);
                		for(i = 0; i < strlen(str); i++)
                		{
                    			str[i] = tolower(str[i]);
                		}
                		wordSearch(&wordRoot, str, &root);
            		}
        	}
    	//}
	
	close(file);
	printf("File closed");
	//MPI_Finalize();
	return 0;
}
