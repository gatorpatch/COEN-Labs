#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NODE struct node

struct node {
    int num;
    struct node *next;
};

int main(int argc,char *argv[]) {
    FILE *current;
    int cNum;
    NODE *head;
    head = NULL;
    if(argc == 1) {
        printf("no text file parameter\n");
        return 1;
    }
    else {
        current = fopen(argv[1],"r");
        if(current != NULL) {
            fscanf(current,"%d",&cNum);
            NODE *add;
            NODE *point;
            add = (NODE *)malloc(sizeof(NODE));
            if(head == NULL) {
                head = add;
            }
            else {
                point = head;
                while(point->next != NULL) {
                    point = point->next;
                }
                point->next = add;
            }
            add->num = cNum;
            add->next = NULL;
        }
    }
}


