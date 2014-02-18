/*定时器中断--双位数码管59s倒计时*/
#include<reg52.h>
unsigned char code number[]=
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};
unsigned char code screen[]=
{
	0xc0,0xfe,0xfd,0xfb,0xf7,0xef,0xdf
};
sbit DULA=P2^6;
sbit WELA=P2^7;
sbit led_1=P1^0;
sbit beep=P2^3;

unsigned int t0=0,t1=0;/*T0,T1中断次数*/
unsigned int num=60;/*计时次数*/
unsigned int tens=6,units=0;

void delay_ms(unsigned int time);
void show_2_number(unsigned int tens,unsigned int units);
void main()
{
	
	TMOD=0x11;
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	TH1=(65536-45872)/256;
	TL1=(65536-45872)%256;
	EA=1;/*打开全局中断允许位*/
	ET0=1;/*打开T0中断允许位*/
	ET1=1;
	TR0=1;/*打开T0运行控制位*/
	TR1=1;
	
	while(1)
	{
		show_2_number(tens,units);/*始终刷新，等待中断改变数值*/
	}

	
}

void show_2_number(unsigned int tens,unsigned int units)
{
	DULA=1;
	P0=number[tens];
	DULA=0;
	P0=0xff;/*消影*/
	WELA=1;
	P0=screen[1];
	WELA=0;
	delay_ms(10);
	
	DULA=1;
	P0=number[units];
	DULA=0;
	P0=0xff;
	WELA=1;
	P0=screen[2];
	WELA=0;
	delay_ms(10);
	
}
void delay_ms(unsigned int time)
{
	unsigned int i,j;
	for(i=time;i>0;i--)
		for(j=110;j>0;j--)
			;
}
void timer() interrupt 1 /*中断处理函数，T0的中断序号为1*/
{
	TH0=(65536-45872)/256;/*/*延时50ms 重装初值*/
	TL0=(65536-45872)%256;
	t0++;
	if(t0==20)/*20次中断：1s*/
	{
		t0=0;
		num--;
		if(num==0)
			num=60;
		tens=num/10;/*分配num到十位*/
		units=num%10;/*分配num到个位*/
	}
}

void led_flash() interrupt 3
{
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	t1++;
	if(t1==10)
	{
		t1=0;
		led_1=~led_1;
		
	}
}




