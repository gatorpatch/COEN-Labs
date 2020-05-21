.syntax unified
.cpu cortex-m4
.text

.global Zeller1 
.thumb_func
.align
Zeller1:
        PUSH {R4-R6}
        LDR R5,=1           //Set's R5 as constant 1
        ADD R0,R0,R2        //Adds the k and the D together
        LSL R6,R5,2         //Sets R6 to constant 4
        UDIV R2,R2,R6       //Divides R2(D) by 4, unsigned via the lab instruction to discard fractions
        UDIV R4,R3,R6       //Divides R3(C) by 4 and puts it in R4
        LSL R3,R3,1         //Times C by 2
        ADD R0,R0,R2        //Adds the D/4 to the total
        ADD R0,R0,R4        //Adds the C/4 to the total
        LDR R6,=13          //Sets R6 to constant 13 
        MUL R1,R1,R6        //R1(m) = R1(m) * 13
        SUB R1,R1,1         //R1 = R1 - 1
        ADD R6,R5,R5,LSL 2  //Sets R6 as constant 5
        UDIV R1,R1,R6       //Divides the 13m-1 by 5
        ADD R0,R0,R1        //Adds R1(13m-1/5) to the total
        SUB R0,R0,R3        //total - 2c
        LDR R6,=7           //Sets the R6 as constant 7
        SDIV R4,R0,R6       //Divides F by 7
        MLS R0,R6,R4,R0     //Calculates the remainder R0 = R0 - R6 * R4
        CMP R0,0            //checks if the remainder is negative or positive
        IT LT
        ADDLT R0,R0,R6      //Adds 7 to f if negative
        POP {R4-R6}
        BX LR

.global Zeller2
.thumb_func
.align
Zeller2:
        PUSH {R4-R7}
        LDR R5,=1           //Set's R5 as constant 1
        ADD R0,R0,R2        //Adds the k and the D together
        LSR R2,R2,2         //Divides R2(D) by 4 using the shift right 2
        LSR R4,R3,2         //Divides R3(C) by 4 using the shift right
        LSL R3,R3,1         //Times C by 2
        ADD R0,R0,R2        //Adds the D/4 to the total
        ADD R0,R0,R4        //Adds the C/4 to the total
        LDR R6,=13          //Sets R6 to constant 13 
        MUL R1,R1,R6        //R1(m) = R1(m) * 13
        SUB R1,R1,1         //R1 = R1 - 1
        LDR R6,=3435973837  //Magic constant for dividing (13m-1) by 5
        UMULL R7,R6,R6,R1   //R6.R7 <- R6(magic num) * R1(13m-1)
        LSR R1,R6,2         //Shifts R6 right 2
        ADD R0,R0,R1        //Adds R1(13m-1/5) to the total
        SUB R0,R0,R3        //total - 2c
        MOV R4,R0           //saves the dividend
        LDR R5,=7           //Sets the R6 as constant 7
        LDR R6,=2454267027  //Another magic constant for diving f by 7
        SMMLA R6,R6,R0,R0   //R6 <- R0 + (R0 * R6)
        LSR R0,R0,31        //part of the integer division code
        ADD R0,R0,R6,ASR 2  //R0 <- R0 + (R6 << 2)
        MLS R0,R5,R0,R4     //Calculates the remainder R0 = R4 - R5 * R0
        CMP R0,0            //checks if the remainder is negative or positive
        IT LT               
        ADDLT R0,R0,R6      //Adds 7 to f if negative
        POP {R4-R7}
        BX LR

.global Zeller3
.thumb_func
.align
Zeller3:
        PUSH {R4-R6}
        LDR R5,=1           //Set's R5 as constant 1
        ADD R0,R0,R2        //Adds the k and the D together
        LSL R6,R5,2         //Sets R6 to constant 4
        UDIV R2,R2,R6       //Divides R2(D) by 4, unsigned via the lab instruction to discard fractions
        UDIV R4,R3,R6       //Divides R3(C) by 4 and puts it in R4
        LSL R3,R3,1         //Times C by 2
        ADD R0,R0,R2        //Adds the D/4 to the total
        ADD R0,R0,R4        //Adds the C/4 to the total
        LSL R6,R1,3         //R6 <- R1(m) * 8
        ADD R1,R1,R1,LSL 2  //R1 <- R1 + (R1 * 4) (essentially m*5)
        ADD R1,R1,R6        //Adds the two multipliers together to get m * 13
        SUB R1,R1,1         //R1 = R1 - 1
        ADD R6,R5,R5,LSL 2  //Sets R6 as constant 5
        UDIV R1,R1,R6       //Divides the 13m-1 by 5
        ADD R0,R0,R1        //Adds R1(13m-1/5) to the total
        SUB R0,R0,R3        //total - 2c
        LDR R6,=7           //Sets the R6 as constant 7
        SDIV R4,R0,R6       //Divides F by 7
        ADD R0,R4           //Adds an extra r4 to r0, because we are dividing by 7 instead of eight (look at next code if confused, it should make sense)
        LSL R4,3            //R4 * 8
        SUB R0,R0,R4        //subtracts (r4 * 8) from the (r0 + R4), essentially doing R0 = R0 - (7 * R4)
        CMP R0,0            //checks if the remainder is negative or positive
        IT LT
        ADDLT R0,R0,R6      //Adds 7 to f if negative
        POP {R4-R6}
        BX LR


