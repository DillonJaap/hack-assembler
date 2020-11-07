// make sure your assembler skips comments
// also make sure it skips  over blank lines


// leading and trailing white space
A=D-M
    A=D-M
    A=D-M			//space



(label_test)
// make sure you can run any possible instruction
X53
x53
D-M// this should be the same as D-M

// test with dest
A=X53
A=D-M // same as A=X53

// test with jump
X53;JMP
D-M;JMP

// test with jump and dest
A=X53;JMP
A=D-M;JMP

// dest assembler directives
.EQU cool 12345
@cool
.EQU oh_cool 7645
@oh_cool
.EQU bin_num 0b101
@bin_num


// properly use hex and binary
@1234
@0x646A
@0X10
@0b1
@0B101000000000000


// creates variables (because there are no corresponding labels)
@test
@thing

// LEGAL labels
($MONEY$)
(___)
(_.$:)
(Xx_$6969$_xX)
