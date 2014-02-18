/*中断--使用定时器计时--延时一秒，显示+1*/
#include<reg52.h>
void delay_ms(unsigned int time);
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
unsigned int t=0;/*中断次数*/
unsigned int num=0;
void main()
{
	/*定时器初始化*/
	TMOD=0x01; /*不能位寻址--使用T0，定时器，方式1 0000 0 0 0 1*/
	TH0=(65536-45872)/256;/*延时50ms*/
	TL0=(65536-45872)%256;
	EA=1;/*打开全局中断允许位*/
	ET0=1;/*打开T0中断允许位*/
	TR0=1;/*打开T0运行控制位*/
	while(1)
	{
		if(t==20)/*20次中断：1s*/
		{
			t=0;
			if(num==16)
				num=0;
			DULA=1;
			P0=number[num];
			DULA=0;
			WELA=1;
			P0=screen[1];
			WELA=0;
			num++;
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
void T0_timer() interrupt 1 /*中断处理函数，T0的中断序号为1*/
{
	TH0=(65536-45872)/256;/*重装初值*/
	TL0=(65536-45872)%256;
	t++;/*中断次数+1，一次中断是50ms*/
}