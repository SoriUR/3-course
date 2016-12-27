#include <reg51.h>
 
void div(){
    unsigned int A;
    long S;
    char i;
		int ov=0;
	
    S=P1<<8;
		//S=S&0xffff;
    A=P2<<8;
	
		if(S>=A){
			ov=1;
			goto out;
		}
		
    for (i=0 ; i<8; i++ ){  
        S = S<<1;
        if ((S-A)>=0){
            S = S-A+1;
				}
    }
		
		//S=S;
    P3 = S; //Write result of DIV to P3
		out:
		if(ov==1){
			A=0xFF;
			P3=0x00;
		}
}
 
void mul(){                  
    unsigned short handl = P1; //Mult_1 
    unsigned char val2 = P2; //Mult_2
    unsigned short result = 0; //Result
    char ost;
    int i = 0;
    for (i = 0; i< 8; i++){
        if (0x01&val2){ //Even or not (2)?
            result += handl;
        }
        handl<<=1;
        val2>>=1;
    }  
    ost = result;
    P0 = ost;
    P3 = result>>8;
}
 
main()
{
//  P1 INPUT
//  P2 INPUT
//  P3 OUTPUT 
//  P0 OUTPUT  
    mul(); 
	
//  P2 OUTPUT;
    div();
    while(1);
}