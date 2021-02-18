#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "my_headers.h"

int hashsize[] = {11, 111, 997};	//��ϣ������������һ�����ʵ���������

/**
 * �㷨9.17���ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ�أ������ҳɹ�����pָʾ�������ݣ�������
 * SUCCESS��������pָʾ����λ�ã�������UNSUCCESS��cͳ�Ƴ�ͻ���������ֵΪ0��������ʱ
 * ���ֹ�ϣ������ʱ�����¹�ϣ������������
 */
Status SearchHash(HashTable &H, KeyType K, int &p, int &c)
{
	c = 0;		//��ͻ������ʼ��
	p = Hash(K, hashsize[H.sizeindex]);
	while (H.elem[p].key != NULLKEY		//�ñ����м�¼
		&& !EQ(K, H.elem[p].key)) {	//���ҹؼ��ֲ���
			c++;			//��ͻ������1
			if (c == hashsize[H.sizeindex]) {	//��ϣ���������ؽ�
				p = hashsize[H.sizeindex];	//����λ��
				RecreateHashTable(H);
				return UNSUCCESS;
			}
			collision(p, c, hashsize[H.sizeindex]);		
	}
	if EQ(K, H.elem[p].key) {	//���ҳɹ�
		return SUCCESS;
	} else {	//���Ҳ��ɹ���p���ص��ǲ���λ��
		return UNSUCCESS;
	}
}

/**
 * ��ϣ������ֱ�Ӷ�ַ��
 */
int Hash(KeyType K, int p)
{
	return (K%p);
}

/**
 * ������ͻʱ���ɿ��Ŷ�ַ�������¸�λ�ã�cΪ������lenΪ��ϣ������p���ظ�λ��
 */
Status collision(int &p, int c, int len)
{
	if (c == len) {
		return ERROR;
	} else {
		p = (p + c) % len;
		return OK;
	}
	
}

/**
 * �㷨9.17�����Ҳ��ɹ�ʱ��������Ԫ��e�����Ŷ�ַ��ϣ��H�У�������OK������ͻ��������
 * ���ؽ���ϣ������UNSUCCESS��
 */
Status InsertHash(HashTable &H, ElemType e)
{
	int p, c;
	c = 0;
	if (SearchHash(H, e.key, p, c) == SUCCESS) {
		return DUPLICATE;
	} else if (c < hashsize[H.sizeindex] / 2) {
		H.elem[p] = e;
		H.count++;
		return OK;
	} else {
		RecreateHashTable(H);
		return UNSUCCESS;
	}
}

/**
 * �ؽ���ϣ���ɹ�����OK��ʧ�ܷ���ERROR
 */
Status RecreateHashTable(HashTable &H)
{
	int i;
	H.elem = (ElemType *)realloc(H.elem, 
			hashsize[H.sizeindex + 1] * sizeof(ElemType));
	if (NULL == H.elem) {
		return ERROR;
	} else {
		for (i = hashsize[H.sizeindex]; 
			i < hashsize[H.sizeindex + 1]; i++) {
			H.elem[i].key = NULLKEY;
		}
		H.sizeindex++;
		return OK;
	}
	
}

/**
 * ��ʼ����ϣ���ɹ�����OK��ʧ�ܷ���ERROR
 */
Status InitHashTable(HashTable &H)
{
	H.sizeindex = 0;
	H.count = 0;
	H.elem = (ElemType *)malloc(hashsize[H.sizeindex] * sizeof(ElemType));
	if (NULL == H.elem) {
		return ERROR;
	}
	for (int i = 0; i < hashsize[H.sizeindex]; i++) {
		H.elem[i].key = NULLKEY;
	}
	return OK;
}

/**
 * ���ļ�filename�ж������ݽ�����ϣ��H���ɹ�����OK��ʧ�ܷ���ERROR
 */
Status CreateHashTable(HashTable &H, char *filename)
{
	ElemType e;
	FILE *pf;
	InitHashTable(H);
	pf = fopen(filename, "r");
	if (NULL == pf) {
		printf("���ļ�%sʧ�ܣ�\n", filename);
		return ERROR;
	}
	while (EOF != fscanf(pf, "%d", &e.key)) {
		InsertHash(H, e);
	}
	fclose(pf);
	return OK;
}

/**
 * ��ӡ��ϣ���е�Ԫ�صĹؼ���
 */
void DisplayHashTable(HashTable H)
{
	int i;
	for (i = 0; i < hashsize[H.sizeindex]; i++) {
		if (NULLKEY != H.elem[i].key) {
			printf("%d ", H.elem[i].key);
		}	
	}
}