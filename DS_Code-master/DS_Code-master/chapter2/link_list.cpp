//��������Ĺ��켰�㷨

#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"
#include "link_list.h"

void InitList_L(struct LNode * &L)
{
	//����һ���յ���������L
	L = (struct LNode *) malloc (sizeof(LNode));
	L->next = NULL;
}

void DestoryList_L(struct LNode * &L)
{
	//���ٱ�L
	free(L);
	L = NULL;
}

void ClearList_L(struct LNode * &L)
{
	//����L����Ϊ�ձ�
	L->next = NULL;
}

bool ListEmpty_L(struct LNode * &L)
{
	//�ж��Ƿ�Ϊ�ձ��Ƿ���true, ���򷵻�false
	if (NULL == L->next)
		return true;
	else
		return false;
}

int ListLength_L(struct LNode * &L)
{

	int len = 0; // ����
	struct LNode *p = L->next;  // pָ���һ�����
	while (NULL != p) {
		len++;
		p = p->next;
	}
	return len;
}

//�㷨2.8
Status GetElem_L(struct LNode * &L, int i, ElemType &e)
{
	//LΪ��ͷ���ĵ�����ͷָ��
	//����i��Ԫ�ش���ʱ����ֵ����e������OK�����򷵻�ERROR
	struct LNode *p = L->next;  // pָ���һ�����
	int j = 1;  // jΪ������
	while(p != NULL && j < i) {
		p = p->next;
		j++;
	}

	if(p == NULL || j > i)
		return ERROR;
	e = p->data;
	return OK;
} // GetElem_L

int LocateElem_L(struct LNode * &L, ElemType e, Status (*compare)(ElemType, ElemType))
{
	//���Ա�L�Ѵ��ڣ�compare()������Ԫ���ж�����
	//����L�е�һ����e�����ϵ��compare()������Ԫ�ص�λ��������������Ԫ�ز����ڣ�����0	//����L�е�һ�����������ϵ������Ԫ��

	struct LNode *p = L->next;  // pָ���һ�����
	int i = 0;  // λ��
	while (NULL != p) {
		i++;
		if (compare(e, p->data))
			return i;
		p = p->next;
	}
	return 0;
}

Status PriorElem_L(struct LNode * &L, ElemType cur_e, ElemType &pre_e)
{
	//Ҫ�����Ա�L����
	//��cur_e��L������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܣ�pre_e�޶���
	
	int i = 0;
	struct LNode *p = L->next;
	while (NULL != p) {
		i = LocateElem_L(L, cur_e, compare_equal_Sq);
		if (0 != i && 1 != i) {
			GetElem_L(L, i-1, pre_e);
			return OK;
		}
		p = p->next;
	}
	return ERROR;
}

Status NextElem_L(struct LNode * &L, ElemType cur_e, ElemType &next_e)
{
	//Ҫ�����Ա�L����
	//��cur_e��L������Ԫ�أ��Ҳ������һ��������next_e�������ĺ������������ʧ�ܣ�next_e�޶���
	
	int i = 0;
	struct LNode *p = L->next;
	while (NULL != p) {
		i = LocateElem_L(L, cur_e, compare_equal_Sq);
		if (i<ListLength_L(L)) {
			GetElem_L(L, i+1, next_e);
			return OK;
		}
		p = p->next;
	}
	return ERROR;
}

Status ListInsert_L(struct LNode * &L, int i, ElemType e)
{
	//Ҫ�����Ա���ڣ�1<=i<=ListLength_Sq(L)+1
	//�ڵ�i��λ��֮ǰ��������Ԫ��e
	struct LNode *p;
	struct LNode *newNode;
	int j;
	p = L;
	j = 0;
	while (NULL != p && j < i-1) {  // Ѱ�ҵ�i-1�����
		p = p->next;
		++j;
	}
	if (NULL == p || j > i-1)
		return ERROR;
	newNode = (struct LNode *)malloc(sizeof(LNode));  // �����½��
	newNode->data = e;
	newNode->next = p->next;
	p->next = newNode;
	return OK;
} //ListInsert_L

Status ListDelete_L(struct LNode * &L, int i, ElemType &e)
{
	//���Ա�����ҷǿգ�1<=i<=ListLength_Sq(L)
	//ɾ��L�ĵ�i��Ԫ�أ�����e������ֵ
	struct LNode *p;
	struct LNode *del_p;
	int j;
	p = L;
	j = 0;
	while (NULL != p->next && j < i-1) {  // Ѱ�ҵ�i�����
		p = p->next;
		++j;
	}
	if (NULL == p->next || j > i-1)
		return ERROR;
	del_p = p->next;   // del_pָ��ɾ���Ľ��
	p->next = del_p->next;
	e = del_p->data;
	free(del_p);
	del_p = NULL;
	return OK;
} // ListDelete_L

Status ListTraverse_L(struct LNode * &L, Status (*visit)(struct LNode * &))
{
	//Ҫ�����Ա����
	//���ζ�L��ÿ��Ԫ�ص��ú���visit(), һ��visit()ʧ�ܣ������ʧ�ܣ�����FALSE,���򷵻�TRUE

	struct LNode *p;
	p = L->next;   // pָ���һ�����L->next; 
	while (NULL != p) {
		if(ERROR == visit(p))
			return ERROR;
		p = p->next;
	}
	return OK;
}

Status visit_display_L(struct LNode * &L)
{
	printf("%d ", L->data);
	return OK;
}


//�㷨
//�㷨2.11
void CreateList_L(struct LNode * &L, int n)
{
	//��λ������n��Ԫ�ص�ֵ����������ͷ���ĵ�����
	int i;
	struct LNode *p;
	L= (struct LNode *) malloc (sizeof(LNode));
	L->next = NULL;
	for (i=n; i>0; i--) {
		p = (struct LNode *) malloc (sizeof(LNode));  // �����½��
		scanf("%d", &p->data);
		p->next = L->next;
		L->next = p;
	}
} // CreatList_L

//�㷨2.12
void MergeList_L(struct LNode * &La, struct LNode * &Lb, struct LNode * &Lc)
{
	//La, Lb�ǵݼ�����
	//�鲢��Lc��Ҳ���ǵݼ�����
	struct LNode * pa = La->next; // paָ��La�ĵ�һ�����
	struct LNode * pb = Lb->next; // pbָ��Lb�ĵ�һ�����
	struct LNode * pc = Lc = La;

	while (NULL != pa && NULL != pb) {
		if (pa->data <= pb->data) {
			pc->next = pa;
			pc = pc->next;
			pa = pa->next;
		} else {
			pc->next = pb;
			pc = pc->next;
			pb = pb->next;
		}
	}

	if (NULL == pa)
		pc->next = pb;
	else
		pc->next = pa;
	free(Lb);
	Lb = NULL;
}