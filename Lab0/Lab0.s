.section .data
hex_number:
.word 0xbaddecaf

.section .text
.global main

/*
NOTE about the ASM dialect. You can set it via the
".syntax" directive, see line below.

Unified syntax is stricter but more clear to see
what the instruction does to the processor, i.e.
much more tedious! To get started it is easier
to not use it. But we will use it in the instructor
supplied code for clarity. If you uncomment the line
below the code will throw a bunch of errors. You can
fix them by looking at Appendix-D of the ARMv6-M
reference manual. For now just leave the line
commented out.
*/

//.syntax unified


main:
		MOV   R3, #7
		MOV   R2, #0    //Should set the Z flag
		MOV   R7, #19
		ADD   R0, R1

		/*
		To move larger 32bit numbers into a
		register this syntax does not work.
		The compiler should complain if you
		comment out the line below. Why is that?
		*/

		//MOVS   R1, #0xbaddecaf

		/*
		To get larger numbers into registers, you
		need to load them from memory. The value
		is defined in the '.data' section above.
		The two lines below load it into R1.
		*/


		LDR	 	R0, =hex_number //loads address of hex_number
						//this is the "load literal" version LDR (Sec. A6.7.27 of ARMv6-M)

		LDR		R1, [R0]        //loads number into R1
						//this is the "register" version of LDR (Sec. A6.7.28 of ARMv6-M)


forever:
		B     forever

.end
