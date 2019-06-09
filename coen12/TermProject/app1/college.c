#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "dataset.h"

int main() {
    //create set of 3000
    SET *sp = createDataSet(3000);
    //these gives the random number generator a key based on current time
    srand(time(0));
    //initilizes the id, age, and i varibles
    int idNum,age,i;
    idNum = 0;
    //generates 1000 random students and places them in my data structure
    for(i = 0;i < 1000;i++) {
        idNum = idNum + ((rand() % 2) + 1);
        age = ((rand() % 13) + 18);
        insertElement(sp,age,idNum);
    }
    //generates the random student and searches for them
    int randAge,randStatus;
    randAge = ((rand() % 13) + 18);
    randStatus = searchAge(sp,randAge);
    //then deletes the random student
    if(randStatus != -1) {
        removeElement(sp,randAge);
    }
    //then finds the max age gap between students
    int maxGap;
    maxGap = maxAgeGap(sp);
    printf("Max Age Gap:%d\n",maxGap);
    //finally destroys the data set
    destroyDataSet(sp);
}



