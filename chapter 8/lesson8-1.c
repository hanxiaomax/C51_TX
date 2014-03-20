#include <reg52.h>	
#include <L8-IIC.h>
sbit SDA=P2^0;	
sbit SCL=P2^1;
void START();//起始信号
void STOP();//停止信号
void RESPONS();//应答信号
void INIT();//初始化
void wirte_byte(unsigned char DATA);//写数据
unsigned char read_byte();//读数据
void delay();
void delay_ms(unsigned int time);
void wirte_add(unsigned char address,unsigned char DATA);//向某个地址写数据
unsigned char read_add(unsigned char address);//从某个地址读取数据
void main()
{
	INIT();//初始化
	wirte_add(25,0xee);
	delay_ms(10);//此处应有短暂延时，太长或者太短都不可以
	/*随机读取*/
	P1=read_add(25);
}

void START()
{
	SDA=1;
	delay();
	SCL=1;
	delay();
	SDA=0;
	delay();
}
void STOP()
{
	SDA=0;
	delay();
	SCL=1;
	delay();
	SDA=1;
	delay();
}
void RESPONS()
{
	unsigned char i=0;
	SCL=1;
	delay();
	while(SDA==1&&i<250)
		i++;
	SCL=0;
	delay();
}
void INIT()
{
	SCL=1;
	delay();
	SDA=1;
	delay();
}
void wirte_byte(unsigned char DATA)
{
	unsigned char i,temp;
	temp=DATA;
	for(i=0;i<8;i++)
	{
		temp=temp<<1;
		SCL=0;
		delay();
		SDA=CY;//高位移出后进入CY
		delay();
		SCL=1;
		delay();
		
	}
	SCL=0;
	delay();
	SDA=1;//释放数据总线
	delay();
}

unsigned char read_byte()
{
	unsigned char DATA;
	unsigned int i;
	SCL=0;
	delay();
	SDA=1;
	delay();
	for(i=0;i<8;i++)
	{
		SCL=1;
		delay();
		DATA=(DATA<<1)|SDA; //SDA是每次返回读到的数据，放在k的末尾，每次循环向高位运动
		SCL=0;
		delay();
	}
	delay();
	return DATA;
}
void delay()
{
	;;
}
void delay_ms(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<110;j++);
}

void wirte_add(unsigned char address,unsigned char DATA)
{
	START();//起始信号
	wirte_byte(0Xa0);//写器件地址1010000 0
	RESPONS();//应答
	wirte_byte(address);//器件内部存储器地址
	RESPONS();//应答
	wirte_byte(DATA);//数据
	RESPONS();//应答
	STOP();//停止
}

unsigned char read_add(unsigned char address)
{
	unsigned char DATA;
	START();//起始信号
	wirte_byte(0Xa0);//器件地址
	RESPONS();
	wirte_byte(address);//器件内部存储器地址
	RESPONS();
	START();
	wirte_byte(0xa1);//写器件地址1010000 1
	RESPONS();
	DATA=read_byte();
	STOP();
	return DATA;
}