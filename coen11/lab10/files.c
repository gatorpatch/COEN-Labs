#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "global.h"


//reads the file from the given file
void readFile(char *file,int key) {
    //this sets up the file to be read
    FILE *fileName;
    fileName = fopen(file,"r");
    //varibles for the fscanf
    int cSize,i;
    char cName[LENGTH];
    char currentCrypt[100];
    //if the file doesn't exist, shouldn't happen given the check on main but here just in case
    if(fileName == NULL) {
        printf("The file %s does not exist\n",file);
    }
    //fgets outputs the string, which is the number of elements it was able to pull. when that value is null then we've reached the end of the file
    while(fgets(currentCrypt,100,fileName) != NULL) {
        i = 0;
        //Goes to the end of the line
        while(currentCrypt[i] != '\n') {
            currentCrypt[i] = ((currentCrypt[i]) ^ (key));
            i++;
        }
        sscanf(currentCrypt,"%s\t%d\n",cName,&cSize);
        //gotta check if the name is a duplicate
        if(check_duplicate(cName) == 0) {
            insert(cName,cSize);
        }
    }
    //close the file up
    fclose(fileName);
}

//suprisingly, this saves the file
void saveFile(char *file,int key) {
    //sets up the file for writing, the w+ will erase the old file if there was one, and this is only run after the program's already loaded whatevers on that
    FILE *fileName;
    char buffer[70];
    fileName = fopen(file,"w+");
    //those all essential varibles for inserting stuff
    char cName[LENGTH];
    int cSize,i,j;
    //get that pointer to interate through the various linked lists
    struct reserv *current;
    //sets up the header for the file
    //fprintf(fileName,"%s\t%s\n","Name","Group Size");
    //fprintf(fileName,"%s\n","-------------------");
    //runs through the linked lists, and puts the values into the file
    for(i = 0;i < 4;i++) {
        current = lists[i].head;
        //makes sure we haven't reached the end of the list
        while(current != NULL) {
            //adds those to the list with a tab in the middle
            j = 0;
            sprintf(buffer,"%s\t%d\n",current->name,current->size);
            //encrypts with the supplied key
            while(buffer[j] != '\n') {
                buffer[j] = ((buffer[j]) ^ (key));
                j++;
            }
            fprintf(fileName, "%s", buffer);
            current = current->next;
        }
    }
    //closes the file
    fclose(fileName);
}

void *autosave(void* fileName) {
    RESERV *current;
    FILE *currentFile;
    int i;
    while(1) {
        pthread_mutex_lock(&lock);
        currentFile = fopen(fileName,"wb");
        for(i = 0;i < 4;i++) {
            current = lists[i].head;
            while(current != NULL) {
                fwrite(current,sizeof(struct reserv),1,currentFile);
                current = current->next;
            }
        }
        fclose(currentFile);
        pthread_mutex_unlock(&lock);
        sleep(15);
    }
}


void readAutoSave(char *fileName) {
    RESERV current;
    FILE *currentFile;
    int i;
    pthread_mutex_lock(&lock);
    currentFile = fopen(fileName,"rb");
    while(fread(&current,sizeof(struct reserv),1,currentFile) == 1) {
        printf("%s - %d\n",current.name,current.size);
    }
    fclose(currentFile);
    pthread_mutex_unlock(&lock);
}

