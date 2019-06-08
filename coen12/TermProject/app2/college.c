#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include "dataset.h"

int main() {
    SET *sp = createDataSet(3000);
    srand(time(0));

    int idNum,age,i;
    idNum = 0;
    for(i = 0;i < 1000;i++) {
        idNum = idNum + ((rand() % 2) + 1);
        age = ((rand() % 30) + 18);
        insertElement(sp,idNum,age);
    }
    int randStuID, randAge, randLocation;
    randStuID = ((rand() % 2000) + 1);
    randAge = ((rand() % 30) + 1);
    randLocation = searchID(sp,randStuID);

    if(randLocation != -1) {
        removeElement(sp,randStuID);
    }

    destroyDataSet(sp);
}
