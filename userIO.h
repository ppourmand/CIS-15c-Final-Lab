/*          File:   userIO.h                                    */
/*        Author:   Michael Nguyen                              */
/*        Status:   Incomplete                                  */
/*    Created on:   5/28/13                                     */
/*  Last updated:   5/28/13                                     */

#ifndef USERIO_H
#define USERIO_H

#include "team.h"

//prints menu
void printMenu();
//get user selection
char getChoice();

/////////////////////////printing functions/////////////////////////////
//print the data in hash table sequence
void printHashed(DATA_HEAD *data);
//print the data in key sequence
void printKeySequence(DATA_HEAD *data);
//print the indented tree
void printTree(DATA_HEAD *data);
//process function for regular tree
void processPrint (void *companyData);
//process function for indented tree
void processIndentedTree(void *companyPtr, int level);
////////////////////////////////////////////////////////////////////////
//function to allocate memory to a new string
char* allocateString(char str[]);
//insert function
void insertCompany(DATA_HEAD *data);
//delete function
void deleteCompany(DATA_HEAD *data);
//search function
//BST search function
void search(DATA_HEAD *data);
//Undo delete
void undoDelete(DATA_HEAD *data);

#endif // USERIO_H
