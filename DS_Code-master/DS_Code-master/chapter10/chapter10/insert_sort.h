/* �������� */

#ifndef _INSERT_SORT_H_
#define _INSERT_SORT_H_

/* ��̬���� */
#define SIZE 100
typedef struct {	//��������
	int key;
	int next;
}SLNode;
typedef struct {	//��̬����
	SLNode r[SIZE];	//0�ŵ�ԪΪ��ͷ���
	int length;	//����ǰ����
}SLinkList;

Status CreateSqList(SqList &L, char *filename);
void InsertSort(SqList &L);
void BInsertSort(SqList &L);
void TwoInsertSort(SqList &L);
void TableInsertSort(SLinkList &S);
Status CreateSLinkList(SLinkList &S, char *filename);
void Arrang(SLinkList &SL);
void swap(int &i, int &j);
void ShellInsert(SqList &L, int dk);
void ShellSort(SqList &L, int dlta[], int t);

#endif