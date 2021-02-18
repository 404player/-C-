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

