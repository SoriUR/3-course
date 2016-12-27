Dseg at 0x10 
x1: Ds 1
x2: Ds 1
y1: Ds 1
y2: Ds 1
	
cseg at 0x00
mov x1, #5
mov x2, #5
mov y1, #5
mov y2, #5
// r0 - res1
// r1 - res2
// r2 - res3
	mov r0, #0
	mov r1, #0
	mov r2, #0
	
	mov a,x1
	mov b,y1
	mul ab
	mov b,a
	mov a,#100
	subb a,b
	mov r0,a
	
	mov a,#10
	mov b,x2
	subb a,b
	mov b,y2
	mul ab
	mov b,a
	mov a,#100
	subb a,b
	mov r1,a
	
	mov a,#10
	mov b,y1
	subb a,b
	mov b,x2
	mul ab
	mov b,a
	mov a,#100
	subb a,b
	
	mov b,r1
	mul ab
	
END