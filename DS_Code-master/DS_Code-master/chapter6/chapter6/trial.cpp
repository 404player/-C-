/* �˻ʺ�����ݹ���� */

#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

int chess[8][8] = {0};
int count = 0;		//��ĸ���
/**
 * �㷨6.16���˻ʺ��������
 * ���뱾����ǰ����N*N��������ǰi-1���Ѿ������˻���������i-1������
 * �ִӵ�i�������Ϊ���������ѡ����ʵ�λ��
 * ��i>n�������ǰ����
 */
void trial(int i, int n)
{
	int j;
	if (i > n)
		display_chess(n);
	else {
		for (j=1; j<=n; j++) {
			put(i, j);	//��i��j�аڷ�һ������
			if (isReasonable(n, i, j))
				trial(i+1, n);
			remove(i, j);	//�Ƴ�i��j�е�����
		}
	}
}

/**
 * ��ӡ��ǰ����
 */
void display_chess(int n)
{
	int i, j;
	count++;	//��ĸ�����1
	printf("%d.\n", count);
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++)
			printf("%d ", chess[i][j]);
		printf("\n");
	}
	printf("-----------------------------------\n");
}


/**
 * �ڵ�i�е�j�з�������
 */
void put(int i, int j)
{
	chess[i-1][j-1] = 1;
}

/**
 * �Ƴ���i�е�j������
 */
void remove(int i, int j)
{
	chess[i-1][j-1] = 0;
}

/**
 * �ڵ�row�е�col���ûʺ��Ƿ�Ϸ����Ϸ�����true
 */
bool isReasonable(int n, int row, int col)
{
	int i, j, count1, count2, count3;
	count1 = count2 = count3 = 0;
	for (i=0; i<n; i++) {
		count3 = 0;
		for (j=0; j<n; j++) {
			if (i-j == row-col && 1 == chess[i][j])
				count1++;
			if (i+j == row+col-2 && 1 == chess[i][j])
				count2++;
			if (i+1 == col && 1 == chess[j][i])
				count3++;
		}
		if (count3 > 1)
			return false;
	}
	if (count1 > 1 || count2 > 1)
		return false;
	return true;
}