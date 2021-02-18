#include <stdio.h>

#include "my_headers.h"

/**
 * �㷨10.6��a��������˳���L���ӱ�L.r[low...high]�ļ�¼��ʹ�����¼��λ��
 * ������������λ�ã���ʱ����֮ǰ(֮�󣩵ļ�¼����С��������
 */
int Partition_a(SqList &L, int low, int high)
{
	int pivotkey;
	pivotkey = L.elem[low];		//��һ����¼�������¼
	while (low < high) {
		while (low < high && L.elem[high] >= pivotkey) {
			--high;
		}
		swap(L.elem[low], L.elem[high]);
		while (low < high && L.elem[low] <= pivotkey) {
			++low;
		}
		swap(L.elem[low], L.elem[high]);
	}
	return low;
}

/**
 * �㷨10.7(b)�����㷨10.7(a)�ĸĽ��㷨�������˽����Ĳ���
 */
int Partition(SqList &L, int low, int high)
{
	int pivotkey;
	L.elem[0] = L.elem[low];
	pivotkey = L.elem[low];		//��һ����¼�������¼
	while (low < high) {
		while (low < high && L.elem[high] >= pivotkey) {
			--high;
		}
		L.elem[low] = L.elem[high];
		while (low < high && L.elem[low] <= pivotkey) {
			++low;
		}
		L.elem[high] = L.elem[low];
	}
	L.elem[low] = L.elem[0];
	return low;
}

/**
 * �㷨10.7���ݹ鷨��˳���L�е�������L.r[low...high]����������
 */
void QSort(SqList &L, int low, int high)
{
	int pivotloc;
	if (low < high) {
		pivotloc = Partition(L, low, high);
		QSort(L, low, pivotloc - 1);
		QSort(L, pivotloc + 1, high);
	}
}

/**
 * �㷨10.8����������
 */
void QuickSort(SqList &L)
{
	QSort(L, 1, L.length);
}