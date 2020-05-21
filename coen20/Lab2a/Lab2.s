.syntax unified
.cpu    cortex-m4
.text


.global Add
.thumb_func
Add:    
        ADD     R0,R0,R1    //adds R0 and R1 and puts it in R0
        BX      LR

.global Less1
.thumb_func
Less1:
        SUB     R0,1        //subtracts the value of R0 by 1
        BX      LR

.global Square2x
.thumb_func
Square2x:
        PUSH {LR}           //needed to use another function
        ADD R0,R0,R0        //Adds R0 to itself, storing the sum in R0
        BL Square
        POP {PC}            //returns the value from the stack

.global Last
.thumb_func
Last:
        PUSH {R4,LR}        //temp varible needed, R4 is that one
        MOV R4,R0           //Moves value from r0 to r4, so we can get square root of R0 and add
        BL SquareRoot
        ADD R0,R0,R4
        POP {R4,PC}         //pops out the value of temp varible and returns the value

.end
