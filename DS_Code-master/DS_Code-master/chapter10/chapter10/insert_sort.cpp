#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "my_headers.h"

/**
 * ���ļ�filename�ж������ݴ���˳���L��0�ŵ�Ԫ����
 */
Status CreateSqList(SqList &L, char *filename)
{
	InitList_Sq(L);

	FILE *pf;
	ElemType e;

	pf = fopen(filename, "r");
	if (NULL == pf) {
		printf("���ļ�%sʧ�ܣ�\n", filename);
		return ERROR;
	}
	while (fscanf(pf, "%d", &e) != EOF) {
		ListInsert_Sq(L, 2, e);
	}
	fclose(pf);
	return OK;
}

/**
 * �㷨10.1����˳�������������
 */
void InsertSort(SqList &L)
{
	int i, j;
	for (i = 2; i <= L.length; i++) {
		if (L.elem[i] < L.elem[i-1]) {	//Ѱ�Һ��ʵĲ���λ��
			L.elem[0] = L.elem[i];
			L.elem[i] = L.elem[i-1];
			for (j = i-2; 
				L.elem[0] < L.elem[j]; j--) {
					L.elem[j+1] = L.elem[j];//��¼����
			}
			L.elem[j+1] = L.elem[0];	//���뵽��ȷλ��
		}
	}
}

/**
 * �㷨10.2���۰��������
 */
void BInsertSort(SqList &L)
{
	int i, j, low, high, mid;
	for (i = 2; i <= L.length; i++) {
		L.elem[0] = L.elem[i];
		high = i - 1;
		low = 1;
		while (high >= low) {	//�۰��ѯ����λ�ã�ӦΪlowλ��
			mid = (high + low) / 2;
			if (L.elem[0] < L.elem[mid]) {
				high = mid - 1;
			} else {
				low = mid + 1;
			}
		}
		for (j = i - 1; j >= low; j--) {	//��¼����
			L.elem[j+1] = L.elem[j];
		}
		L.elem[low] = L.elem[0];
	}
}

/**
 * 2��·���������㷨
 */
void TwoInsertSort(SqList &L)
{
	ElemType *d;
	int first, final, i, j;
	d = (ElemType *)malloc((L.length+1) * sizeof(ElemType));
	first = 0;
	final = 0;
	if (L.length > 0) {
		d[1] = L.elem[1];	//L�еĵ�һ��Ԫ����d���м�λ��
		first = 0;
		final = 1;
	}
	
	for (i = 2; i <= L.length; i++) {
		if (L.elem[i] > d[1]) {	//���뵽�󲿷�
			for (j = final; L.elem[i] < d[j]; j--) {	
				d[j+1] = d[j];	//��¼����
			}
			++final;
			d[j+1] = L.elem[i];	//����
		} else {	//���뵽ǰ����
			if (0 == first) {
				first = L.length;
				d[L.length] = L.elem[i];
			} else {
				for (j = first; L.elem[i] > d[j]; j++) {
					d[j - 1] = d[j];	//��¼����
				}
				--first;
				d[j-1] =L.elem[i]; 
			}
		}
	}

	if (0 == first) {
		for (i = 1; i <= L.length; i++) {
			L.elem[i] = d[i];
		}
	} else {
		for (i = first, j = 1; i <= L.length; i++, j++) {
			L.elem[j] = d[i];
		}
		for (i = 1; i <= final; i++, j++) {
			L.elem[j] = d[i];
		}
	}
}

/**
 * ��̬���������
 */
void TableInsertSort(SLinkList &S)
{
	int i, j, p;
	S.r[0].key = INT_MAX;
	
	if (S.length > 0) {
		S.r[1].next = 0;
		S.r[0].next = 1;
	}
	
	for (i = 2; i <= S.length; i++) {
		p = 0;
		for (j = S.r[0].next; S.r[i].key > S.r[j].key && j > 0; 
			p = j, j = S.r[j].next) {	//Ѱ�Ҳ���λ��
			;
		}
		S.r[i].next = j;
		S.r[p].next = i;
	}
}

/**
 * ������̬�������ļ�filename�ж�ȡ���ݣ���ȡʧ�ܷ���ERROR
 */
Status CreateSLinkList(SLinkList &S, char *filename)
{
	FILE *pf;
	int key, i;
	i = 1;
	S.length = 0;
	pf = fopen(filename, "r");
	if (NULL == pf) {
		printf("���ļ�%sʧ�ܣ�\n", filename);
		return ERROR;
	}
	while (EOF != fscanf(pf, "%d", &key)) {
		S.r[i].key = key;
		S.length++;
		++i;
	}
	fclose(pf);
	return OK;
}

/**
 * �㷨10.3�����ݾ�̬����SL�и�����ָ��ֵ������¼λ�ã�ʹ��SL�м�¼���ؼ��ַǵݼ�����
 * ˳������
 */
void Arrang(SLinkList &SL)
{
	int p, q, i, temp;
	p = SL.r[0].next;	//ָ�������еĵ�һ����¼
	for (i = 1; i <= SL.length; i++) {
		if (p != i) {
			swap(SL.r[i].key, SL.r[p].key);
			q = SL.r[p].next;
			SL.r[p].next = SL.r[i].next;
			SL.r[i].next  = p;
			p = q;
		}

		while (p <= i && p != 0) {
			p = SL.r[p].next;
		}
	}
}

/**
 * ����������i, j
 */
void swap(int &i, int &j)
{
	int temp;
	temp = i;
	i = j;
	j = temp;
}

/**
 * �㷨10.4
 */
void ShellInsert(SqList &L, int dk)
{
	int i, j;
	for (i = dk + 1; i <= L.length; i++) {
		if (L.elem[i] < L.elem[i - dk]) {
			L.elem[0] = L.elem[i];
			for (j = i - dk; j > 0 && L.elem[0] < L.elem[j]; 
				j = j - dk) {
				L.elem[j + dk] = L.elem[j];
			}
			L.elem[j + dk] = L.elem[0];
		}
	}
}

/**
 * �㷨10.5��ϣ�����򣬰���������dlta[0...t-1]��˳���L��ϣ������
 * ��dlta[t-1]����Ϊ1
 */
void ShellSort(SqList &L, int dlta[], int t)
{
	int k;
	for (k = 0; k < t; k++) {
		ShellInsert(L, dlta[k]);
	}
}