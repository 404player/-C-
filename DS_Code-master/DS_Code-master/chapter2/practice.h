#ifndef _PRACTICE_H_
#define _PRACTICE_H_

/* ϰ��2.38 ������� */
typedef struct myLNode{
	ElemType data;
	struct myLNode * prior;
	struct myLNode * next;
	int freq;   // ����Ƶ��
}*myLink;

typedef struct {
	myLink head, tail;
	int len;
} myLinkList;

int compareList(struct Sqlist La, struct Sqlist Lb);
void invertList(struct LNode * &L);
void invertMergeList(struct LNode * &La, struct LNode * &Lb, struct LNode * &Lc);
Status initMyList(myLinkList &L);
void locate(myLinkList L, ElemType x);
#endif