/*--------------------------------------------------------------------------
1.�����ǰ��λ��ʾA/D�ɼ�����ֵ����δ�յ���λ������ǰ��Ϊ000
2.�յ���λ�����͵�ʮ������01ʱ������λ�����͡�turn on ad����ÿ���ȡһ��A/D��ֵ
������λ�����͡�The voltage is xxxx����xxxxΪʮ�������������ҲҪˢ��
3.�յ���λ�����͵�ʮ������02ʱ������λ�����͡�turn off ad��������ܱ���
4.�յ���λ�����͵�����ʮ��������ʱ������λ�����͡�Error����
----------------------------------------------------------------------------*/
#include<reg52.h>
#include<intrins.h>
#include<stdio.h>

sbit DULA=P2^6;
sbit WELA=P2^7;
sbit wr=P3^6;
sbit rd=P3^7;


unsigned char code number[]= /*���ֱ���*/
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};
unsigned char code screen[]=/*��Ļ����*/
{
	0xc0,0x7e,0x7d,0x7b
};//���±���ʹCSAD=0

unsigned char flag,get;
unsigned char flag_uart;//����ͨ�ű�־
unsigned char flag_time;//��ʱ����־
unsigned char flag_on;//AD���ر�־
unsigned char get,i;
unsigned char t0_num;//��ʱ���жϴ���
unsigned char ad_val;//ad����
float ad_vol;//ת������Ҫ����λ����ӡ������

void delay_ms(unsigned int);/*������ʱ����*/
void init();
void display(unsigned int);
unsigned char get_ad();


void main()
{
	init();//��ʼ����ʱ���ͼĴ���
	WELA=1;//�ر����棬ֱͨ��ʽ
	P0=0X7F;//��Ƭѡ�ź�
	WELA=0;//��������
	/*Ƭѡ������ע����ʾ������*/
	while(1)
	{
		if(flag_uart==1)
		{
			flag_uart=0;
			ES=0;//�رմ����жϣ�����ÿ����һ���ֽڣ�����������ж�
			TI=1;//�ֶ���1������puts������
			printf("get:%d\n",get);
			switch(flag_on)//�Ƿ�����ADоƬ��־
			{
				case 0: puts("Turn on ad!\n");
						TR0=1;//������ʱ��T0
						break;
				case 1: puts("Turn off ad!\n");
						TR0=0;//�رն�ʱ��T0
						break;
				case 2: puts("error!");
						break;
			}
			while(!TI);//��ѭ�����ȴ������ж��źţ��������puts�Ƿ������
			TI=0;//�����ж�λ�����λ
			ES=1;//���Ŵ����ж�
			
		}
		if(flag_time==1)//��ʱ����־,ÿ��1s����һ��
		{
			flag_time=0;
			ad_val=get_ad();
			ad_vol=(float)ad_val*5.0/256.0;
			
			ES=0;//�رմ����жϣ�����ÿ����һ���ֽڣ�����������ж�
			TI=1;//�ֶ���1������puts������
			printf("The voltage is %f V\n",ad_vol);
			while(!TI);//��ѭ�����ȴ������ж��źţ��������puts�Ƿ������
			TI=0;//�����ж�λ�����λ
			ES=1;//���Ŵ����ж�
		}
		display(ad_val);
	}
	
}






void delay_ms(unsigned int time)/*������ʱ����*/
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<110;j++)
			;
}

void init()//��ʼ������˳�����������
{
	TMOD=0X21;//0010 0001,T1��ʱ����ʽ2����,T0��ʽ1����
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TH1=0Xfd;//SMOD=0ʱ
	TL1=0Xfd;
	
	TR1=1;//������ʱ��
	ET0=1;//T0��ʱ���жϿ���
	
	
	
	SM0=0;
	SM1=1;//��ʽ1���� 10λ�첽��ʽ
	REN=1;//���������������
	EA=1;//�����ж�
	ES=1;//���Ŵ����ж�
}
void display(unsigned int num)
{
	unsigned int hun,tens,unit;

	hun=num/100;
	tens=(num/10)%10;
	unit=num%10;//�õ���λ��Ӧ�ö�10����

	DULA=1;
	P0=number[hun];
	DULA=0;
	P0=0xff;
	WELA=1;
	P0=screen[1];/*��Ļ�����P0��*/
	WELA=0;
	delay_ms(5);/*��ʱ10ms*/


	DULA=1;
	P0=number[tens];
	DULA=0;
	P0=0xff;
	WELA=1;/*��λѡ����*/
	P0=screen[2];/*��Ļ�����P0��*/
	WELA=0;
	delay_ms(5);/*��ʱ10ms*/


	DULA=1;
	P0=number[unit];
	DULA=0;
	P0=0xff;	
	WELA=1;/*��λѡ����*/
	P0=screen[3];/*��Ļ�����P0��*/
	WELA=0;
	delay_ms(5);/*��ʱ10ms*/
}
unsigned char get_ad()
{
	unsigned char ad_value;
	wr=1;
	_nop_();
	wr=0;//����A/Dת��
	_nop_();
	wr=1;
	
	P1=0xff;//��ȡP1��֮ǰ���丳ֵȫ1
	
	rd=1;
	_nop_();
	rd=0;//ADоƬ����ʹ��
	_nop_();
	ad_value=P1;//��ȡ����
	rd=1;//���ݶ��ߺ���������
	
	return ad_value;
}


void timer() interrupt 1   //��ʱһ��
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
	RI=0;//�����ж������λ
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
ES=0;//�رմ����ж�
TI=1;//???
���ȱ�٣���ֻ��ʾһλ
-----------------*/


/*-----------
ʹ��stdio.h�ĺ���Ǯ��Ҫ�����ڳ�ʼ����ϣ���������Ϊ��ʽ1������������λ��һ��
-----------------*/
