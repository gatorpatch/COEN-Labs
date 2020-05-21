#include <stdio.h>

int32_t     Bits2Signed(int8_t bits[8]);
uint32_t    Bits2Unsigned(int8_t bits[8]);
void        Increment(int8_t bits[8]);
void        Unsigned2Bits(uint32_t n, int8_t bits[8]);

int32_t Bits2Signed(int8_t bits[8]) {
     int32_t convert = Bits2Unsigned(bits);     //my save varible
     if(convert > 127) {
         convert -= 256;
     }
     return convert;
}

uint32_t Bits2Unsigned(int8_t bits[8]) {
    uint32_t convert = 0;           //my save varible
    int i;
    for(i = 7;i >= 0;i--) {                     //basically the code given in the hint
        convert = 2*convert + bits[i];
    }
    return convert;
}

void Increment(int8_t bits[8]) {
    int i;
    for(i = 0;i < 8;i++) {              //this guy itiarates through the program and flips 1s and 0s, if it flips a 1 it breaks since it just added one
        if(bits[i] == 0) {    
            bits[i] = 1;
            break;
        }
        if(bits[i] == 1) {
            bits[i] = 0;
        }
    }
    return;
}

void Unsigned2Bits(uint32_t n, int8_t bits[8]) {
    int i = 0;
    int remain;
    while(i < 8) {          //uses the repeat division method to loop through the array
        remain = n % 2;
        n = n / 2;
        bits[i] = remain;
        i++;
    }
    return;
}
