#include "reg51.h"

main(){
	unsigned long x,y,S;
	// 1 - x*x/2! + x*x*x*x/4! - x*x*x*x*x*x/6!;
	// 1 - x^2/2(1+x^2/3*4(1+x^2/5*6))
	// m - x^2/2!/m^2(m + x^2/2!/m^2(m+x^2/2!/m^2))
	P3 = 0;
	while(1){
	for (x = 0; x<0xFF; x++){
		S = 0xFF;
		y = (x*x)>>8;

		S = 0xff - ((((y*S)>>8)*8)>>8);
		S = 0xff - ((((y*S)>>7)*20)>>7);
		S = 0xff - ((((y*S)>>7)*128)>>8);
		P3 = S;
	}
}
}