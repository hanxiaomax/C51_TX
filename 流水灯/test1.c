/*不断加速，再还原*/
#include<reg52.h>
#include<intrins.h>
/*流水灯：随意延时*/
void easy_delay(unsigned int time);
void main()
{	
	int i,j,k,t;
	k=0x7f;/*必须要有一个0，进行位移运算的时候才能使状态改变*/
	t=200;
	while(1)
	{	
			
			j=_crol_(k,1);/*循环右移1位*/
			k=j;
			P1=j; /*不能对P1进行直接加减或者位运算*/
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
		for(j=0;j<100;j++)/*双层嵌套增加延时时间*/
				;
}
