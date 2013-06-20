
/*      	File:	fileIO.c									*/
/*	      Author:	Pasha and Jeanine Fallen Bailey             */
/*   Assisted by:  	Michael Nguyen              				*/
/*        Status:   Complete									*/
/*	  Created on:	5/31/13										*/
/*	Last updated:	6/17/13										*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "userIO.h"
#include "fileIO.h"
#include "team.h"
#include "bst.h"
#include "stack.h"
#include "hash.h"

//===================================================================
// Returns the number of companies in the input file
//===================================================================
int getArrSize(FILE* in)
{
    int size = 0;
    char temp[MAX_CHARS];

    while(fgets(temp, MAX_CHARS, in) != NULL)
        size++;

    fclose(in);
    return size * 2; //return double the array size to fit in new user records
}
//===================================================================
// Reads in the data from a file and inserts into BST and hashed
// array.
//===================================================================
void readInFile(DATA_HEAD *data)
{
    FILE *dataFile;
    COMPANY *companyNode;
    char filename[MAX_CHARS], tmpName[MAX_CHARS];
    char ch;
    int tmpRev, tmpProfit, tmpNumEmployee;
    int i = 0, isDuplicate, len, size;

    do
    {
        printf("Please enter a filename [enter for default]:");
        fgets(filename, MAX_CHARS, stdin);
        if(filename[0] == '\n')
            strcpy(filename, default_file);
        else
        {
            //flush new line
            len = strlen(filename);
            if( filename[len-1] == '\n' || filename[len-1]=='\r' )
                filename[len-1]='\0'; // change '\n' to '\0'
            else
            { // no '\n' read, so flush to '\n'
                while( (ch=getchar()) != '\n' && ch != '\r' )
                {
                    ;
                }
            }
        }
        dataFile = fopen(filename, "r");
    }
    while(dataFile == NULL);

    //Creates structures
    data->pTree  = createBST(myStringCompare);
    data->pStack = createStack();

    size = getArrSize(dataFile);
    //need to reopen connection
    dataFile = fopen(filename, "r");

    data->arraySize = size;
    data->count = 0;
    data->pHash = (HASH*)malloc(sizeof(DATA_HEAD) * data->arraySize);
    //initialize hashed array
    for(i = 0; i < data->arraySize; i++)
    {
        data->pHash[i].status = 0;
        data->pHash[i].numOfCollisions = 0;
        data->pHash[i].numOfProbes = 0;
        data->pHash[i].hashData = NULL;
    }
    //Reads in, parses, mallocs, assigns
    while(fscanf(dataFile, " %[^,],%d,%d,%d[^\n]", tmpName, &tmpRev, &tmpProfit, &tmpNumEmployee) != EOF)
    {
        companyNode = (COMPANY*)malloc(sizeof(COMPANY));

        //Checks to see if allocated properly
        if(companyNode == NULL){exit(1);}

        companyNode->companyName = (char*)malloc(strlen(tmpName) + 1);

        //Checks to see if allocated properly
        if(companyNode->companyName == NULL){exit(1);}

        strcpy(companyNode->companyName, tmpName);
        companyNode->numberOfEmployees = tmpNumEmployee;
        companyNode->revenuePerBillion = tmpRev;
        companyNode->profitPerMillion = tmpProfit;

        //Inserts company data (name, revenue, profit, employees) into the BST
        //If duplicate, print an error
        isDuplicate = searchHash(data, tmpName, companyNode);
        if(isDuplicate == 1)
            printf("ERROR: DUPLICATE DATA\n");
        else
        {
            insertHash(data, companyNode);
            insertBST(data->pTree, companyNode);
            data->count++;
        }
    }
    printf("\nNumber Of Data Records read in: %d\n\n", data->count);
    fclose(dataFile);
}

//===================================================================
// Compare function for BST
//===================================================================
int myStringCompare(void* pcompany1, void* pcompany2)
{
    //strcasecmp is case insensitive compare
    return strcasecmp( ((COMPANY*)pcompany1)->companyName, ((COMPANY*)pcompany2)->companyName);
}

//===================================================================
// Cleans up and frees all data
//===================================================================
void cleanupData(DATA_HEAD *data)
{
	destroyBST(data->pTree, freeBST);
    destroyStack(data->pStack);
    free(data->pHash);
    free(data);
}
//===================================================================
// Frees BST nodes
//===================================================================
void freeBST(void* companyData)
{
    free(((COMPANY*)companyData)->companyName);
    free((COMPANY*)companyData);
}

//===================================================================
// Writes to output file and calls function to clear out the stack
//===================================================================
void saveToFile(DATA_HEAD* data)
{
	COMPANY* temp;
    FILE* outputFile;
    char filename[MAX_CHARS];
    int i, len;
    char ch;

    do
    {
        printf("Please enter a filename for output file [enter for default]:");
        fgets(filename, MAX_CHARS, stdin);
        if(filename[0] == '\n')
            strcpy(filename, "out.txt");
        else
        {
            //flush new line
            len = strlen(filename);
            if( filename[len-1] == '\n' || filename[len-1]=='\r' )
                filename[len-1]='\0'; // change '\n' to '\0'
            else
            { // no '\n' read, so flush to '\n'
                while( (ch=getchar()) != '\n' && ch != '\r' )
                {
                    ;
                }
            }
        }

        outputFile = fopen(filename, "w");
    }
    while(outputFile == NULL);

    //Writes to output file in hashed sequence
    printf("Writing to %s...\n", filename);
    for (i = 0; i < data->arraySize; i++)
    {
        if(data->pHash[i].status == 1) //status is filled, data exists at index
            fprintf(outputFile, "%s,%d,%d,%d\n", data->pHash[i].hashData->companyName, data->pHash[i].hashData->revenuePerBillion, data->pHash[i].hashData->profitPerMillion, data->pHash[i].hashData->numberOfEmployees);
    }
	//need to free the company name as well as the company
	//modifying stack ADT does not work since this is specific to this program
	while(!emptyStack(data->pStack))
	{
		temp = (COMPANY*)popStack(data->pStack); //pop everything from the stack
		free(temp->companyName); //free company name and then company
		free(temp);
	}
	data->pStack->count = 0; //reset stack
	data->pStack->top = NULL;

    fclose(outputFile);
	printf("\n");
}
