// code to make all the LEDs turn white
.section .text;
.global main;
main:
	LDR R4,=0x2000;
	LDR R5,=0x40048038;
	STR R4,[R5];
	LDR R4,=0x100;
	LDR R5,=0x4004D040;
	STR R4,[R5];
	LDR R5,=0x4004D018;
	STR R4,[R5];
	MOV R0,#250;
	LSL R0,R0,#3;
	LDR R5,=0x4004D008;
	STR R4,[R5];
	LDR R5,=0x4004D00C;
	STR R4,[R5];
	LDR R4,=0x1004C;
	LDR R5,=0x400FF114;
	STR R4,[R5];
	R0:SUB R0,#1;
	BNE R0;
	LDR R0,=0x404040;
	LDR R1,=0x8;
	LDR R2,=0x400FF104;
	LDR R3,=0x400FF108;
	MOV R4,R0;
	MOV R5,#1;
	LSL R5,#23;
	R2:MOV R6,R5;
	AND R6,R4,R6;
	BNE R4;
	STR R1,[R2];
	ADD R7,#1;
	MOV R8,R7;
	STR R1,[R3];
	B R6;R4:
	STR R1,[R2];
	MOV R7,#1;
	MOV R8,R7;
	ADD R7,#1;
	MOV R7,R8;
	LSL R7,#1;
	CMP R7,R8;
	ADD R7,R8;
	MOV R7,R8;
	STR R1,[R3];
	R6:LSR R5,#1;
	CMP R5,#0;
	BNE R2;
	LDR R0,=0x404040;
	LDR R1,=0x8;
	LDR R2,=0x400FF104;
	LDR R3,=0x400FF108;
	MOV R4,R0;
	MOV R5,#1;
	LSL R5,#23;
	R1:MOV R6,R5;
	AND R6,R4,R6;
	BNE R3;
	STR R1,[R2];
	ADD R7,#1;
	MOV R7,R8;
	STR R1,[R3];
	B R5;
	R3:STR R1,[R2];
	MOV R7,#1;
	MOV R8,R7;
	ADD R7,R8;
	MOV R7,R8;
	ADD R7,#1;
	MOV R7,R8;
	LSL R7,#1;
	CMP R7,R8;
	STR R1,[R3];
	R5:LSR R5,#1;
	CMP R5,#0;
	BNE R1;
	R7:B R7;
.end
