#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * �㷨4.1 �� 4.5 Ϊ��������ʵ��
 */

/**
 * �㷨4.6��KMP�㷨
 */
int Index_KMP(SString S, SString T, int pos)
{
	int i = pos;
	int j = 1;
	int *next;
	next = (int *) malloc (T[0]*sizeof(int));
	if (!next)
		return ERROR;
	get_next(T, next);
	while (i <= S[0] && j <= T[0]) {
		if (0 == j || S[i] == T[j]) {
			++i;
			++j;
		} else
			j = next[j];
	}
	if (j > T[0])
		return i-T[0];	//ƥ��ɹ�
	else
		return 0;
}

/**
 * �㷨4.7����ģʽ��T��next����ֵ����������next��
 */
void get_next(SString T, int next[])
{
	int i = 1;	// ��T��������ʱ��ƥ����ַ�λ��
	int j = 0;	// ��T����ģʽ��ʱ��ƥ����ַ�λ��
	next[0] = T[0];
	next[1] = 0;
	while (i < T[0]) {
		if (j == 0 || T[i] == T[j]) {	// j == 0ʱ��next[i] = 1;
			++i;
			++j;
			next[i] = j;	// ��ʱ��T[i-1] == T[j-1]
		}
		else
			j = next[j];	//��ƥ��ʱ��ģʽ���Ƶ�next[j]λ�����¿�ʼƥ��
	}
}

/** 
 * �㷨 4.8
 */
void get_nextval(SString, int nextval[])
{
	int i = 1;	// ��T��������ʱ��ƥ����ַ�λ��
	int j = 0;	// ��T����ģʽ��ʱ��ƥ����ַ�λ��
	nextval[0] = T[0];
	nextval[1] = 0;
	while (i < T[0]) {
		if (j == 0 || T[i] == T[j]) {	// j == 0ʱ��next[i] = 1;
			++i;
			++j;
			if (T[i] != T[j])
				nextval[i] = j;	// ��ʱ��T[i-1] == T[j-1]
			else
				nextval[i] = nextval[j];
		}
		else
			j = nextval[j];	//��ƥ��ʱ��ģʽ���Ƶ�next[j]λ�����¿�ʼƥ��
	}
}