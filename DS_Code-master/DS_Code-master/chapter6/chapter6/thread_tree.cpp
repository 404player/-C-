#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"


/**
 * ������˳���������
 */
Status CreateBiThrTree(BiThrTree &T)
{
	char ch;
//	scanf("%c", &ch);
	ch = getchar();
	if (' ' == ch)
		T = NULL;
	else {
		T = (BiThrNode *)malloc(sizeof(BiThrNode));
		if (!T)
			return ERROR;
		T->data = ch;
		T->LTag = Link;
		T->RTag = Link;
		CreateBiThrTree(T->lchild);	//����������
		CreateBiThrTree(T->rchild);	//����������
	}
	return OK;
}

/**
 * �㷨6.5��Tָ��ͷ��㣬ͷ��������lchildָ�����㣬����ָ����������һ����㣬������������������ķǵݹ��㷨
 */
Status InOrderTraverse_Thr(BiThrTree T, Status (*visit)(TElemType e))
{
	BiThrTree p;
	p = T->lchild;		//pָ������
	while (p != T) {	//�������������ʱ��p == T
		while (Link == p->LTag)
			p = p->lchild;	// �ߵ��������ľ�ͷ
		if (ERROR == visit(p->data))
			return ERROR;
		while (Thread == p->RTag && p->rchild != T) {	//����Ϊ������ָ���̽�㣬��pΪ���һ�����ʱ��p->rchild == T (ͷ���)
			p = p->rchild;
			if (ERROR == visit(p->data))		//���ʺ�̽��
				return ERROR;
		}
		p = p->rchild;		//������������ʱ����pָ����������������pָ��ͷ��㣬������������
	}
	return OK;
}
BiThrTree pre;
/**
 * �㷨6.6���������������T��������������������Thrtָ��ͷ���
 */
Status InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
	printf("");	//��֪��ʲôԭ�򣬲�����һ���ʲô����ʾ������������������
	if (!(Thrt = (BiThrNode *)malloc(sizeof(BiThrTree)) ))	//��ͷ���
		return ERROR;
	Thrt->LTag = Link;
	Thrt->RTag = Thread;
	Thrt->rchild = Thrt;
	if (!T)
		Thrt->lchild = Thrt;		//TΪ��������ͷ�����ָ��ָ��ͷ���
	else {
		Thrt->lchild = T;		//ͷ�������ָ������
		pre = Thrt;			//pre��ʼʱָ��ͷ���
		InThreading(T);		//�����������������
		pre->rchild = Thrt;		//���һ����������������һ����������ָ��ͷ���
		pre->RTag = Thread;
		Thrt->rchild = pre;		//ͷ��������ָ�����һ�������Ľ��
	}
	return OK;
}

/**
 * �㷨6.7
 */
void InThreading(BiThrTree p)
{
	if (p) {
		InThreading(p->lchild);	//������������
		if (!p->lchild) {	//����Ϊ��ʱ��ǰ������
			p->LTag = Thread;
			p->lchild = pre;	//preΪ����������ʵ�ǰһ�����
		}
		if (!pre->rchild) {	//ǰһ����������Ϊ��ʱ���������
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;		//����preָ��p��ǰ��
		InThreading(p->rchild);	//������������
	}
}