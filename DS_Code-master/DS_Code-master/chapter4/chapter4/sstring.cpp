/* ˳�򴮻�������ʵ�� */

#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * ����һ����ֵ����chars�Ĵ�T, chars���ַ�������
 */
Status StrAssign(SString &T, char *chars)
{
	int i = 0;
	while ('\0' != *(chars+i) && i < MAXSTRLEN) {
		T[i+1] = *(chars+i);
		++i;
	}
	T[0] = i;	//�����ȸ���0�ŵ�Ԫ
	
	return 0;
}

/**
 * �ɴ�S���Ƶô�T
 */
Status StrCopy(SString &T, SString S)
{
	int i;
	for (i=0; i<=S[0]; i++) {
		T[i] = S[i];
	}
	return 0;
}

/**
 * ��SΪ�մ�������true�����򷵻�false
 */
bool StrEmpty(SString S)
{
	if (0 == S[0])
		return true;
	return false;
}

/**
 * ��S>T, ����>0, S=T, =0, S<T, <0
 */
Status StrCompare(SString S, SString T)
{
	int i = 1, j = 1;
	while (i<=S[0] && j<=T[0]) {
		if (S[i] > T[i])
			return 1;
		else if (S[i] < T[i])
			return -1;
		else {
			i++;
			j++;
		}
	}
	if (S[0] == T[0])	//�������ʱ
		return 0;
	else if (S[0] < T[0])
		return -1;
	else
		return 1;
}

/**
 * ���ش�����
 */
int StrLength(SString S)
{
	return S[0];
}

/**
 * ��S��Ϊ�մ�
 */
void ClearString(SString &S)
{
	S[0] = 0;
}

/**
 * ��T����S1��S2���������Ĵ�
 */
void Concat(SString &T, SString S1, SString S2)
{
	int t = 1, s = 1;
	while (t <= MAXSTRLEN && s <= S1[0]+S2[0]) {
		if (s <= S1[0])
			T[t++] = S1[s++];
		else {
			T[t++] = S2[s-S1[0]];
			++s;
		}
	}
	T[0] = t-1;
}

/**
 * ��ӡ��
 */
void displayStr(SString T)
{
	int i = 1;
	while (i <= T[0])
		printf("%c", T[i++]);
}

/**
 * ��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ����������Ϸ�����ERROR, ���򷵻�OK
 */
Status SubString(SString &Sub, SString S, int pos, int len)
{
	int i, j;
	i = pos;
	j = 1;
	if (pos < 1 || pos > S[0] 
		|| len < 0 || len > S[0]-pos +1)	// �������Ϸ�
			return ERROR;
	 while (j <= len) {
		Sub[j] = S[i];
		++i;
		++j;
	 }
	 Sub[0] = len;
	 return OK;
}

/**
 * ��������S�е�pos-1���ַ�����Ӵ�Tλ��, �����ڷ���0, TΪ�ǿմ�
 */
int Index(SString S, SString T, int pos)
{
	int i, j;
	i = pos;
	j = 1;
	if (pos < 1 || pos > S[0] || 0 == T[0])	//�������Ϸ�
		return ERROR;
	while (i <= S[0]) {
		if (S[i] == T[j]) {
			i++;
			j++;
		} else {
			i = i-j+2;
			j = 1;
		}

		if (j == T[0]+1)	//����ƥ����Ӵ�
			return (i-j+1);
	}
	return 0;
	
}

/**
 * T�Ƿǿմ�����V�滻������������T��ȵĲ��ص����Ӵ�
 */
Status Replace(SString &S, SString T, SString V)
{
	int pos;
	pos = 1;
	pos = Index(S, T, pos);
	while (0 != pos && ERROR != pos) {	//�ҵ����Ӵ�
		StrDelete(S, pos, T[0]);	//��ɾ���Ӵ�
		StrInsert(S, pos, V);		//�ٲ���Ҫ�滻�Ĵ�
		pos = Index(S, T, pos+V[0]);
	}
	return OK;
}

/**
 * �ڴ�S�ĵ�pos���ַ�֮ǰ���봮T, ��ѭ�ض�ԭ��
 */
Status StrInsert(SString &S, int pos, SString T)
{
	int tlen, slen;
	int i, j, k;
	k = 0;
	
	if (pos < 1 || pos > S[0]+1)	//�������Ϸ�
		return ERROR;
	tlen = T[0];
	slen = S[0];
	i = pos;
	j = 1;
	if (pos == S[0]+1) {	//�������������
		while (S[0]+j <= MAXSTRLEN && j <= T[0]) {
			S[S[0]+j] = T[j];
			j++;
		}
		if (j <= T[0])	//�ռ䲻�����ض���
			S[0] = MAXSTRLEN;
		else
			S[0] = S[0] + T[0];
	} else {		//�����м�����
		for (i=S[0]; i>=pos; i--) {
			if (i+tlen <= MAXSTRLEN)
				S[i+tlen] = S[i];
			else
				k = i;	// �����λ��
		}
		i = pos;
		j = 1;
		while (i <= MAXSTRLEN && j <= tlen) {
			S[i] = T[j];
			i++;
			j++;
		}
		if (j <= T[0])
			S[0] = MAXSTRLEN;
		else {
			if (k != 0)	//����������
				S[0] = MAXSTRLEN;
			else 
				S[0] = S[0] + T[0];
		}
	}
	return OK;
}

/**
 * �Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlen���Ӵ�
 */
Status StrDelete(SString &S, int pos, int len)
{
	int i, j;
	if (pos < 1 || pos > S[0]-len+1)
		return ERROR;
	if (S[0] == pos+len-1)
		S[0] = S[0]-len;
	else {
		i = pos+len;
		while (i <= S[0]) {	//ɾ���Ӵ�
			S[i-len] = S[i];
			i++;
		}
		S[0] = S[0]-len;
	}
	return OK;
}
