/*�ж�--ʹ�ö�ʱ����ʱ--��ʱһ�룬��ʾ+1*/
#include<reg52.h>
void delay_ms(unsigned int time);
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
sbit DULA=P2^6;
sbit WELA=P2^7;
unsigned int t=0;/*�жϴ���*/
unsigned int num=0;
void main()
{
	/*��ʱ����ʼ��*/
	TMOD=0x01; /*����λѰַ--ʹ��T0����ʱ������ʽ1 0000 0 0 0 1*/
	TH0=(65536-45872)/256;/*��ʱ50ms*/
	TL0=(65536-45872)%256;
	EA=1;/*��ȫ���ж�����λ*/
	ET0=1;/*��T0�ж�����λ*/
	TR0=1;/*��T0���п���λ*/
	while(1)
	{
		if(t==20)/*20���жϣ�1s*/
		{
			t=0;
			if(num==16)
				num=0;
			DULA=1;
			P0=number[num];
			DULA=0;
			WELA=1;
			P0=screen[1];
			WELA=0;
			num++;
		}
	}
	
}
void delay_ms(unsigned int time)
{
	unsigned int i,j;
	for(i=time;i>0;i--)
		for(j=110;j>0;j--)
			;
}
void T0_timer() interrupt 1 /*�жϴ�������T0���ж����Ϊ1*/
{
	TH0=(65536-45872)/256;/*��װ��ֵ*/
	TL0=(65536-45872)%256;
	t++;/*�жϴ���+1��һ���ж���50ms*/
}