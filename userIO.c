/*          File:   userIO.c                                         */
/*        Author:   Michael Nguyen                                   */
/*        Status:   Incomplete                                       */
/*    Created on:   5/31/13                                          */
/*  Last updated:   6/8/13                                          */

//Header Files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "userIO.h"
#include "team.h"
#include "bst.h"
#include "hash.h"
#include "stack.h"
#include "main.h"

//===================================================================
// Prints the main menu for the user
//===================================================================
void printMenu()
{
    printf("a. Add new company data\n");
    printf("d. Delete company data\n");
    printf("s. Search company\n");
    printf("h. List data in hash table sequence\n");
    printf("k. List data in key sequence\n");
    printf("t. Print indented tree\n");
    printf("w. Write data to file\n");
    printf("e. Print efficiency\n");
    printf("u. Undo delete\n");
    printf("q. Quit\n");
}
//===================================================================
// Prompts for the choice of the user and repeats if invalid
//===================================================================
char getChoice()
{
    char input = ' ';

    do
    {
        printf("Enter menu choice:");
        scanf(" %c", &input);
        if(tolower(input) != 'a' && tolower(input) != 'd' && tolower(input) != 's' && tolower(input) != 'h' && tolower(input) != 'k' &&
            tolower(input) != 't' && tolower(input) != 'w' && tolower(input) != 'e' && tolower(input) != 'u' && tolower(input) != 'q')
        {
              printf("Invalid input.\n");
        }
        FLUSH;
    }
    while(tolower(input) != 'a' && tolower(input) != 'd' && tolower(input) != 's' && tolower(input) != 'h' && tolower(input) != 'k' &&
            tolower(input) != 't' && tolower(input) != 'w' && tolower(input) != 'e' && tolower(input) != 'u' && tolower(input) != 'q');

    return input;
}
//////////////we can decide which one to use after everyone uploads their code////////////////

//===================================================================
// Prints the data in hashed sequence (as inputed into the hashed
// array)
//===================================================================
void printHashed(DATA_HEAD *data)
{
    //walks the array and prints in column format
    //index value                key field(i.e. name)
    int i;
    printf("Index value:    Key Field:\n\n");
    for (i = 0; i < data->arraySize; i++)
    {
        if (((data->pHash)[i]).status == 1) //status is filled, data exists at index
            printf("%-2d              %-10s\n", i, ((data->pHash)[i]).hashData->companyName);
    }
    printf("\n");
}
//===================================================================
// Prints the data in key sequence (alphabetically)
//===================================================================
void printKeySequence(DATA_HEAD *data)
{
    //walk the BST/AVL and print
    //key field(name)                  other fields (ints)
    printf("Company Name:             Revenue(Billion)    Profits(Million)    # of Employees\n");
    inOrder(data->pTree, processPrint);
    printf("\n");
}
//===================================================================
// Function for printing the company data of each company
//===================================================================
void processPrint (void *companyPtr)
{
    COMPANY *companyData;

    companyData = (COMPANY*)companyPtr;

    printf("%-30s %-10d     %-10d           %-10d\n", companyData->companyName, companyData->revenuePerBillion, companyData->profitPerMillion, companyData->numberOfEmployees);
}
//===================================================================
//
//===================================================================
void printTree(DATA_HEAD *data)
{
    inRankOrder(data->pTree, processIndentedTree);
    printf("\n");
}
//===================================================================
//
//===================================================================
void processIndentedTree(void *companyPtr, int level)
{
    int i;
    COMPANY *companyData;

    companyData = (COMPANY*)companyPtr;

    for (i = 1; i < level; i++)
        printf("  "); //format it for every level
    printf("%d. %-20s\n", level, companyData->companyName);
}
//===================================================================
// Allocates new memory for a string
//===================================================================
char* allocateString(char str[])
{
    char *strPtr;

    strPtr = (char *)malloc(strlen(str) + 1);
    if(strPtr != NULL)
        strcpy(strPtr, str);
    else
    {
        printf("Not enough memory, exiting program...\n");
        exit(1);
    }

    return strPtr;
}
//===================================================================
// Prompts for a new company to insert.  If already exists, return
// error. If does not exist, ask user for all information for company
// and inserts into the BST and hashed array
//===================================================================
void insertCompany(DATA_HEAD *data)
{
    COMPANY *newCompany;
    int len;
    char name[MAX_CHARS];

    printf("Enter name of company: ");
    fgets(name, MAX_CHARS, stdin);
    len = strlen(name);
    if(name[len-1] == '\n' || name[len-1]=='\r')
            name[len-1]='\0'; // change '\n' to '\0'

    newCompany = (COMPANY*)malloc(sizeof(COMPANY));
    if(newCompany == NULL)
    {
        printf("Not enough memory, exiting program...\n");
        exit(1);
    }
    newCompany->companyName = allocateString(name);
    //if search tree function returns succes
    if(!searchHash(data, name, newCompany)) //company name has not been found, therefore does not exist in tree.
    {
        printf("Enter revenue per billion: ");
        scanf("%d", &(newCompany->revenuePerBillion));
        printf("Enter profits per million: ");
        scanf("%d", &(newCompany->profitPerMillion));
        printf("Enter number of employees: ");
        scanf("%d", &(newCompany->numberOfEmployees));
        insertManager(data, newCompany);
        (data->count)++;
        printf("%s added!\n", newCompany->companyName);
        printf("\nNumber Of Data Records: %d\n\n", data->count);
    }
    else
        printf("ERROR: DUPLICATE DATA\n");

    printf("\n");
}
//===================================================================
// Deletes a company from the BST/Hashed array (if it exists)
//===================================================================
void deleteCompany(DATA_HEAD *data)
{
    COMPANY *companyPtr;
    COMPANY *deletedPtr;
    int len;
    char name[MAX_CHARS];

    printf("Enter name of company: ");
    fgets(name, MAX_CHARS, stdin);
    len = strlen(name);
    if(name[len-1] == '\n' || name[len-1]=='\r')
            name[len-1]='\0'; // change '\n' to '\0'

    companyPtr = (COMPANY*)malloc(sizeof(COMPANY));
    if(companyPtr == NULL)
    {
        printf("Not enough memory, exiting program...\n");
        exit(1);
    }
    companyPtr->companyName = allocateString(name);

    deletedPtr = deleteManager(data, companyPtr);
    if(deletedPtr)
    {
        (data->count)--;
        printf("Deleted record: %-30s\n", deletedPtr->companyName);
        printf("\nNumber Of Data Records: %d\n", data->count);
        pushStack(data->pStack, deletedPtr);
    }
    else
        printf("Company is not in the list.\n");

    free(companyPtr->companyName);
    free(companyPtr);
    printf("\n");
}
//===================================================================
// Searches the hash for a company and returns information to the user
//===================================================================

void search(DATA_HEAD *data)
{
    COMPANY companyPtr;
    int len;
    char name[MAX_CHARS];
    int success = 0;

    printf("Enter name of company: ");
    fgets(name, MAX_CHARS, stdin);
    len = strlen(name);

    //Chanages \n or \r (depending on OS) to \0
    if(name[len-1] == '\n' || name[len-1]=='\r')
        name[len-1]='\0';

    //if search tree function returns succes
    success = searchHash(data, name, &companyPtr);
    if(success == 1)
    {
        printf("Company Name:           Revenue(Billion)   Profits(Million)    # of Employees\n");
        printf("%-30s%d               %d             %d\n", companyPtr.companyName, companyPtr.revenuePerBillion, companyPtr.profitPerMillion, companyPtr.numberOfEmployees);
    }
    else
        printf("Company is not in the list.\n");

    printf("\n");
}

//===================================================================
// Function to undo a delete of a company.  Does not allow to undo
// delete of a company that is already in the BST
//===================================================================
void undoDelete(DATA_HEAD *data)
{
    COMPANY* companyNode;
    int isDuplicate;

    //If there is something in the stack
    if(!emptyStack(data->pStack))
    {
        companyNode = (COMPANY*)popStack(data->pStack);

        //Check to see if there is duplicate
        isDuplicate = searchHash(data, companyNode->companyName, companyNode);

        //If there is, print and error, else, insert into the hashed array
        if(isDuplicate == 1)
        {
            printf("ERROR: DUPLICATE DATA\n");
            printf("%s has already been entered into the system\n", companyNode->companyName);
            free(companyNode);
        }
        else
        {
            printf("%s reinserted into the system\n", companyNode->companyName);
            insertManager(data, companyNode);
            updateCollision(data);
            (data->count)++;
            printf("\nNumber Of Data Records: %d\n", data->count);
        }
    }
    else
        printf("Nothing to undo.\n"); //nothing in the stack

    printf("\n");
}
