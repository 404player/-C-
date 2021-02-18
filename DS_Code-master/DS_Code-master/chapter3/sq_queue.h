/* ѭ�����У����е�˳���ʾ��ʵ�� */

#ifndef _SQ_QUEUE_H_
#define _SQ_QUEUE_H_

#define MAXQSIZE 5

typedef struct {		//����ѭ������
	QElemType *base;	//��ʼ���Ķ�̬����洢�ռ�
	int front;		//ͷָ��
	int rear;		//βָ��
}SqQueue;

Status InitQueue(SqQueue &Q);
Status DestroyQueue(SqQueue &Q);
Status ClearQueue(SqQueue &Q);
Status QueueEmpty(SqQueue &Q);
Status QueueLength(SqQueue Q);
Status GetHead(SqQueue Q, QElemType &e);
Status EnQueue(SqQueue &Q, QElemType e);
Status DeQueue(SqQueue &Q, QElemType &e);
Status QueueTraverse(SqQueue Q, Status (*visit)(QElemType &e));




#endif