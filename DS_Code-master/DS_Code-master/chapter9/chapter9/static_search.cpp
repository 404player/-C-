/* ��̬����ҵ�����㷨ʵ�� */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "my_headers.h"

/**
 * ����һ����n������Ԫ�صľ�̬���ұ�ST���������ݴ�ָ���ļ�filename�ж�ȡ
 * ����ɹ�����OK�����ļ�ʧ�ܴ��󷵻�FILE_NOT_EXIT���������󷵻�ERROR
 */
Status CreateTable(SSTable &ST, int n, char *filename)
{
	int i;
	FILE *pFile;
	ST.length = n;
	ST.elem = (ElemType *)malloc((ST.length+1) * sizeof(ElemType));
	if (NULL == ST.elem) {		//�����ڴ�ռ�ʧ��
		return ERROR;
	}
	pFile = fopen(filename, "r");
	if (pFile == NULL) {	//���ļ�ʧ��
		printf("���ļ�%sʧ�ܣ�����\n", filename);
		return FILE_NOT_EXIT;
	} else {		//�ɹ����ļ�
		for (i = 1; i <= ST.length; i++) {
				if (EOF == fscanf(pFile, "%d %s %f", 
					&ST.elem[i].key, 
					&ST.elem[i].data, 
					&ST.elem[i].weigth)) {
					printf("��ȡ��¼��������\n", 
						i, filename, ST.length);
					return ERROR;
				}
			
		}
		fclose(pFile);
		return OK;
	}
}

/**
 * ��̬���ұ�ST���ڣ����ٱ�ST
 */
void Destroy(SSTable &ST)
{
	if (ST.elem != NULL) {
		free(ST.elem);
		ST.elem = NULL;
		ST.length = 0;
	}
}

/**
 * �㷨9.1����˳���ST�йؼ��ֵ���key������Ԫ��
 * ���ҵ�������Ԫ��λ�ã����򷵻�0
 */
int Search_Seq(SSTable ST, KeyType key)
{
	int i;
	ST.elem[0].key = key;		//���ڱ���
	for (i = ST.length; !EQ(ST.elem[i].key, key); i--) {
		;
	}
	return i;
}

/**
 * �㷨9.2���������۰����
 * ���ҵ�������Ԫ��λ�ã����򷵻�0
 */
int Search_Bi(SSTable ST, KeyType key)
{
	int low, mid, high;
	int temp;
	low = 1;		//��ʼ����ʼ״̬
	high = ST.length;
	while (low <= high) {
		mid = (low + high) / 2;
		if (LT(key, ST.elem[mid].key)) {		//�м�ֵ��
			high = mid - 1;
			
		} else if (LT(ST.elem[mid].key, key)) {		//�м�ֵС
			low = mid + 1;
		} else {		// ST.elem[0].key == mid, �ҵ�
			return mid;
		}
	}
	/* ִ����whileѭ����low > high, ��ʾû���ҵ�ֵ */
	return 0;
}

/**
 * �㷨9.3���ݹ鹹������Ȳ�����T,sw[]�б��������R[0...length]���ۼ�Ȩֵ��
 * ��Pi = |(SWh + SWl-1) - (SWi + SWi-1)|
 */
void SecondOptimal(BiTree &T, ElemType R[], float sw[], int low, int high)
{
	int i, j;
	i = low;
	float min = fabs(sw[high]-sw[low]);	//��ʼ������i = low��ʱ��
	float dw = sw[high] + sw[low - 1];
	for (j = low + 1; j <= high; j++) {		//ѡ����С�Ħ�Piֵ
		if (fabs(dw - sw[j] - sw[j - 1]) < min) {
			i = j;
			min = fabs(dw - sw[j] - sw[j - 1]);
		}
	}

	T = (BiTree)malloc(sizeof(BiTNode));
	T->data.key = R[i].key;
	if (i == low) {
		T->lchild = NULL;	//������Ϊ��
	} else {
		SecondOptimal(T->lchild, R, sw, low, i-1);	//����������
		
	}

	if (i == high) {
		T->rchild = NULL;	//������Ϊ��
	} else {
		SecondOptimal(T->rchild, R, sw, i+1, high);	//����������
	}
}

/**
 * ���������R[0...length]���ۼ�Ȩֵ�����������sw[]��
 */
void getTableSW(ElemType R[], float sw[], int length)
{
	int i;
	sw[0] = 0;
	for (i = 1; i <= length; i++) {
		sw[i] = sw[i - 1] + R[i].weigth;
	}
}

/**
 * �㷨9.4�� �������ST����һ�ô��Ų�����T
 */
Status CreateSOSTree(SOSTree &T, SSTable ST)
{
	float *sw;
	sw = (float *)malloc((ST.length+1) * sizeof(float));
	if (NULL == sw) {
		return ERROR;
	}
	if (0 == ST.length) {
		T = NULL;
	} else{
		getTableSW(ST.elem, sw, ST.length);
		SecondOptimal(T, ST.elem, sw, 1, ST.length);
	}
	return OK;
}