#include<reg52.h>

sbit led=P1^0; 
sbit key=P3^4;/*ʹ�ö������̵�һ����*/

void main()
{
	while(1)
	{
		key=0xff;/*���븴λ*/
		if(key==0)/*�����⵽�͵�ƽ*/
			led=0;/*����led*/
		else
			led=1;
	}
}