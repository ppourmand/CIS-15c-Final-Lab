/*      	File:	main.c										*/
/*	      Author:	Pasha Pourmand								*/
/*        Status:   Incomplete									*/
/*	  Created on:	5/27/13										*/
/*	Last updated:	6/2/13										*/

//Header Files
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "stack.h"
#include "team.h"
#include "userIO.h"
#include "hash.h"
#include "fileIO.h"
#include "main.h"

// in the global area
//// memory leak check
//#ifdef _MSC_VER
//#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
//#endif

int main()
{

	 //head node points to everything so we don't need to deal with the other structs
    DATA_HEAD* node;

    //allocate head node
    node = malloc(sizeof(DATA_HEAD));

    //Checks to see if memory allocated properly
    if(!node){exit(1);}

    //Reads in the file and inputs into BST and Hashed Array
	readInFile(node);

	//Prints the user Menu
	menuOptions(node);

	//Saves to a file, must clear out the stack (inside of the function)
	saveToFile(node);

	//Clears all memory
	cleanupData(node);
	// at the end of main, before return
// check if there's memory leak
/*printf("\nMemory Check:\n");
#ifdef _MSC_VER
   printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
#endif
// end of program
system("pause");
	*/return 0;
}

void menuOptions(DATA_HEAD *node)
{
	char userChoice;

    do
    {
        printMenu();
        userChoice = getChoice();

        //Manager for all user input choices
        switch(userChoice)
        {
            case 'a':
                insertCompany(node);
                break;
            case 'd':
                deleteCompany(node);
                break;
            case 's':
                search(node);
                break;
            case 'h':
                printHashed(node);
                break;
            case 'k':
                printKeySequence(node);
                break;
            case 't':
                printTree(node);
                break;
            case 'w':
                saveToFile(node);
                break;
            case 'e':
                printEfficiency(node);
                break;
            case 'u':
                undoDelete(node);
                break;
            default:
                return;
        }
    }
    while(userChoice != 'q');
}

//===================================================================
// Manager for insertion of the BST and hashed array
//===================================================================
void insertManager(DATA_HEAD *data, COMPANY* newCompany)
{
    insertBST(data->pTree, newCompany);
    insertHash(data, newCompany);
}
COMPANY* deleteManager(DATA_HEAD *data, COMPANY* companyPtr)
{
    COMPANY* deletedPtr;

    if(deleteBST(data->pTree, companyPtr, (void**)&deletedPtr), deleteHash(data, companyPtr->companyName))
        return deletedPtr;
    else
        return NULL;
}
