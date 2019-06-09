/*
 * File:        table.c
 *
 * Copyright:	2017, Darren C. Atkinson
 *
 * Description: This file contains the public and private function and type
 *              definitions for a set abstract data type for generic
 *              pointer types.  A set is an unordered collection of unique
 *              elements.
 *
 *              This implementation uses a hash table to store the
 *              elements, with linear probing to resolve collisions.
 *              Insertion, deletion, and membership checks are all average
 *              case constant time.
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <stdbool.h>
# include "set.h"

# define EMPTY   0
# define FILLED  1
# define DELETED 2

struct set {
    int count;                  /* number of elements in array */
    int length;                 /* length of allocated array   */
    void **data;                /* array of allocated elements */
    char *flags;                /* state of each slot in array */
    int (*compare)();		/* comparison function         */
    unsigned (*hash)();		/* hash function               */
};

/*
 * Function:    search
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: Return the location of ELT in the set pointed to by SP.  If
 *		the element is present, then *FOUND is true.  If not
 *		present, then *FOUND is false.  The element is first hashed
 *		to its correct location.  Linear probing is used to examine
 *		subsequent locations.
 */ 

static int search(SET *sp, void *elt, bool *found)
{
    int available, i, locn, start;


    available = -1;
    start = (*sp->hash)(elt) % sp->length;

    for (i = 0; i < sp->length; i ++) {
        locn = (start + i) % sp->length;

        if (sp->flags[locn] == EMPTY) {
            *found = false;
            return available != -1 ? available : locn;

        } else if (sp->flags[locn] == DELETED) {
            if (available == -1)
		available = locn;

        } else if ((*sp->compare)(sp->data[locn], elt) == 0) {
            *found = true;
            return locn;
        }
    }

    *found = false;
    return available;
}


/*
 * Function:    createSet
 *
 * Complexity:  O(m)
 *
 * Description: Return a pointer to a new set with a maximum capacity of
 *		MAXELTS.
 */

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
    int i;
    SET *sp;


    assert(compare != NULL && hash != NULL);

    sp = malloc(sizeof(SET));
    assert(sp != NULL);

    sp->data = malloc(sizeof(char *) * maxElts);
    assert(sp->data != NULL);

    sp->flags = malloc(sizeof(char) * maxElts);
    assert(sp->flags != NULL);

    sp->compare = compare;
    sp->hash = hash;
    sp->length = maxElts;
    sp->count = 0;

    for (i = 0; i < maxElts; i ++)
        sp->flags[i] = EMPTY;

    return sp;
}


/*
 * Function:    destroySet
 *
 * Complexity:  O(m)
 *
 * Description: Deallocate memory associated with the set pointed to by SP.
 *		The elements themselves are not deallocated since we did not
 *		allocate them in the first place.  That's the rule: if you
 *		didn't allocate it, then you don't deallocate it.
 */

void destroySet(SET *sp)
{
    assert(sp != NULL);

    free(sp->flags);
    free(sp->data);
    free(sp);
}


/*
 * Function:    numElements
 *
 * Complexity:  O(1)
 *
 * Description: Return the number of elements in the set pointed to by SP.
 */

int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
}


/*
 * Function:    addElement
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: Add ELT to the set pointed to by SP.
 */

void addElement(SET *sp, void *elt)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL);
    locn = search(sp, elt, &found);

    if (!found) {
	assert(sp->count < sp->length);

	sp->data[locn] = elt;
	sp->flags[locn] = FILLED;
	sp->count ++;
    }
}


/*
 * Function:    removeElement
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: Remove ELT from the set pointed to by SP.  A element is
 *		deleted by changing the state of its slot.
 */

void removeElement(SET *sp, void *elt)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL);
    locn = search(sp, elt, &found);

    if (found) {
	sp->flags[locn] = DELETED;
	sp->count --;
    }
}


/*
 * Function:    findElement
 *
 * Complexity:  O(1) average case, O(n) worst case
 *
 * Description: If ELT is present in the set pointed to by SP then return
 *		it, otherwise return NULL.
 */

void *findElement(SET *sp, void *elt)
{
    int locn;
    bool found;


    assert(sp != NULL && elt != NULL);

    locn = search(sp, elt, &found);
    return found ? sp->data[locn] : NULL;
}

//Simple swap function used to find the midpoint and also to sort the array
//O(1)
void swap(void *array[], int loc1, int loc2) {
    void *temp = NULL;
    temp = array[loc1];
    array[loc1] = array[loc2];
    array[loc2] = temp;
}

//Takes the bounds given in the left and right, and finds the midpoint's correct place in the full array, which allows the program to correctly sort around that pivot in the correct place
//O(1)
void *midPoint(void *array[], int left, int right,int (*compare)()) {
    int midPoint = (right - left) / 2;

    if(compare(array[left],array[right]) < 0) {
        swap(array, left, right);
    }
    if(compare(array[left],array[midPoint]) < 0) {
        swap(array, left, midPoint);
    }
    if(compare(array[midPoint], array[right]) < 0) {
        swap(array, midPoint, right);
    }
    return array[midPoint];
}

//Partitions the array based on the midpoint from the midpoint function, interating through the list until all things are on the correct side of the pivot
//O(n)
int partition(void *array[], int low, int high, int (*compare)()) {
    void *pivot = midPoint(array, low, high, compare);
    int left = low;
    int right = high;
    while(left < right) {
        while(compare(array[left],pivot) > 0) {
            left++;
        }
        while(compare(array[right],pivot) < 0) {
            right--;
        }
        if(left <= right) {
            swap(array, left, right);
            left++;
            right--;
        }
    }
    return left;
}

//A quicksort function that sorts around a midpoint pivot
//O(n)
void quickSort(void *array[], int low, int high, int (*compare)()) {
    if(low < high) {
        int pi = partition(array, low, high, compare);
        quickSort(array, low, pi - 1, compare);
        quickSort(array, pi + 1, high, compare);
    }
}

//takes a set and returns a sorted void array
//O(n)
void *getElements(SET *sp) {
    assert(sp != NULL);
    int i,k;
    void **qSortArr;
    qSortArr = malloc(sizeof(void*)*sp->count);
    for(i = 0,k = 0;i < sp->length;i++) {
        if(sp->flags[i] == FILLED) {
            qSortArr[k] = sp->data[i];
            k++;
        }
    }
    quickSort(qSortArr,0,k-1,sp->compare);
    return qSortArr;
}

