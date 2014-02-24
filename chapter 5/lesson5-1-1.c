#include<reg52.h>
#include<intrins.h> //_nop_() 延时一个机器周期
sbit wr=P3^6;
sbit rd=P3^7;
/*CSAD在锁存器U2上，故不在此处声明*/
sbit DULA=P2^6;
sbit WELA=P2^7;
unsigned char code screen[]=/*屏幕编码*/
{
	0xc0,0x7e,0x7d,0x7b
};//重新编码使CSAD=0
unsigned char code number[]= /*数字编码*/
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};
unsigned int num;

void delay_ms(unsigned int );
void display(unsigned num);
void main()
{
	unsigned int i;
	WELA=1;//关闭锁存器，直通
	P0=0x7f;//CSAD片选信号：011111111
	WELA=0;//锁存
	//始终片选
	while(1)
	{
		wr=0;//AD写入，启动A/D转换
		_nop_();//延时一个机器周期
		wr=1;
		for(i=20;i>0;i--)//延时，使转换完成（没有使用中断且转换速度较慢）
		{
			display(num);
		}
		P1=0xff;//读取P1口之前给其赋值全1
		rd=0;//AD芯片：读使能
		num=P1;//读取数据
		rd=1;//数据读走后马上拉高
	}	
}
void delay_ms(unsigned int time)//简易延时程序
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<110;j++)
			;
}
void display(unsigned int num)
{
	unsigned int hun,tens,unit;
	
	hun=num/100;
	tens=(num/10)%10;
	unit=num%10;//得到个位数应该对10求余
	
	DULA=1;
	P0=number[hun];
	DULA=0;
	P0=0xff;
	WELA=1;
	P0=screen[1];/*屏幕编码给P0口*/
	WELA=0;
	delay_ms(5);/*延时10ms*/
	
	
	DULA=1;
	P0=number[tens];
	DULA=0;
	P0=0xff;
	WELA=1;/*开位选锁存*/
	P0=screen[2];/*屏幕编码给P0口*/
	WELA=0;
	delay_ms(5);/*延时10ms*/
	
	
	DULA=1;
	P0=number[unit];
	DULA=0;
	P0=0xff;	
	WELA=1;/*开位选锁存*/
	P0=screen[3];/*屏幕编码给P0口*/
	WELA=0;
	delay_ms(5);/*延时10ms*/
}
/*------------------------------------------------------------
1.CS低电平的时候，WR出现一段低电平脉冲，启动转换。
2.转换成功后产生一个中断，如果不使用中断，延时一段时间再读取即可。
3.CS低电平的时候，RD出现一段低电平脉冲，读取数据
--------------------------------------------------------------*/