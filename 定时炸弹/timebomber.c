#include<reg52.h>
unsigned char code number[]= /*数字编码*/
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};
unsigned char code screen[]=/*屏幕编码*/
{
	0xc0,0xfe,0xfd,0xfb,0xf7,0xef,0xdf
};


sbit beep=P2^3;/*蜂鸣器*/
sbit WELA=P2^7;/*位选*/
sbit DULA=P2^6;/*段选*/
sbit LED=P1^0;

void delay_ms(unsigned int time);/*延时*/
void display(unsigned num);/*数码管显示*/
void light(unsigned int t);/*流水灯*/
void Beep(unsigned int f);
void initiate();/*初始化*/

unsigned int num=60;
unsigned int f;
unsigned int count0,count1;/*中断发生次数*/
unsigned int tt=0;
void main()
{
	initiate();
	display(num);
	while(1)
	{
		TR0=1;
		display(num);
	}
	
}
void initiate()
{
	TMOD=0x11;
	TH0=(65536-45872)/256; 
	TL0=(65536-45872)%256;
	TH1=(65536-45872)/256; 
	TL1=(65536-45872)%256;
	EA=1;
	ET0=1;
	ET1=1;
}

void display(unsigned num)
{
	unsigned int tens,units;
	tens=num/10;
	units=num%10;
	
	DULA=1;
	P0=number[tens];
	DULA=0;
	P0=0xff;
	WELA=1;
	P0=screen[1];
	WELA=0;
	delay_ms(5);
	
	DULA=1;
	P0=number[units];
	DULA=0;
	P0=0xff;
	WELA=1;
	P0=screen[2];
	WELA=0;
	delay_ms(5);
}


void delay_ms(unsigned int time)
{
	unsigned int i,j;
	for(i=time;i>0;i--)
		for(j=110;j>0;j--)
			;
}

void count_down() interrupt 1
{
	TH0=(65536-45872)/256; 
	TL0=(65536-45872)%256;
	count0++;
	f++;
	count1++;
	if(count0==20)
	{
		count0=0;
		num--;
		if(num==0)
		{
			num=60;
			P1=0x00;
		}
	}
	if(f==(num/10+1))
	{
		f=0;
		beep=~beep;
		LED=~LED;
	}
	
	/*if(count1==100)
	{
		count1=0;
		tt++;
		if(tt==12)
			tt=0;
	}*/
}
