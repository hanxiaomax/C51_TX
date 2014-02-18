#include<reg52.h>

sbit key1=P3^4;/*���ö�������ʹ�õ�I/O��*/
sbit key2=P3^5;
sbit key3=P3^6;
sbit key4=P3^7;

sbit DULA=P2^6;/*��ѡ*/
sbit WELA=P2^7;/*λѡ*/

unsigned char code number[]= /*���ֱ���*/
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f
};
unsigned char code screen[]=/*��Ļ����*/
{
	0xc0,0xfe,0xfd,0xfb,0xf7,0xef,0xdf
};/*0xc0��Ϊռλʹ�ã�ע�ⲻҪʹ��screen[0]*/

void delay_ms(unsigned int);/*������ʱ����*/
void show_number(unsigned int);/*��Ļ��ʾ����*/
void init(void);/*��ʱ����ʼ������*/
void keyscan();/*����ɨ�躯��*/

unsigned int num;/*����*/
unsigned int count;/*�жϴ���*/
void main()
{
	init();
	while(1)
	{
		keyscan();
		show_number(num);
	}
	
}
void delay_ms(unsigned int time)/*������ʱ����*/
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<110;j++)
			;
}


/*����һ������Ȼ�����ڲ���֣����������������ʾ*/
void show_number(unsigned int num)
{
	unsigned int hund,tens,units;
	hund=num/100;/*�����λ��*/
	tens=(num/10)%10;
	units=num%10;/*�����λ��*/
	
	DULA=1;/*����ѡ����*/
	P0=number[hund];/*ʮλ�������ֱ����P0��*/
	DULA=0;
	P0=0xff;/*��Ӱ*/
	WELA=1;/*��λѡ����*/
	P0=screen[1];/*��Ļ�����P0��*/
	WELA=0;
	delay_ms(5);/*��ʱ10ms*/
	
	DULA=1;/*����ѡ����*/
	P0=number[tens];/*ʮλ�������ֱ����P0��*/
	DULA=0;
	P0=0xff;/*��Ӱ*/
	WELA=1;/*��λѡ����*/
	P0=screen[2];/*��Ļ�����P0��*/
	WELA=0;
	delay_ms(5);/*��ʱ10ms*/

	DULA=1;
	P0=number[units];
	DULA=0;
	P0=0xff;
	WELA=1;
	P0=screen[3];
	WELA=0;
	delay_ms(5);
	
}

void init(void)/*��ʱ����ʼ������*/
{
	TMOD=0x01;/*���ö�ʱ��������ʽ*/
	TH0=(65536-45872)/256; /*װ���ֵ��50ms�ж�һ��*/
	TL0=(65536-45872)%256;
	EA=1;/*�����ж�*/
	ET0=1;/*����T0��ʱ���ж�*/
}

void keyscan()/*����ɨ�躯��*/
{
	if(key1==0)
	{
		delay_ms(10);/*ȥ����*/
		if(key1==0)/*�ٴμ���Ƿ�Ϊ�͵�ƽ*/
		{
			num++;/*���ּ�1*/
			if(num==999)
				num=0;
			while(!key1)/*�ȴ������ͷţ�����ʼ��Ϊ�棬ͣ������*/
				;
		}
	}
	if(key2==0)
	{
		delay_ms(10);/*ȥ����*/
		if(key2==0)/*�ٴμ���Ƿ�Ϊ�͵�ƽ*/
		{
			if(num==0)
				num=999;
			num--;/*���ּ�1*/
			while(!key2)
				;
		}
	}
	if(key3==0)
	{
		delay_ms(10);
		if(key3==0)
		{
			num=0;/*����*/
			while(!key3)
				;
		}
	}
	if(key4==0)
	{
		delay_ms(10);/*ȥ����*/
		if(key4==0)/*�ٴμ���Ƿ�Ϊ�͵�ƽ*/
		{
			TR0=~TR0;/*��������ֹͣ��ʱ��T0*/
			while(!key4)/*�ȴ������ͷţ�����ʼ��Ϊ�棬ͣ������*/
				;
		}
	}
}

void timer() interrupt 1 /*�жϷ�����������Ҫ����*/
{
	TH0=(65536-45872)/256; /*�����ֵ*/
	TL0=(65536-45872)%256;
	count++;
	if(count==2)
	{
		count=0;
		num++;
		if(num==999)
			num=0;
	}
	
}

/*----------------------------------------------------------
��������һ�������Ƶĵط�����000��ʱ�����-1��������bug��
�����+1���ٻ��˵�000����-1�������ģ���δ��������⡣������ֵҲ���С�
�����num--����if���棬�򲻻����룬���ǻ�ֱ������998
------------------------------------------------------------*/


