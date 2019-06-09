#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include "dataset.h"

int main() {
    //creates the data set with a fixed size of 3000 students
    SET *sp = createDataSet(3000);
    //randomizes the random number key used by rand()
    srand(time(0));
    //initilizes those int varibles
    int idNum,age,i;
    idNum = 0;
    //creates 1000 random students
    for(i = 0;i < 1000;i++) {
        idNum = idNum + ((rand() % 2) + 1);
        age = ((rand() % 30) + 18);
        insertElement(sp,idNum,age);
    }
    //creates a random student and searches for it
    int randStuID, randAge, randLocation;
    randStuID = ((rand() % 2000) + 1);
    randAge = ((rand() % 12) + 18);
    randLocation = searchID(sp,randStuID);
    //if the student is found it removes them from the data set
    if(randLocation != -1) {
        removeElement(sp,randStuID);
    }
    //then destroys the whole data set
    destroyDataSet(sp);
}
