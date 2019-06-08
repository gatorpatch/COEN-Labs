# ifndef DATASET_H
# define DATASET_H

typedef struct node NODE;

typedef struct set SET;

int searchID(SET *sp,int idQuery);

SET *createDataSet(int maxElts);

void destroyDataSet(SET *sp);

void insertElement(SET *sp,int idNum,int age);

void removeElement(SET *sp,int idNum);

int searchID(SET *sp,int idQuery);

# endif /* DATASET_H */
