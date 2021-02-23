/* =================================== **
**    线性表的链式存储结构（链表）     **
** ==================================== */

#ifndef LINKLIST_H
#define LINKLIST_H


#include <stdio.h>
#include <stdlib.h> //提供 malloc, realloc, free, exit 原型
#include <string> //提供strstr原型
#include "Status.h"

/* 定义数据元素类型 */
typedef int ElemType;

/* =================================== **
**             单链表结构              **
**          单链表存在头结点           **
** ==================================== */

typedef struct LNode
{
    ElemType data; //结点的数据域
    struct LNode* next; //结点的指针域，指向下一个结点
}LNode;

typedef LNode* LinkList; //指向单链表结点的指针


/* ==================================== **
**               初始化                 **
**     成功返回OK，否则返回ERROR        **
** ==================================== */

Status InitList(LinkList* L);


/* ==================================== **
**               销毁                   **
**        释放链表所占的内存            **
** ==================================== */

Status DestroyList(LinkList* L);

/* ==================================== **
**              置空                    **
**  需要释放链表中非头结点所占空间      **
** ==================================== */

Status ClearList(LinkList L);


/* ==================================== **
**               判空                   **
**        判断链表中是否包含有数据      **
**        有返回True,没有返回ERROR      **
** ==================================== */

Status ListEmpty(LinkList L);

/* ==================================== **
**               计数                   **
**      返回L中数据元素个数             **
** ==================================== */

int ListLength(LinkList L);

/* ==================================== **
**               取值                   **
**     返回表中第i个元素，并赋给e       **
**          i的值从1开始算              **
** ==================================== */

int GetElem(LinkList L, int i, ElemType* e);

/* ============================================ **
**                    查找                      **
**   返回链表中与e符合compare关系的元素位序     **
**           若查找失败，则返回0                **
**       元素e是compare函数的第二个形参         **
** ============================================= */

int LocateElem(LinkList L, ElemType e, Status(Compare)(ElemType,ElemType));

/* ============================================ **
**                    寻找前驱                  **
**               获取元素cur_e的前驱            **
**       若存在，将值存储至pre_e,并返回OK       **
**             若不存在，返回ERROR              **
** ============================================= */

Status PriorElem(LinkList L, ElemType cur_e, ElemType* pre_e);


/* ============================================ **
**                    寻找后继                  **
**               获取元素cur_e的后继            **
**       若存在，将值存储至next_e,并返回OK      **
**              若不存在，返回ERROR             **
** ============================================= */

Status NextElem(LinkList L, ElemType cur_e, ElemType* next_e);

/* ============================================ **
**                     插入元素                 **
**             向链表第i个元素插入元素e         **
**                 插入成功则返回OK             **
**                  否则返回ERROR               **
** ============================================= */

Status ListInsert(LinkList L, int i, ElemType e);


/* ============================================ **
**                     删除元素                 **
**             向链表第i个元素删除元素e         **
**    删除成功则返回OK，并将删除元素存储到e中   **
**                  否则返回ERROR               **
** ============================================= */

Status ListDelete(LinkList L, int i, ElemType* e);

/* ============================================ **
**                     遍历                     **
**          用Visit函数访问顺序表               **
** ============================================= */

void TraverseList(LinkList L, void(Visit)(ElemType));


/* ============================================ **
**              前插法创建单链表                **
**         每次插入链表的头部，头结点之后       **
**    从控制台读取数据，path为NULL 或是 空串    **
**    从文件中读取读取数据，path填写文件路径    **
** ============================================= */

void CreateList_H(LinkList *L, int n, char* path);

/* ============================================ **
**              尾插法创建单链表                **
**                **
**    从控制台读取数据，path为NULL 或是 空串    **
**    从文件中读取读取数据，path填写文件路径    **
** ============================================= */

#endif // LINKLIST_H
