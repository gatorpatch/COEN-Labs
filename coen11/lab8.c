#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LENGTH 20

//initilize the global variables and the structures
//the structures used in the array to hold the info of the linked list
struct list {
    struct reserv *head;
    struct reserv *tail;
};
//reservation structure
struct reserv {
    char name[LENGTH];
    int size;
    struct reserv *next;
};
//impliment it at the start so stuff works
int check_duplicate(char name[LENGTH]);

//initilizing the array of list structures with null values since it's empty
struct list lists[4] = {{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL}};

//I decided for my sanity I'd convert this if function to a actual function for brevity and sanity
int findArray(int reservSize) {
    if(reservSize == 1 || reservSize == 2) {
        return 0;
    }
    else if(reservSize == 3 || reservSize == 4) {
        return 1;
    }
    else if(reservSize == 5 || reservSize == 6) {
        return 2;
    }
    else {
        return 3;
    }
}

//insert function adds a new node at the end of the linked list
void insert(char *cName,int cSize) {
    //initializes a new node to add to end of linked list, with an if statement taking care of a special case
    struct reserv *add;
    int currentList;
    //finds the number of the array that points to the linked list for this value
    currentList = findArray(cSize);
    add = (struct reserv*)malloc(sizeof(struct reserv));
    //if the list has no entries
    if(lists[currentList].head == NULL) {
        lists[currentList].head = add;
        lists[currentList].tail = add;
    }
    //all other cases
    else {
        lists[currentList].tail->next = add;
    }
    //copies inputed stuff into the node
    strcpy(add->name,cName);
    add->size = cSize;
    lists[currentList].tail = add;
    add->next = NULL;
}

//removes the oldest entry that is less than or equal to an inputed number 
void removee() {
    //initialize some varible that make sure we print whether we removed anything
    int remove,anyRemove,finalList,i;
    anyRemove = 0;
    //initilize a current and a previous node pointer so we can go through the list and have access to the last value when removing
    struct reserv *current;
    struct reserv *previous;
    //makes sure the list isn't empty
    printf("Size of resevation to remove: ");
    scanf("%d",&remove);
    //again, using the super handy function to find the specific linked list we're deleting to
    finalList = findArray(remove);
    //pointer to interate through the array of structures
    for(i = 0;i <= finalList;i++) {
        current = lists[i].head;
		previous = current;
		while(current != NULL && anyRemove == 0) {
			if(remove >= current->size) {
                //Lots and lots of special cases
                anyRemove = 1;
                //This is if we're deleting the head
                if(current == previous) {
                    printf("Removing reservation %s with %d people\n",current->name,current->size);
                    lists[i].head = current->next;
                    free(current);
                    break;
                }
                //this is if we are deleting the tail
                else if(current->next == NULL) {
                    printf("Removing reservation %s with %d people\n",current->name,current->size);
                    lists[i].tail = previous;
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
	}
	//if the varible isn't tripped let the user know that we didn't find anything
	if(anyRemove == 0) {
		printf("No reservations with a size of %d found\n",remove);
	}
}

//lists the entries and the number of people
void show() {
    //Pointer to initerate through the linked list
    struct reserv *current;
    //added a array of strings just to list which list we're printing, purely cosmetic
    char names[4][LENGTH] = {"1-2","3-4","5-6","6<"};
    current = (struct reserv*)malloc(sizeof(struct reserv));
    int i;
    //pointer to interate through the array of structures
    for(i = 0; i < 4;i++) {
        printf("%s\n",names[i]);
        current = lists[i].head;
        //checks if the list is initially empty
        if(current != NULL) {
            //then runs through till it's equal to null, so basically the end of the list
            while(current != NULL) {
                printf("%s - %d people\n",current->name,current->size);
                current = current->next;
            }
        }
        else {
            printf("The list is empty\n");
        }
    }
}

//lists all entries less than or equal to the inputed size
void search_size() {
    //Not sure if it was neccessary, but I put another second linked list for the search function so the length can be infinite(given infinite memory) 
    //These are the head and tails of this second list, which it's only purpose is to add found entries to print out
    struct reserv *serHead = NULL;
    struct reserv *serTail = NULL;
    int sFind,currentList, i;
    //Pointer for the global linked list
    struct reserv *current;
    printf("Enter Size: ");
    scanf("%d",&sFind);
    //using my handy little function to find the array to focus on at the start
    currentList = findArray(sFind);
    //this starts with the highest value linked list, then interates down to the last list, making it go through all relevent lists
    for(i = currentList;i >= 0;i--) {
        //starts at the head of each of the lists
        current = lists[i].head;
        //finds the entries that match and places them in an array
        while(current != NULL) {
            if(current->size <= sFind) {
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
    }
    //then outputs the found stuff
    current = serHead;
    while(current != NULL) {
        printf("%s - %d\n",current->name,current->size);
        current = current->next;
    }

}

//checks if an name has been used in the reservation system
int check_duplicate(char name[LENGTH]) {
    struct reserv *current;
    current = (struct reserv*)malloc(sizeof(struct reserv));
    int i;
    //for loop runs through all of the linked lists
    for(i = 0;i < 4;i++) {
        current = lists[i].head;
        while(current != NULL) {
            if(strcmp(current->name,name) == 0) {
                return 1;
            }
            current = current->next;
        }
    }
    return 0;
}

//changes the size value and moves it to the correct linked list, this one was a lot of fun to debug
void changeSize() {
    //initilize the relevent varibles
    char sName[LENGTH];
    int oldSize,newSize,currentArray,foundName;
    //pointers initialized, current and previous are the currently looked at reservation and the previous, then the new pointer acts as a placeholder if a linked list is empty
    struct reserv *current;
    struct reserv *prev;
    struct reserv *new;
    new = (struct reserv*)malloc(sizeof(struct reserv));
    printf("Name of reservation: ");
    scanf("%s",sName);
    printf("Original size: ");
    scanf("%d",&oldSize);
    printf("New size: ");
    scanf("%d",&newSize);
    //this whole function is why I implimented the findArray function, because I have to use this big block of code so often
    currentArray = findArray(oldSize);
    current = lists[currentArray].head;
    prev = current;
    //varible that tells me if i've found the relevent varible so I can tell the user if it exists or not
    foundName = 0;
    //runs through until it finds something
    while(current != NULL && foundName == 0) {
        //compares current with the inputed value
        if(strcmp(current->name,sName) == 0) {
            //this is the easiest case, if the reservation doesn't have to change arrays
            if(findArray(oldSize) == findArray(newSize)) {
                current->size = newSize;
                foundName = 1;
            }
            //these are the ones that need to move linked lists
            else {
                //initilize the new array location, so the new linked list
                int newArray;
                newArray = findArray(newSize);
                //this is if the reservation is the head of the linked list
                if(prev == current) {
                    lists[currentArray].head = current->next;
                    //if it's the only value in the list, then it also has to change the tail value
                    if(current->next == NULL) {
                        lists[currentArray].tail = lists[currentArray].head;
                    }
                }
                //this is if the reservation is the tail, and it's not the only one in the linked list
                else if(lists[currentArray].tail == current && lists[currentArray].head != lists[currentArray].tail) {
                    lists[currentArray].tail = prev;
                    prev->next = NULL;
                }
                //if it's chilling in the middle of the linked list
                else {
                    prev->next = current->next;
                }
                //this is if the new linked list is empty
                if(lists[newArray].tail == NULL) {
                    lists[newArray].head = current;
                    lists[newArray].tail = current;
                }
                //this is if it isn't empty
                else {
                    prev = lists[newArray].tail;
                    prev->next = current;
                    lists[newArray].tail = current;
                }
                current->next = NULL;
                current->size = newSize;
                foundName = 1;
            }
        }
        prev = current;
        current = current->next;
    }
    if(foundName == 0) {
        printf("No reservation found with the name %s\n",sName);
    }
}



//this one frees all the memory of the program
void freeNode(struct reserv *p) {
    //If we've gone past the tail, then end
    if(p == NULL) {
        return;
    }
    //recurses then frees current node, only after all nodes after have freed
    freeNode(p->next);
    free(p);
}

//reads the file from the given file
void readFile(char *file) {
    //this sets up the file to be read
    FILE *fileName;
    fileName = fopen(file,"r");
    //varibles for the fscanf
    int cSize;
    char cName[LENGTH];
    //if the file doesn't exist, shouldn't happen given the check on main but here just in case
    if(fileName == NULL) {
        printf("The file %s does not exist\n",file);
    }
    //sets the start of the file after the header
    else {
        fseek(fileName,36,SEEK_SET);
    }
    //fscanf outputs a int, which is the number of elements it was able to pull. when that value isn't 2, then we're out of elements to read
    while(fscanf(fileName,"%s %d",cName,&cSize) == 2) {
        //gotta check if the name is a duplicate
        if(check_duplicate(cName) == 0) {
            insert(cName,cSize);
        }
    }
    //close the file up
    fclose(fileName);
}

//suprisingly, this saves the file
void saveFile(char *file) {
    //sets up the file for writing, the w+ will erase the old file if there was one, and this is only run after the program's already loaded whatevers on that
    FILE *fileName;
    fileName = fopen(file,"w+");
    //those all essential varibles for inserting stuff
    char cName[LENGTH];
    int cSize,i;
    //get that pointer to interate through the various linked lists
    struct reserv *current;
    //sets up the header for the file
    fprintf(fileName,"%s\t%s\n","Name","Group Size");
    fprintf(fileName,"%s\n","-------------------");
    //runs through the linked lists, and puts the values into the file
    for(i = 0;i < 4;i++) {
        current = lists[i].head;
        //makes sure we haven't reached the end of the list
        while(current != NULL) {
            //adds those to the list with a tab in the middle
            fprintf(fileName,"%s\t%d\n",current->name,current->size);
            current = current->next;
        }
    }
    //closes the file
    fclose(fileName);
}

//prints each seperate list backwards
void listBackwards(struct reserv *p) {
    //this means that we've gone past the tail, and to stop
    if(p == NULL) {
        return;
    }
    //recurses and prints the info of each list entry
    listBackwards(p->next);
    printf("%s - %d\n",p->name,p->size);
}

//prints a inputed name backwards
void nameBackwards(char *p) {
    //this means that we've gone past the tail, and to stop
    if(*p == '\0') {
        return;
    }
    //recureses and prints the current character, but only after all the next recursives run
    nameBackwards(p+1);
    printf("%c",*p);
}


int main(int argc,char *argv[]) {
    //none of this works if we forget to add a file varible
    if(argc == 1) {
        printf("The name of the file is missing!\n");
        return 1;
    }
    //if the file actually exists, then we load from it
    if(fopen(argv[1],"r") != NULL) {
        readFile(argv[1]);
    }
    int answer,cSize,i;
    char cName[LENGTH];
    char header[][LENGTH] = {"1-2","3-4","5-6","6<"};
    //infinite loop based on a variable that will never change
    while(LENGTH == 20) {
        printf("\nCommands:\n1:Insert\n2:Delete\n3:Show\n4:Search Size\n5:Print Each List Backwards\n6:Print Each Name Backwards\n\n");
        printf("Enter Command: ");
        scanf("%d",&answer);
        switch(answer) {
            case 1:
                //we've moved all the input stuff from the function since it now takes varibles, cause save and load
                printf("Name for reservation: ");
                scanf("%s",cName);
                if(check_duplicate(cName) == 0) {
                    printf("Size for reservation: ");
                    scanf("%d",&cSize);
                    insert(cName,cSize);
                }
                else {
                    printf("This name has already been used for a reservation\n");
                }
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
            case 5:
                //runs through each list outside
                for(i = 0;i < 4;i++) {
                    printf("%s\n",header[i]);
                    listBackwards(lists[i].head);
                }
                break;
            case 6:
                //runs through each list outside the function
                for(i = 0;i < 4;i++) {
                    printf("%s\n",header[i]);
                    struct reserv *p = lists[i].head;
                    while(p != NULL) {
                        nameBackwards(p->name);
                        printf("\n");
                        p = p->next;
                    }
                    
                }
                break;
            case 0:
                saveFile(argv[1]);
                for(i = 0;i < 4;i++) {
                    freeNode(lists[i].head);
                    lists[i].head = NULL;
                    lists[i].tail = NULL;
                }
                return 0;
                break;
        }
    }
}


