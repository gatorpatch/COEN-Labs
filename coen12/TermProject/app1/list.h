# ifndef LIST_H
# define LIST_H

typedef struct list LIST;

extern LIST *createList(int age);

extern void destroyList(LIST *lp);

extern int numItems(LIST *lp);

extern void addFirst(LIST *lp,int ID,int age);

extern int removeFirst(LIST *lp);

# endif /* LIST_H */
