/*-------------------------------
字母从右侧移入，在屏幕中部暂停1s，
至左侧全部消失后再从右侧移入
--------------------------------*/
#include <reg52.h>
#include <string.h>
#define MAX(x,y) (x>y?x:y)//如果不加括号会变成16+x>y?x:y
unsigned char code line1[]=" ROUND ONE ";
unsigned char code line2[]="  START!";
sbit WELA=P2^7;
sbit DULA=P2^6;
sbit LCDEN=P3^4;
sbit LCDRS=P3^5;

unsigned char num;//字符个数，并做数组索引号
void delay_ms(unsigned int time);//简易延时
void write_com(unsigned char com);//传递命令
void write_data(unsigned char date);//传递数据
void init();//初始化


void main()
{
	while(1) 
	{
		unsigned int pos=0;
		init();
		write_com(0x80+0x10);//光标位置在右侧外
		for(num=0;num<strlen(line1);num++)//strlen来计算字符串长度
		{
			write_data(line1[num]);
			delay_ms(5);
		}
		write_com(0x80+0x50);//光标位置调整到第二行右侧外
		for(num=0;num<strlen(line2);num++)
		{
			write_data(line2[num]);
			delay_ms(5);
		}
		while(pos!=16+MAX(strlen(line1),strlen(line2)))
		{	
			if (pos==(16+MAX(strlen(line1),strlen(line2)))/2)//在中间暂停1s
			{
				delay_ms(1000);
			}
			write_com(0x18);//屏幕左移
			delay_ms(200);
			pos++;
		}
	}
	
	
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