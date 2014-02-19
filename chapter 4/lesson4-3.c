#include<reg52.h>
sbit DULA=P2^6;
sbit WELA=P2^7;

unsigned char code number[]= /*���ֱ���*/
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};
void delay_ms(unsigned int);/*������ʱ����*/
void matrix_keyscan();/*����ɨ�躯��*/
void display(unsigned int num);

unsigned int num;/*����*/
void main()
{
	DULA=1;
	P0=0;
	DULA=0;
	WELA=1;
	P0=0xc0;/*11 000000*/
	WELA=0;
	
	while(1)
	{
		matrix_keyscan();
	}
	
}
void delay_ms(unsigned int time)/*������ʱ����*/
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<110;j++)
			;
}

void display(unsigned int num)/*��ĿҪ��������ʾ��ͬ���ʲ���λѡ*/
{
	DULA=1;
	P0=number[num];
	DULA=0;
}

/*----------------------------------------
������̣�
������̵��н�P3�ڵ���λ���нӸ���λ���ֱ����
��λ�͵͵�ƽ���ҷֱ������λ�Ƿ���ֵ͵�ƽ��
�����͵͵�ƽ�����μ�⣬ѭ��ɨ��.
----------------------------------------*/
void matrix_keyscan()/*����ɨ�躯��*/
{
	unsigned char temp,key;
	P3=0xfe;/*11111110:���ȸ�P3^0�͵͵�ƽ*/
	temp=P3;
	temp=temp&0xf0;/*��λ�룬ȥ����4λ������λ���������*/
	if(temp!=0xf0)/*0xf0=11110000 ��λ��0*/
	{
		delay_ms(10);/*ȥ����*/
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)/*ȥ������ʱ֮���ٴμ��*/
		{
			P1=0xfe;
			temp=P3;/*temp���¸�ֵΪP3*/
			switch(temp)
			{
				case 0xee:/*11101110����һ�е�һ��*/
					key=0;/*��һ����������*/
					break;
				case 0xde:
					key=1;
					break;
				case 0xbe:
					key=2;
					break;
				case 0x7e:
					key=3;
					break;
			}
			while(temp!=0xf0)/*�ȴ������ͷ�*/
			{
				temp=P3;
				temp=temp&0xf0;/*ʼ����ȥ����λ���жϸ���λ�Ƿ�ȫ1��ȫ1���ͷ�*/
			}
			display(key);/*key��Ϊ���ֱ���������*/
		}
	}
	P3=0xfd;/*11111110:��˳�򣬸�P3^1�͵͵�ƽ*/
	temp=P3;
	temp=temp&0xf0;/*��λ�룬ȥ����4λ������λ���������*/
	if(temp!=0xf0)/*0xf0=11110000 ��λ��0*/
	{
		delay_ms(10);/*ȥ����*/
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)/*ȥ������ʱ֮���ٴμ��*/
		{
			P1=0xfd;
			temp=P3;/*temp���¸�ֵΪP3*/
			switch(temp)
			{
				case 0xed:/*11101101*/
					key=4;
					break;
				case 0xdd:
					key=5;
					break;
				case 0xbd:
					key=6;
					break;
				case 0x7d:
					key=7;
					break;
			}
			while(temp!=0xf0)/*�ȴ������ͷ�*/
			{
				temp=P3;
				temp=temp&0xf0;/*ʼ����ȥ����λ���жϸ���λ�Ƿ�ȫ1��ȫ1���ͷ�*/
			}
			display(key);/*key��Ϊ���ֱ���������*/
		}
	}
	P3=0xfb;/*11111110:��˳�򣬸�P3^1�͵͵�ƽ*/
	temp=P3;
	temp=temp&0xf0;/*��λ�룬ȥ����4λ������λ���������*/
	if(temp!=0xf0)/*0xf0=11110000 ��λ��0*/
	{
		delay_ms(10);/*ȥ����*/
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)/*ȥ������ʱ֮���ٴμ��*/
		{
			P1=0xfb;
			temp=P3;/*temp���¸�ֵΪP3*/
			switch(temp)
			{
				case 0xeb:
					key=8;
					break;
				case 0xdb:
					key=9;
					break;
				case 0xbb:
					key=10;
					break;
				case 0x7b:
					key=11;
					break;
			}
			while(temp!=0xf0)/*�ȴ������ͷ�*/
			{
				temp=P3;
				temp=temp&0xf0;/*ʼ����ȥ����λ���жϸ���λ�Ƿ�ȫ1��ȫ1���ͷ�*/
			}
			display(key);/*key��Ϊ���ֱ���������*/
		}
	}
	P3=0xf7;/*11111110:��˳�򣬸�P3^1�͵͵�ƽ*/
	temp=P3;
	temp=temp&0xf0;/*��λ�룬ȥ����4λ������λ���������*/
	if(temp!=0xf0)/*0xf0=11110000 ��λ��0*/
	{
		delay_ms(10);/*ȥ����*/
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)/*ȥ������ʱ֮���ٴμ��*/
		{
			P1=0xf7;
			temp=P3;/*temp���¸�ֵΪP3*/
			switch(temp)
			{
				case 0xe7:/*11101101*/
					key=12;
					break;
				case 0xd7:
					key=13;
					break;
				case 0xb7:
					key=14;
					break;
				case 0x77:
					key=15;
					break;
			}
			while(temp!=0xf0)/*�ȴ������ͷ�*/
			{
				temp=P3;
				temp=temp&0xf0;/*ʼ����ȥ����λ���жϸ���λ�Ƿ�ȫ1��ȫ1���ͷ�*/
			}
			display(key);/*key��Ϊ���ֱ���������*/
		}
	}

}


