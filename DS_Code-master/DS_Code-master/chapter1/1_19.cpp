//ϰ��1.19
/* ��1.19�� �Ա�д�㷨������i!��2^i��ֵ����������   
a[0..ARRSIZE-1]�ĵ�i-1�������� (i=1,2,��,n)��   
����������������������ֵΪMAXINT����n>   
ARRSIZE���ĳ��k(1��k��n)ʹk!��2^k>MAXINTʱ��Ӧ   
��������ע��ѡ������Ϊ�Ϻõĳ���������*/

#include <stdio.h>
#define arrsize 40
#define MAXINT 65535

void main()
{
	int n, i, j;
	int a[arrsize];
	int temp = 1;
	bool flag = true;

	printf("please input n: ");
	scanf("%d", &n);

	if(n > arrsize)
	{
		flag = false;
	}

	for(i=0; i<n && flag; i++)
	{
		temp = 1;
		for(j=i; j>0 && flag; j--)
		{
			if(temp > MAXINT/(2*j))
			{
				flag = false;
			}
			temp *= 2*j;
		}
		if(0 == i)
		{
			a[i] = 1;
		}
		else
		{
			a[i] = temp;
		}
	}

	for(i=0; i<n && flag; i++)
	{
		printf("%d\t", a[i]);
	}
	if(!flag)
	{
		printf("Input wrong!");
	}
	printf("\n");
}