#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * �㷨6.8���Ҽ���S��i�����Ӽ��ĸ�
 */
int find_mfset(MFSet S, int i)
{
	int j;
	if (i<1 || i>S.n)
		return ERROR;
	for (j=i; S.nodes[j].parent>0; j=S.nodes[j].parent)
		;
	return j;
}


/**
 * �㷨6.9��S.nodes[i]��S.nodes[j]�ֱ�ΪS�Ļ����ཻ�������Ӽ�Si��Sj�ĸ���㣬
 * �󲢼�SiUSj
 */
Status merge_mfset(MFSet &S, int i, int j)
{
	if (i<1 || i>S.n || j<1 || j>S.n)
		return ERROR;
	S.nodes[i].parent = j;
	return OK;
}

/**
 * �㷨6.10���Ľ����󲢼����㷨��������parent���д洢�Ӽ�������Ԫ�صĸ�ֵ
 */
Status mix_mfset(MFSet &S, int i, int j)
{
	if (i<1 || i>S.n || j<1 || j>S.n)
		return ERROR;
	if (S.nodes[i].parent > S.nodes[j].parent) {	// Si������Ա����Sj����
		S.nodes[j].parent += S.nodes[i].parent;
		S.nodes[i].parent = j;
	} else {
		S.nodes[i].parent += S.nodes[j].parent;
		S.nodes[j].parent = i;
	}
	return OK;
}

/**
 * �㷨6.11���㷨6.8�ĸĽ�������ѹ��·����
 * ȷ��i�����Ӽ���������i����·�������н�㶼��ɸ��ĺ��ӽ��
 */
int fix_mfset(MFSet &S, int i)
{
	int j, k, t;

	if (i<1 || i>S.n)
		return ERROR;
	for (j=i; S.nodes[j].parent>0; j=S.nodes[j].parent) //ѭ�������� j ���Ǹ����
		;
	for (k=i; k!=j; k=t) {
		t = S.nodes[k].parent;
		S.nodes[k].parent = j;
	}
	return j;	//����i�����Ӽ��ĸ����
}