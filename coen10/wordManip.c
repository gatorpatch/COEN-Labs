#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//global varibles
char words[10][11] = {"\0","\0","\0","\0","\0","\0","\0","\0","\0","\0"};
int length[10];
int i;
int j;
char numStart[10][11];
int counter;

//input function
void input(void) {
    char wordPlace[11];
    char wordInput[11];
    int location;
    counter = 0;
    //gets the words from the user and alphabetizes them after each inputed. Breaks if ctl+D is pressed
    for(j = 0;j < 10;j++) {
        printf("Input: ");
        if(scanf("%s",wordInput) == 1) {
            counter++;
            for(i = 0;i < 10;i++) {
                if(strcmp(wordInput,words[i]) < 0 || strcmp("\0",words[i]) == 0) {
                    location = i;
                    break;
                }
            }
            for(i = 8; i > location - 1;i--) {
                strcpy(words[i+1],words[i]);
            }
            strcpy(words[location],wordInput);
        }
        else {
            break;
        }
    }
}
//reverse function
void reverse(void) {
    char wordRev[10][11];
    //goes through and copies the words backwards into a temp array
    for(i = 0; i < counter;i++) {
        strcpy(wordRev[i],words[counter-1-i]);
    }
    //copies the temp array straight into the real array
    for(i = 0;i < counter;i++) {
        strcpy(words[i],wordRev[i]);
    }
    output();
}
//case function
void caseFunc(void){
    //sets pointer varibles
    char *letter = &words[0][0];
    int *wordCount = &length[0];
    //cycles through the words getting the length, and changing all lowercase letters to uppercase using pointers
    for(i = 0;i < 10;i++) {
        *wordCount = strlen(words[i]);
        for(j = 0;j < 10;j++) {  
            if(islower(*letter)) {
                *letter = toupper(*letter);
            }
            letter++;
        }
        letter++;
        wordCount++;
    }
    output();
}
//Calculate function
void calc(void) {
    int shortest = 0;
    int longest = 0;
    int average = 0;
    int numStar = 0;
    //Runs through the array to find the longest, shortest, and all words that start with non alphabet symbols or numbers
    for(i = 0;i < counter;i++) {
        average = average + length[i];
        if(length[i] < length[shortest]) {
            shortest = i;
        }
        if(length[i] > length[longest]) {
            longest = i;
        }
        if(isalpha(words[i][0]) == 0) {
            strcpy(numStart[numStar],words[i]);
            numStar++;
        }
    }
    average = average / counter;
    printf("Calculations:\nLongest: %s(%d)\nShortest: %s(%d)\nAverage Word Length: %d\n",words[longest],length[longest],words[shortest],length[shortest],average);
    printf("Words starting with numbers:\n");
    for(i = 0;i < numStar;i++) {
        printf("%s\n", numStart[i]);
    }
    output();
}
//Output array
void output(void) {
    printf("Array:\n");
    for(i=0;i < counter;i++) {
        printf("%s\n",words[i]);
    }
}

void main(void) {
    input();
    reverse();
    caseFunc();
    calc();
}
