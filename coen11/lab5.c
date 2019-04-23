#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LENGTH 20

//initilize the global variables and the structure
struct reserv {
    char name[LENGTH];
    int size;
    struct reserv *next;
};

//initilize the head and tail pointers for the linked list
struct reserv *head = NULL;
struct reserv *tail = NULL;

//insert function adds a new node at the end of the linked list
void insert(VOID) {
    char rname[LENGTH];
    int num;
    printf("Name: ");
    scanf("%s",rname);
    printf("Size: ");
    scanf("%d",&num);
    //runs the duplicate function to check that the name hasn't been used
    if(check_duplicate(rname) == 0) {
        //initializes a new node to add to end of linked list, with an if statement taking care of a special case
        struct reserv *current;
        current = (struct reserv*)malloc(sizeof(struct reserv));
        //if the list has no entries
        if(head == NULL) {
            head = current;
            tail = head;
        }
        //all other cases
        else {
            tail->next = current;
            tail = current;
        }
        //copies inputed stuff into the node
        strcpy(tail->name,rname);
        tail->size = num;
        tail->next = NULL;
    }
    else {
        printf("Duplicate name is not valid\n");
    }
}

//removes the oldest entry that is less than or equal to an inputed number 
void removee(VOID) {
    //initialize some varible that make sure we print whether we removed anything
    int remove,anyRemove;
    anyRemove = 0;
    //initilize a current and a previous node pointer so we can go through the list and have access to the last value when removing
    struct reserv *current;
    struct reserv *previous;
    current = head;
    previous = head;
    //makes sure the list isn't empty
    if(current != NULL) {
        printf("Size of resevation to remove: ");
        scanf("%d",&remove);
        //pointer to interate through the array of structures
        while(current != NULL) {
            if(remove >= current->size) {
                //Lots and lots of special cases
                anyRemove = 1;
                //This is if we're deleting the head
                if(current == previous) {
                    printf("Removing reservation %s with %d people\n",current->name,current->size);
                    head = current->next;
                    free(current);
                    break;
                }
                //this is if we are deleting the tail
                else if(current->next == NULL) {
                    printf("Removing reservation %s with %d people\n",current->name,current->size);
                    tail = previous;
                    previous->next = NULL;
                    free(current);
                    break;
                }
                //this is everything else (hint: the middle)
                else {
                    printf("Removing reservation %s with %d people\n",current->name,current->size);
                    previous->next = current->next;
                    free(current);
                    break;
                }
            }
            //switches our varibles to crawl through the list
            previous = current;
            current = current->next;
        }
        //if the varible isn't tripped let the user know that we didn't find anything
        if(anyRemove == 0) {
            printf("No reservations with a size of %d found\n",remove);
        }
    }
    else {
        printf("The list is empty\n");
    }
}

//lists the entries and the number of people
void show(VOID) {
    //Pointer to initerate through the linked list
    struct reserv *current;
    current = head;
    //pointer to interate through the array of structures
    if(current != NULL) {
        while(current != NULL) {
            printf("%s - %d people\n",current->name,current->size);
            current = current->next;
        }
    }
    else {
        printf("The list is empty");
    }
}

//lists all entries less than or equal to the inputed size
void search_size(VOID) {
    //Not sure if it was neccessary, but I put another second linked list for the search function so the length can be infinite(given infinite memory) 
    //These are the head and tails of this second list, which it's only purpose is to add found entries to print out
    struct reserv *serHead = NULL;
    struct reserv *serTail = NULL;
    int find;
    //Pointer for the global linked list
    struct reserv *current = head;
    printf("Enter Size: ");
    scanf("%d",&find);
    //finds the entries that match and places them in an array
    while(current != NULL) {
        if(current->size <= find) {
            //As all linked list, special cases are here
            struct reserv *serCurrent = NULL;
            serCurrent = (struct reserv*)malloc(sizeof(struct reserv));
            //if no entries to the secondary list
            if(serHead == NULL) {
                serHead = serCurrent;
                serTail = serHead;
            }
            //everything else
            else {
                serTail->next = serCurrent;
                serTail = serCurrent;
            }
            strcpy(serTail->name,current->name);
            serTail->size = current->size;
            serTail->next = NULL;

        }
        current = current->next;
    }
    //and prints the entries found in 
    current = serHead;
    while(current != NULL) {
        printf("%s - %d\n",current->name,current->size);
        current = current->next;
    }
}

//checks if an name has been used in the reservation system
int check_duplicate(char name[LENGTH]) {
    struct reserv *current;
    current = head;
    while(current != NULL) {
        if(strcmp(current->name,name) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void main(VOID) {
    int answer;
    //infinite loop based on a variable that will never change
    while(LENGTH == 20) {
        printf("\nCommands:\n1:Insert\n2:Delete\n3:Show\n4:Search Size\n\n");
        printf("Enter Command: ");
        scanf("%d",&answer);
        switch(answer) {
            case 1:
                insert();
                break;
            case 2:
                removee();
                break;
            case 3:
                show();
                break;
            case 4:
                search_size();
                break;
            case 0:
                return;
                break;
        }
    }
}


