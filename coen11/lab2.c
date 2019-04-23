#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 10
#define LENGTH 20

//initilize the global variables
int counter;
char name[SIZE][LENGTH];
int size[SIZE];

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
		strcpy(name[counter],rname);
		size[counter] = num;
		counter++;
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
		for(i = 0;i < counter;i++) {
			if(remove >= size[i]) {
				anyRemove = 1;
				remLocation = i;
			}
		}
		if(anyRemove == 0) {
			printf("No reservations with a size of %d found\n",remove);
		}
		else {
			printf("Removing resevation %s with %d people\n",name[remLocation],size[remLocation]);
			for(i = remLocation;i < counter - 1;i++) {
				strcpy(name[i],name[i+1]);
				size[i] = size[i+1];
			}
			counter--;
		}
	}
	else {
		printf("The list is empty");
	}
}

//lists the entries and the number of people
void list(VOID) {
	int i;
	if(counter != 0) {
		for(i = 0; i < counter;i++) {
			printf("%s - %d people\n",name[i],size[i]);
		}
	}
	else {
		printf("The list is empty");
	}
}

void main(VOID) {
	int answer;
	counter = 0;
	//infinite loop based on a variable that will never change
	while(SIZE == 10) {
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
				list();
				break;
			case 0:
				return;
				break;
		}
	}
}

		
