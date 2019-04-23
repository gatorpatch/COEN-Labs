#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_WORD_LENGTH 30

int main(int argc, char *argv[]) {
    //sets up the file pointer
    FILE *current;
    current = fopen(argv[1],"r");
    //sets up the count integer
    int count;
    count = 0;
    //this is a literal pointless string that each word is sent to
    char garbage[MAX_WORD_LENGTH];
    //this will check that a filename was given as an arguement
    if(argc == 1) {
        printf("No filename given\n");
        return 0;
    }
    //this will end the program if filename is wrong
    if(current == NULL) {
        printf("Given filename does not exist\n");
        return 0;
    }
    //this is the main count function
    while(fscanf(current,"%s",garbage) != EOF) {
        count++;
    }
    //prints the word count before program ends
    printf("%i total words\n",count);
    //of course we need to close the file
    fclose(current);
    return 0;
}
