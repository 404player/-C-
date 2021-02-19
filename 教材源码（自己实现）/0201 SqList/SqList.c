/* =============================== **
**      ���Ա��˳��洢�ṹ       **
**      ʵ�ָ��ֲ�������           **
** ================================ */

#include "SqList.h"

/* ==================================== **
**               ��ʼ��                 **
**     �ɹ�����OK�����򷵻�ERROR        **
** ==================================== */

Status InitList(SqList* L)
{
    (*L).elem = (ElemType*)malloc(ListInitSize * sizeof(ElemType)); //Ϊ˳�������СΪListInsertSize���ڴ�ռ�
    if(!(*L).elem) exit(OVERFLOW); //�ڴ����ʧ���˳�

    (*L).length = 0;     // �ձ���Ϊ0
    (*L).listsize = ListInitSize; // �ڴ�����ΪListInsertSize

    return OK; // ��ʼ���ɹ�
}

/* ==================================== **
**               ����                   **
**      �ͷ�˳�����ռ���ڴ�            **
** ==================================== */

Status DestroyList(SqList* L)
{
    if(L == NULL || (*L).elem == NULL ) return ERROR;//ȷ��˳���ṹ����

    free((*L).elem);//�ͷ�˳����ڴ�
    (*L).elem = NULL;//�ͷź��ÿ�ָ��

    (*L).length = 0;
    (*L).listsize = 0;
    return OK;

}

/* ==================================== **
**              �ÿ�                    **
**      ֻ����Ϊ�ձ�,���ͷ��ڴ�         **
** ==================================== */

Status ClearList(SqList* L)
{
    if(L = NULL || (*L).elem == NULL) return ERROR;

    (*L).length = 0;
    return OK;
}

/* ==================================== **
**               �п�                   **
**        �ж�˳������Ƿ�������      **
**        �з���True,û�з���ERROR      **
** ==================================== */

Status ListEmpty(SqList L)
{
    return L.length == 0 ? TRUE : FALSE;
}

/* ==================================== **
**               ����                   **
**      ����L������Ԫ�ظ���             **
** ==================================== */

int ListLength(SqList L)
{
    return L.length;
}

/* ==================================== **
**               ȡֵ                   **
**     ���ر��е�i��Ԫ�أ�������e       **
**          i��ֵ��1��ʼ��              **
** ==================================== */

int GetElem(SqList L, int i, ElemType* e)
{
    if(i < 1 || i > L.length) return ERROR;//�ж�i�ĺϷ���

    *e = L.elem[i - 1];//����ֵ������e

    return OK;
}

/* ============================================ **
**                    ����                      **
**   ����˳�������e����compare��ϵ��Ԫ��λ��   **
**           ������ʧ�ܣ��򷵻�0                **
**       Ԫ��e��compare�����ĵڶ����β�         **
** ============================================= */

int LocateElem(SqList L, ElemType e, Status(Compare)(ElemType,ElemType))
{
    int i; //���ڼ���
    ElemType* p;

    if(L.elem == NULL) return ERROR; //ȷ��˳���ṹ����
    i = 1;
    p = L.elem; //pָ��˳����һ��Ԫ�ش洢λ��

    while(i <= L.length && !Compare(*p++, e)) ++ i;

    if(i <= L.length) return i;
    else return ERROR;

}

/* ============================================ **
**                    Ѱ��ǰ��                  **
**               ��ȡԪ��cur_e��ǰ��            **
**       �����ڣ���ֵ�洢��pre_e,������OK       **
**             �������ڣ�����ERROR              **
** ============================================= */

Status PriorElem(SqList L, ElemType cur_e, ElemType* pre_e)
{
    int i; //���ڼ���
    if(L.elem == NULL && L.length < 2 ) return ERROR;

    i = 0;
    while(i < L.length && L.elem[i] != cur_e) ++i;

    if(i == 0 || i >= L.length) return ERROR;
    *pre_e = L.elem[i - 1];

    return OK;
}

/* ============================================ **
**                    Ѱ�Һ��                  **
**               ��ȡԪ��cur_e�ĺ��            **
**       �����ڣ���ֵ�洢��next_e,������OK      **
**              �������ڣ�����ERROR             **
** ============================================= */

Status NextElem(SqList L, ElemType cur_e, ElemType* next_e)
{
    int i; //���ڼ���
    if(L.elem == NULL && L.length < 2) return ERROR;

    i = 0;
    while(i < L.length - 1 && L.elem[i] != cur_e) ++i;

    if(i >= L.length) return ERROR;
    *next_e = L.elem[i + 1];

    return OK;
}

/* ============================================ **
**                     ����Ԫ��                 **
**             ��˳����i��Ԫ�ز���Ԫ��e       **
**                 ����ɹ��򷵻�OK             **
**                  ���򷵻�ERROR               **
** ============================================= */

Status ListInsert(SqList* L, int i, ElemType e)
{
    ElemType* newbase;
    ElemType* p, * q;

    if(L == NULL || (*L).elem == NULL) return ERROR; //�ж�˳���ṹ�Ƿ����

    if(i < 1 || i > (*L).length + 1) return ERROR; //�ж�i�Ƿ�Ϸ�

    //���洢�ռ��������������пռ�����
    if((*L).length >= ListInitSize)
    {
        newbase = (ElemType*) realloc((*L).elem, ((*L).length + LISTINCREMENT) * sizeof(ElemType));
        if(newbase == NULL) exit(OVERFLOW);

        (*L).elem = newbase;
        (*L).listsize += LISTINCREMENT;

    }

    q = &(*L).elem[i - 1];

    for(p = &(*L).elem[(*L).length - 1]; p >= q; p --) *(p + 1) = *p;

    //����e
    *q = e;

    //˳����ȼ�1
    (*L).length ++;

    return OK;
}

/* ============================================ **
**                     ɾ��Ԫ��                 **
**             ��˳����i��Ԫ��ɾ��Ԫ��e       **
**    ɾ���ɹ��򷵻�OK������ɾ��Ԫ�ش洢��e��   **
**                  ���򷵻�ERROR               **
** ============================================= */

Status ListDelete(SqList* L, int i, ElemType* e)
{
    ElemType* p, * q;

    if(L == NULL || (*L).elem == NULL) return ERROR;//  ȷ��˳����Ƿ����

    if(i < 1 || i > (*L).length) return ERROR;

    p = &(*L).elem[i - 1]; //�ҵ�Ҫɾ����Ԫ��
    *e = *p; //��Ԫ�ش洢��e��

    q = (*L).elem + (*L).length - 1;

    for(++ p; p <= q; p ++) *(p -  1) = *p;

    (*L).length --;

    return OK;
}

Status ListDelete(SqList* L, int i, ElemType* e);

/* ============================================ **
**                     ����                     **
**          ��Visit��������˳���               **
** ============================================= */

void TraverseList(SqList L, void(Visit)(ElemType))
{
    for(int i = 0; i < L.length; i ++) Visit(L.elem[i]);
    printf("\n");
}
