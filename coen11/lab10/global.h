#ifndef LIST_H_
#define LIST_H_
#define LENGTH 20
#define RESERV struct reserv
#define LIST struct list

struct reserv{
    char name[LENGTH];
    int size;
    struct reserv *next;
};

struct list{
    struct reserv *head;
    struct reserv *tail;
};

extern LIST lists[4];
extern pthread_mutex_t lock;
int findArray();
void insert();
void removee();
void show();
void search_size();
int check_duplicate();
void changeSize();
void freeNode();
void readFile();
void saveFile();
void listBackwards();
void nameBackwards();
void *autosave();
void readAutoSave();

#endif
