//----------------------------------------------------------------------------------
//        File: team.h
//      Author: Pasha Pourmand
//      Status: Incomplete - In Progress
// Last edited: 2013/05/28
//----------------------------------------------------------------------------------

#ifndef TEAM_H
#define TEAM_H

#define SIZE 100
#define MAX_CHARS 100
#define default_file "CompanyData.txt"
#define DEFAULT_OUT "output.txt"
#define FLUSH while(getchar() != '\n')

//Structure definition for data
typedef struct{
    char *companyName;
    int revenuePerBillion;
    int profitPerMillion;
    int numberOfEmployees;
}COMPANY;

/* bst node structure */
typedef struct bstNode
{
    void * dataPtr;
    struct bstNode * left;
    struct bstNode * right;
}BST_NODE;

/* bst header structure */
typedef struct
{
    int count;
    int (*compare) (void * a, void * b);
    BST_NODE * root;
}BST;

//Hashed array structure
typedef struct
{
    int status; //use 0 for empty, 1 for filled, 2 for deleted
    int numOfCollisions;
    int numOfProbes;
    COMPANY* hashData;
}HASH;

// stack node
typedef struct stackNode
{
    void *dataPtr;
    struct stackNode *link;
}STACK_NODE;

//STACK head node structure
typedef struct
{
    int count;
    STACK_NODE *top;
}STACK;

//Structure Definition for head node
typedef struct{
    int count;
    int arraySize;
    HASH *pHash;
    BST *pTree;
    STACK *pStack;
}DATA_HEAD;

#endif
