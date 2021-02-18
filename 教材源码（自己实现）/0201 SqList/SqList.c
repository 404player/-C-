/* =============================== **
**      线性表的顺序存储结构       **
**      实现各种操作函数           **
** ================================ */

#include "SqList.h"

/* ==================================== **
**               初始化                 **
**     成功返回OK，否则返回ERROR        **
** ==================================== */

Status InitList(SqList* L)
{
    (*L).elem = (ElemType*)malloc(ListInitSize * sizeof(ElemType)); //为顺序表分配大小为ListInsertSize的内存空间
    if(!(*L).elem) exit(OVERFLOW); //内存分配失败退出

    (*L).length = 0;     // 空表长度为0
    (*L).listsize = ListInitSize; // 内存容量为ListInsertSize

    return OK; // 初始化成功
}

/* ==================================== **
**               销毁                   **
**      释放顺序表所占的内存            **
** ==================================== */

Status DestroyList(SqList* L)
{
    if(L == NULL || (*L).elem == NULL ) return ERROR;//确定顺序表结构存在

    free((*L).elem);//释放顺序表内存
    (*L).elem = NULL;//释放后置空指针

    (*L).length = 0;
    (*L).listsize = 0;
    return OK;

}

/* ==================================== **
**              置空                    **
**      只重置为空表,不释放内存         **
** ==================================== */

Status ClearList(SqList* L)
{
    if(L = NULL || (*L).elem == NULL) return ERROR;

    (*L).length = 0;
    return OK;
}

/* ==================================== **
**               判空                   **
**        判断顺序表中是否含有数据      **
**        有返回True,没有返回ERROR      **
** ==================================== */

Status ListEmpty(SqList L)
{
    return L.length == 0 ? TRUE : FALSE;
}

/* ==================================== **
**               计数                   **
**      返回L中数据元素个数             **
** ==================================== */

int ListLength(SqList L)
{
    return L.length;
}

/* ==================================== **
**               取值                   **
**     返回表中第i个元素，并赋给e       **
**          i的值从1开始算              **
** ==================================== */

int GetElem(SqList L, int i, ElemType* e)
{
    if(i < 1 || i > L.length) return ERROR;//判定i的合法性

    *e = L.elem[i - 1];//返回值并传到e

    return OK;
}

/* ============================================ **
**                    查找                      **
**   返回顺序表中与e符合compare关系的元素位序   **
**           若查找失败，则返回0                **
**       元素e是compare函数的第二个形参         **
** ============================================= */

int LocateElem(SqList L, ElemType e, Status(Compare)(ElemType,ElemType))
{
    int i; //用于计数
    ElemType* p;

    if(L.elem == NULL) return ERROR; //确认顺序表结构存在
    i = 1;
    p = L.elem; //p指向顺序表第一个元素存储位置

    while(i <= L.length && !Compare(*p++, e)) ++ i;

    if(i <= L.length) return i;
    else return ERROR;

}

/* ============================================ **
**                    寻找前驱                  **
**               获取元素cur_e的前驱            **
**       若存在，将值存储至pre_e,并返回OK       **
**             若不存在，返回ERROR              **
** ============================================= */

Status PriorElem(SqList L, ElemType cur_e, ElemType* pre_e)
{
    int i; //用于计数
    if(L.elem == NULL && L.length < 2 ) return ERROR;

    i = 0;
    while(i < L.length && L.elem[i] != cur_e) ++i;

    if(i == 0 || i >= L.length) return ERROR;
    *pre_e = L.elem[i - 1];

    return OK;
}

/* ============================================ **
**                    寻找后继                  **
**               获取元素cur_e的后继            **
**       若存在，将值存储至next_e,并返回OK      **
**              若不存在，返回ERROR             **
** ============================================= */

Status NextElem(SqList L, ElemType cur_e, ElemType* next_e)
{
    int i; //用于计数
    if(L.elem == NULL && L.length < 2) return ERROR;

    i = 0;
    while(i < L.length - 1 && L.elem[i] != cur_e) ++i;

    if(i >= L.length) return ERROR;
    *next_e = L.elem[i + 1];

    return OK;
}

