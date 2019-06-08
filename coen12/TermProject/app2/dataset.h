# ifndef DATASET_H
# define DATASET_H

typedef struct node NODE;

typedef struct set SET;

extern int searchID(SET *sp,int idQuery);

extern SET *createDataSet(int maxElts);

extern void destroyDataSet(SET *sp);

extern void insertElement(SET *sp,int idNum,int age);

extern void removeElement(SET *sp,int idNum);

extern int searchID(SET *sp,int idQuery);

# endif /* DATASET_H */
