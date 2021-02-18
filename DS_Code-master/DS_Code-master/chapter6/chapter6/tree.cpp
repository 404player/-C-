#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * �㷨6.4��������˳���������
 */
Status CreateBiTree(BiTree &T)
{
	char ch;
	scanf("%c", &ch);
	if (' ' == ch)
		T = NULL;
	else {
		T = (BiTNode *)malloc(sizeof(BiTNode));
		if (!T)
			return ERROR;
		T->data = ch;
		CreateBiTree(T->lchild);	//����������
		CreateBiTree(T->rchild);	//����������
	}
	return OK;
}

/**
 * ��ӡһ��Ԫ��
 */
Status display(TElemType e)
{
	printf("%c ", e);
	return OK;
}

/**
 * �㷨6.1�������������������ÿ��Ԫ�ص��ú���viist
 */
Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
	if (T) {
		if (OK == visit(T->data))
			if (OK == PreOrderTraverse(T->lchild, visit))
				if (OK == PreOrderTraverse(T->rchild, visit))
					return OK;
		return ERROR;
	} else
		return OK;
}

/**
 * �����������������ÿ��Ԫ�ص��ú���viist
 */
Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
	if (T) {
		if (OK == InOrderTraverse(T->lchild, visit))
			if (OK == visit(T->data))	
				if (OK == InOrderTraverse(T->rchild, visit))
					return OK;
		return ERROR;
	} else
		return OK;
}

/**
 * �����������������ÿ��Ԫ�ص��ú���viist
 */
Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
	if (T) {
		if (OK == PostOrderTraverse(T->lchild, visit))
			if (OK == PostOrderTraverse(T->rchild, visit))
				if (OK == visit(T->data))	
					return OK;
		return ERROR;
	} else
		return OK;
}

/**
 * ������������������ö���ʵ��
 */
Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
	BiTree p;
	LinkQueue Q;
	InitQueue(Q);
	p = T;
	while (p || !QueueEmpty(Q)) {
		if (p) {
			visit(p->data);
			if (p->lchild)
				EnQueue(Q, p->lchild);
			if (p->rchild)
				EnQueue(Q, p->rchild);
			if (!QueueEmpty(Q))
				DeQueue(Q, p);
			else		//����Ϊ��ʱ���˳�whileѭ��
				break;
		}
	}
	return OK;
}

/**
 * �ǵݹ鷨ʵ���������������T
 */
Status PreOrderTraverse2(BiTree T, Status (*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S)) {
		if (p) {	//���ʸ�ָ�룬��ָ���ջ
			if (ERROR == visit(p->data))
				return ERROR;
			Push(S, p);
			p = p->lchild;
		} else {
			Pop(S, p);
			p = p->rchild;
		}
	}
	return OK;
}

/**
 * �㷨6.2���ǵݹ鷨ʵ���������������T
 */
Status InOrderTraverse2(BiTree T, Status (*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	Push(S, T);		// ��ָ���ջ
	while (!StackEmpty(S)) {
		while (OK == GetTop(S, p) && p)	//�����ߵ���ͷ
			Push(S, p->lchild);
		Pop(S, p);		//��ָ����ջ
		if (!StackEmpty(S)) {
			Pop(S, p);
			if (ERROR == visit(p->data))
				return ERROR;
			Push(S, p->rchild);
		} // if
	} // while
	return OK;
}

/**
 * �㷨6.3���ǵݹ鷨ʵ���������������T
 */
Status InOrderTraverse3(BiTree T, Status (*visit)(TElemType e))
{
	SqStack S;
	BiTree p;
	InitStack(S);
	p = T;
	while (p || !StackEmpty(S)) {
		if (p) {	//��ָ���ջ������������
			Push(S, p);
			p = p->lchild;
		}
		else {		//��ָ����ջ�����ʸ���㣬����������
			Pop(S, p);
			if (ERROR == visit(p->data))
				return ERROR;
			p = p->rchild;
		} //if
	} //while
	return OK;
}

/**
 * �ǵݹ鷨ʵ�ֺ������������T
 */
Status PostOrderTraverse2(BiTree T, Status (*visit)(TElemType e))
{
	SqStack S;
	InitStack(S);
	BiTree p;
	int Tag[20];	//��־ջ
	int t = 1;
	p = T;
	while (p || !StackEmpty(S)) {
		while (p) {	//�����ߵ���ͷ
			Push(S, p);
			p = p->lchild;
			Tag[t++] = 0;
		}

		while (!StackEmpty(S) && 1 == Tag[t-1]) {	//����־Ϊ1��ʾ�������Ѿ����ʹ�
			Pop(S, p);
			t--;
			if (ERROR == visit(p->data))
				return ERROR;
		}

		if (!StackEmpty(S)) {	//����־Ϊ0�����������������������־��Ϊ1
			Tag[t-1] = 1;
			GetTop(S, p);
			p = p->rchild;
		} 
		else
			break;
	}

	return OK;
}