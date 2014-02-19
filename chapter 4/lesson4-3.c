#include<reg52.h>
sbit DULA=P2^6;
sbit WELA=P2^7;

unsigned char code number[]= /*数字编码*/
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};
void delay_ms(unsigned int);/*简易延时程序*/
void matrix_keyscan();/*键盘扫描函数*/
void display(unsigned int num);

unsigned int num;/*数字*/
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
void delay_ms(unsigned int time)/*简易延时程序*/
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<110;j++)
			;
}

void display(unsigned int num)/*题目要求六个显示相同，故不需位选*/
{
	DULA=1;
	P0=number[num];
	DULA=0;
}

/*----------------------------------------
矩阵键盘：
矩阵键盘的行接P3口低四位，列接高四位。分别给第
四位送低电平，且分别检测高四位是否出现低电平。
依次送低电平，依次检测，循环扫描.
----------------------------------------*/
void matrix_keyscan()/*键盘扫描函数*/
{
	unsigned char temp,key;
	P3=0xfe;/*11111110:首先给P3^0送低电平*/
	temp=P3;
	temp=temp&0xf0;/*按位与，去掉低4位，高四位视情况而定*/
	if(temp!=0xf0)/*0xf0=11110000 高位有0*/
	{
		delay_ms(10);/*去抖动*/
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)/*去抖动延时之后再次检测*/
		{
			P1=0xfe;
			temp=P3;/*temp重新赋值为P3*/
			switch(temp)
			{
				case 0xee:/*11101110：第一行第一列*/
					key=0;/*第一个按键按下*/
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
			while(temp!=0xf0)/*等待按键释放*/
			{
				temp=P3;
				temp=temp&0xf0;/*始终略去第四位，判断高四位是否全1，全1则释放*/
			}
			display(key);/*key作为数字编码表的索引*/
		}
	}
	P3=0xfd;/*11111110:按顺序，给P3^1送低电平*/
	temp=P3;
	temp=temp&0xf0;/*按位与，去掉低4位，高四位视情况而定*/
	if(temp!=0xf0)/*0xf0=11110000 高位有0*/
	{
		delay_ms(10);/*去抖动*/
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)/*去抖动延时之后再次检测*/
		{
			P1=0xfd;
			temp=P3;/*temp重新赋值为P3*/
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
			while(temp!=0xf0)/*等待按键释放*/
			{
				temp=P3;
				temp=temp&0xf0;/*始终略去第四位，判断高四位是否全1，全1则释放*/
			}
			display(key);/*key作为数字编码表的索引*/
		}
	}
	P3=0xfb;/*11111110:按顺序，给P3^1送低电平*/
	temp=P3;
	temp=temp&0xf0;/*按位与，去掉低4位，高四位视情况而定*/
	if(temp!=0xf0)/*0xf0=11110000 高位有0*/
	{
		delay_ms(10);/*去抖动*/
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)/*去抖动延时之后再次检测*/
		{
			P1=0xfb;
			temp=P3;/*temp重新赋值为P3*/
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
			while(temp!=0xf0)/*等待按键释放*/
			{
				temp=P3;
				temp=temp&0xf0;/*始终略去第四位，判断高四位是否全1，全1则释放*/
			}
			display(key);/*key作为数字编码表的索引*/
		}
	}
	P3=0xf7;/*11111110:按顺序，给P3^1送低电平*/
	temp=P3;
	temp=temp&0xf0;/*按位与，去掉低4位，高四位视情况而定*/
	if(temp!=0xf0)/*0xf0=11110000 高位有0*/
	{
		delay_ms(10);/*去抖动*/
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)/*去抖动延时之后再次检测*/
		{
			P1=0xf7;
			temp=P3;/*temp重新赋值为P3*/
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
			while(temp!=0xf0)/*等待按键释放*/
			{
				temp=P3;
				temp=temp&0xf0;/*始终略去第四位，判断高四位是否全1，全1则释放*/
			}
			display(key);/*key作为数字编码表的索引*/
		}
	}

}


