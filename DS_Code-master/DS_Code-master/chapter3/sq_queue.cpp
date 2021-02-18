/* ѭ�����еĻ��������� */

#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * ��ʼ��, ����һ���յ�ѭ������
 */
Status InitQueue(SqQueue &Q)
{
	Q.base = (QElemType *) malloc (MAXQSIZE*sizeof(QElemType));
	if (!Q.base)
		return ERROR;
	Q.front = 0;
	Q.rear = 0;
	return OK;
}

/**
 * ���ٶ���
 */
Status DestroyQueue(SqQueue &Q)
{
	free(Q.base);
	Q.base = NULL;
	return OK;
}

/**
 * ��ն���
 */
Status ClearQueue(SqQueue &Q)
{
	Q.front = Q.rear = 0;
	return OK;
}

/**
 * �ж��Ƿ�Ϊ��
 */
Status QueueEmpty(SqQueue &Q)
{
	if (Q.rear == Q.front)
		return TRUE;
	return FALSE;
}

/**
 * ���ض���QԪ�ظ���
 */
Status QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;  // ���յ���Ŀ���㷨�������������
}

/**
 * �õ���ͷԪ�أ���e����, ����Ϊ�շ���ERROR�����򷵻�OK
 */
Status GetHead(SqQueue Q, QElemType &e)
{
	if (Q.rear == Q.front)
		return ERROR;
	e = *(Q.base+Q.front);
	return OK;
}

/**
 * ����Ԫ��eΪQ���µĶ�βԪ�أ�������������ERROR�����򷵻�OK
 */
Status EnQueue(SqQueue &Q, QElemType e)
{
	if ((Q.rear+1)%MAXQSIZE == Q.front)   //������, ʹ������ʹ�㷨�����
		return ERROR;
	*(Q.base+Q.rear) = e;
	Q.rear = (Q.rear+1)%MAXQSIZE; 
	return OK;
}

/**
 * �����в��գ�����OK�����򷵻�ERROR��ɾ����ͷԪ�أ���e������ֵ��
 */
Status DeQueue(SqQueue &Q, QElemType &e)
{
	if (Q.front == Q.rear)
		return ERROR;
	e = *(Q.base+Q.front);
	Q.front = (Q.front+1)%MAXQSIZE;
}

/**
 * �Ӷ�ͷ����β����Q��ÿ��Ԫ�ص���visit(), visit()ʧ�������ʧ��
 */
Status QueueTraverse(SqQueue Q, Status (*visit)(QElemType &e))
{
	int p;
	p = Q.front;
	while (p != Q.rear) {
		if (!(*visit)(*(Q.base+p)))
			return ERROR;
		p = (p+1)%MAXQSIZE;
	}
	return OK;
}