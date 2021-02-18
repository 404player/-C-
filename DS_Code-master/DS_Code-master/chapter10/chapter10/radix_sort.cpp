/* �������� */

#include <stdio.h>

#include "my_headers.h"

/**
 * �㷨10.15�������㷨����̬����L��r���м�¼�Ѱ�(key[0]...key[i-1])����
 * ���㷨����i���ؼ��ֽ���RADIX���ӱ�ʹͬһ�ӱ��м�¼��key[i]��ͬ��
 * f[0...RADIX-1]��e[0...RADIX-1]�ֱ�ָ����ӱ��е�һ����¼�����һ����¼.
 */
void Distribute(SLCell r[], int i, ArrType &f, ArrType &e)
{
	int j, p;
	for (j = 0; j < RADIX; j++) {	//��ʼ��f[]
		f[j] = 0;
	}
	for (p = r[0].next; p != 0; p = r[p].next) {
		j = ord(r[p].keys[i]);
		if (!f[i]) {
			f[j] = p;
		} else {
			r[e[j]].next = p;
		}
		e[j] = p;
	}
}

/**
 * ���ؼ���Kӳ�䵽[0...RADIX-1]
 */
int ord(KeysType K)
{
	return K;
}

/**
 * �㷨10.16���ռ��㷨��
 */
void Collect(SLCell r[], int i, ArrType f, ArrType e)
{
	int j, t;
	for (j = 0; f[j] != 0; j = succ(f, j)) {
		;
	}
	r[0].next = f[j];
	t = e[j];
	while (j < RADIX) {
		for (j = succ(f, j); j < RADIX-1 && !f[i]; j = succ(f, j)) {
			;
		}
		if (f[j]) {
			r[t].next = f[j];
			t = e[j];
		}
	}
	r[t].next = 0;
}

/**
 * ��f[j]��ĵ�һ���ǿ��ӱ�
 */
int succ(ArrType f, int j)
{
	int i;
	for (i = j + 1; f[i] != 0; i++) {
		;
	}
	return i;
}

/**
 * �㷨10.17����������
 */
void RadixSort(SLList &L)
{
	int i;
	ArrType f, e;
	for (i = 0; i < L.recnum; ++i) {
		L.r[i].next = i + 1;
	}
	L.r[L.recnum].next = 0;
	for (i = 0; i < L.keynum; i++) {
		
		Distribute(L.r, i, f, e);
		Collect(L.r, i, f, e);
	}
}