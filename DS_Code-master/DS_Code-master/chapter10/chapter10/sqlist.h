#ifndef _SqList_H_
#define _SqList_H_

//����˳���ṹ������㷨��������

#define OVERFLOW -1
#define LIST_INIT_SIZE 10  // ���Ա�洢�ռ��ʼ��������
#define LISTINCREMENT 10   //���Ա�洢�ռ��������
#define NOTEXIT 0

struct SqList{
	ElemType *elem;  //�洢�ռ��ַ
	int length;    // ��ǰ����
	int listsize;  //��ǰ����Ĵ洢����
};

Status InitList_Sq(struct SqList &L);
void DestoryList_Sq(struct SqList &L);
void ClearList_Sq(struct SqList &L);
Status ListEmpyt_Sq(struct SqList L);
Status ListLength_Sq(struct SqList L);
void GetElem_Sq(struct SqList L, int i, ElemType &e);
Status compare_equal_Sq(ElemType e1, ElemType e2);
Status LocateElem_Sq(struct SqList L, ElemType e, Status (*compare)(ElemType, ElemType));
Status PriorElem_Sq(struct SqList L, ElemType cur_e, ElemType &pre_e);
Status NextrElem_Sq(struct SqList L, ElemType cur_e, ElemType &next_e);
void ListInsert_Sq(struct SqList &L, int i, ElemType e);
void ListDelete_Sq_Sq(struct SqList &L, int i, ElemType &e);
Status ListTraverse_Sq(struct SqList L, Status (*visit)(ElemType));
Status visit_display_Sq(ElemType e);

void unionList_Sq(struct SqList &La, struct SqList Lb);
void MergeList_Sq(struct SqList La, struct SqList Lb, struct SqList &Lc);

#endif