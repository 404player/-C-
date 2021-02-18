/* ������ϰ�� */

#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * ϰ��6.39�������½�һ�ô���˫����ͽ���־����
 */
Status CreatePTagTree(PTagTree &T)
{
	char ch;
	scanf("%c", &ch);
	if (' ' == ch)
		T = NULL;
	else {
		T = (PTagNode *)malloc(sizeof(BiTNode));
		T->parent = NULL;
		if (!T)
			return ERROR;
		T->data = ch;
		T->mark = Left;	
		CreatePTagTree(T->lchild);	//����������
		CreatePTagTree(T->rchild);	//����������
		printf("");			//���˸�ȥ�ˣ������ȥ�˱�����ʱ���ӡԪ�صĻ�ʲô����ӡ������
		if (NULL != T->lchild)
			T->lchild->parent = T;	//˫����
		if (NULL != T->rchild)
			T->rchild->parent = T;	//˫����
	}
	return OK;
}

/**
 * ϰ��6.39���������������ջ�͵ݹ�ʵ�֣�����ǰ��ִ��T->parent = NULL; ����������bug, ��ʱ���ڵ��Ե�ʱ�����ǶԵ�,
 * ���Ǵ�ӡ����������֪����ʲôԭ��Ӧ�����½����ĺ����й�
 */
Status MyPostOrderTraverse(PTagTree T, Status (*visit)(TElemType e))
{
	PTagTree p, pre;
	p = T;		//pָ������
	while (NULL != p) {
		while (p->lchild && Left == p->mark) {		//�����ߵ���ͷ
			p->mark = Right;		//�´ε���Щ���ʱӦ����������
			p = p->lchild;
		}
		if (NULL == p->lchild)
			p->mark = Right;

		if (p->rchild && Right == p->mark) {
			p->mark = Visit;
			p = p->rchild;
		} else if (NULL == p->rchild) {
			p->mark = Visit;
		}

		while (Visit == p->mark) {
			if (ERROR == visit(p->data))
				return ERROR;
			p = p->parent;
			if (NULL == p)
				break;
		}
	}
	return OK;
}

/**
 * ϰ��6.41�����������λ�����������е�k��λ�ý���ֵ����value���ظ�ֵ��
 * �����k��λ�ò����ڣ���������ERROR�����򷵻�OK��
 * ���뺯��ǰcount��ֵҪ��Ϊ0��countΪ���������м����ı���
 */
Status get_PreOrderValue(BiTree T, int k, int &count, int &value)
{
	if (T) {
		count++;
		if (count == k) {
			value = T->data;
			return OK;
		}
		else {
			if (OK == get_PreOrderValue(T->lchild, k, count, value))	//����������
				return OK;
			else if (OK == get_PreOrderValue(T->rchild, k, count, value))	//����������
				return OK;
			else 
				return ERROR;
		}
	} else
		return ERROR;
}

/**
 * ���������λ�����������е�k��λ�ý���ֵ
 */
Status get_InOrderValue(BiTree T, int k, int &count, int &value)
{
	if (T) {
		if (OK == get_InOrderValue(T->lchild, k, count, value))
			return OK;
		count++;
		if (count == k) {
			value = T->data;
			return OK;
		}
		if (OK == get_InOrderValue(T->rchild, k, count, value))
			return OK;
		return ERROR;
	} else
		return ERROR;
}

/**
 * ���������λ�ں��������е�k��λ�ý���ֵ
 */
Status get_PostOrderValue(BiTree T, int k, int &count, int &value)
{
	if (T) {
		if (OK == get_PostOrderValue(T->lchild, k, count, value))
			return OK;
		if (OK == get_PostOrderValue(T->rchild, k, count, value))
			return OK;
		count++;
		if (count == k) {
			value = T->data;
			return OK;
		}
		return ERROR;
	} else
		return ERROR;
}

/**
 * ϰ��6.42���õݹ鷽�������������Ҷ�ӽ�����Ŀ
 */
void get_LeafCount(BiTree T, int &count)
{
	if (T) {
		if (NULL == T->lchild && NULL == T->rchild)	//Ҷ��
			count++;
		else {
			get_LeafCount(T->lchild, count);	//����������
			get_LeafCount(T->rchild, count);	//����������
		}
	}
}

/**
 * ϰ��6.43���õݹ鷨�������������н������������໥����
 */
void ExchangSubtree(BiTree T)
{
	BiTree temp;
	if (T) {
		if (NULL != T->lchild || NULL != T->rchild) {	//������������
			temp = T->lchild;	
			T->lchild = T->rchild;
			T->rchild = temp;
			ExchangSubtree(T->lchild);		//��������������µ���������
			ExchangSubtree(T->rchild);		//��������������µ���������
		}
	}
}

/**
 * ϰ��6.44�������������Ԫ��ֵx�Ľ��Ϊ������������ȣ�deep����������ȣ�
 * ��������xԪ�صĽ�㣬�򷵻�ERROR�����򷵻�OK
 */
Status get_NodeDeepth(BiTree T, TElemType x, int &deep)
{
	if (T) {
		if (x == T->data) {
			deep = get_TreeDeepth(T);
			return OK;
		} else {
			if (OK == get_NodeDeepth(T->lchild, x, deep))
				return OK;
			if (OK == get_NodeDeepth(T->rchild, x, deep))
				return OK;
			return ERROR;
		}
	} else
		return ERROR;
}

/**
 * ���ض���������ȣ��ݹ��㷨
 */
int get_TreeDeepth(BiTree T)
{
	int ldeep, rdeep;
	if (NULL == T)
		return 0;
	ldeep = get_TreeDeepth(T->lchild);
	rdeep = get_TreeDeepth(T->rchild);
	if (ldeep > rdeep)
		return (ldeep+1);
	return (rdeep+1);
}

/**
 * ɾ��һ���������ͷ���Ӧ�Ľ��ռ�
 * ע�⣬��Ҫ���˼�&������T�޷��ͷ�
 */
void DestroyTree(BiTree &T)
{
	if (T) {
		DestroyTree(T->lchild);	//��ɾ����������
		DestroyTree(T->rchild);
		free(T);
		T = NULL;
	}
}

/**
 * ϰ��6.45�����ڶ�������ÿ��Ԫ��ֵΪx�Ľ�㣬ɾ������Ϊ�������������ͷ���Ӧ���ռ�
 */
void DeleteNode(BiTree &T, TElemType x)
{
	if (T) {
		if (T->data == x)
			DestroyTree(T); 
		else {
			DeleteNode(T->lchild, x);
			DeleteNode(T->rchild, x);
		}
	}
}

/**
 * ϰ��6.46���õݹ鷨����һ�ö�����T��Tc
 */
void CopyTree(BiTree T, BiTree &Tc)
{
	if (T) {
		Tc = (BiTree)malloc(sizeof(BiTNode));
		Tc = T;
		Tc->data = T->data;
		Tc->lchild = T->lchild;
		Tc->rchild = T->rchild;
		if (T->lchild)		//����������
			CopyTree(T->lchild, Tc->lchild);
		if (T->rchild)		//����������
			CopyTree(T->rchild, Tc->rchild);
	}
}

/**
 * �õ�һ�ôӸ���ָ�����p��·����T��ɾ������Ľڵ�;
 */
Status PathTree(BiTree &T, BiTree p)
{
	if (T) {
		if (T == p) {
			if (T->lchild)
				DestroyTree(T->lchild);
			if (T->rchild)
				DestroyTree(T->rchild);
			return OK;
		} else {
			if (OK == PathTree(T->lchild, p))	//��ǰ��㲻�ǣ��͵���������Ѱ��
				return OK;
			else					//��������Ҳ�Ҳ�����ɾ��������
				DestroyTree(T->lchild);
			if (OK == PathTree(T->rchild, p))
				return OK;
			else
				DestroyTree(T->rchild);
			return ERROR;
		}
	} else
		return ERROR;
}

/**
 * ϰ��6.47�������������������tree.cpp��ʵ����
 */

/**
 * ϰ��6.48��*rootΪ����㣬*p��*qΪ��������������㣬�������������Ĺ�ͬ���ȵ��㷨
 * m ���ָ���乲ͬ���ȵ�λ��
 */
Status get_MinComAncester(BiTree root, BiTree p, BiTree q, BiTree m)
{

	return OK;
}

/**
 * ϰ��4.49���ǵݹ鷨�ж������������Ƿ�Ϊ��ȫ������
 */
bool isCompleteBiTree(BiTree T)
{
	LinkQueue Q;
	InitQueue(Q);
	BiTree p;
	int flag = 1;	//�Ƿ�����������һ��ı�־���������һ����flag��0
	p = T;
	while (p || !QueueEmpty(Q)) {
		if (p) {
			if (p->lchild && p->rchild && 1 == flag) {	//���Һ��Ӷ�����
				EnQueue(Q, p->lchild);
				EnQueue(Q, p->rchild);
			} else if (p->lchild && !p->rchild && 1 == flag) {	//���Ӵ��ڣ��Һ��Ӳ�����,�������һ��
				flag = 0;
				EnQueue(Q, p->lchild);
			} else if (!p->lchild && p->rchild)	//���Ӳ����ڣ��Һ��Ӵ���,����
				return false;
			else if (!p->lchild && !p->rchild)	//���Һ��Ӷ�������
				flag = 0;
			else
				return false;

			if (!QueueEmpty(Q))
				DeQueue(Q, p);
			else
				return true;
		}
	}
	return true;
}

/**
 * ϰ��6.50������Ԫ�飨F, C, L/R������ʽ����һ�ö���������^AL ABL ^^L������AΪ������
 */
Status MyCreateTree(BiTree &T)
{
	char c;
	BiTree p, q;
	BiTree R[20];		//�����Ѿ������˵Ľ��
	int len = 0;		//��������ָ��
	c = getchar();
	while (' ' == c || '\t' == c || '\n' == c)	//���˿��ַ�
		c = getchar();
	if ('^' == c) {				//������
		c = getchar();
		if ('^' != c) {
			T = (BiTree)malloc(sizeof(BiTNode));
			if (!T)
				return ERROR;	//����ʧ��
			R[len++] = T;		//��������������
			T->data = c;
			T->lchild = NULL;
			T->rchild = NULL;
			c = getchar();
		} else {
			T = NULL;
			return OK;	//��������
		}
	} else				//�������
		return ERROR;

	while (1) {			//��������
		c = getchar();
		while (' ' == c || '\t' == c || '\n' == c)	//���˿��ַ�
			c = getchar();
		if ('^' == c)	//�������
			return OK;
		if (ERROR == SearchNode(R, len, c, p))		//�����������õ�ָ���ĸ����
			return ERROR;
		c = getchar();		//�õ���Ԫ��ڶ����ַ�
		q = (BiTree)malloc(sizeof(BiTNode));		//Ϊ�ӽ�����ռ�
		if (!q)
			return ERROR;	//����ʧ��
		R[len++] = q;		//����������������
		q->data = c;
		q->lchild = NULL;
		q->rchild = NULL;
		c = getchar();		//�õ���Ԫ��������ַ�
		if ('L' == c || 'l' == c)
			p->lchild = q;
		else if ('R' == c || 'r' == c)
			p->rchild = q;
		else			//�������
			return ERROR;
	}
}

/**
 * �ڳ���Ϊlen�Ľ������������Ԫ��ֵc�Ľ�㣬����p���أ�ȷ��û��Ԫ��ֵ��ͬ�Ľ��
 * �ҵ�����OK�����򷵻�ERROR
 */
Status SearchNode(BiTree R[], int len, char c, BiTree &p)
{
	int i;
	for (i=0; i<len; i++)
		if (c == R[i]->data) {
			p = R[i];
			return OK;
		}
	return ERROR;
}

/**
 * +������*��/���ȼ��ж�,��P53���еĲ�һ��
 */
char PrecedeTree(char c1, char c2)
{
	switch (c1) {
	case '+':
	case '-':
		switch (c2) {
		case '*':
		case '/':
			return '<';
		default:
			break;
		}
		break;
	case '*':
	case '/':
		switch (c2) {
		case '+':
		case '-':
			return '>';
		default:
			break;
		}
		break;
	default:
		break;
	}
	return ' ';
}

/**
 * ϰ��6.51������Զ����ʾ�������ʽ���������ʵ������ţ���α�P129ҳͼ6.9
 */
void OutputExpression(BiTree T)
{
	if (T) {
		if (isOpt(T->data)) {		//���ý���������ʱ
			if (T->lchild && '>' == PrecedeTree(T->data, T->lchild->data)) {	//�ж�������ȼ�
				printf("(");
				OutputExpression(T->lchild);
				printf(")");
			} else
				OutputExpression(T->lchild);
			printf("%c", T->data);
			if (T->rchild && '>' == PrecedeTree(T->data, T->rchild->data)) {
				printf("(");
				OutputExpression(T->rchild);
				printf(")");
			} else
				OutputExpression(T->rchild);
		} else {			//�ý��Ϊ�������ʱ��ֱ�Ӵ�ӡ����
			printf("%c", T->data);
		}
	}
}

/**
 * �ж�һ���ַ��Ƿ���+,-,*,/��������Ƿ���true,���򷵻�false
 */
bool isOpt(char c)
{
	if ('+' == c || '-' == c || '*' == c || '/' == c)
		return true;
	return false;
}