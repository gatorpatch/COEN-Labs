#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

//global varibles
char schedule[5][20] = {"\0","\0","\0","\0","\0"};
char phoneNum[5][11] = {"\0","\0","\0","\0","\0"};
int groupSize[5] = {0,0,0,0,0};
int counter;
int input;
int end = 0;
int i;
int priorityUsed;
priorityUsed = 0;

//Function that creates a lesson with phone number, name, and group size data
void request(void) {
    int kill = 0;
    int groupCount;
    char name[20];
    char phone[11];
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter phone number: ");
    scanf("%s", phone);
    //checks if there is anything scheduled first
    if(counter < 5) { 
        //makes sure no duplicate names
        for(i = 0; i < 5; i++) {
            if(strcmp(name, schedule[i]) == 0) {
                kill = 1;
                printf("There is already a appointment in this name\n");
            }
        }
        if(kill == 0) {
            printf("How many people are in your group? ");
            scanf("%d", &groupCount);
            //makes sure that the group size is valid before writing anything
            if(groupCount < 5 && groupCount > 0) {
                groupSize[counter] = groupCount;
                strcpy(schedule[counter], name);
                strcpy(phoneNum[counter], phone);
            }
            else {
                printf("A group can be between 1 and 4 people\n");
            }
        }
    }
    else {
        printf("All busy, come back tomorrow\n");
    }
}

//removes an appointment
void cancel(void) {
    char name[20];
    int location;
    int kill = 0;
    printf("What is the name for the appointment: ");
    scanf("%s", name);
    //checks for an appointment under that name
    if(counter < 5) {
        for(i = 0; i < 5; i++) {
            if(strcmp(schedule[i], name) == 0) {
                strcpy(schedule[i], "\0");
                location = i;
                kill = 1;
            }
        }
    }
    //if not it lets the user know that no appointment was found
    if(kill == 0){
        printf("No appointment found for %s\n", name);
    }
    //then proceeds to move up the remaining appointments, letting the user know where each on is moved
    else {
        strcpy(schedule[location], "\0");
        strcpy(phoneNum[location], "\0");
        groupSize[location] = 0;
        for(i = (location); i < 4; i++) {
            //makes sure not to inform the user about null values being moved
            if(strcmp(schedule[i],"\0") != 0) {
                printf("%s's lesson with %d people under the phone number %s is being moved to %dPM.\n",schedule[i],groupSize[i],phoneNum[i],i);
            }
            strcpy(schedule[i],schedule[i+1]);
            strcpy(phoneNum[i], phoneNum[i+1]);
            groupSize[i] = groupSize[i+1];
        }
        strcpy(schedule[4], "\0");
        strcpy(schedule[4], "\0");
        groupSize[4] = 0;
    }
}

//lists the appointments as either free, or lists out the name, phone number, and number of members in each
void list(void) {
    printf("Schedule:\n");
    //cycles through the code and prints on each line whether there is an appointment or not for each timeslot, if there is prints the name of the appointment
    for(i = 0; i < 5; i++) {
        if(strcmp("\0", schedule[i]) == 0) {
            printf("%dpm - free\n",i+1);
        }
        else {
            printf("%dpm - Name: %s - Phone: %s - # in Group: %d\n",(i+1),schedule[i],phoneNum[i],groupSize[i]);
        }
    }
}

//searches the schedule for appointments starting with the same letter
void letter(void) {
    char name[20];
    if(counter > 0) {
        printf("Enter letter: ");
        scanf("%s", name);
        for(i = 0; i < 5; i++) {
            if(strncmp(name,schedule[i],1) == 0) {
                printf("%dpm - %s\n",(i+1),schedule[i]);
            }
        }
    }
    else {
        printf("The schedule is empty\n");
    }
}
//searches the list for appointments with the same amount of group members
void group(void) {
    int groupSearch;
    if(counter > 0) {
        printf("Enter group size: ");
        scanf("%d", &groupSearch);
        for(i = 0; i < 5; i++) {
            if(groupSize[i] == groupSearch) {
                printf("%dpm - %s\n",(i+1),schedule[i]);
            }
        }
    }
    else {
        printf("The schedule is empty\n");
    }
}
//The priority option places the inserted info into the first slot of the day, then moves each existing appointment down an hour. It only can be triggered once a day
void priority(void) {
    //checks if the option has been used yet in the program
    if(priorityUsed == 0) {
        priorityUsed = 1;
        int groupCount;
        char name[20];
        char phone[11];
        printf("Enter name: ");
        scanf("%s", name);
        printf("Enter phone number: ");
        scanf("%s", phone);
        printf("Enter group size: ");
        scanf("%d", &groupCount);
        //makes sure the group count works
        if(groupCount < 5 && groupCount > 0) {
            //runs down the list backwards moving the appointments down.
            for(i = 4; i > -1; i--) {
                //makes sure not to inform the user about null values being moved
                if(strcmp(schedule[i],"\0") != 0) {
                    printf("%s's lesson with %d people under the phone number %s is being moved to %dPM.\n",schedule[i],groupSize[i],phoneNum[i],i+2);
                }               
                strcpy(schedule[i+1],schedule[i]);
                strcpy(phoneNum[i+1], phoneNum[i]);
                groupSize[i+1] = groupSize[i];
            }
            groupSize[0] = groupCount;
            strcpy(schedule[0], name);
            strcpy(phoneNum[0], phone);
        }
    }
    //if the user has already used the option it lets them know
    else {
        printf("The priority option was used, please come back tomorrow.\n");
    }
}

int main(void) {
    //infinite loop until end varible is set as 1
    while(end == 0) {
        //counting loop that finds out the number of appointments 
        counter = 0;
        for(i = 0; i < 5; i++) {
            if(strcmp("\0",schedule[i]) != 0) {
                counter++;
            }
        }
        //The main prompt
        printf("Enter option: ");
        scanf("%d", &input);
        switch(input) {
            case 1 :
                request();
                break;
            case 2 :
                cancel();
                break;
            case 3 :
                list();
                break;
            case 4 :
                letter();
                break;
            case 5:
                group();
                break;
            case 6:
                priority();
                break;
            case 9 :
                end = 1;
                break;
            //if anything other than the cases are inputed return a invalid input statement
            default :
                printf("Invalid input\n");
                break;
        }
    }
}


