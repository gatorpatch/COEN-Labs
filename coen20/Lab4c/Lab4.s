.syntax unified
.cpu cortex-m4
.text

.global MxPlusB
.thumb_func
.align
MxPlusB:    
            PUSH {R4}
            MUL R1,R0,R1        //mtop = x * mtop = dvnd
            MUL R0,R1,R2        //dvnd = dvnd * dvsr(mbtm)
            ASR R0,R0,31        //dvnd >> 31
            MUL R0,R0,R2        //(dvnd * dvsr >> 31) * dvsr(mbtm)
            LSL R0,R0,1         //((dvnd * dvsr >> 31) * dvsr) << 1
            ADDS R0,R0,R2       //(((dvnd * dvsr >> 31) * dvsr) << 1) + dvsr(mbtm), better known as the rounding
            MOV R4,R2           //Saves the mbtm, since we're gonna divide stuff by 2 but we'll need it later
            LDR R2,=2           //sets R2 to 2, so we can divide stuff for the quotient
            SDIV R0,R0,R2       //rounding/2
            ADDS R0,R0,R1       //rounding/2 + dvnd(mtop)
            SDIV R0,R0,R4       //divides the last value by dvsr(mbtm), aka the quotient value
            ADDS R0,R0,R3       //mx(value in R0) + b(R3)
            POP {R4}
            BX LR
.end
