#include <reg51.h>
char bdata mem;
bit r;
sbit x1=mem^0;
sbit x2=mem^1;
sbit y1=mem^2;
sbit y2=mem^3;
sbit p1=P1^0;
sbit p2=P2^0;
main()
{   

	for(mem=0;mem<0x10;mem++)
		{
			r = ((x1&y1)|(!x2&y2))&(!x2|y1);
		if(mem<=0x07){
			P1<<=1;
			p1=r;
		}else{
			P2<<=1;
			p2=r;
		}
	}
	while(1);
}
//00000101 11001101