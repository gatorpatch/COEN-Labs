#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "dataset.h"
#include "list.h"

//sets up the node, list, and set structures
typedef struct node {
    int ID;
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
    LIST **lists;
}SET;

//This creates the data set, which is a basic hashed array of linked lists
//O(n)
SET *createDataSet(int maxElts) {
    int i;
    SET *sp;
    sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->count = 0;
    sp->length = maxElts;
    sp->lists = malloc(sizeof(LIST*)*13);
    assert(sp->lists != NULL);
    for(i = 0;i < 13;i++) {
        sp->lists[i] = createList(i + 18);
        //int value= sp->lists[i]->count;
        //printf("countVal:%d\n",value);
    }
    return sp;
}

//Destroys the data set
//O(n)
void destroyDataSet(SET *sp) {
    assert(sp != NULL);
    int i;
    for(i = 0;i < 13;i++) {
        destroyList(sp->lists[i]);
    }
    free(sp->lists);
    free(sp);
}

//searches for students with a certain age, returning a -1 if the linked list has a count of zero(is empty)
//O(n)
int searchAge(SET *sp,int age) {
    assert(sp != NULL);
    NODE *current;
    int found;
    found = -1;
    current = sp->lists[age - 18]->head;
    printf("Searching for %d year old students\n",age);
    if(sp->lists[age - 18]->count > 0) {
        found = sp->lists[age - 18]->count;
        printf("Found %d students\n",found);
        current = current->next;
        while(current->ID != -1) {
            printf("Found:\n------\nStudent ID:%d\nAge:%d\n",current->ID,current->age);
            current = current->next;
        }
        
    }
    return found;
}

//inserts an element into the respective linked list for ages
//O(1)
void insertElement(SET *sp,int age,int id) {
    assert(sp != NULL);
    if(sp->count < sp->length) {
        addFirst(sp->lists[age - 18],id,age);
        sp->count++;
    }
}
//removes the elements
//O(n)
void removeElement(SET *sp,int age) {
    assert(sp != NULL);
    while(sp->lists[age - 18]->count != 0) {
        removeFirst(sp->lists[age - 18]);
        sp->count--;
    }
}
//finds the min age
//O(1)
int minAge(SET *sp) {
    assert(sp != NULL);
    int i;
    for(i = 0;i < 13;i++) {
        if(sp->lists[i]->count != 0) {
            return sp->lists[i]->age;
        }
    }
    return -1;
}
//finds the max age
//O(1)
int maxAge(SET *sp) {
    assert(sp != NULL);
    int i;
    for(i = 12;i >= 0;i--) {
        if(sp->lists[i]->count != 0) {
            return sp->lists[i]->age;
        }
    }
    return -1;
}

//finds the biggest age diffrence in students
//O(1)
int maxAgeGap(SET *sp) {
    assert(sp != NULL);
    int min,max;
    min = minAge(sp);
    max = maxAge(sp);
    return max - min;
}
