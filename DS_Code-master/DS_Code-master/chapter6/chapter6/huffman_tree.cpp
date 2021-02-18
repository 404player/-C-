/* �շ��������շ�������ʵ�� */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_headers.h"

/**
 * �㷨6.12����շ���������㷨
 * w���n���ַ���Ȩֵ����>0��������շ�����HT�������n���ַ��ĺշ�������HC
 */
Status HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
	int m, i, s1, s2, start, current, further;
	HuffmanTree p;
	char *cd;
	s1 = 0;
	s2 = 0;
	if (n <= 1)
		return ERROR;
	m = 2*n-1;	//һ����n�����ĺշ�������2*n-1�����
	HT = (HuffmanTree)malloc((m+1) * sizeof(HTNode));	// 0�ŵ�Ԫδ��
	for (p = HT+1, i=1; i<=n; ++i, ++p, ++w) {	//��ʼ��ǰn����㣬����n��Ȩֵ���θ�������
		(*p).weight = *w;		
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	for (; i<=m; ++i, ++p) {		//��ʼ��ʣ��Ľ��
		(*p).weight = 0;		
		(*p).parent = 0;
		(*p).lchild = 0;
		(*p).rchild = 0;
	}
	for (i=n+1; i<=m; ++i) {		//���շ�����
		s1 = 0;
		s2 = 0;
		Select(HT, i-1, s1, s2);	//�ҵ�Ȩ��С�����������, ��s1��ȨС��s2
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	/* ��Ҷ�ӵ���������ÿ���ַ��ĺշ������� */
	HC = (HuffmanCode)malloc((n+1)*sizeof(char *));		//����n���ַ������ͷָ��������0��Ԫδ��
	cd = (char *)malloc(n*sizeof(char));	//���������Ĺ����ռ䣬n���ַ��ı���λ�����Ϊn-1λ�����һλ�洢'\0'
	cd[n-1] = '\0';
	for (i=1; i<=n; i++) {	//����ַ���շ�������
		start = n-1;
		for (current=i, further=HT[i].parent; further!=0; 
			current=further, further=HT[further].parent) {	//��Ҷ�ӿ�ʼ�������������
				if (current == HT[further].lchild)
					cd[--start] = '0';
				else
					cd[--start] = '1';
		}
		HC[i] = (char *)malloc((n-start)*sizeof(char));	//Ϊ��i���ַ��������ռ�
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
	cd = NULL;
	return OK;
}

/**
 * ������HT[1...n]��ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1,s2, ����s1��ȨС��s2��Ȩ
 */
Status Select(HuffmanTree HT, int n, int &s1, int &s2)
{
	int i;
	for (i=1; i<=n; i++) {		//�������Ȩֵ��С���������
		if (0 == HT[i].parent) {	//��parentΪ0�Ľ����Ѱ��
			 if (0 == s1)
				s1 = i;
			 else if (0 == s2)
				s2 = i;
			 else
				 max(HT, s1, s2, i);

		}
	}
	if (s1 > s2) {
		i = s1;
		s1 = s2;
		s2 = i;
	}
	return OK;
}

/**
 * s1, s2����HT��s1, s2, n����Ȩֵ��С������
 */
void max(HuffmanTree HT, int &s1, int &s2, int n)
{
	if (HT[s1].weight <= HT[s2].weight) {
		if (HT[n].weight < HT[s2].weight)
			s2 = n;
	} else {
		if (HT[n].weight < HT[s1].weight)
			s1 = n;
	}
}

/**
 * �㷨6.13�������շ����������,HTΪ�Ѵ��ڵĺշ�������HC�����ַ�����, nΪ�ַ�����,������Ҷ�Ӹ���
 */
void get_huffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{
	int i;
	char *cd;	//����Ĺ����ռ�
	int cdlen;	//���볤��
	char p;
	HC = (HuffmanCode)malloc((n+1)*sizeof(char *));	//����ָ������ͷָ��ռ䣬0�ŵ�Ԫδ��
	cd = (char *)malloc(n*sizeof(char));
	cdlen = 0;
	p = 2*n-1;	//pָ������

	for (i=1; i<=p; i++)
		HT[i].weight = 0;	//�����շ�����ʱ��������־
	while (p) {
		if (0 == HT[p].weight) {	//����
			HT[p].weight = 1;
			if (HT[p].lchild != 0) {
				p = HT[p].lchild;
				cd[cdlen++] = '0';
			} else if (0 == HT[p].rchild) {
				HC[p] = (char *)malloc((cdlen+1)*sizeof(char));
				cd[cdlen] = '\0';
				strcpy(HC[p], cd);
			}
		} else if (1 == HT[p].weight) {	//����
			HT[p].weight = 2;
			if (HT[p].rchild != 0) {
				p = HT[p].rchild;
				cd[cdlen++] = '1';
			}
		} else {
			HT[p].weight = 0;
			p = HT[p].parent;
			cdlen--;
		}
	}

}