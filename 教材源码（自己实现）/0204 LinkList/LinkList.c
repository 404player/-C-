#include <stdio.h>
#include <stdlib.h>

Status InitList(LinkList *L) {  //L��ͷָ�룬ָ��ͷ��
    (*L) = (LinkList) malloc(sizeof(LNode));
    if((*L) == NULL)  exit(OVERFLOW);

    (*L) -> next = NULL;//��Ԫ���Ϊ��

    return OK;
}

