/*      	File:	bst.h										*/
/*	      Author:	Jeanine Fallen Bailey						*/
/*        Status:   ?											*/
/*	  Created on:	5/31/13										*/
/*	Last updated:	5/31/13										*/

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "team.h"

/* Allocates memory for a bst head node		*/
/* Pre	   nothing                          */
/* Post	   head is allocated and initialized*/
/* Return  head's address if successful     */
/*         null if overflow                 */
BST *createBST (int (*compare) (void * a, void * b) );


/* Inserts data into a bst				*/
/* Pre	   bst has been created			*/
/* Post	   data is inserted				*/
/* Return  1 if successful				*/
/*	       0 if overflow				*/
/*	      -1 if duplicate               */
int insertBST (BST *bst, void *dataInPtr);


/* internal insert function - uses recursion	*/
/* to insert new data at a leaf	node			*/
/* Pre		bst has been created				*/
/*			root pointer points to current root */
/*			newptr points to new data node		*/
/*			dupcheck is set to 1				*/
/* Post		data has been inserted				*/
/* 			or dupcheck set to 0				*/
/* Return	pointer to new root					*/
BST_NODE * _insert(BST * bst, BST_NODE * root, BST_NODE * newptr, int * dupcheck);


/* Deletes data from the bst	             */
/* Pre	   bst has been created		         */
/*		   dltKey points to the target data  */
/* Post    bst node is deleted and recycled  */
/*		   data is returned to the user		 */
/* Return  1 if successful			         */
/*	       0 if not found	                 */
int deleteBST (BST * bst, void * dltKey,  void ** retptr);



/* internal delete function - uses recursion to		*/
/* delete a data node from the bst					*/
/* Pre		bst has been created					*/
/*			root points to current root				*/
/*			dltKey points to target data			*/
/*			success is a reference to boolean for	*/
/*			 success in deletion					*/
/* Post		delete data is returned to the user		*/
/*			bst node is delete and recycled			*/
/* Return	root pointer							*/
BST_NODE * _delete (BST * bst, BST_NODE * root, void * dltKey,
					int * success,  void ** retptr);



/* Retrieves data in the bst						*/
/* Pre		bst is created							*/
/*			keyPtr is pointer to key of target data	*/
/* Post		data is found							*/
/* Return	pointer to data found if successful		*/
/*			null if not found		                */
void * retrieveBST (BST * bst, void * keyPtr);


/* internal search function - uses recursion to look	*/
/* matched data											*/
/* Pre		bst points to head node						*/
/*			keyPtr points to target data				*/
/*			root points to current root node			*/
/* Post		found data pointer returned					*/
/* Return	found data pointer							*/
/*			NUll if not found							*/
void * _retrieve(BST * bst, void * keyPtr, BST_NODE * root);


/* Inorder (RNL) traverse the bst						*/
/* Pre		bst has been created						*/
/*			process function pointer points to function */
/*			  to function that processes each node		*/
/* Post		all nodes have been processed				*/
/* Return	nothing										*/
void inOrder (BST * bst, void (*process) (void * dataPtr) );


/* internal inorder traverse - uses recursion to traverse	*/
/* and process each node									*/
/* Pre		root is pointer to current root					*/
/*			process is pointer to process function			*/
/* Post		all nodes have been processed					*/
/* Return	nothing											*/
void _traverse (BST_NODE * root, void (*process) (void * dataPtr) );

/* InRankOrder traverse the bst	in rank order			*/
/* Pre		bst has been created						*/
/*			process function pointer points to function */
/*			  to function that processes each node		*/
/* Post		all nodes have been processed				*/
/* Return	nothing										*/
void inRankOrder (BST * bst, void (*process) (void * dataPtr, int level));

/* internal hierarchical rank order traverse - uses recursion to traverse	*/ //needs a special process function
/* and process each node									*/
/* Pre		root is pointer to current root					*/
/*			process is pointer to process function			*/
/* Post		all nodes have been processed					*/
/* Return	nothing											*/
void _rank (BST_NODE * root, void (*process) (void * dataPtr, int level), int level);

/* Checks to see if the bst is empty		*/
/* Pre	   bst has been created			    */
/* Return  1 if empty                       */
/*	       0 if bst has data				*/
int emptyBST (BST * bst);


/* Checks to see if bst is full.			*/
/* which means memory cannot be allocated   */
/* for another node                         */
/* Pre	   bst has been created				*/
/* Return  1 if full                        */
/*	       0 if there is memory             */
int fullBST (BST * bst);


/* Returns the number of elements in the bst	*/
/* Pre	   bst has been created				    */
/* Return  bst count							*/
int BSTCount (BST * bst);


/* Deletes all data from a bst and recycles		*/
/* its memory, then deletes and recycles bst	*/
/* head pointer                                 */
/* Pre	   bst is created						*/
/* Post	   all data have been deleted and       */
/*             recycled                         */
/* Return  null pointer                         */
BST *destroyBST (BST * bst, void (*freeFcn) (void * dataPtr));


/* internal destroy function - uses recursion to	*/
/* free all memory for data and tree node			*/
/* Pre		root is pointer to current root			*/
/* Post		all data and nodes are freed			*/
/* Return	nothing									*/
void _destroy(BST_NODE * root, void (*freeFcn) (void * dataPtr));



#ifdef __cplusplus
}
#endif
