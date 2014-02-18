#include<reg52.h>

sbit led=P1^0; 
sbit key=P3^4;/*使用独立键盘第一个键*/

void main()
{
	while(1)
	{
		key=0xff;/*输入复位*/
		if(key==0)/*如果检测到低电平*/
			led=0;/*点亮led*/
		else
			led=1;
	}
}