.section .text
.global set_led
.type set_led %function

.equ 	PSOR, 	0x400FF104
.equ 	PCOR, 	0x400FF108
.equ	third, 	0x00000008

led_setup:
	PUSH {R4, R5, R6, LR}
	LDR R4, =PSOR
	LDR R5, =PCOR

	MOV R6, R0
	MOV R3, #1
	LSL R3, #23

loop:
	AND R6, R3
	BEQ zero
	B one

bit_one:
	LDR R2, =third
	STR R2, [R4]
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
	STR R2, [R5]
	B low

bit_zero:
	LDR R2, =third
	STR R2, [R4]
	NOP
	STR R2, [R5]
make_low:
	MOV R6, R0
	LSR R3, #1
	CMP R3, #0
	BNE check_loop

end:
	POP {R4, R5, R6, PC}





