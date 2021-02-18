/* ����ϰ�� */

#include <stdio.h>
#include <stdlib.h>

#include "Sqlist.h"
#include "link_list.h"
#include "link_list2.h"
#include "polynomial.h"
#include "practice.h"

/* ϰ��2.12 */
int compareList(struct Sqlist La, struct Sqlist Lb)
{
	int i;
	ElemType * pa;
	ElemType * pb;
	pa = La.elem;   // ��La, Lb��ַ�����pa, pb
	pb = Lb.elem;
	i = 0;
	while (i<La.length && i<Lb.length) {
		if (*(pa+i) > *(pb+i)) 
			return 1;
		else if (*(pa+i) < *(pb+i))
			return -1;
		else
			i++;
	}

	if (i == La.length && i == Lb.length)
		return 0;
	if (i < Lb.length)
		return -1;
	if (i < La.length)
		return 1;
}

/**
 * ϰ��2.22, �Ե�����ʵ�־͵�����
 */
void invertList(struct LNode * &L)
{
	struct LNode *p;
	struct LNode *temp;
	p = L->next;    // pָ�������һ�����
	L->next = NULL;
	while (NULL != p) {   //�������н��, ��ÿ�������뵽L�ĵ�һ�����֮ǰ
		temp = p->next;
		p->next = L->next;
		L->next = p;
		p = temp;
	}
}

/**
 * ϰ��2.24, La��Lb�������鲢Lc�ݼ�
 */
void invertMergeList(struct LNode * &La, struct LNode * &Lb, struct LNode * &Lc)
{
	struct LNode *pa;
	struct LNode *pb;
	struct LNode *pc;
	struct LNode *temp;
	pa = La->next;
	pb = Lb->next;
	pc = Lc = La;
	pc->next = NULL;
	while (pa && pb) {
		if (pa->data <= pb->data) {     // ����pa��pc�ĵ�һ�����֮ǰ
			temp = pa->next;
			pa->next = pc->next;   
			pc->next = pa;
			pa = temp;
		} else {
			temp = pb->next;
			pb->next = pc->next;
			pc->next = pb;
			pb = temp;
		}
	} // while

	if (pa) {
		while (NULL != pa) {
			temp = pa->next;
			pa->next = pc->next;
			pc->next = pa;
			pa = temp;
		} // while
	}
	if (pb) {
		while (NULL != pb) {
			temp = pb->next;
			pb->next = pc->next;
			pc->next = pb;
			pb = temp;		
		} // while
	}
}

/**
 * ϰ��2.38
 */
Status initMyList(myLinkList &L)
{
	myLink p;
	p = (myLink) malloc (sizeof(myLNode));  //����ͷ���
	if (!p)
		return ERROR;
	p->next = NULL;
	L.head = p;
	L.tail = p;
	L.len = 0;
	return OK;
}

void locate(myLinkList L, ElemType x)
{
}