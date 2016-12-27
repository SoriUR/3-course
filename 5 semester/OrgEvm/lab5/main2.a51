Dseg at 0x10
	aa:ds 1
	bb:ds 1
	cc:ds 1
	dd:ds 1
Cseg at 0
	jmp START
input: DB 1,2,2,-1,1,2,2,2,1,2,-2,-1,1,2,-2,2,-1,1,1,-1,-1,1,1,2,-1,2,-1,1,-1,2,-1,-2

START:
 mov DPTR, #input
 mov r2, #0
 mov r1, #0
LOOP:
mov a, r2
movc a, @a+DPTR
mov aa, a

mov a, r2
add a, #0x01
movc a, @a+DPTR
mov bb, a

mov a, r2
add a, #0x02
movc a, @a+DPTR
mov cc, a

mov a, r2
add a, #0x03
movc a, @a+DPTR
mov dd, a
	
clr c
mov a, dd
xrl a, #0x80
mov r0, a
mov a, cc
xrl a, #0x80
subb a, r0  //cc-dd 
jc RES_1 //if (dd>=cc)  goto res=1
jz RES_1
 
//(a<c)&(b!=c)||(d>=c)

clr c
mov a, bb
xrl a, #0x80
mov r0, a
mov a, cc
xrl a, #0x80
subb a,r0
jz RES_0 //if (bb != cc) goto res=0

clr c
mov a, aa
xrl a, #0x80
mov r0, a
mov a, cc
xrl a, #0x80
subb a, aa  //cc-aa
jc RES_0 //if (aa < cc) goto M0
jmp RES_1

RES_0:
clr c
jmp END_LOOP
RES_1:
setb c
END_LOOP:
mov a, P1
rl a
mov P1, a
mov P1.0,c
inc r2
inc r2
inc r2
inc r2
mov a, r1
inc r1
subb a,#0x07
jnc EXIT
jmp LOOP
EXIT:
END

	 