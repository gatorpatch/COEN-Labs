#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pqueue.h"

//defines how stuff is heaped on the array, to convert it from the tree to the 2darray
#define SIZE 10
#define parent(x) ((x-1)/2)
#define right(x) ((2*x)+2)
#define left(x) ((2*x)+1)

//Priority queue struct
typedef struct pqueue {
    int count;
    int length;
    void **data;
    int(*compare)();
}PQ;

//Function creates a queue and initializes it with a void array of 10 items
//O(1)
PQ *createQueue(int (*compare)()) {
    assert(compare != NULL);
    PQ *pq;
    pq = malloc(sizeof(PQ));
    assert(pq != NULL);
    pq->count = 0;
    pq->length = SIZE;
    pq->compare = compare;
    pq->data = malloc(sizeof(void *)*SIZE);
    return pq;
}

//Function deallocates and destroys the array
//O(1)
void destroyQueue(PQ *pq) {
    assert(pq != NULL);
    free(pq->data);
    free(pq);
}

//Function returns the number of items in the array
//O(1)
int numEntries(PQ *pq) {
    assert(pq != NULL);
    return pq->count;
}

//Adds entry to the end of the queue
//O(log(n))
void addEntry(PQ *pq,void *entry) {
    assert(pq != NULL && entry != NULL);
    //this means it has to expand memory, since it doubles sometimes the individual big-O will become larger, however it has to do this infrequently
    if(pq->length == pq->count) {
        pq->length = pq->length * 2;
        pq->data = realloc(pq->data,sizeof(void *)*pq->length);
    }
    pq->data[pq->count] = entry;
    int current = pq->count;
    //makes sure that the number on the top of the queue is the largest number
    while(pq->compare(pq->data[current],pq->data[parent(current)]) < 0) {
        void *temp;
        temp = pq->data[parent(current)];
        pq->data[parent(current)] = pq->data[current];
        pq->data[current] = temp;
        current = parent(current);
    }
    pq->count++;
}

//Removes and returns smallest value
//O(log(n))
void *removeEntry(PQ *pq) {
    assert(pq != NULL);
    int smallest,current;
    smallest = 0;
    current = 0;
    void *rootPoint = pq->data[0];
    pq->data[current] = pq->data[pq->count - 1];
    pq->count--;
    //makes sure it has children
    while(left(current) < pq->count) {
        smallest = left(current);
        //checks if it even has to check the right one
        if(right(current) < pq->count) {
            if(pq->compare(pq->data[left(current)],pq->data[right(current)]) < 0) {
                smallest = left(current);
            }
            else {
                smallest = right(current);
            }
        }
        //makes sure those compare correctly otherwise we've reached the bottom
        if(pq->compare(pq->data[smallest],pq->data[current]) < 0) {
            void *temp = pq->data[smallest];
            pq->data[smallest] = pq->data[current];
            pq->data[current] = temp;
            current = smallest;
        }
        else {
            break;
        }
    }
    return rootPoint;
}
