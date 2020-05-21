.syntax unified
.cpu    cortex-m4
.text

.global UseLDRB
.thumb_func
UseLDRB:    
            .rept 512                       //Repeats the next lines 512 times
            LDRB R2,[R1],1                  //Copies the date one byte at a time
            STRB R2,[R0],1
            .endr
            BX LR

.global UseLDRH
.thumb_func
UseLDRH:
            .rept 256                       //Repeats 256 times
            LDRH R2,[R1],2                  //copies 2 bytes, [] means it removes a command by adding the 2 constant to the address of r2, which iterates it correctly 2 bytes ahead
            STRH R2,[R0],2
            .endr
            BX LR

.global UseLDR
.thumb_func
UseLDR:
            .rept 128                       //Repeats 128 times
            LDR R2,[R1],4                   //copies 4 bytes
            STR R2,[R0],4
            .endr
            BX LR

.global UseLDRD
.thumb_func
UseLDRD:
            .rept 64                        //Repeats 64 times
            LDRD R3,R2,[R1],8               //Copies 8 bytes at a time
            STRD R3,R2,[R0],8
            .endr
            BX LR

.global UseLDM
.thumb_func
UseLDM:   
            PUSH {R4-R9}
            .rept 16                        //repeats 16 times
            LDMIA R1!,{R2-R9}               //Pushes the 32 bytes into the r2-r9, using a write-back flag to update addresses of the data
            STMIA R0!,{R2-R9}
            .endr
            POP {R4-R9}
            BX LR
.end
