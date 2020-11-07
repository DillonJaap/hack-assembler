//**********************************
// ERROR CHECKING
//**********************************

// can't redefine directives/labels
.EQU cool 11110
.EQU cool 11111
(label_test)

// not a redefinition
@okay
@okay

//Destination
B=D-M
B=D-M;JMP

// jump
D-M;JPM
D-M;POOP
A=D-M;JPM

// comp
D-D
D-D;JMP
A=D-D
A=M-A;JEQ

// all together
B=Y&X;JPM
B=2;JPM
B=2
3;PPD

// A-type illegal value integer is to large
@0b1000000000000000
@32768 // max is 32767
@0x8000

// illegal labels
(%okay%)
())
()
(okay
(123dk)
(YEET*&)
(//okay)
(
(//test
)

@
@123obs

// illegal EQU
.EQ yes 1
.EQU 12yes 408
.EQU yes90
.EQU 409
.EQU
.
.EQUsdfhjk
.EQU18

// x-instruction
xZo
xFF // to large
