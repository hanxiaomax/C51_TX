/*���ϼ��٣��ٻ�ԭ*/
#include<reg52.h>
#include<intrins.h>
/*��ˮ�ƣ�������ʱ*/
void easy_delay(unsigned int time);
void main()
{	
	int i,j,k,t;
	k=0x7f;/*����Ҫ��һ��0������λ�������ʱ�����ʹ״̬�ı�*/
	t=200;
	while(1)
	{	
			
			j=_crol_(k,1);/*ѭ������1λ*/
			k=j;
			P1=j; /*���ܶ�P1����ֱ�ӼӼ�����λ����*/
			easy_delay(t);
			if(k==0x7f)
			{
				t-=50;
				if(t<0)
					t=200;
			}
	}
}
void easy_delay(unsigned int time)/*unsigned int 0-255*/
{
	int i,j,k;
	for(i=0;i<time;i++)
		for(j=0;j<100;j++)/*˫��Ƕ��������ʱʱ��*/
				;
}
