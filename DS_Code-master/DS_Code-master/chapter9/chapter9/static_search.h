/* ��̬�� */

#ifndef _STATIC_SEARCH_H_
#define _STATIC_SEARCH_H_





typedef struct {
	ElemType *elem;		//��̬��Ԫ�أ�0�ŵ�Ԫ�洢Ҫ��ѯ�Ĺؼ���ֵ����"�ڱ�"��
	int length;		//��̬����
}SSTable;

typedef BiTree SOSTree;		//���Ų�����

Status CreateTable(SSTable &ST, int n, char *filename);
void Destroy(SSTable &ST);
int Search_Seq(SSTable ST, KeyType key);
int Search_Bi(SSTable ST, KeyType key);
void SecondOptimal(BiTree &T, ElemType R[], float sw[], int low, int high);
void getTableSW(ElemType R[], float sw[], int length);
Status CreateSOSTree(SOSTree &T, SSTable ST);

#endif