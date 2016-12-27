bseg at 0x10 
x1 bit ACC.0
x2 bit ACC.1
y1 bit ACC.2
y2 bit ACC.3
	
cseg at 0x00
	jmp START
START:	   
// r0 - mem
// r1 - res
	mov r0, #0
	mov P1, #0
	mov P2, #0
LOOP:
	mov a, r0
	mov b, #0x10
	cjne a, b, LOOP_CONTINUE
	jmp LOOP_END
LOOP_CONTINUE:
// r = ((x1&y1)|((!x2)&y2))&((!x2)|y1)
	mov c, x2
	cpl c
	orl c, y1
	mov ACC.4, c     // (!x2)|y1)
	mov c, x1
	anl c, y1
	mov ACC.5, c	// x1&y1
	mov c, x2
	cpl c
	anl c, y2       //(!x2)&y2
	orl c, ACC.5
	anl c, ACC.4
	mov ACC.6, c 
	mov b, a
	mov a, r0
	subb a,#0x07
	jnc SECOND_BAIT
	mov a, b
	mov c, ACC.6
	mov a, P1
	rl a
	mov P1, a
	mov P1.0, c
	jmp INC_R0
SECOND_BAIT:
	mov a, b
	mov c, ACC.6
	mov a, P2
	rl a
	mov P2, a
	mov P2.0, c
INC_R0:
	inc r0
	jmp LOOP
LOOP_END:
END