# ifndef DATASET_H
# define DATASET_H

typedef struct node NODE;

typedef struct list LIST;

typedef struct set SET;

extern SET *createDataSet(int maxElts);

extern LIST *createList(int listAge);

extern void destroyDataSet(SET *sp);

extern LIST *searchAge(SET *sp,int age);

extern void insertElement(SET *sp,int age,int id);

extern void removeElement(SET *sp,int age);

extern int maxAgeGap(SET *sp);

# endif /* DATASET_H */
