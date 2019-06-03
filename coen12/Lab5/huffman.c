#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "pack.h"
#include "pqueue.h"

typedef struct node NODE;

//function runs up the tree until it hits the root, counting the hops
//O(n);
int hopCount(NODE *leaf) {
    int hopCount;
    hopCount = 0;
    //runs until it hits the root, then it returns the number of hops
    while(leaf->parent != NULL) {
        leaf = leaf->parent;
        hopCount++;
    }
    return hopCount;
}

//Compare function
//O(1)
int compare(struct node *firstComp,struct node *secondComp) {
    return (firstComp->count < secondComp->count) ? -1 : (firstComp->count > secondComp->count);
}

//main function creates the huffman tree
int main(int argc,char *argv[]) {
    FILE *fp = fopen(argv[1],"r");
    if(fp == NULL) {
        return 0;
    }
    //sets up the array of the frequency of characters
    int frequency[257] = {0};
    //runs through each character of the file until it hits the EOF, updating the count on each spot in the array by ascii char keys 
    while(1) {
        int occurrence;
        occurrence = fgetc(fp);
        if(feof(fp)) {
            break;
        }
        frequency[occurrence]++;
    }
    //creates the priority queue that helps figure out how the priority tree will work
    PQ *priQueue = createQueue(compare);
    //then creates the array of leaves and initilizes them all as null
    struct node *leaves[257] = {0};
    int i;
    for(i = 0;i < 257;i++) {
        leaves[i] = NULL;
    }
    //setup the nonzero nodes with a tree
    for(i = 0;i < 256;i++) {
        if(frequency[i] > 0) {
            NODE *currentNode = malloc(sizeof(struct node));
            currentNode->count = frequency[i];
            currentNode->parent = NULL;
            addEntry(priQueue,currentNode);
            leaves[i] = currentNode;
        }
    }
    //This is a special case for the EOF, since it won't get picked up by the frequency counter since it breaks the endless while loop
    NODE *endNode = malloc(sizeof(struct node));
    endNode->count = 0;
    endNode->parent = NULL;
    addEntry(priQueue,endNode);
    leaves[256] = endNode;
    //This while loop runs until the priority queue consists of one tree, as that means that it's the huffman tree since it has no unconnected trees
    while(numEntries(priQueue) > 1) {
        NODE *childOne = removeEntry(priQueue);
        NODE *childTwo = removeEntry(priQueue);
        NODE *newParent = malloc(sizeof(struct node));
        newParent->count = childOne->count + childTwo->count;
        childOne->parent = newParent;
        childTwo->parent = newParent;
        newParent->parent = NULL;
        addEntry(priQueue,newParent);
    }
    //then it runs through all the characters and prints them if they're greater than 0, along with the number of bits they take up
    for(i = 0;i < 257;i++) {
        if(leaves[i] != NULL) {
            int hopNum;
            hopNum = hopCount(leaves[i]);
            if(isprint(i)) {
                printf("'%c': %d x %d bits = %d bits\n",i,frequency[i],hopNum,frequency[i]*hopNum);
            }
            else {
                printf("%03o: %d x %d bits = %d bits\n",i,frequency[i],hopNum,frequency[i]*hopNum);
            }

        }
    }
    //packs the final project
    pack(argv[1],argv[2],leaves);
}
