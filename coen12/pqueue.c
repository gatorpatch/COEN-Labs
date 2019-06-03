/*
*   Spencer Goles   COEN 12    27 Febuary 2019
*   Description: This program is a priority queue 
*
*/

//Preprocessors
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pqueue.h"

//Defined constant and macros
#define START 10
#define p(x) (((x)-1)/2)
#define l(x) (((x)*2)+1)
#define r(x) (((x)*2)+2)

typedef struct pqueue 
{
	int count;
	int length;
	void **data;
	int (*compare) ();
}PQ;

//Function creates and initializes que
//Big-O: O(1)
PQ *createQueue(int (*compare)())
{
	PQ *pq;
	pq = malloc(sizeof(PQ));
	assert(pq != NULL);
	pq->count = 0;
	pq->length = START;
	pq->compare = compare;
	assert(compare != NULL);
	pq->data = malloc(sizeof(void*)*START);
	return pq;
}

//Function destroys queue by freeing from memory
//Big-O: O(1)
void destroyQueue(PQ *pq)
{
	assert(pq != NULL);
    	free(pq->data);
    	free(pq);
}

//Function returns the number of nodes
//Big-O: O(1)
int numEntries(PQ *pq)
{
	assert(pq != NULL);
    	return pq->count;
}

//Function adds a node to the priority queue and reallocates memory to 2x size if full to limit expensive reallocation
//Big-O: O(log n)
void addEntry(PQ *pq, void *entry)
{
	assert(pq != NULL && entry != NULL);
    	if(pq->length == pq->count)
    	{
        	pq->data = realloc(pq->data, sizeof(void *)*pq->length*2);
        	pq->length *= 2;
    	}
    	pq->data[pq->count] = entry;
    	int loc = pq->count; 
    	while(pq->compare(pq->data[loc], pq->data[p(loc)]) < 0)
    	{
        	void *temp = pq->data[p(loc)];
        	pq->data[p(loc)] = pq->data[loc]; 
        	pq->data[loc] = temp; 
    	}
    	pq->count++;
}

//Function returns the deleted element and reorganizes queue as neccessary 
//Big-O: O(log n)
void *removeEntry(PQ *pq)
{
	assert(pq != NULL);
    	void *root = pq->data[0];
    	int loc, small; 
    	loc = 0;
    	small = 0; 
    	pq->data[loc] = pq->data[pq->count - 1];
    	pq->count--;
    	while(l(loc) < pq->count)
    	{
        	small = l(loc);
        	if(r(loc) < pq->count)
        	{
            		if(pq->compare(pq->data[l(loc)] , pq->data[r(loc)]) < 0)
                		small = l(loc); 
            		else 
                		small = r(loc); 
        	}
        	if(pq->compare(pq->data[small],pq->data[loc]) < 0)
        	{
            		void *temp = pq->data[small]; 
            		pq->data[small] = pq->data[loc];
            		pq->data[loc] = temp; 
            		loc = small; 
        	}
        	else
            		break;
    	} 
    	return root; 
}
