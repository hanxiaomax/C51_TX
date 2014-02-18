#include<reg52.h>

sbit key1=P3^4;/*设置独立键盘使用的I/O口*/
sbit key2=P3^5;
sbit key3=P3^6;
sbit key4=P3^7;

sbit DULA=P2^6;/*段选*/
sbit WELA=P2^7;/*位选*/

unsigned char code number[]= /*数字编码*/
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f
};
unsigned char code screen[]=/*屏幕编码*/
{
	0xc0,0xfe,0xfd,0xfb,0xf7,0xef,0xdf
};/*0xc0作为占位使用，注意不要使用screen[0]*/

void delay_ms(unsigned int);/*简易延时程序*/
void show_number(unsigned int);/*屏幕显示程序*/
void init(void);/*定时器初始化函数*/
void keyscan();/*键盘扫描函数*/

unsigned int num;/*数字*/
unsigned int count;/*中断次数*/
void main()
{
	init();
	while(1)
	{
		keyscan();
		show_number(num);
	}
	
}
void delay_ms(unsigned int time)/*简易延时程序*/
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<110;j++)
			;
}


/*给定一个数，然后在内部拆分，在两个数码管上显示*/
void show_number(unsigned int num)
{
	unsigned int hund,tens,units;
	hund=num/100;/*分离百位数*/
	tens=(num/10)%10;
	units=num%10;/*分离个位数*/
	
	DULA=1;/*开段选锁存*/
	P0=number[hund];/*十位数的数字编码给P0口*/
	DULA=0;
	P0=0xff;/*消影*/
	WELA=1;/*开位选锁存*/
	P0=screen[1];/*屏幕编码给P0口*/
	WELA=0;
	delay_ms(5);/*延时10ms*/
	
	DULA=1;/*开段选锁存*/
	P0=number[tens];/*十位数的数字编码给P0口*/
	DULA=0;
	P0=0xff;/*消影*/
	WELA=1;/*开位选锁存*/
	P0=screen[2];/*屏幕编码给P0口*/
	WELA=0;
	delay_ms(5);/*延时10ms*/

	DULA=1;
	P0=number[units];
	DULA=0;
	P0=0xff;
	WELA=1;
	P0=screen[3];
	WELA=0;
	delay_ms(5);
	
}

void init(void)/*定时器初始化函数*/
{
	TMOD=0x01;/*设置定时器工作方式*/
	TH0=(65536-45872)/256; /*装入初值：50ms中断一次*/
	TL0=(65536-45872)%256;
	EA=1;/*开放中断*/
	ET0=1;/*开放T0定时器中断*/
}

void keyscan()/*键盘扫描函数*/
{
	if(key1==0)
	{
		delay_ms(10);/*去抖动*/
		if(key1==0)/*再次检测是否为低电平*/
		{
			num++;/*数字加1*/
			if(num==999)
				num=0;
			while(!key1)/*等待按键释放，否则始终为真，停在这里*/
				;
		}
	}
	if(key2==0)
	{
		delay_ms(10);/*去抖动*/
		if(key2==0)/*再次检测是否为低电平*/
		{
			if(num==0)
				num=999;
			num--;/*数字减1*/
			while(!key2)
				;
		}
	}
	if(key3==0)
	{
		delay_ms(10);
		if(key3==0)
		{
			num=0;/*清零*/
			while(!key3)
				;
		}
	}
	if(key4==0)
	{
		delay_ms(10);/*去抖动*/
		if(key4==0)/*再次检测是否为低电平*/
		{
			TR0=~TR0;/*启动或者停止定时器T0*/
			while(!key4)/*等待按键释放，否则始终为真，停在这里*/
				;
		}
	}
}

void timer() interrupt 1 /*中断服务函数，不需要声明*/
{
	TH0=(65536-45872)/256; /*重入初值*/
	TL0=(65536-45872)%256;
	count++;
	if(count==2)
	{
		count=0;
		num++;
		if(num==999)
			num=0;
	}
	
}

/*----------------------------------------------------------
本程序有一个不完善的地方，当000的时候，如果-1，则会出现bug，
如果先+1，再回退到000，再-1是正常的，还未解决该问题。给定初值也不行。
如果把num--放在if后面，则不会乱码，但是会直接跳到998
------------------------------------------------------------*/


