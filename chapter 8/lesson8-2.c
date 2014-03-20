#include <reg52.h>	
#include "L8-IIC.h"
sbit DULA=P2^6;
sbit WELA=P2^7;
/*-------------
变量和编码定义
-------------*/
unsigned int sec;
bit write=0;//相当于一个unsigned int flag，只是为了控制写入的时机
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

/*-------------
函数原型声明
-------------*/
void show_2_number(unsigned int );//数码管动态显示
void timer_init();
/*------
主函数
------*/
void main()
{
	INIT();//初始化IIC总线
	timer_init();//初始化定时器，但不启动
	sec=read_add(2);//上电后首先从芯片读取之前数据
	if (sec>99)//防止读取错误
		sec=0;
	TR0=1;//开始计时
	while(1) 
	{	
		if (write==1)//1s钟到，可以写入
		{
			write_add(2,sec);
			write=0;//写入后清零
		}
		show_2_number(sec);//刷新
	}
}
/*-------
函数定义
-------*/
void show_2_number(unsigned int sec)
{
	unsigned int tens,units;
	tens=sec/10;
	units=sec%10;
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

void timer_init()
{
	TMOD=0x01;
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	EA=1;/*打开全局中断允许位*/
	ET0=1;/*打开T0中断允许位*/
	
}

void timer() interrupt 1 /*中断处理函数，T0的中断序号为1*/
{
	unsigned int times;
	TH0=(65536-45872)/256;/*延时50ms 重装初值*/
	TL0=(65536-45872)%256;
	times++;//中断次数
	if(times==20)/*20次中断：1s*/
	{
		times=0;//中断次数清零
		sec++;//每隔1s，秒数+1
		write=1;//每隔1s，置1
		if (sec==99)
			sec=0;
	}	
}
/*在这个程序里，读写不需要人为延时，间隔时间已经足够*/