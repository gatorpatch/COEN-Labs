#include "set.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//First we have to create the set struct
typedef struct set {
    int count;
    int length;
    char **data;
}SET;

//initilize this guy up here so that we can use him in findElement and getElements
static int search(SET *sp,char *elt,bool *found);

//This guy creates the SET
//O(n)
SET *createSet(int maxElts) {
    //creates the pointer of the created set
    SET *sp;
    sp = malloc(sizeof(SET));
    //checks if the set is initialized correctly
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    //uses the sizeof function to allocate memory for the string array
    sp->data = malloc(sizeof(char*)*maxElts);
    //makes sure the data is initialized
    assert(sp->data != NULL);
    //returns the pointer to the created set
    return sp;
}

//This guy destroys the given set
//O(n)
void destroySet(SET *sp) {
    //checks that the set supplied exists
    assert(sp != NULL);
    //runs through the array of strings and clears each
    int i;
    for(i = 0;i < sp->count;i++) {
        free(sp->data[i]);
    }
    //then frees the memory allocated for the whole array, and then the array itself
    free(sp->data);
    free(sp);
}

//This guy returns the number of elements in sp
//O(1)
int numElements(SET *sp) {
    //checks the sets existence
    assert(sp != NULL);
    //then returns the count varible from the set
    return(sp->count);
}

//This guy adds elt to the set
//O(n)
void addElement(SET *sp,char *elt) {
    //checks if the set and elt are valid
    assert(sp != NULL && elt != NULL);
    //we also have to test that the count is less than the set length, to see if we have the space to add to the set
    assert(sp->count < sp->length);
    //makes sure that the elt isn't a duplicate, creates a boolean to test and pulls the int returned for the location
    bool check = true;
    int location;
    location = search(sp,elt,&check);
    if(check == false) {
        //runs through the thing backwards, moving down each element until it reaches the location we add to
        int i;
        for(i=sp->count;i > location;i--) {
            sp->data[i] = sp->data[i-1];
        }
        //actually have to put the value in there
        sp->data[location] = strdup(elt);
        sp->count++;
    }
}

//this one removes an element name elt
//O(n)
void removeElement(SET *sp, char *elt) {
    //checks that the set and elt are valid
    assert(sp != NULL && elt != NULL);
    //finds the position of the elt and makes sure it exists
    bool check = true;
    int location;
    location = search(sp,elt,&check);
    //if this boolean isn't true, then the search function didn't find anything
    if(check == true) {
        free(sp->data[location]);
        //for loop runs through all the stuff under it and move it up one
        int i;
        for(i = location + 1;i < sp->count;i++) {
            sp->data[i-1] = sp->data[i];
        }
        //then as always you have to update the count
        sp->count--;
    }
}

//this one finds an element
//O(logn)
char *findElement(SET *sp, char *elt) {
    //checks that the set and elt are valid
    assert(sp != NULL && elt != NULL);
    //finds that position, and also creates a bool to check that it exists
    bool found = true;
    int position = search(sp,elt,&found);
    //if that position is -1, then it doesn't exist so we can return NULL, if not then returns the data value at that position
    if(found == false) {
        return NULL;
    }
    else {
        return sp->data[position];
    }
}

//this one creates an array of the elements in sp
//O(n)
char **getElements(SET *sp) {
    //checks that set is valid
    assert(sp != NULL);
    char **arrayCopy;
    //allocate memory for the new array
    arrayCopy = malloc(sizeof(char*)*sp->count);
    //check that the allocation worked
    assert(arrayCopy != NULL);
    //runs through the set and adds to the new array
    int i;
    for(i = 0;i < sp->count;i++) {
        arrayCopy[i] = sp->data[i];
    }
    return arrayCopy;
}

//finally, we get to the search function. This search function needs to use the binary search function, so it cuts the array in half until the midpoint is the correct string or it finds where the string should go. Boolean dictates whether the string was found or not
//O(logn)
static int search(SET *sp,char *elt,bool *found) {
    //that trusty assert function
    assert(sp != NULL && elt != NULL);
    //first we create the varibles for the lo, hi, and midpoint for the search function
    int lo,hi,mid;
    lo = 0;
    hi = sp->count - 1;
    //this guy only fails when the thing isn't in the array, since the hi or lo value will eventually swap when the element isn't there
    while(lo <= hi) {
        mid = (lo+hi)/2;
        //strcmp returns a negative value when the first string (elt in this case) has a lower value than the second term, so that means that we set the hi value at the midpoint
        if(strcmp(elt,sp->data[mid]) < 0) {
            hi = mid - 1;
        }
        //strcmp works the other way also, so this means the midpoint value is less than the elt
        else if(strcmp(elt,sp->data[mid]) > 0) {
            lo = mid + 1;
        }
        else {
            *found = true;
            return mid;
        }
    }
    *found = false;
    return lo;
}

