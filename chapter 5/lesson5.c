/*--------------------------------------
����DAC0832оƬ���������ʹD12�����𽥱仯��
�����������ʱ���������
---------------------------------------*/
#include<reg52.h>
sbit CSDA=P3^2;//Ƭѡ���͵�ƽ��Ч
sbit my_WR=P3^6;//дѡͨ���͵�ƽ��Ч��WR��reg52�ж����
sbit BEEP=P2^3;
sbit DULA=P2^6;
sbit WELA=P2^7;
void delay_ms(unsigned int );
void main()
{
	unsigned int val;//��������ѹ
	unsigned int flag;//�������ֵ��־
	DULA=0;//��U1����
	WELA=0;//��U2����
	//����������棬����ܻ��ܵ�����
	CSDA=0;//�͵�ƽ
	my_WR=0;//�͵�ƽ
	P0=0;
	while(1)
	{
		if(flag==0)
		{
			val+=5;
			P0=val;//��P0���������
			if(val==255)
			{
				flag=1;
				BEEP=0;
				delay_ms(100);
				BEEP=1;
			}
			delay_ms(50);//״̬ά��50ms
		}
		else //flag==1
		{
			val-=5;
			P0=val;
			if(val==0)
			{
				flag=0;
				BEEP=0;
				delay_ms(100);
				BEEP=1;
			}
			delay_ms(50);
		}
	}
}

void delay_ms(unsigned int times)
{
	unsigned int i,j;
	for(i=0;i<times;i++)
		for(j=0;j<110;j++)
		;
}