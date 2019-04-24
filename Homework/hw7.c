#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define LENGTH 20
#define NODE struct node

struct node {
    int value;
    struct node *next;
};

void everyOther(char *initString,char *finalString,int state) {
    if(*initString == '\0') {
        *finalString = *initString;
        return;
    }
    else if(state == 0) {
        *finalString = *initString;
        everyOther(initString+1,finalString+1,1);
    }
    else {
        everyOther(initString+1,finalString,0);
    }
    return;
}

void reverseLink(NODE *current,NODE *next) {
    if(next->next == NULL) {
        next->next = current;
    }
    else {
        reverseLink(next,next->next);
    }
}

void main() {
    /*
    char string1[LENGTH];
    char string2[LENGTH];
    printf("Insert string: ");
    scanf("%s",string1);
    everyOther(string1,string2,0);
    printf("%s",string2);
    */
    int i;
    i = 0;
    NODE *head;
    NODE *tail;
    NODE *current;
    head = (NODE*)malloc(sizeof(NODE));
    while(i < 10) {
        if(i = 0) {
            current = head;
        }
        else if(i = 9) {
            tail = current;
        }
        current->value = i;
        current->next = (NODE*)malloc(sizeof(NODE));
        current = current->next;
        i++;
    }
    reverseLink(head,head->next);
    current = tail;
    while(current != NULL) {
        int cValue;
        cValue = current->value;
        printf("%d\n",&cValue);
        current = current->next;
    }
}
