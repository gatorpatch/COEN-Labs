#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "dataset.h"

#define HASH(x) (x-18)

typedef struct node {
    int id;
    int age;
    struct node *next;
    struct node *prev;
}NODE;

typedef struct list {
    int count;
    int age;
    struct node *head;
}LIST;

typedef struct set {
    int count;
    int length;
    struct list **lists;
}SET;

SET *createDataSet(int maxElts) {
    int i;
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->lists = malloc(sizeof(LIST*)*13);
    for(i = 0;i < ;i++) {

    }
}

LIST *createList(int listAge) {
    LIST *lp;
    lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->age = listAge;
    lp->head = malloc(sizeof(NODE));
    assert(lp->head != NULL);
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    return lp;
}

void insertElement(SET *sp,int age,int id) {
    assert(sp != NULL);
    NODE *newNode,*oldNode;
    newNode = malloc(sizeof(NODE));
    assert(newNode != NULL);
    newNode->age = age;
    newNode->id = id;
    oldNode = sp->lists[HASH(age)]->head
    

void removeElement(SET *sp,int age) {
    NODE *nextD, *currentD;
    assert(lp != NULL);
    currentD = lp->head;
    do {
        nextD = ccurrentD->next;
        free(currentD);
        currentD = nextD;
    }while(currentD != lp->head);
    free(lp);
}


