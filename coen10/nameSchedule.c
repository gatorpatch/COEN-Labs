#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    //initilize the array and some varibles
    char schedule[5][20] = {"\0","\0","\0","\0","\0"};
    char name[10];
    int input;
    int end;
    int kill;
    int i;
    int counter;
    end = 0;
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
        //Option 1 checks if there are any available appointments. If there are it will return with a prompt to enter a name, if not it'll return a message to come back tomorrow
        switch(input) {
            case 1 :
                printf("Enter name for appointment: ");
                scanf("%s", name); 
                if(counter == 5) {
                    printf("All busy, come back tomorrow\n");
                }
                else {
                    i = 0;
                    kill = 0;
                    //cycles through the array until it finds a zero
                    while(kill == 0) {
                        if(strcmp("\0",schedule[i]) == 0) {
                            strcpy(schedule[i], name);
                            i += 1;
                            printf("The lesson is scheduled for %dam\n",i);
                            kill = 1;
                        }
                        i++;
                    }
                }
                break;
            //Function to delete a lesson under a specific name
            case 2 :
                printf("What is the name for the appointment: ");
                scanf("%s", name);
                int location;
                location = 0;
                kill = 0;
                //if there is a lesson at inputed time it sets the position in the array as \0
                for(i = 0; i < 5; i++) {
                    if(strcmp(schedule[i], name) == 0) {
                        strcpy(schedule[i], "\0");
                        location = i;
                        kill = 1;
                    }
                }
                //if not it lets the user know that no appointment was found
                if(kill == 0){
                    printf("No appointment found for %s", name);
                }
                else {
                    for(i = (location); i < 4; i++) {
                        strcpy(schedule[i],schedule[i+1]);
                    }
                    strcpy(schedule[4], "\0");
                }
                break;
            //function to list out the schedule of appointments, says if it's free or says the name of the appointment
            case 3 :
                printf("Schedule:\n");
                //cycles through the code and prints on each line whether there is an appointment or not for each timeslot, if there is prints the name of the appointment
                for(i = 0; i < 5; i++) {
                    if(strcmp("\0", schedule[i]) == 0) {
                        printf("%dpm - free\n",i+1);
                    }
                    else {
                        printf("%dpm - %s\n",(i+1),schedule[i]);
                    }
                }
                break;
            //Checks that the schedule isn't empty, and if not prompts the user to put in a character. It then searches through the schedule and returns the names staring with the input
            case 4 :
                if(counter > 0) {
                    printf("Enter letter: ");
                    scanf("%s", name);
                    for(i = 0; i < 5; i++) {
                        if(strncmp(name,schedule[i],1) == 0) {
                            printf("%dam - %s\n",(i+1),schedule[i]);
                        }
                    }
                }
                else {
                    printf("The schedule is empty\n");
                }
                break;
            //triggers the end function which stops the overall while loop and ends the program
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
