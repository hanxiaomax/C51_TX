/*--------------------------------------
控制DAC0832芯片输入电流，使D12亮度逐渐变化，
在最亮和最暗的时候蜂鸣器响
---------------------------------------*/
#include<reg52.h>
sbit CSDA=P3^2;//片选，低电平有效
sbit my_WR=P3^6;//写选通，低电平有效。WR在reg52中定义过
sbit BEEP=P2^3;
sbit DULA=P2^6;
sbit WELA=P2^7;
void delay_ms(unsigned int );
void main()
{
	unsigned int val;//数字量电压
	unsigned int flag;//电流最大值标志
	DULA=0;//打开U1锁存
	WELA=0;//打开U2锁存
	//如果不打开锁存，数码管会受到干扰
	CSDA=0;//低电平
	my_WR=0;//低电平
	P0=0;
	while(1)
	{
		if(flag==0)
		{
			val+=5;
			P0=val;//对P0口整体操作
			if(val==255)
			{
				flag=1;
				BEEP=0;
				delay_ms(100);
				BEEP=1;
			}
			delay_ms(50);//状态维持50ms
		}
		else //flag==1
		{
			val-=5;
			P0=val;
			if(val==0)
			{
				flag=0;
				BEEP=0;
				delay_ms(100);
				BEEP=1;
			}
			delay_ms(50);
		}
	}
}

void delay_ms(unsigned int times)
{
	unsigned int i,j;
	for(i=0;i<times;i++)
		for(j=0;j<110;j++)
		;
}