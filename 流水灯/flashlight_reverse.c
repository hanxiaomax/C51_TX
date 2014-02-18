/*不断加速，再还原，再反向*/
#include<reg52.h>
#include<intrins.h>
void delay_ms(unsigned int time);/*延时_ms*/
void flash(unsigned int times);/*闪烁times次*/
sbit beep=P2^3;
void main()
{	
	unsigned int round=0;
	while(1)
	{
		unsigned int i,temp;/*使用unsigned比较好，占用内存小*/
		if(round==5)/*计数器归零，保证最短延时*/
			round=0;
		temp=0xfe;
		for(i=0;i<8;i++)
		{
			P1=temp;
			delay_ms(500-round*100);
			temp=_crol_(temp,1);/*cror用高位补低位*/
		}
		temp=0x7f;
		for(i=0;i<8;i++)
		{
			P1=temp;
			temp=_cror_(temp,1);
			delay_ms(500-round*100);
		}
		round++;
		flash(round);/*第几轮就闪烁几次*/
		
	}
}
void flash(unsigned int times)
{
	while(times>0)
	{
		P1=0xff;
		delay_ms(200);
		P1=0x00;
		delay_ms(200);
		times--;
		beep=0;
		delay_ms(200);
		beep=1;
	}
}
/*当内外均为unsigned int且内层为110时，外层i的值大致为毫秒数*/
void delay_ms(unsigned int time)/*unsigned int 0-255*/
{
	int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<110;j++)/*双层嵌套增加延时时间*/
				;
}