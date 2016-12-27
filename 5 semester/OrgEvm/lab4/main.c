#include "reg51.h"
#include "math.h"

main(){
	float x,y;
	while(1){
		for (x=0;x<1;x+=0.01){	 
			P2 = 0;
			y = cos(x);
			P2 = 0x7F;
			P3 = 100*y;
		}
	}
}