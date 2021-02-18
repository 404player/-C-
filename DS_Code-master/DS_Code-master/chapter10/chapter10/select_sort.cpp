#include <stdio.h>

#include "my_headers.h"

/**
 * �㷨10.9����˳�������ѡ������
 */
void SelectSort(SqList &L)
{
	int i, j;
	for (i = 1; i < L.length; i++) {
		j = SelectMinKey(L, i);
		if (i != j) {
			swap(L.elem[i], L.elem[j]);
		}
	}
}

/**
 * ѡ��L.r[i...L.length]��key��С�ļ�¼��������λ��
 */
int SelectMinKey(SqList L, int i)
{
	int pos, k, min;
	min = L.elem[i];
	pos = i;
	for (k = i + 1; k <= L.length; k++) {
		if (min > L.elem[k]) {
			min = L.elem[k];
			pos = k;
		}
	}
	return pos;
}

/**
 * �㷨10.10����֪H.r[s...m]�м�¼�Ĺؼ��ֳ�H.r[s].key֮�������ѵĶ��壬
 * ����������H.r[s]�Ĺؼ��֣�ʹH.r[s...m]��Ϊһ���󶥶�
 */
void HeapAdjust(HeapType &H, int s, int m)
{
	int rc, j;
	rc = H.elem[s];
	for (j = 2 * s; j <= m; j = j * 2) {
		if (j < m && H.elem[j] < H.elem[j + 1]) {
			++j;
		}
		if (rc >= H.elem[j]) {
			break;;
		}
		H.elem[s] = H.elem[j];
		s = j;
	}
	H.elem[s] = rc;
}

/**
 * �㷨10.11
 */
void HeapSort(HeapType &H)
{
	int i;
	for (i = H.length / 2; i > 0; i--) {
		HeapAdjust(H, i, H.length);
	}
	for (i = H.length; i > 1; i--) {
		swap(H.elem[1], H.elem[i]);
		HeapAdjust(H, 1, i - 1);
	}
}