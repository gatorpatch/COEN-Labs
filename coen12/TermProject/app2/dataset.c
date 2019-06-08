#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "dataset.h"

#define EMPTY 0
#define FULL 1

typedef struct node {
    int id;
    int age;
} NODE;

typedef struct set {
    int count;
    int length;
    struct node **array;
    int *flag;
} SET;

int searchID(SET *sp,int idQuery);

SET *createDataSet(int maxElts) {
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = maxElts;
    sp->array = malloc(sizeof(struct node)*maxElts);
    sp->flag = malloc(sizeof(int)*maxElts);
    assert(sp->array != NULL && sp->flag != NULL);
    int i;
    for(i = 0;i < sp->length;i++) {
        sp->flag[i] = EMPTY;
    }
    return sp;
}

void destroyDataSet(SET *sp) {
    assert(sp != NULL);
    int i;
    for(i = 0;i < sp->length;i++) {
        if(sp->flag[i] == FULL) {
            free(sp->array[i]);
        }
    }
    free(sp->array);
    free(sp->flag);
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
    sp->flag[idNum] = FULL;
    sp->count++;
}

void removeElement(SET *sp,int idNum) {
    assert(sp != NULL);
    printf("Attempting to delete student with ID:%d\n",idNum);
    int loc = searchID(sp,idNum);
    if(loc != -1) {
        printf("Deletion successful\n");
        free(sp->array[loc]);
        sp->flag[loc] = EMPTY;
        sp->count--;
    }
    else {
        printf("Deletion Failed, student with ID Number %d does not exist\n",idNum);
    }
}

int searchID(SET *sp,int idQuery) {
    assert(sp != NULL);
    printf("Searching for student with ID:%d\n",idQuery);
    if(sp->flag[idQuery] == FULL) {
        printf("Student found\n");
        return idQuery;
    }
    else {
        printf("Student not found in records\n");
        return -1;
    }
}
