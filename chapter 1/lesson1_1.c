/*��λ����*/
#include<reg51.h>
sbit D1=P1^0;/*��Ƭ��P1��,�����P�����Ǵ�д*/
sbit D2=P1^2;
sbit D3=P1^4;
sbit D4=P1^6;
void main()
{
	D1=D2=D3=D4=0;
}