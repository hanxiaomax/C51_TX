/*--------------------------------------------------------------------------
1.数码管前三位显示A/D采集的数值，在未收到上位机命令前，为000
2.收到上位机发送的十六进制01时，向上位机发送“turn on ad”，每秒读取一次A/D的值
并向上位机发送“The voltage is xxxx”。xxxx为十进制数。数码管也要刷新
3.收到上位机发送的十六进制02时，向上位机发送“turn off ad”，数码管保持
4.收到上位机发送的其他十六进制数时，向上位机发送“Error！”
----------------------------------------------------------------------------*/
#include<reg52.h>
#include<intrins.h>
#include<stdio.h>

sbit DULA=P2^6;
sbit WELA=P2^7;
sbit wr=P3^6;
sbit rd=P3^7;


unsigned char code number[]= /*数字编码*/
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};
unsigned char code screen[]=/*屏幕编码*/
{
	0xc0,0x7e,0x7d,0x7b
};//重新编码使CSAD=0

unsigned char flag,get;
unsigned char flag_uart;//串口通信标志
unsigned char flag_time;//定时器标志
unsigned char flag_on;//AD开关标志
unsigned char get,i;
unsigned char t0_num;//定时器中断次数
unsigned char ad_val;//ad数据
float ad_vol;//转换后需要在上位机打印的数据

void delay_ms(unsigned int);/*简易延时程序*/
void init();
void display(unsigned int);
unsigned char get_ad();


void main()
{
	init();//初始化定时器和寄存器
	WELA=1;//关闭锁存，直通方式
	P0=0X7F;//送片选信号
	WELA=0;//打开锁存器
	/*片选常开，注意显示屏编码*/
	while(1)
	{
		if(flag_uart==1)
		{
			flag_uart=0;
			ES=0;//关闭串口中断，否则每发送一个字节，程序就申请中断
			TI=1;//手动置1，否则puts不发送
			printf("get:%d\n",get);
			switch(flag_on)//是否启动AD芯片标志
			{
				case 0: puts("Turn on ad!\n");
						TR0=1;//启动定时器T0
						break;
				case 1: puts("Turn off ad!\n");
						TR0=0;//关闭定时器T0
						break;
				case 2: puts("error!");
						break;
			}
			while(!TI);//死循环，等待发送中断信号，用来检测puts是否发送完毕
			TI=0;//发送中断位软件置位
			ES=1;//开放串口中断
			
		}
		if(flag_time==1)//定时器标志,每隔1s进入一次
		{
			flag_time=0;
			ad_val=get_ad();
			ad_vol=(float)ad_val*5.0/256.0;
			
			ES=0;//关闭串口中断，否则每发送一个字节，程序就申请中断
			TI=1;//手动置1，否则puts不发送
			printf("The voltage is %f V\n",ad_vol);
			while(!TI);//死循环，等待发送中断信号，用来检测puts是否发送完毕
			TI=0;//发送中断位软件置位
			ES=1;//开放串口中断
		}
		display(ad_val);
	}
	
}






void delay_ms(unsigned int time)/*简易延时程序*/
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<110;j++)
			;
}

void init()//初始化设置顺序是有意义的
{
	TMOD=0X21;//0010 0001,T1定时器方式2工作,T0方式1工作
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TH1=0Xfd;//SMOD=0时
	TL1=0Xfd;
	
	TR1=1;//启动定时器
	ET0=1;//T0定时器中断开放
	
	
	
	SM0=0;
	SM1=1;//方式1工作 10位异步方式
	REN=1;//串口允许接受数据
	EA=1;//开放中断
	ES=1;//开放串口中断
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
unsigned char get_ad()
{
	unsigned char ad_value;
	wr=1;
	_nop_();
	wr=0;//启动A/D转换
	_nop_();
	wr=1;
	
	P1=0xff;//读取P1口之前给其赋值全1
	
	rd=1;
	_nop_();
	rd=0;//AD芯片：读使能
	_nop_();
	ad_value=P1;//读取数据
	rd=1;//数据读走后马上拉高
	
	return ad_value;
}


void timer() interrupt 1   //延时一秒
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	t0_num++;
	if(t0_num==20)
	{
		t0_num=0;
		flag_time=1;
	}
	
}

void ser() interrupt 4
{
	RI=0;//接收中断软件复位
	get=SBUF;
	flag_uart=1;
	if(get==0x01)
		flag_on=0;
	else if(get==0x02)
		flag_on=1;
	else
		flag_on=2;
}

/*-----------
flag_uart=0;
ES=0;//关闭串口中断
TI=1;//???
如果缺少，则只显示一位
-----------------*/


/*-----------
使用stdio.h的函数钱，要将串口初始化完毕，串口设置为方式1，波特率与上位机一致
-----------------*/
