#include <reg52.h>
#include <string.h>
unsigned char code line[]="The world is";
unsigned char code line2[]="   my oyster!!!";
sbit LCDEN=P3^4;//LCD使能
sbit LCDRS=P3^5;//LCD命令/数据设置
sbit DULA=P2^6;//U1锁存器
sbit WELA=P2^7;//U2锁存器  

unsigned char num;//字符个数，并做数组索引号
void delay_ms(unsigned int time);//简易延时
void write_com(unsigned char com);//传递命令
void write_data(unsigned char date);//传递数据
void init();//初始化

void main()
{
	init();
	write_com(0x80);//光标放置在起始处
	for(num=0;num<strlen(line);num++)//strlen来计算字符串长度
	{
		write_data(line[num]);
		delay_ms(5);
	}
	write_com(0x80+0x40);//光标位置调整到第二行
	for(num=0;num<strlen(line2);num++)
	{
		write_data(line2[num]);
		delay_ms(5);
	}
	while(1);
}	

void delay_ms(unsigned int time)
{
	int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<110;j++)
		;
}

void write_com(unsigned char com)
{
	LCDRS=0;//模式设置：写命令
	P0=com;//传递命令数据
	delay_ms(5);//短暂延时，待数据稳定
	LCDEN=1;//液晶屏幕使能脉冲
	delay_ms(5);
	LCDEN=0;//完成脉冲
}
void write_data(unsigned char date)
{
	LCDRS=1;//模式设置：写数据
	P0=date;//传递命令数据
	delay_ms(5);//短暂延时，待数据稳定
	LCDEN=1;//液晶屏幕使能脉冲
	delay_ms(5);
	LCDEN=0;//完成脉冲
}

void init()
{
	DULA=0;//U1锁存器直通方式
	WELA=0;//U2锁存器直通方式
	LCDEN=0;
	write_com(0x38);//显示模式设置00111000，见手册
	write_com(0x0c);//光标设置：00001100
	write_com(0x06);//光标设置：00000110
	write_com(0x01);//显示清零，数据指针清零
}