//����Ĺ��켰�㷨

#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"
#include "link_list2.h"

Status MakeNode(Link &p, ElemType e)
{
	//������pָ���ֵΪe�Ľ�㣬������OK; ������ʧ�ܣ��򷵻�ERROR
	p = (Link) malloc (sizeof(LNode2));
	if (!p)   // ����ʧ��
		return ERROR;
	p->data = e;
	return OK;
} //MakeNode

void FreeNode(Link &p)
{
	//�ͷ�p��ָ���
	free(p);
	p = NULL;
} //FreeNode

Status InitList(LinkList &L)
{
	//����һ���յ���������L
	Link p;
	p = (Link) malloc (sizeof(LNode2)); //����ͷ���
	if(!p)
		return ERROR;
	p->next = NULL;  // ͷ������һ��Ԫ���ÿ�
	L.head = L.tail = p;
	L.len = 0;  //��ʼΪ0
	return OK;
}

Status ClearList(LinkList &L)
{
	//��L��Ϊ�ձ����ͷ�ԭ����Ľ��ռ�
	Link p, q;
	p = L.head->next;
	L.head->next = NULL;
	while (NULL != p) {   //��������Ԫ��
		q = p->next;
		free(p);
		p = q;
	}
	L.tail = L.head;
	L.len = 0;
	return OK;
}

Status DestroyList(LinkList &L)
{
	//�������Ա�L��L���ٴ���
	ClearList(L);     //�ͷų�ͷβ�������н��
	free(L.head);    // �ͷ�ͷβ���
	L.head = L.tail = NULL;
	L.len = 0;
	return OK;	
}

Status InsFirst(Link h, Link s)
{
	//��֪hָ������ͷ��㣬��s��ָ�������һ�����֮ǰ
	s->next = h->next;
	h->next = s;
	return OK;
}

Status DelFirst(Link h, Link &q)
{
	//��֪hָ������ͷ��㣬ɾ����һ����㲢��q���أ�����Ϊ�շ���ERROR
	if (NULL == h->next)   // ����Ϊ��
		return ERROR;
	q = h->next;
	h->next = q->next;
	q->next = NULL;
	return OK;
}

Status Append(LinkList &L, Link s)
{
	//��ָ��s��ָ��һ�����������L�����һ�����֮�󣬲��޸�βָ��
	int i = 1;  // ��������¼s���ӵĽ����
	L.tail->next = s;   //����
	while (NULL != s->next) {    //Ѱ��βָ��
		s = s->next;
		i++;
	}
	L.tail = s;		//�޸�βָ��
	L.len += i;
	return OK;
}

Status Remove(LinkList &L, Link &q)
{
	//ɾ��Lβ��㣬����q����
	Link p;
	p = L.head;
	if (L.head == L.tail) 
		return ERROR;
	q = L.tail;
	while (L.tail != p->next) {   // Ѱ��βָ��
		p = p->next;
	}
	p->next = NULL;    //ɾ��βָ����
	L.tail = p;      //�޸�βָ��
	L.len--;
	return OK;
}

Status InsBefore(LinkList &L, Link &p, Link s)
{
	// ��֪pָ����������L�е�һ����㣬��s��ָ��������p��ָ���֮ǰ��   
	// ���޸�ָ��pָ���²���Ľ��   
	Link h = L.head;
	while (p != h->next) {    //����ָ��p��ָ���
		h = h->next;
	}
	h->next = s;
	s->next = p;
	p = s;
	L.len++;
	return OK;
}

Status InsAfter(LinkList &L, Link &p, Link s)
{
	// ��֪pָ����������L�е�һ����㣬��s��ָ��������p��ָ���֮��   
	// ���޸�ָ��pָ���²���Ľ��   
	s->next = p->next;
	p->next = s;
	if (p == L.tail)
		L.tail = s;  //�޸�βָ��
	p = s;
	L.len++;
	return OK;
}

Status SetCurElem(Link &p, ElemType e)
{
	// ��֪pָ�����������е�һ����㣬��e����p��ָ���������Ԫ�ص�ֵ  
	p->data = e;
	return OK;
}

ElemType GetCurElem(Link p)
{
	//��֪pָ�����һ����㣬����p��ָ���������Ԫ�ص�ֵ
	return p->data;
}

Status ListEmpty(LinkList L)
{
	//LΪ�ձ���TRUE������FALSE
	if (NULL == L.head->next)
		return TRUE;
	else
		return FALSE;
}

int ListLength(LinkList L)
{
	//����L��Ԫ�ظ���
	return L.len;
}

Position GetHead(LinkList L)
{
	//����L��ͷ���λ��
	return L.head;
}

Position GetLast(LinkList L)
{
	//����L��β���λ��
	return L.tail;
}

Position PriorPos(LinkList L, Link p)
{
	// ��֪pָ����������L�е�һ����㣬����p��ָ����ֱ��ǰ����λ��   
	// ����ǰ�����򷵻�NULL
	Link pri = L.head;
	while (pri->next != p) {
		pri = pri->next;
	}
	if (L.head == pri)
		return NULL;  // û��ֱ��ǰ��
	return pri;
}

Position NextPos(LinkList L, Link p)
{	
	//���غ��λ�ã����򷵻�NULL
	if (L.tail == p)
		return NULL;
	return p->next;
}

Status LocatePos(LinkList L, int i, Link &p)
{
	// ����pָʾ��������L�е�i������λ�ã�������1��iֵ���Ϸ�ʱ����0   
	// i=0Ϊͷ���
	if (i<0 || i>L.len)
		return 0;
	p = L.head;
	while (0 != i) {
		i--;
		p = p->next;
	}
	return 1;
}

Position LocateElem(LinkList L, ElemType e,  
			 int (*compare)(ElemType, ElemType)) 
{
	// ������������L�е�1����e���㺯��compare()�ж���ϵ��Ԫ�ص�λ�ã�   
	// ��������������Ԫ�أ��򷵻�NULL
	int i;
	Link p;
	p = L.head->next;   // ָ���һ�����
	for (i=0; i<L.len; i++) {
		if (0 == (*compare)(e, p->data))
			return p;
		p = p->next;
	}
	return NULL;
}

Status ListTraverse(LinkList L,void (*visit)(Link))
{
	// ���ζ�L��ÿ������Ԫ�ص��ú���visit() 
	Link p = L.head->next;
	while (NULL != p) {  //��������Ԫ��
		visit(p);
		p = p->next;
	}
	return OK;
}


void visit_display(Link p)
{
	printf("%d ", p->data);
}

/**
 * �㷨2.20���ڴ�ͷ���ĵ������Ա�L�ĵ�i��Ԫ��֮ǰ����Ԫ��e
 */
Status ListInsert(LinkList &L, int i, ElemType e)
{
	Link h, s;
	if (!LocatePos(L, i-1, h))
		return ERROR;
	if (!MakeNode(s, e))
		return ERROR;
	if (h == L.tail) 
		L.tail = s;   // �޸�βָ��
	InsFirst(h, s);       //���ڴӵڲ�����㿪ʼ��������i-1�����������ͷ���
	L.len++;
	return OK;
}

/**
 * �㷨2.21
 */
Status MergeList(LinkList &La, LinkList &Lb, LinkList &Lc, 
				int (*compare)(ElemType, ElemType))
{
	Link ha, hb, pa, pb, q;
	ElemType a, b;
	if (!InitList(Lc))
		return ERROR;
	ha = GetHead(La);
	hb = GetHead(Lb);
	pa = NextPos(La, ha);
	pb = NextPos(Lb, hb);
	while (pa && pb) {
		a = GetCurElem(pa);
		b = GetCurElem(pb);
		if (compare(a, b) <= 0) {   // a<=b
			DelFirst(ha, q);
			Append(Lc, q);
			pa = NextPos(La, ha);
		} else {    // a>b
			DelFirst(hb, q);
			Append(Lc, q);
			pb = NextPos(Lb, hb);
		}   
	} // while
	if (pa)
		Append(Lc, pa);
	else
		Append(Lc, pb);
	FreeNode(ha);
	FreeNode(hb);
	return OK;
}

/**
 * �ȽϺ���
 */
int compare(ElemType e1, ElemType e2)
{
	if (e1 > e2)
		return 1;
	else if (e1 == e2)
		return 0;
	else 
		return -1;
}