/* �鱾�ϵ������㷨ʵ�� */
#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * �жϵ�ǰλ���ܲ���ͨ������ǰλ�ÿ�ͨ����ָ��λ��δ�������
 */
bool Pass(PosType curpos)
{
	if (1 == Map[curpos.row][curpos.col])
		return false;
	return true;
}

/**
 * ���߹��ĵط������㼣
 */
void FootPrint(PosType curpos)
{
	Map[curpos.row][curpos.col] = 1;
}

/**
 * ��һ��λ�ã�di��1��4��ʾ�Ӷ�����
 */
PosType NextPos(PosType pos, int di)
{
	PosType curpos;
	switch (di) {
	case 1:   //��, �м�1
		curpos.row = pos.row;
		curpos.col = pos.col+1;
		break;
	case 2:  //�ϣ��м�1
		curpos.row = pos.row+1;
		curpos.col = pos.col;
		break;
	case 3:  //�����м�1
		curpos.row = pos.row;
		curpos.col = pos.col-1;
		break;
	case 4:  //�����м�1
		curpos.row = pos.row-1;
		curpos.col = pos.col;
		break;
	}
	return curpos;
}

/**
 * �㷨3.3���Թ��㷨
 */
Status MazePath(PosType start, PosType end)
{
	PosType curpos;
	int curstep = 1; //̽����һ��
	curpos = start;		
	SElemType e;		//ͨ����
	do {
		if (Pass(curpos)) {   // �����ǰλ����ͨ��
			FootPrint(curpos);     //�����㼣
			e.ord = curstep;
			e.seat = curpos;
			e.di = 1;		
			Push (S, e);		// ����·��
			if (curpos.row == end.row && curpos.col == end.col)
				return (OK);	//�����յ�
			curpos = NextPos(curpos, 1);	//����ǰλ�õĶ�����Ϊ��һλ��
			curstep++;		//̽����һ��
		}  else {    //�����ǰλ�ò���ͨ��
			if (!StackEmpty(S)) {
				Pop(S, e);   
				while (4 == e.di && !StackEmpty(S))
					Pop(S, e);	//����λ�õ�4�����Ѿ�̽����ɣ������˻�һ��
				if (e.di < 4) {    //��һ������̽��
					e.di++;
					Push(S, e);
					curpos = NextPos(e.seat, e.di);
				}
			}
		}
	}while(!StackEmpty(S));

	return ERROR;
}

Status display_path(SElemType e)
{
	printf("(%d, %d) ", e.seat.row, e.seat.col);
	switch (e.di) {
	case 1:
		printf("��\n");
		break;
	case 2:
		printf("��\n");
		break;
	case 3:
		printf("��\n");
		break;
	case 4:
		printf("��\n");
		break;
	}
	return OK;
}