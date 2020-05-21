#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//List struct
struct list {
    int count;
    int age;
    struct node *head;
};

//node struct
struct node {
    int ID;
    int age;
    struct node *next;
    struct node *prev;
};
typedef struct node NODE;

//createList allocates the memory and creates a dummy node list
//Runtime:O(1)
LIST *createList(int age) {
    //creates the list struct and allocates memory
    struct list *lp;
    lp = malloc(sizeof(struct list));
    assert(lp != NULL);
    //sets the count to zero and creates the dummy node
    lp->count = 0;
    lp->age = age;
    lp->head = malloc(sizeof(struct node));
    assert(lp->head != NULL);
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    lp->head->ID = -1;
    return lp;
}

//destroyList destroys the list by freeing all elts and the freeing the list pointer
//Runtime: O(n)
void destroyList(LIST *lp) {
    NODE *nextD, *currentD;
    assert(lp != NULL);
    currentD = lp->head;
	do {
        nextD = currentD->next;
        free(currentD);
        currentD = nextD;
    }while(currentD != lp->head);
    free(lp);
}

//addFirst adds the elt to the front of the enque
//Runtime:O(1)
void addFirst(LIST *lp,int ID,int age) {
    NODE *newNode;
    assert(lp != NULL);
    newNode = malloc(sizeof(struct node));
    assert(newNode != NULL);
    newNode->ID = ID;
    newNode->age = age;
    newNode->next = lp->head->next;
    lp->head->next = newNode;
    newNode->prev = lp->head;
    newNode->next->prev = newNode;
    lp->count++;
}

//removeFirst removes the first elt of the enque
//Runtime:O(1)
int removeFirst(LIST *lp) {
    NODE *delNode;
    int id;
    assert(lp != NULL);
    delNode = lp->head->next;
    id = delNode->ID;
    lp->head->next = delNode->next;
    delNode->next->prev = lp->head;
    free(delNode);
    lp->count--;
    return id;
}
