#include <reg51.h>
float r,r1,r2,r3,x1=0.5,x2=0.5,y1=0.5,y2=0.5;
main()
{   
	{
		r1=(1-x1*y1);
		r2=(1-(1-x2)*y2);
		r3=(1-x2*(1-y1));
		r =r1*r2*r3;
	}
	while(1);
}