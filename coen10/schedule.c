#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void) {
    //initilize the array and some varibles
    int schedule[] = {0, 0, 0, 0, 0};
    int input;
    int end;
    int i;
    int counter;
    end = 0;
    //infinite loop until end varible is set as 1
    while(end == 0) {
        //counting loop that finds out the number of appointments 
        counter = 0;
        for(i = 0; i < 5; i++) {
            if(schedule[i] == 1) {
                counter++;
            }
        }
        //The main prompt
        printf("Enter option: ");
        scanf("%d", &input);
        //Option 1 checks if there are any available appointments. If there are it will return the appointment time, if not it'll return a message to come back tomorrow
        if(input == 1) {
            if(counter == 5) {
                printf("All busy, come back tomorrow\n");
            }
            else {
                //a quick varible setup to break the loop when it finds a match
                int kill;
                kill = 0;
                i = 0;
                //cycles through the array until it finds a zero
                while(kill == 0) {
                    if(schedule[i] == 0) {
                        schedule[i] = 1;
                        i += 1;
                        printf("The lesson is scheduled for %dpm\n",i);
                        kill = 1;
                    }
                    i++;
                }
            }
        }
        //Function to delete a lesson
        else if(input == 2) {
            printf("What lesson time do you want to cancel: ");
            scanf("%d", &input);
            //if there is a lesson at inputed time it sets the position in the array as 0
            if(schedule[input-1] == 1) {
                schedule[input-1] = 0;
            }
            //if not it lets the user know
            else {
                printf("No appointment found at %dpm\n",input);
            }
        }
        //function to list out the schedule of appointments
        else if(input == 3) {
            printf("Schedule:\n");
            //cycles through the code and prints on each line whether there is an appointment or not for each timeslot
            for(i = 0; i < 5; i++) {
                if(schedule[i] == 0) {
                    printf("%dpm - free\n",i+1);
                }
                else {
                    printf("%dpm - lesson\n",i+1);
                }
            }
        }
        //triggers the end function which stops the overall while loop and ends the program
        else if(input == 9) {
            end = 1;
        }
    }
}
