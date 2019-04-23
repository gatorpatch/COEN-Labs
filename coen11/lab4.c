#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 10
#define LENGTH 20

//initilize the global variables
int counter;
union info{
    char birthday[LENGTH];
    int years;
    float avg_age;
};

struct reservation {
    char name[LENGTH];
    int size;
    int special_occasion;
    union info extra;
};

struct reservation reserv[SIZE];

//insert function adds a new entry at the end of the array 
void insert(VOID) {
	//checks that the list isn't full
	if(counter != SIZE) {
		char rname[LENGTH],specialName[LENGTH];
		int num, special, anniversary;
                float avgAge;
		printf("Name: ");
		scanf("%s",rname);
		printf("Size: ");
		scanf("%d",&num);
                //Asks for special occasion so it can futher prompt info
                printf("1:Birthday\n2:Anniversary\n");
                printf("Special Occasion: ");
                scanf("%d",&special);
                //runs the duplicate function to check that the name hasn't been used
                if(check_duplicate(rname) == 0) {
                    //either asks about the birthday name, the anniversary years, or the average age
                    if(special == 1) {
                        printf("Birthday persons name: ");
                        scanf("%s",specialName);
                        strcpy(reserv[counter].extra.birthday,specialName);
                    }
                    else if(special == 2) {
                        printf("Anniversary year: ");
                        scanf("%d",&anniversary);
                        reserv[counter].extra.years = anniversary;
                    }
                    else {
                        printf("Average age of group: ");
                        scanf("%f",&avgAge);
                        reserv[counter].extra.avg_age = avgAge;
                    }
                    strcpy(reserv[counter].name,rname);
                    reserv[counter].size = num;
                    reserv[counter].special_occasion = special;
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
			if(remove >= current->size && anyRemove == 0) {
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
                                reserv[i].special_occasion = reserv[i+1].special_occasion;
                                //These copy over the union value correctly
                                if(reserv[i+1].special_occasion == 1) {
                                    strcpy(reserv[i].extra.birthday,reserv[i+1].extra.birthday);
                                }
                                else if(reserv[i+1].special_occasion == 2) {
                                    reserv[i].extra.years = reserv[i+1].extra.years;
                                }
                                else {
                                    reserv[i].extra.avg_age = reserv[i+1].extra.avg_age;
                                }
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
                    //these make sure it prints the extra info correctly as the right date type
                    if(current->special_occasion == 1) {
                        printf("%s - %d people. %s's Birthday\n",current->name,current->size,current->extra.birthday);
                    }
                    else if(current->special_occasion == 2) {
                        printf("%s - %d people. %d Year Anniversary\n",current->name,current->size,current->extra.years);
                    }
                    else {
                        printf("%s - %d people. Average age is %f years old\n",current->name,current->size,current->extra.avg_age);
                    }
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
            if(reserv[i].special_occasion == 1) {
                printf("%s - %d people. %s's Birthday\n",reserv[i].name,reserv[i].size,reserv[i].extra.birthday);
            }
            else if(reserv[i].special_occasion == 2) {
                printf("%s - %d people. %d Year Anniversary\n",reserv[i].name,reserv[i].size,reserv[i].extra.years);
            }
            else {
                printf("%s - %d people. Average age is %f years old\n",reserv[i].name,reserv[i].size,reserv[i].extra.avg_age);
            }
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

		
