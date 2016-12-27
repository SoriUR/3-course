XSEG AT 0
    result: DS 2

CSEG AT 0
    jmp START
    input: DB 0x83,0xE7

START:
	mov P0, #0
	clr a
//---------MUL------------
// r0 - lowHandl || P1
// r1 - highHandl
// r2 - val2 || P2
// r3 - lowRes
// r4 - highRes
// r5 - i
	mov r0, P1
	mov r1, #0
	mov r2, P2
	mov r3, #0
	mov r4, #0
	mov r5, #8
MUL_LOOP:
// check for loop end
	mov a, r5
	jz MUL_LOOP_END
// if (0x01&val2)
	mov a, r2
	anl a, #0x01
	jz MUL_ROL_DATA
// result += handl;
	mov a, r3
	mov b, r0
	add a, b
	mov r3, a
	mov a, r4
	mov b, r1
	addc a, b
	mov r4, a
MUL_ROL_DATA:
// val2>>=1;
	mov a, r2
	rr a
	mov r2, a
// handl<<=1;
	mov a, r0
	rlc a
	mov r0, a
	mov a, r1
	rl a
	mov b, #0
	addc a, b
	mov r1, a
// i++
	dec r5
	jmp MUL_LOOP		
MUL_LOOP_END:

	mov P3, r4
	mov P0, r3
//---------DIV---------------
	clr a
// r0 - lowS || P1
// r1 - highS
// r2 - lowA || P2
// r3 - highA
// r5 - i
	mov r0, #0
	mov r1, P1
// A=P3<<8
	mov r2, #0
	mov r3, P2
// i = 8
	mov r5, #8
DIV_LOOP:
	mov a,	r5
//i=0?
	jz DIV_LOOP_END
	clr c
	mov a, r0
	rlc a
	mov r0, a
	mov a, r1
	rl a
	addc a, #0
	mov r1, a
// if (S-A >= 0){
	add a, #0
	mov b, r3
	subb a, b
	jc DIV_SKIP_MATH
	mov r1, a
	mov a,r0
	mov b,r2
	subb a,b
	inc a
	mov r0, a
DIV_SKIP_MATH:
	dec r5
	jmp DIV_LOOP
DIV_LOOP_END:
	mov P3, r0
	//mov P0, r0
	mov P0, #0
	jmp START
END