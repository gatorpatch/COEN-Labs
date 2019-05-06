#include "set.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//defines those flags
#define EMPTY 1
#define DELETED 2
#define FILLED 3

//First we have to create the set struct
typedef struct set {
    int count;
    int length;
    char **data;
    int *flag;
}SET;

//initilize this guy up here so that we can use him in findElement and getElements, and also initialized the hash function
unsigned strhash(char *s);
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
    sp->flag = malloc(sizeof(int*)*maxElts);
    //makes sure the data is initialized
    assert(sp->data != NULL && sp->flag != NULL);
    //then initializes all the flags with a value of empty
    int i;
    for(i = 0;i < sp->length;i++) {
        sp->flag[i] = EMPTY;
    }
    //returns the pointer to the created set
    return sp;
}

//This guy destroys the given set
//O(n)
void destroySet(SET *sp) {
    //checks that the set supplied exists
    assert(sp != NULL);
    //runs through the array of strings and clears each if it was filled
    int i;
    for(i = 0;i < sp->count;i++) {
        if(sp->flag[i] == FILLED) {
            free(sp->data[i]);
        }
    }
    //then frees the memory allocated for the whole array, the whole array of flags, and then the array itself
    free(sp->data);
    free(sp->flag);
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
    //boolean for the search function
    bool isDup = false;
    //then runs the search function with an int variable to read the search's found location
    int loc;
    loc = search(sp,elt,&isDup);
    //checks if the set and elt are valid
    assert(sp != NULL && elt != NULL);
    //we also have to test that the count is less than the set length, to see if we have the space to add to the set
    assert(sp->count < sp->length);
    //makes sure that the elt isn't a duplicate
    if(isDup == false) {
        //uses the nifty little strdup function, which automatically mallocs and then inserts the string into that allocated memory, cutting down on our code
        sp->data[loc] = strdup(elt);
        //gotta update that flag too
        sp->flag[loc] = FILLED;
        //we then have to update the count
        sp->count++;
    }
}

//this one removes an element name elt
//O(n)
void removeElement(SET *sp, char *elt) {
    //boolean for the search function
    bool isDup;
    isDup = false;
    //checks that the set and elt are valid
    assert(sp != NULL && elt != NULL);
    //finds the position of the elt
    int loc = search(sp,elt,&isDup);
    //if the position isn't -1 (meaning it exists), then it'll delete it and move the last element to it's spot
    if(isDup == false) {
        //frees the string
        free(sp->data[loc]);
        //then flags as deleted
        sp->flag[loc] = DELETED;
        //then updates the count
        sp->count--;
    }
}

//this one finds an element
//O(n)
char *findElement(SET *sp, char *elt) {
    bool isFound;
    isFound = false;
    //checks that the set and elt are valid
    assert(sp != NULL && elt != NULL);
    //finds that position
    int loc = search(sp,elt,&isFound);
    //if that position is -1, then it doesn't exist so we can return NULL, if not then returns the data value at that position
    if(isFound == false) {
        return NULL;
    }
    else {
        return sp->data[loc];
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
    //runs through the set and adds to the new array, checking the flag to see if it's filled or not before adding it to the array
    int i,j;
    for(i = 0,j = 0;i < sp->length;i++) {
        if(sp->flag[i] == FILLED) {
            arrayCopy[j] = sp->data[i];
            j++;
        }
    }
    return arrayCopy;
}

//Hash function to get the location things are at
unsigned strhash(char *s) {
    unsigned hash = 0;

    while (*s != '\0') {
        hash = 31 * hash + *s ++;
    }
    return hash;
}

//finally, we get to the search function. This guy runs through the set and looks for the elt, using sequencial search in this case
//O(n)
static int search(SET *sp,char *elt, bool *found) {
    //check that set and elt to make sure
    assert(sp != NULL && elt != NULL);
    int delLoc = -1;
    *found = false;
    unsigned key;
    key = strhash(elt);
    int i;
    for(i = 0;i < sp->length;i++) {
        int loc;
        loc = (key + i) % (sp->length);
        //if the flag is empty(equal to 1), the program checks if it's found anything with a deleted flag, and if it hasn't it returns the empty location
        if(sp->flag[loc] == EMPTY) {
            //if it has found a deleted node and this node is empty, that means that the elt is not in the array farther down the stack and you can safely returned the deleted flag node
            if(delLoc != -1) {
                return delLoc;
            }
            return loc;
        }
        //if the flag is an deleted, it registers the location of the deleted and it keeps going to make sure it's not at the next location
        else if(sp->flag[loc] == DELETED) {
            delLoc = loc;
        }
        //if the flag is full, then it checks if the element is the search elt, and if not keeps going;
        else if(sp->flag[loc] == FILLED) {
            if(strcmp(sp->data[loc],elt) == 0) {
                *found = true;
                return loc;
            }
        }
    }
    return -1;

}
    
