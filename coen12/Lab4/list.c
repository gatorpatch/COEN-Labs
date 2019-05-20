#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//List struct
struct list {
    int count;
    struct node *head;
    int (*compare)(); //function pointer
};

//node struct
struct node {
    void *data;
    struct node *next;
    struct node *prev;
};
typedef struct node NODE;

//createList allocates the memory and creates a dummy node list
//Runtime:O(1)
LIST *createList(int (*compare)()) {
    //creates the list struct and allocates memory
    struct list *lp;
    lp = malloc(sizeof(struct list));
    assert(lp != NULL);
    //sets the count to zero and creates the dummy node
    lp->count = 0;
    lp->compare = compare;
    lp->head = malloc(sizeof(struct node));
    assert(lp != NULL);
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
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

//numItems returns the count of the list
//Runtime:O(1)
int numItems(LIST *lp) {
    assert(lp != NULL);
    return lp->count;
}

//addFirst adds the elt to the front of the enque
//Runtime:O(1)
void addFirst(LIST *lp,void *item) {
    NODE *newNode;
    assert(lp != NULL);
    newNode = malloc(sizeof(struct node));
    assert(newNode != NULL);
    newNode->data = item;
    newNode->prev = lp->head;
    newNode->next = lp->head->next;
    lp->head->next = newNode;
    newNode->next->prev = newNode;
    lp->count++;
}

//addLast adds the elt to the end of the enque
//Runtime:O(1)
void addLast(LIST *lp,void *item) {
    NODE *newNode;
    assert(lp != NULL);
    newNode = malloc(sizeof(struct node));
    assert(newNode != NULL);
    newNode->data = item;
    newNode->prev = lp->head->prev;
    newNode->next = lp->head;
    lp->head->prev = newNode;
    newNode->prev->next = newNode;
    lp->count++;
}

//removeFirst removes the first elt of the enque
//Runtime:O(1)
void *removeFirst(LIST *lp) {
    NODE *delNode;
    void *dData;
    assert(lp != NULL);
    delNode = lp->head->next;
    dData = delNode->data;
    lp->head->next = delNode->next;
    delNode->next->prev = lp->head;
    free(delNode);
    lp->count--;
    return dData;
}

//removeLast removes the last elt of the enque
//Runtime:O(1)
void *removeLast(LIST *lp) {
    NODE *delNode;
    void *dData;
    assert(lp != NULL);
    delNode = lp->head->prev;
    dData = delNode->data;
    lp->head->prev = delNode->prev;
    delNode->next->next = lp->head;
    free(delNode);
    lp->count--;
    return dData;
}

//getFirst returns the first elt
//Runtime:O(1)
void *getFirst(LIST *lp) {
    assert(lp != NULL);
    return lp->head->next->data;
}

//getLast returns the last elt
//Runtime:O(1)
void *getLast(LIST *lp) {
    assert(lp != NULL);
    return lp->head->prev->data;
}

//removeItem removes the node when it matches with the given item value
//Runtime:O(n)
void removeItem(LIST *lp,void *item) {
    NODE *current;
    assert(lp != NULL && lp->compare != NULL);
    current = lp->head->next;
    while(current != lp->head) {
        if(lp->compare(current->data,item) == 0) {
            current->next->prev = current->prev;
            current->prev->next = current->next;
            free(current);
            lp->count--;
            return;
        }
        current = current->next;
    }
}

//findItem returns the node containing the data listed in the item varible
//Runtime:O(n)
void *findItem(LIST *lp,void *item) {
    assert(lp != NULL && lp->compare != NULL);
    NODE *current;
    current = lp->head->next;
    while(current != lp->head) {
        if(lp->compare(current->data,item) == 0) {
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}

//getItem returns an array of all the data from the nodes
//Runtime:O(n)
void *getItems(LIST *lp) {
    assert(lp != NULL);
    void **copy = malloc(sizeof(void *)*lp->count);
    assert(copy != NULL);
    NODE *current;
    current = lp->head->next;
    int i;
    for(i = 0;i < lp->count;i++) {
        copy[i] = current->data;
        current = current->next;
    }
    return copy;
}
    
