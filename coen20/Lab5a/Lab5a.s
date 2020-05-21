.syntax unified
.cpu cortex-m4
.text

.global MatrixMultiply
.thumb_func
.align
MatrixMultiply:
                PUSH {R4-R11,LR}
outerFor:
                LDR R4,=0               //Sets row counter to zero
                CMP R4,2                //compares row > 2
                BGT innerFor            //Branches if row > 2
                ADD R4,R4,1             //iterates row counter
                B outerFor              //branches back to start of loop
innerFor:
                LDR R5,=0               //Sets column counter to zero
                CMP R5,2                //checks if the column > 2
                BGT kLoop               //Branches if column > 2
                LDR R7,=R0              //Saves the A matrix pointer
                LDR R0,=0               //Set A>row,col to zero
                ADD R5,R5,1             //iterates the column counter
                B innerFor              //branches back to the start of the for
kLoop:          
                LDR R6,=0               //Sets k-count to zero
                CMP R6,2                //checks if the k-count > 2
                BGT outerFor            //branches when K-count > 2
                LDR R10,=3              //Loads the constant 3
                LDR R9,=0               //puts a zero in R9 before we STR into
                MLA R11,R10,R4,R5       //R11 = R10(3) * R4(row) + R5(Column)
                STR R9,[R7,R11,LSL 2]   //I heard this from when you were helping rohil, but I'm a bit consfused on exactly what it is doing 
                //Also need help calling the mult and add
                

for (row = 0; row < 3; row++)
	{
	for (col = 0; col < 3; col++)
		{
		A[row][col] = 0 ;
		for (k = 0; k < 3; k++)
			{
			A[row][col] = MultAndAdd(A[row][col], B[row][k], C[k][col]) ;
			}
		}
	}

