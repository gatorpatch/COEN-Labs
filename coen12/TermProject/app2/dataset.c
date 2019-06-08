#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "dataset.h"

typedef struct node {
    int id;
    int age;
} NODE;

typedef struct set {
    int count;
    int length;
    NODE *array;
} SET;

int searchID(SET *sp,int idQuery);

SET *createDataSet(int maxElts) {
    SET *sp;
    sp = (SET*)malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = maxElts;
    sp->array = malloc(sizeof(NODE*)*maxElts);
    assert(sp->array != NULL);
    return sp;
}

void destroyDataSet(SET *sp) {
    assert(sp != NULL);
    int i;
    for(i = 0;i < sp->length;i++) {
        if(sp->array[i] != NULL) {
            free(sp->array[i]);
        }
    }
    free(sp->array);
    free(sp);
}

void insertElement(SET *sp,int idNum, int age) {
    assert(sp != NULL);
    NODE *addElt;
    addElt = malloc(sizeof(NODE));
    assert(sp->count < sp->length && addElt != NULL);
    sp->array[idNum] = addElt;
    addElt->id = idNum;
    addElt->age = age;
    sp->count++;
}

void removeElement(SET *sp,int idNum) {
    assert(sp != NULL);
    printf("Attempting to delete student with ID:%d\n",&idNum);
    int loc = searchID(sp,idNum);
    if(loc != -1) {
        printf("Deletion successful\n");
        free(sp->array[loc]);
        sp->count--;
    }
    else {
        printf("Deletion Failed, student with ID Number %d does not exist\n",&idNum);
    }
}

int searchID(SET *sp,int idQuery) {
    assert(sp != NULL);
    printf("Searching for student with ID:%d\n",&idQuery);
    NODE *current;
    current = sp->array[idQuery];
    if(current != NULL) {
        printf("Student found\n");
        return idQuery;
    }
    else {
        printf("Student not found in records");
        return -1;
    }
}
