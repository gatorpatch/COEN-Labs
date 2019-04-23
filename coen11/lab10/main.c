#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "global.h"

//initilize the pthread lock
pthread_mutex_t lock;

//initilize the array
LIST lists[4] = {{NULL,NULL},{NULL,NULL},{NULL,NULL},{NULL,NULL}};

//the glorious main function
int main(int argc,char *argv[]) {
    //none of this works if we forget to add a file varible
    if(argc == 1) {
        printf("The name of the file is missing!\n");
        return 1;
    }
    //generates the key from supplied string
    int key;
    key = atoi(argv[2]);
    //if the file actually exists, then we load from it
    if(fopen(argv[1],"r") != NULL) {
        readFile(argv[1],key);
    }
    pthread_t thread;
    pthread_mutex_init(&lock,NULL);
    pthread_create(&thread,NULL,autosave,(void *)argv[1]);
    int answer,cSize,i;
    char cName[LENGTH];
    char header[][LENGTH] = {"1-2","3-4","5-6","6<"};
    //infinite loop based on a variable that will never change
    while(LENGTH == 20) {
        printf("\nCommands:\n1:Insert\n2:Delete\n3:Show\n4:Search Size\n5:Print Each List Backwards\n6:Print Each Name Backwards\n7:Read from Autosave\n\n");
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
            case 7:
                readAutoSave(argv[1]);
                break;
            case 0:
                //end the autosave thread
                pthread_mutex_lock(&lock);
                pthread_cancel(thread);
                pthread_mutex_unlock(&lock);
                //save the text file
                saveFile(argv[1],key);
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

