#include "set.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//First we have to create the set struct
typedef struct set {
    int count;
    int length;
    char **data;
}SET;

//initilize this guy up here so that we can use him in findElement and getElements
static int search(SET *sp,char *elt);

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
    //makes sure that the elt isn't a duplicate
    if(search(sp,elt) == -1) {
        //uses the nifty little strdup function, which automatically mallocs and then inserts the string into that allocated memory, cutting down on our code
        sp->data[sp->count] = strdup(elt);
        //we then have to update the count
        sp->count++;
    }
}

//this one removes an element name elt
//O(n)
void removeElement(SET *sp, char *elt) {
    //checks that the set and elt are valid
    assert(sp != NULL && elt != NULL);
    //finds the position of the elt
    int position = search(sp,elt);
    //if the position isn't -1 (meaning it exists), then it'll delete it and move the last element to it's spot
    if(position != -1) {
        free(sp->data[position]);
        //takes that last value and moves it to the freed location
        sp->data[position] = sp->data[sp->count - 1];
        //then updates the count
        sp->count--;
    }
}

//this one finds an element
//O(n)
char *findElement(SET *sp, char *elt) {
    //checks that the set and elt are valid
    assert(sp != NULL && elt != NULL);
    //finds that position
    int position = search(sp,elt);
    //if that position is -1, then it doesn't exist so we can return NULL, if not then returns the data value at that position
    if(position == -1) {
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

//finally, we get to the search function. This guy runs through the set and looks for the elt, using sequencial search in this case
//O(n)
static int search(SET *sp,char *elt) {
    //check that set and elt to make sure
    assert(sp != NULL && elt != NULL);
    //now we simply run through the program and see if we can find the thing
    int i;
    for(i = 0;i < sp->count;i++) {
        //checks if they equal with strcmp
        if(strcmp(elt,sp->data[i]) == 0) {
            return i;
        }
    }
    //if not found returns -1
    return -1;
}
    
