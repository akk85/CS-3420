.section .text
.global fib


//Set up constants for port. Don't Change!
.equ 	PCRD5, 		0x4004C014 //PORTD_PCR5   (GREEN), the manual has these backward
.equ 	SCGC5, 		0x40048038 //SIM_SCGC5    address
.equ 	PDDRD,  	0x400FF0D4 //GPIOB_PDDR   address
.equ 	PCORD,  	0x400FF0C8 //GPIOB_PCOR   address
.equ 	PSORD,  	0x400FF0C4 //GPIOB_PSOR   address


.equ 	bit_twelve, 	0x00001000  // 1 << 12, for turning on port clock
.equ 	bit_eight, 	0x00000100  // 1 << 8,  for setting MUX to GPIO
.equ	bit_five, 	0x00000020  // 1 << 5,  for manipulating PIN


/*
---  Write your code below this line ---
Feel free to include additional labels as needed.
*/

main:
	MOV		R0, #7
	BL		LEDSETUP
	BL		fib
	BL 		morse_digit
	B		forever
fib:
    PUSH	{R4-R7, LR}
    CMP     R0, #0
    BLE		.return_zero
    CMP     R0, #1
    BEQ     .return_one

    //recursive call fib(n-1)
    SUB     R0, R0, #1
    BL      fib
    MOV     R4, R0

    //recursive call fib(n-2)
    LDR     R5, [SP, #24]
    SUB     R0, R5, #1
    BL      fib
    ADD     R0, R4, R0
    POP     {R4-R7, PC}



.return_zero:
	MOV		R0, #0
	POP		{R4-R7, PC}

.return_one:
	MOV		R0, #1
	POP		{R4-R7, PC}


morse_digit:
	PUSH	{LR}
	CMP     R0, #0
    BEQ     digit_0
	CMP     R0, #1
    BEQ     digit_1
    CMP     R0, #2
    BEQ     digit_2
    CMP     R0, #3
    BEQ     digit_3
    CMP     R0, #4
    BEQ     digit_4
    CMP     R0, #5
    BEQ     digit_5
    CMP     R0, #6
    BEQ     digit_6
    CMP     R0, #7
    BEQ     digit_7
    CMP     R0, #8
    BEQ     digit_8
    CMP     R0, #9
    BEQ     digit_9
    B       end_morse
    B		forever

//Morse code for each digit
digit_1:
    // Morse code for digit 1: dot dash dash dash dash
    PUSH 	{LR}
    BL      dot
    BL      dash
    BL      dash
    BL      dash
    BL      dash
    POP		{PC}

digit_2:
    // Morse code for digit 2: dot dot dash dash dash
    PUSH 	{LR}
    BL      dot
    BL      dot
    BL      dash
    BL      dash
    BL      dash
	POP		{PC}
digit_3:
    // Morse code for digit 3: dot dot dot dash dash
	PUSH 	{LR}
    BL      dot
    BL      dot
    BL      dot
    BL      dash
    BL      dash
	POP		{PC}
digit_4:
    // Morse code for digit 4: dot dot dot dot dash
	PUSH 	{LR}
    BL      dot
    BL      dot
    BL      dot
    BL      dot
    BL      dash
	POP		{PC}
digit_5:
    // Morse code for digit 5: dot dot dot dot dot
    PUSH 	{LR}
    BL      dot
    BL      dot
    BL      dot
    BL      dot
    BL      dot
	POP		{PC}
digit_6:
    // Morse code for digit 6: dash dot dot dot dot
    PUSH 	{LR}
    BL      dash
    BL      dot
    BL      dot
    BL      dot
    BL      dot
	POP		{PC}
digit_7:
    // Morse code for digit 7: dash dash dot dot dot
    PUSH 	{LR}
    BL      dash
    BL      dash
    BL      dot
    BL      dot
    BL      dot
	POP		{PC}

digit_8:
    // Morse code for digit 8: dash dash dash dot dot
    PUSH 	{LR}
    BL      dash
    BL      dash
    BL      dash
    BL      dot
    BL      dot
	POP		{PC}
digit_9:
    // Morse code for digit 9: dash dash dash dash dot
    PUSH 	{LR}
    BL      dash
    BL      dash
    BL      dash
    BL      dash
    BL      dot
	POP		{PC}
digit_0:
    // Morse code for digit 0: dash dash dash dash dash
    PUSH 	{LR}
    BL      dash
    BL      dash
    BL      dash
    BL      dash
    BL      dash
	POP		{PC}

//dot and dash
dot:
	PUSH	{LR}
	BL		LEDSETUP
	BL		LEDON
	BL		DELAY_DOT
	BL		LEDOFF
	BL		DELAY_DOT
	POP		{PC}
dash:
	PUSH	{LR}
	BL		LEDSETUP
	BL		LEDON
	BL		DELAY_DASH
	BL		LEDOFF
	BL		DELAY_DASH
	POP 	{PC}

//delay subroutine
DELAY_DOT:
    LDR   R1, =DELAY_DOT_COUNT
    LDR   R1, [R1]
DELAY_LOOP_DOT:
    SUB		R1, R1, #1
    BNE		DELAY_LOOP_DOT
    BX		LR

// Delay subroutine for a dash
DELAY_DASH:
    LDR   R1, =DELAY_DASH_COUNT
    LDR   R1, [R1]
DELAY_LOOP_DASH:
    SUB		R1, R1, #1
    BNE		DELAY_LOOP_DASH
    BX		LR

/*
---  And above this one ---
*/

// Call this function first to set up the LED
// You only need to call this once
LEDSETUP:
	PUSH  {R4, R5}    //To preserve R4 and R5
	LDR   R4, =bit_twelve // Load the value 1 << 12
	LDR   R5, =SCGC5
	STR   R4, [R5]

	LDR   R4, =bit_eight  //MUX Port to be GPIO
	LDR   R5, =PCRD5
	STR   R4, [R5]

	LDR   R4, =bit_five
	LDR   R5, =PDDRD
	STR   R4, [R5]
	POP   {R4, R5}
	BX    LR

// The functions below are for you to use freely
LEDON:
	PUSH  {R4, R5}
	LDR   R4, =bit_five
	LDR   R5, =PCORD
	STR   R4, [R5]
	POP   {R4, R5}
	BX    LR

LEDOFF:
	PUSH  {R4, R5}
	LDR   R4, =bit_five
	LDR   R5, =PSORD
	STR   R4, [R5]
	POP   {R4, R5}
	BX    LR

//wait forever
forever:
	B		forever
	.end


