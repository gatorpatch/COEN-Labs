#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 10
#define LENGTH 20

//initilize the global variables
int counter;
struct reservation {
    char name[LENGTH];
    int size;
};

struct reservation reserv[SIZE];

//insert function adds a new entry at the end of the array 
void insert(VOID) {
	//checks that the list isn't full
	if(counter != SIZE) {
		char rname[SIZE];
		int num;
		printf("Name: ");
		scanf("%s",rname);
		printf("Size: ");
		scanf("%d",&num);
                //runs the duplicate function to check that the name hasn't been used
                if(check_duplicate(rname) == 0) {
                    strcpy(reserv[counter].name,rname);
                    reserv[counter].size = num;
                    counter++;
                }
                else {
                    printf("Duplicate name is not valid\n");
                }
	}
	else {
		printf("List is full\n");
	}
}

//removes the oldest entry that is less than or equal to an inputed number 
void removee(VOID) {
	int remove,anyRemove,remLocation, i, j;
	anyRemove = 0;
	//makes sure the list isn't empty
	if(counter != 0) {
		printf("Size of resevation to remove: ");
		scanf("%d",&remove);
                //pointer to interate through the array of structures
                struct reservation *current = reserv;
		for(i = 0;i < counter;i++) {
			if(remove >= current->size) {
				anyRemove = 1;
				remLocation = i;
			}
                        current++;
		}
		if(anyRemove == 0) {
			printf("No reservations with a size of %d found\n",remove);
		}
		else {
			printf("Removing resevation %s with %d people\n",reserv[remLocation].name,reserv[remLocation].size);
			for(i = remLocation;i < counter - 1;i++) {
				strcpy(reserv[i].name,reserv[i+1].name);
				reserv[i].size = reserv[i+1].size;
			}
			counter--;
		}
	}
	else {
		printf("The list is empty\n");
	}
}

//lists the entries and the number of people
void show(VOID) {
	int i;
        //pointer to interate through the array of structures
        struct reservation *current = reserv;
	if(counter != 0) {
		for(i = 0; i < counter;i++) {
			printf("%s - %d people\n",current->name,current->size);
                        current++;
		}
	}
	else {
		printf("The list is empty");
	}
}

//lists all entries less than or equal to the inputed size
void search_size(VOID) {
    int entryLoc[SIZE];
    int find,i,j;
    //pointer to interate through the array of structures
    struct reservation *current = reserv;
    j = 0;
    printf("Enter Size: ");
    scanf("%d",&find);
    //finds the entries that match and places them in an array
    for(i = 0; i < counter;i++) {
        if(current->size <= find) {
            entryLoc[j] = i;
            j++;
        }
        current++;
    }
    //and prints the entries found in the last for loop
    for(i = 0;i < j;i++) {
        if(j > 0) {
            printf("%s - %d\n",reserv[i].name,reserv[i].size);
        }
    }
}

//checks if an name has been used in the reservation system
int check_duplicate(char name[LENGTH]) {
    int i;
    //pointer to interate through the array of structures
    struct reservation *current = reserv;
    for(i = 0; i < counter;i++) {
        if(strcmp(current->name,name) == 0) {
            return 1;
        }
        current++;
    }
    return 0;
}

void main(VOID) {
	int answer;
	counter = 0;
        //struct reservation reserv[SIZE];
	//infinite loop based on a variable that will never change
	while(SIZE == 10) {
		printf("Commands:\n1:Insert\n2:Delete\n3:Show\n4:Search Size\n");
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

		
