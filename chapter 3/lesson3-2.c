/*数码管动态显示--高速刷新显示不同数字*/
#include<reg52.h>
sbit DS=P2^6;
sbit WS=P2^7;
sbit beep=P2^3;
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
void delay_ms(unsigned int time);
void screen_number(unsigned int s,unsigned int n);
void main()
{
	int i,j;
	while(1)
	{
		screen_number(1,1);
		screen_number(2,2);
	}
}
void delay_ms(unsigned int time)
{
	unsigned int i,j;
	for(i=time;i>0;i--)
		for(j=110;j>0;j--)
				;
}
void screen_number(unsigned int s,unsigned int n)
{
			DS=1;
			P0=number[n];
			DS=0;
			P0=0xff;/*消影--高延时时不明显，低延时时就会导致显示混*/
			WS=1;
			P0=screen[s];
			WS=0;
			delay_ms(1);
}