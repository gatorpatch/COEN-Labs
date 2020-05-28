.syntax unified
.cpu cortex-m4
.text

.global Root1
.thumb_func
Root1:
    PUSH {R4,R5,LR}     //Pushes R4 and R5 to the stack so we can use them as temp registers
    VMOV R4,S0          //sets R4=a
    VMOV R5,S1          //sets R5=b
    BL Discriminant     //Calls the Discriminant function
    VSQRT.F32 S3,S0     //S3 <- sqrt(S0(discriminant))
    VMOV S0,R4          //S0 gets set as a
    VMOV S1,R5          //S1 gets set as b
    VNEG.F32 S1,S1      //Inverts S1 to it's negative
    VADD.F32 S3,S1,S3   //S3 <- S1(-b) + sqrt(discriminant)
    VADD.F32 S0,S0,S0   //S0 <- S0 + S0(S0 *2)
    VDIV.F32 S0,S3,S0   //S0 <- (-B+sqrt(discriminant))/(a*2.0)
    POP {R4,R5,PC}

.global Root2
.thumb_func
Root2:
    PUSH {R4,R5,LR}     //Pushes R4 and R5 to the stack so we can use them as temp registers
    VMOV R4,S0          //sets R4=a
    VMOV R5,S1          //sets R5=b
    BL Discriminant     //Calls the discrimant function
    VSQRT.F32 S3,S0     //S3 <- Sqrt(S0(discriminant))
    VMOV S0,R4          //S0 gets set as a
    VMOV S1,R5          //S1 gets set as b
    VNEG.F32 S1,S1      //Inverts S1 to it's negative
    VSUB.F32 S3,S1,S3   //S3 <- S1(-b)-sqrt(discriminant)
    VADD.F32 S0,S0,S0   //S0 <- S0 + S0(S0 *2)
    VDIV.F32 S0,S3,S0   //S0 <- (-b)-sqrt(discriminant))/2a
    POP {R4,R5,PC}

.global Discriminant
.thumb_func
Discriminant:
    VMUL.F32 S1,S1,S1   //S1(b)*S1(b)
    VMOV S3,4.0         //sets S3 as constant 4.0
    VMUL.F32 S0,S0,S3   //S0 * 4
    VMLS.F32 S1,S0,S2   //S0 = B*B - (4*a*c)
    VMOV S0,S1          //S0 <- S1
    BX LR

.global Quadratic
.thumb_func
Quadratic:
    VMLA.F32 S3,S0,S2   //S3 <- C + X*B
    VMUL.F32 S0,S0,S0   //S0 <- X^2
    VMUL.F32 S1,S1,S0   //S1 <- A * x^2
    VADD.F32 S0,S3,S1   //Adds the last two together
    BX LR
.end
