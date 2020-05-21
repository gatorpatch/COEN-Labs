.syntax unified
.cpu cortex-m4
.text

.global MatrixMultiply
.thumb_func
.align
MatrixMultiply: PUSH {R4-R11,LR}                    //pushes those registers, R4=row-count, R5=col-count, R6=k-count, R7=temp-a, R8=temp-b, R9=temp-c,R10=3 constant, R11=Other temp
                LDR R4,=0                           //sets the row-count to zero
                MOV R7,R0                           //sets the initial matrix pointers so we can mess with them
                MOV R8,R1
                MOV R9,R2
    rowLoopTop:     CMP R4,2                        //row >= 2 makes it branch
                    BGT rowLoopDone                 //branches to the row-done code
                    LDR R5,=0                       //sets the col-count to zero
        colLoopTop:     CMP R5,2                    //col >= 2 makes it branch
                        BGT colLoopDone             //branches to the col-done code
                        LDR R10,=3                  //Sets the 3 constant
                        MLA R11,R10,R4,R5           //R11 = (R10 * R4) + R5
                        LDR R10,=0                  //Set's R10 as constant zero
                        STR R10,[R7,R11,LSL 2]      //R10 <- R7 + (R11 * 4(LSL 2))
                        LDR R6,=0                   //sets the k-count to zero
            kLoopTop:       CMP R6,2                //k-count >= 2 makes it branch
                            BGT kLoopDone           //branches to the K-done code
                            LDR R0,[R7,R11,LSL 2]   //R0 <- R7 + (R11 * 4(LSL 2))
                            LDR R10,=3              //Sets R10 as constant 3
                            MLA R10,R10,R4,R6       //R11 = R6(k) + R10(3) * R4(row)
                            LDR R1,[R8,R10,LSL 2]   //R7 <- R8() + (R10(othertemp) * 4(done with LSL 2))
                            LDR R10,=3              //Sets the R10 constant as 3
                            MLA R10,R10,R6,R5       //R11 = R10(3) * R6(k-count) + R5(col-count)
                            LDR R2,[R9,R10,LSL 2]   //R9 <- R9(temp-c) + (R11(othertemp) * 4(LSL 2))
                            BL MultAndAdd           //Calls the MultAndAdd
                            STR R0,[R7,R11,LSL 2]   //R0 <- R7 + (R11 * 4(LSL 2))
                            ADD R6,R6,1             //Iterates the K-count
                            B kLoopTop              //branches back to top of K-loop
        kLoopDone:      ADD R5,R5,1                 //iterates the col-count
                        B colLoopTop                //branches back to the top of col-loop
    colLoopDone:    ADD R4,R4,1                     //iterates the row-count
                    B rowLoopTop                    //branches back to the top of row-loop
rowLoopDone:    POP {R4-R11,PC}
.end 
