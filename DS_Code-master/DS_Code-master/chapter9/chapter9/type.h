#ifndef _TYPE_H_
#define _TYPE_H_

#define OK 0
#define ERROR -1
#define FILE_NOT_EXIT -2	
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE 100		//ջ��ʼ��ֵ
#define STACKINCREMENT 10		//ջ����ÿ�����ӵ�ֵ
#define DATA_SIZE 20			//�����������ݵĴ�С

typedef int Status;
typedef int KeyType;

typedef struct {
	KeyType key;			//�ؼ���
	char data[DATA_SIZE];		//��������
	float weigth;			//�����ݱ����ҵ�Ƶ�ʵ�Ȩֵ
}ElemType;

#define EQ(a, b) ((a) == (b))
#define LT(a, b) ((a) < (b))
#define LQ(a, b) ((a) <= (b))

#endif