#include <stdio.h>
#include <stdlib.h>

Status InitList(LinkList *L) {  //L是头指针，指向头结
    (*L) = (LinkList) malloc(sizeof(LNode));
    if((*L) == NULL)  exit(OVERFLOW);

    (*L) -> next = NULL;//首元结点为空

    return OK;
}

