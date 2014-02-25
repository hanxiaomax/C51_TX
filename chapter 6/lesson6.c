/*------------------------------------
只传送单个字符，没考虑双缓冲丢字符的处理
-------------------------------------*/
#include<reg52.h>
unsigned char flag=0,get,i;
unsigned char code table[]=" I get ";
void init();//初始化各种寄存器
void main()
{
	init();
	while(1)
	{
		if(flag==1)
		{
			ES=0;//关闭串口中断
			
			for(i=0;i<7;i++)
			{
				SBUF=table[i];
				while(!TI);
				TI=0;//软件中断归零
			}
			SBUF=get;
			while(!TI);//等待发送中断,否则停在此处
			TI=0;//中断归零
			ES=1;//开串口中断
			flag=0;
		}
	}
}
void init()
{
	TMOD=0X20;//00000010,T1定时器方式2工作
	TH1=0XFD;//SMOD=0
	TL1=0XFD;
	TR1=1;//启动定时器
	REN=1;//接受数据
	SM0=0;
	SM1=1;//方式1工作 10位异步方式
	EA=1;//开放中断
	ES=1;//开放串口中断
}

void ser() interrupt 4 //串口作为中断源
{
	RI=0;//重新归0
	get=SBUF;//从SBUF中读取数据
	flag=1;//标志置1表示收到数据
}
/*-------------------------------------
SBUF在等号的左右，分别表示接受和发送寄存器
-------------------------------------*/