#include <reg51.h>

char code str_a[]="25,82";
char code str_b[]="77,39";

char xdata str_c[6];

main()
{
	char i = 0, char_a=0, char_b=0, buff = 0;
  for( i = 4; i>=0; i-- )
  {
		if(str_a[i]==',')
			str_c[i+1]=str_a[i];
		else{
			char_a = str_a[i]-0x30;
			char_b = str_b[i]-0x30;
			if(char_a+char_b+buff>=0x0A){
				str_c[i+1] = char_a+char_b+buff+0x26;
				buff=0x1;
			}else{
				str_c[i+1] = char_a+char_b+buff+0x30;
			}
    }
		if(i==0 & buff==0x01)
			str_c[i]=0x31;
	}
  while(1);
}
