/*���ϼ��٣��ٻ�ԭ���ٷ���*/
#include<reg52.h>
#include<intrins.h>
void delay_ms(unsigned int time);/*��ʱ_ms*/
void flash(unsigned int times);/*��˸times��*/
sbit beep=P2^3;
void main()
{	
	unsigned int round=0;
	while(1)
	{
		unsigned int i,temp;/*ʹ��unsigned�ȽϺã�ռ���ڴ�С*/
		if(round==5)/*���������㣬��֤�����ʱ*/
			round=0;
		temp=0xfe;
		for(i=0;i<8;i++)
		{
			P1=temp;
			delay_ms(500-round*100);
			temp=_crol_(temp,1);/*cror�ø�λ����λ*/
		}
		temp=0x7f;
		for(i=0;i<8;i++)
		{
			P1=temp;
			temp=_cror_(temp,1);
			delay_ms(500-round*100);
		}
		round++;
		flash(round);/*�ڼ��־���˸����*/
		
	}
}
void flash(unsigned int times)
{
	while(times>0)
	{
		P1=0xff;
		delay_ms(200);
		P1=0x00;
		delay_ms(200);
		times--;
		beep=0;
		delay_ms(200);
		beep=1;
	}
}
/*�������Ϊunsigned int���ڲ�Ϊ110ʱ�����i��ֵ����Ϊ������*/
void delay_ms(unsigned int time)/*unsigned int 0-255*/
{
	int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<110;j++)/*˫��Ƕ��������ʱʱ��*/
				;
}