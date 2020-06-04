.syntax unified
.cpu cortex-m4
.text

.global Q16Divide
.thumb_func
Q16Divide:
    PUSH {R4}               
    EOR R4,R0,R1            //R4(sign) = R0(Dividend) ^ R1(divisor)
    EOR R2,R0,R0,ASR 31     //Inverts R0(Dividend) if R0 < 0
    ADD R0,R2,R0,LSR 31     //Fixes the 2's compliment
    EOR R2,R1,R1,ASR 31     //Inverts R1(Divisor) if R1 < 0
    ADD R1,R2,R1,LSR 31     //Fixes the 2's Compliment
    SDIV R2,R0,R1           //R2(quotient) = R0(Dividend) / R1(divisor)
    MLS R3,R1,R2,R0         //R3 = R0(Dividend) - R1(Divisor) * R2(Quotient)
.rept 16                    //Repeats the code 16 times
    LSL R2,R2,1             //R2(Quotient) <- R2 << 1
    LSL R3,R3,1             //R3(remainder) <- R3 << 1
    CMP R3,R1               //R3(Remainder) >= R1(Divisor)
    ITT HS                  //IT block for higher than or same
    SUBHS R3,R3,R1          //R3 = R3(Remainder) - R1(Divisor)
    ADDHS R2,R2,1           //R2(Quotient)++
.endr               
    EOR R1,R2,R4,ASR 31     //Inverts R2(quotient)
    ADD R0,R1,R4,LSR 31     //Adds 1 to fix 2's compliment
    POP {R4}
    BX LR
.end
