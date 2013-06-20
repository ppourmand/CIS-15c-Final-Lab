/*      	File:	hash.h										*/
/*	      Author:	Keith Ngo									*/
/*	  Created on:	05/26/13									*/
/*	Last updated:   06/16/13									*/

//Hashing algorithm and functions header file
#ifndef HASH_H
#define HASH_H
#define MAX_PROBE 100

/* Hash function produces unique index			*/
/* Pre	   key is the company name				*/
/*		   size is size of hashed array         */
/* Post	   nothing								*/
/* Return  unique index							*/
int hash(char *key, int size);


/* Collision resolution is open addressing - key offset */
/* Pre	   key is the company name						*/
/*		   index is current index						*/
/*		   size is size of hashed array					*/
/* Post	   nothing										*/
/* Return  new unique index								*/
int collision(char *key, int index, int size);


/* Updates collision count after deletion					  */
/* Pre	   dataNode is head node with pointer to hashed array */
/* Post	   All collision counts are updated					  */
/* Return  nothing											  */
void updateCollision(DATA_HEAD *dataNode);


/* Insert function for hashed array							*/
/* Pre	   dataNode is head node with pointer to hash array	*/
/*		   dataInsert is a struct COMPANY data				*/
/* Post	   hashed array points to dataInsert				*/
/* Return  1 for successful									*/
/*		   0 for unsuccessful								*/
int insertHash(DATA_HEAD *dataNode, COMPANY *dataInsert);


/* Delete function for hashed array						*/
/* Pre	   hashNode is dynamically allocated 			*/
/*		   key is the company name						*/
/* Post	   data is deleted from hashed array			*/
/* Return  1 for successful								*/
/*		   0 for not found								*/
int deleteHash(DATA_HEAD *dataNode, char *key);


/* Search function for hashed array					   		  */
/* Pre	   dataNode is head node with pointer to hashed array */
/*		   key is the company name							  */
/*		   returnData is data pointed to					  */
/* Post	   nothing											  */
/* Return  1 for successful									  */
/*		   0 for not found									  */
int searchHash(DATA_HEAD *dataNode, char *key, COMPANY *returnData);


/* Print function for hashed array efficiency				  */
/* (Load factor, number of data records have 				  */
/* collision, and longest collision path)				  	  */
/* Pre	   dataNode is head node with pointer to hashed array */
/* Post	   nothing											  */
/* Return  nothing											  */
void printEfficiency(DATA_HEAD *dataNode);

#endif//HASH_H
