/*ÊıÂë¹ÜÏÔÊ¾*/
#include<reg52.h>
sbit DS=P2^6;
sbit WS=P2^7;
unsigned char code number[]=
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};
unsigned char code screen[]=
{
	0xc0,0xfe,0xfd,0xfb,0xf7
};
void delay_ms(unsigned int time);
void main()
{
	unsigned int i;
	WS=1;
	P0=screen[0];
	WS=0;
	while(1)
	{
		for(i=0;i<16;i++)
		{
			DS=1;
			P0=number[i];
			DS=0;
			delay_ms(500);
		}
	}
}
void delay_ms(unsigned int time)
{
	unsigned int i,j;
	for(i=time;i>0;i--)
		for(j=110;j>0;j--)
				;
}