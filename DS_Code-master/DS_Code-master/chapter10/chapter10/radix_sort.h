#ifndef _RADIX_SORT_H_
#define _RADIX_SORT_H_

#define MAX_NUM_OF_KEY 8	//�ؼ������������ֵ
#define RADIX 10		//�ؼ��ֻ���
#define MAX_SPACE 1000
typedef int KeysType;
typedef struct {
	KeysType keys[MAX_NUM_OF_KEY];
	int next;
}SLCell;

typedef struct {
	SLCell r[MAX_SPACE];	//��̬����Ŀ����ÿռ䣬r[0]Ϊͷ���
	int keynum;		//��¼�ĵ�ǰ�ؼ��ָ���
	int recnum;		//��̬����ĵ�ǰ����
}SLList;

typedef int ArrType[RADIX];	//ָ����������

void Distribute(SLCell r[], int i, ArrType &f, ArrType &e);
int ord(KeysType K);
void Collect(SLCell r[], int i, ArrType f, ArrType e);
int succ(ArrType f, int j);
void RadixSort(SLList &L);

#endif