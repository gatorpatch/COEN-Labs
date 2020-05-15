.syntax unified
.cpu cortex-m4
.text

.global PutNibble
.thumb_func
.align
PutNibble:
    PUSH {R4}       //Pushes the R4 register
    LSR R3,R1,1     //R3 <- R1(which) >> 1 bit(takes the given nibble position and divides it by 2(since each byte has 2 nibbles this is needed)
    ADD R0,R0,R3    //R0 = R0(starting address) + R3(shifted which)
    AND R4,R1,1     //R4 <- R1 & 1(Since you shifted which right, checks to see what the value of the single bit you lost on the right is)
    LDR R3,=15      //Sets the constant at 15
    LDRB R1,[R0]    //Loads address of R0 into R1
    CMP R4,1        //Compares R4 == 1
    ITE EQ          //IT block that fetches and decodes both the LSLEQ and LSLNE commands
    LSLEQ R2,R2,4   //If R4 == 1, R2 <- R2 << 4(Moves the given r2 into the other nibble on R2)
    LSLNE R3,R3,4   //If R4 != 1, R3 <- R3 << 4(moves the 15 into the other nibble on R3)
    AND R1,R1,R3    //R1 <- R1 & R3 (combines the R1 with the 15, will add the one that was dropped off the left based on the last EQ)
    ORR R1,R1,R2    //R1 <- R1 | R2 (combines the R1 with the value of R2, since you did the commands above it will edit the correct nibble here)
    STRB R1,[R0]    //Stores R0 in R1
    POP {R4}        //Pops that R4 from earlier
    BX LR


.global GetNibble
.thumb_func
.align
GetNibble:          //Does the same start as the code to pull the nibble out of the bitfield
    LSR R3,R1,1     //R3 <- R1(which) >> 1 
    ADD R0,R0,R3    //R0 = R0(nibble pointer) + R3
    AND R2,R1,1     //R2 <- R1(which) & 1
    LDR R3,=15      //Sets the constant at 15(all ones)
    LDRB R1,[R0]    //Loads R0 into R1
    CMP R2,1        //Compares R2 == 1
    ITE EQ          //IT block fetches and decodes the next two commands
    LSREQ R1,R1,4   //If R2 == 1, R1 <- R1(which) >> 4
    ANDNE R1,R1,R3  //If R2 != 1, R1 <- R1(which) & R3
    MOV R0,R1       //Copies R1 into R0
    BX LR
.end
