#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#define AVG 20

//creates the structures
typedef struct node {
    void *data;
    struct node *next;
    struct node *prev;
} NODE;

typedef struct list {
    int count;
    int (*compare)();
    struct node *head;
} LIST;

typedef struct set {
    int count;
    int length;
    struct list **lists;
    int (*compare)();
    unsigned (*hash)();
} SET;

//createSet allocates the memory for the set structure, returning a pointer to the initialized set
//Runtime: O(n)
SET *createSet(int maxElts,int (*compare)(),unsigned (*hash)()) {
    int i;
    SET *sp;
    assert(compare != NULL && hash != NULL);
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length= maxElts / AVG;
    sp->compare = compare;
    sp->hash = hash;
    sp->count = 0;
    sp->lists = malloc(sizeof(LIST*)*sp->length);
    for(i = 0;i < sp->length;i++) {
        sp->lists[i] = createList(compare);
    }
    return sp;
}

//destroySet frees the array of lists and then the entire set
//Runtime: O(1)
void destroySet(SET *sp) {
    assert(sp != NULL);
    free(sp->lists);
    free(sp);
}

//numElements returns the count of the set
//Runtime: O(1)
int numElements(SET *sp) {
    assert(sp != NULL);
    return sp->count;
}

//addElements hashes the index for the list array, and then adds the elt to the start of the correct list
//Runtime: O(n)
void addElement(SET *sp,void *elt) {
    assert(sp != NULL && elt != NULL);
    int index = (*sp->hash)(elt) % sp->length;
    if(findItem(sp->lists[index],elt) == NULL) {
        addFirst(sp->lists[index],elt);
        sp->count++;
    }
}

//removeElement hashes the index for the list aray, and the removes the elt from the given list
//Runtime: O(n)
void removeElement(SET *sp,void *elt) {
    assert(sp != NULL && elt != NULL);
    int index = (*sp->hash)(elt) % sp->length;
    if(findItem(sp->lists[index],elt) != NULL) {
        removeItem(sp->lists[index],elt);
        sp->count--;
    }
}

//findElement hashes the index to find the correct list then uses the findItem function to return the value
//Runtime: O(n)
void *findElement(SET *sp, void *elt) {
    assert(sp != NULL && elt != NULL);
    int index = (*sp->hash)(elt) % sp->length;
    return findItem(sp->lists[index],elt);
}

//getElements returns an array of all of the elements of the set, by parsing through each list in the array and grabbing all the values
//Runtime: O(n^2)
void *getElements(SET *sp) {
    assert(sp != NULL);
    void **copy = malloc(sizeof(void*)*sp->count);
    void **current;
    int nCount = 0;
    int i,j;
    for(i = 0;i < sp->length;i++) {
        current = getItems(sp->lists[i]);
        for(j = 0;j < numItems(sp->lists[i]);j++) {
            copy[nCount] = current[j];
            nCount++;
        }
    }
    return copy;
}
