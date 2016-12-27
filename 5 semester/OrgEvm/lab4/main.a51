//P2 = 0;
//S = 0xFF;
//y = (x*x)>>8;
//S = 0xFF - ((y*S)>>8>>1);
//S = 0xFF + ((y*S)>>8>>1);
//S = 0xFF - ((y*S)>>8>>1);
//P2 = 0x1F;
//P3 = S;

CSEG AT 0
START:
	mov r0, #0 // r0 = x;
LOOP:
	mov a,r0
	mov b,r0
	mul ab
	mov a,b //a=x*x>>8
	mov r1,a //r1=y=x*x>>8
	
	mov a,#0xFF
	mov b,r1
	mul ab //s*y
	mov a,b //s*y>>8
	mov b,#0x04
	mul ab //s*y>>8*4
	mov a,b //s*y>>8*4>>8
	mov b,a 
	mov a,#0x80
	subb a,b //0x80-s*y>>8>>1

	mov b,r1
	mul ab //s*y
	mov a,b //s*y>>8
	mov b,#0x0A
	mul ab //s*y>>8*4
	mov a, b //s*y>>8*12>>8
	add a,#0x80

	mov b,r1
	mul ab //s*y
	mov a,b //s*y>>8
	mov b,#0x40
	mul ab
	mov a,b //s*y>>8*64>>8
	mov b,a
	mov a,#0x80
	subb a,b //0x8F-s*y>>8>>1
	
	mov P3, a
	inc r0
	cjne r0, #0x80, LOOP //jump to loop
	jmp START
END