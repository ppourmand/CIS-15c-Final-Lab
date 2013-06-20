/*      	File:	hash.c						*/
/*	      Author:	Keith Ngo					*/
/*	  Created on:	05/26/13					*/
/*	Last updated:	06/16/13					*/

//Hash algorithm and functions implementation file
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "team.h"
#include "hash.h"

//for Visual C++ warnings
//#pragma warning(disable:4996)

/* Hash function produces unique index			*/
/* Pre	   key is the company name				*/
/*		   size is size of hashed array         */
/* Post	   nothing								*/
/* Return  unique index							*/
int hash(char *key, int size)
{
	int sumOfKey = 0, count = -1, index = -1;
	int length = strlen(key);

	//Sum ASCII values of data
	for(count = 0; count < length; count++)
	{
		//ignore vowels
		if(key[count] != 'a' && key[count] != 'e' && key[count] != 'i' &&
			key[count] != 'o' && key[count] != 'u' && key[count] != 'A' &&
			key[count] != 'E' && key[count] != 'I' && key[count] != 'O' &&
			key[count] != 'U')
		{
			sumOfKey = key[count] + (sumOfKey % size);
		}
	}

	//Modulo division
	index = sumOfKey % size;

	return index;
}


/* Collision resolution is open addressing - key offset */
/* Pre	   key is the company name						*/
/*		   index is current index						*/
/*		   size is size of hashed array					*/
/* Post	   nothing										*/
/* Return  new unique index								*/
int collision(char *key, int index, int size)
{
	int sumOfKey = 0, count = -1, newIndex = -1, length = strlen(key);

	//Sum ASCII values of data
	for(count = 0; count < length; count++)
		sumOfKey += *(key + count);

	//open addressing, key offset method
	//new index = current index + (key / array size)
	newIndex = index + (sumOfKey / size);

	//Check index to be within valid range
	while(newIndex > (size - 1))
		newIndex %= size;

	return newIndex;
}

/* Updates collision count after deletion					  */
/* Pre	   dataNode is head node with pointer to hashed array */
/* Post	   All collision counts are updated					  */
/* Return  nothing											  */
void updateCollision(DATA_HEAD *dataNode)
{
	int count = -1, count2 = -1, index = -1;
	int updateCount = -1; //Used to count new collision count, ignoring deleted indexes

	//Traverse through hashed array to update collision counts
	for(count = 0; count < dataNode->arraySize; count++)
	{
		if(dataNode->pHash[count].numOfCollisions > 0)
		{
			updateCount = 0;
			index = hash(dataNode->pHash[count].hashData->companyName, dataNode->arraySize);
			if(dataNode->pHash[index].status == 1)
			{
				//exit loop if data is reached, else increment collision count
				if(strcasecmp(dataNode->pHash[count].hashData->companyName, dataNode->pHash[index].hashData->companyName) == 0)
					break;
				else
					updateCount++;
			}
			//loop used to count collision
			for(count2 = 1; count2 < dataNode->pHash[count].numOfProbes; count2++)
			{
				index = collision(dataNode->pHash[count].hashData->companyName, index, dataNode->arraySize);
				if(dataNode->pHash[index].status == 1)
				{
					//exit loop if data is reached, else increment collision count
					if(strcasecmp(dataNode->pHash[count].hashData->companyName, dataNode->pHash[index].hashData->companyName) == 0)
						break;
					else
						updateCount++;
				}
			}

			//update collision count for index to exclude deleted indexes
			dataNode->pHash[count].numOfCollisions = updateCount;
		}
	}
}


/* Insert function for hashed array							*/
/* Pre	   dataNode is head node with pointer to hash array	*/
/*		   dataInsert is a struct COMPANY data				*/
/* Post	   hashed array points to dataInsert				*/
/* Return  1 for successful									*/
/*		   0 for unsuccessful								*/
int insertHash(DATA_HEAD *dataNode, COMPANY *dataInsert)
{
	int index = -1, tempStatus = -1;
	int collisionCount = 0;//Counts number of collision
	int probe = 0;//Counts number of probes until data is inserted

	index = hash(dataInsert->companyName, dataNode->arraySize);
	probe++;

	//If index is empty or deleted, insert data
	if(dataNode->pHash[index].status == 0 || dataNode->pHash[index].status == 2)
	{
		//hold status before changes
		tempStatus = dataNode->pHash[index].status;

		//Point to data
		dataNode->pHash[index].hashData = dataInsert;

		//Set status to 1 for filled
		//Set number of probes required
		dataNode->pHash[index].status = 1;
		dataNode->pHash[index].numOfProbes = probe;

		//update collision
		if(tempStatus == 2)
			updateCollision(dataNode);

	}
	//If index is filled, run collision resolution to find an empty index
	else
	{
		while(dataNode->pHash[index].status == 1 && probe < MAX_PROBE)
		{
			//Increment collision count
			collisionCount++;
			index = collision(dataInsert->companyName, index, dataNode->arraySize);
			probe++;
		}
		if(dataNode->pHash[index].status == 0 || dataNode->pHash[index].status == 2)
		{
			//hold status before changes
			tempStatus = dataNode->pHash[index].status;

			//Point to data
			dataNode->pHash[index].hashData = dataInsert;

			//Set status to filled
			dataNode->pHash[index].status = 1;

			//Set number of collisions
			dataNode->pHash[index].numOfCollisions = collisionCount;

			//Set number of probes required
			dataNode->pHash[index].numOfProbes = probe;

			//update collision
			if(tempStatus == 2)
				updateCollision(dataNode);
		}
		else
		{
			//0 for unsuccessful, error handling
			return 0;
		}
	}
	//1 for successul insert
	//return 1;
	return 1;
}


/* Delete function for hashed array						*/
/* Pre	   hashNode is dynamically allocated 			*/
/*		   key is the company name						*/
/* Post	   data is deleted from hashed array			*/
/* Return  1 for successful								*/
/*		   0 for not found								*/
int deleteHash(DATA_HEAD *dataNode, char *key)
{
	int index = -1, probe = 0;

	index = hash(key, dataNode->arraySize);
	probe++;

	//delete fails if index is empty
	if(dataNode->pHash[index].status == 0)
		return 0;

	if(dataNode->pHash[index].status == 1 && strcasecmp(dataNode->pHash[index].hashData->companyName, key) == 0)
	{
		//Set pointer to NULL
		dataNode->pHash[index].hashData = NULL;

		//Set status to deleted
		//Set collision count to 0
		dataNode->pHash[index].status = 2;
		dataNode->pHash[index].numOfCollisions = 0;
		dataNode->pHash[index].numOfProbes = 0;

		//Update collision count for all indexes
		updateCollision(dataNode);
	}
	else
	{
		while(dataNode->pHash[index].status != 0 || (dataNode->pHash[index].status == 2 && probe < MAX_PROBE))
		{
			index = collision(key, index, dataNode->arraySize);
			probe++;

			if(dataNode->pHash[index].status == 1 && strcasecmp(dataNode->pHash[index].hashData->companyName, key) == 0)
			{

				//Set pointer to NULL
				dataNode->pHash[index].hashData = NULL;

				//Set status to deleted
				//Set collision count to 0
				dataNode->pHash[index].status = 2;
				dataNode->pHash[index].numOfCollisions = 0;
				dataNode->pHash[index].numOfProbes = 0;

				//Update collision count for all indexes
				updateCollision(dataNode);

				//exit while loop
				break;
			}
			if(dataNode->pHash[index].status == 0 || probe == (MAX_PROBE -1))
			{
				//delete unsuccessful, no data found
				return 0;
			}
		}
	}

	//delete successful
	return 1;
}


/* Search function for hashed array					   		  */
/* Pre	   dataNode is head node with pointer to hashed array */
/*		   key is the company name							  */
/*		   returnData is data pointed to					  */
/* Post	   nothing											  */
/* Return  1 for successful									  */
/*		   0 for not found									  */
int searchHash(DATA_HEAD *dataNode, char *key, COMPANY *returnData)
{
	int index = -1, probe = 0;

	index = hash(key, dataNode->arraySize);
	probe++;

	//search fails if index is empty
	if(dataNode->pHash[index].status == 0)
		return 0;

	if(dataNode->pHash[index].status == 1 && strcasecmp(dataNode->pHash[index].hashData->companyName, key) == 0)
	{
		//return data pointed to
		*returnData = *(dataNode->pHash[index].hashData);
	}
	else
	{
		while(dataNode->pHash[index].status != 0 || (dataNode->pHash[index].status == 2 && probe < MAX_PROBE))
		{
			index = collision(key, index, dataNode->arraySize);
			probe++;
			if(dataNode->pHash[index].status == 1 && strcasecmp(dataNode->pHash[index].hashData->companyName, key) == 0)
			{
				//return data pointed to
				*returnData =  *(dataNode->pHash[index].hashData);

				//exit while loop
				break;
			}
			if(dataNode->pHash[index].status == 0 || probe == (MAX_PROBE -1))
			{
				//search unsuccessful, data not found
				return 0;
			}
		}
	}
	//search successful, data is returned
	return 1;
}


/* Print function for hashed array efficiency				  */
/* (Load factor, number of data records have 				  */
/* collision, and longest collision path)				  	  */
/* Pre	   dataNode is head node with pointer to hashed array */
/* Post	   nothing											  */
/* Return  nothing											  */
void printEfficiency(DATA_HEAD *dataNode)
{
	int count = -1, count2 = -1, index = -1;
	int collisionIndex = -1; //keep track of index with highest collision count
	double loadFactor = -1; //holds value for load factor
	int numOfCollisions = 0; //sum of all indexes with collision
	int numOfElements = 0; //sum of all data in prime area
	int longestCollision = 0; //keep track of longest collision count

	//Check for more than one longest collision path
	//-1 for false, 1 for true
	int multiple = -1;

	//Loop through hashed array to find number of
	//elements with data and longest collision path
	for(count = 0; count < dataNode->arraySize; count++)
	{
		//Count number of elements with data
		if(dataNode->pHash[count].status == 1)
			numOfElements++;

		//Count collisions and keep track of longest collision path
		if(dataNode->pHash[count].numOfCollisions > 0)
		{
			//Increment number of data records with collision
			numOfCollisions++;

			//Check for longest collision path
			if(dataNode->pHash[count].numOfCollisions > longestCollision ||
				dataNode->pHash[count].numOfCollisions == longestCollision)
			{
				//Update longest collision path
				if(dataNode->pHash[count].numOfCollisions > longestCollision)
				{
					longestCollision = dataNode->pHash[count].numOfCollisions;

					//Keep track of the index with longest collision path
					collisionIndex = count;
					multiple = -1;
				}
				//Flag if more than one longest collision path exists
				else
				{
					multiple = 1;
				}
			}
		}
	}

	//Calculate load factor
	loadFactor = ((double)numOfElements / (double)dataNode->arraySize) * 100;

	printf("**************** EFFICIENCY: ****************\n\n");
	printf("Load factor: %.2f%%\n", loadFactor);
	printf("Number of data records with collision: %d\n", numOfCollisions);
	printf("Longest collision path: %d\n", longestCollision);
	printf("Output longest collision path(s):\n");

	//Print longest collision path without traversing through hashed array
	if(multiple == -1)
	{
		printf("\n\nKEY: %s\n\n", dataNode->pHash[collisionIndex].hashData->companyName);

		//print home address
		printf(" (Home Address) => ");
		index = hash(dataNode->pHash[collisionIndex].hashData->companyName, dataNode->arraySize);
		if(dataNode->pHash[index].status == 1)
			printf("[%2d] %s", index, dataNode->pHash[index].hashData->companyName);
		else
			printf("<DELETED>");

		//print overflow
		printf("\n(Overflow Area) => ");
		for(count = 1; count < dataNode->pHash[collisionIndex].numOfProbes; count++)
		{
			index = collision(dataNode->pHash[collisionIndex].hashData->companyName, index, dataNode->arraySize);
			if(dataNode->pHash[index].status == 1)
				printf("[%2d] %s", index, dataNode->pHash[index].hashData->companyName);
			else
				printf("<DELETED>");

			//exit loop if maximum probe has been reached
				if(count + 1 < dataNode->pHash[collisionIndex].numOfProbes)
					printf("\n\t\t=> ");
		}
		printf("\n");
	}
	//Print all longest collision path if more than one longest
	//traverses through hashed array to find all longest paths
	else
	{
		//Loop through hashed array to find and print
		//all of the longest collision paths
		for(count = 0; count < dataNode->arraySize; count++)
		{
			if(dataNode->pHash[count].numOfCollisions == longestCollision)
			{
				printf("\n\nKEY: %s\n\n", dataNode->pHash[count].hashData->companyName);

				//Print home address
				printf(" (Home Address) => ");
				index = hash(dataNode->pHash[count].hashData->companyName, dataNode->arraySize);
				if(dataNode->pHash[index].status == 1)
					printf("[%2d] %s", index, dataNode->pHash[index].hashData->companyName);
				else
					printf("<DELETED>");

				//Print overflow
				printf("\n(Overflow Area) => ");
				for(count2 = 1; count2 < dataNode->pHash[count].numOfProbes; count2++)
				{
					index = collision(dataNode->pHash[count].hashData->companyName, index, dataNode->arraySize);
					if(dataNode->pHash[index].status == 1)
						printf("[%2d] %s", index, dataNode->pHash[index].hashData->companyName);
					else
						printf("<DELETED>");

					//exit loop if maximum probe has been reached
					if(count2 + 1 < dataNode->pHash[count].numOfProbes)
					printf("\n\t\t=> ");
				}
				printf("\n");
			}
		}
	}
	printf("\n*********************************************\n\n");
}
