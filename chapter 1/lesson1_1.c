/*单位操作*/
#include<reg51.h>
sbit D1=P1^0;/*单片机P1口,这里的P必须是大写*/
sbit D2=P1^2;
sbit D3=P1^4;
sbit D4=P1^6;
void main()
{
	D1=D2=D3=D4=0;
}