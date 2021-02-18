#include <stdio.h>
#include <stdlib.h>

#include "my_headers.h"

/**
 * ϰ��3.19����aglorithm.cpp�е�Status chectBracket(char *expr)����ʵ����
 */

/**
 * ϰ��3.21����������ʽд���沨��ʽ
 */
void RPN(SqStack &S1, SqStack &S2)
{
	char c;
	int temp;
	InitStack(S1);		//�洢��ʱ�����
	InitStack(S2);		//�洢�沨��ʽ
	Push(S1, '#');
	c = getchar();
	while (c != '#' || !StackEmpty(S1)) {
		if (!In(c)) {		//������������ǲ�����
			Push(S2, c);
			c = getchar();	//������һ���ַ�
		} else {		//�������
			if ('(' == c) {
				Push(S1, c);
				c = getchar();	//������һ���ַ�
			} else if (')' == c) {
				while (GetTop(S1) != '(') {
					Pop(S1, temp);
					Push(S2, temp);
				}
				if (GetTop(S1) == '(')
					Pop(S1, temp);
				c = getchar();
			} else {
				switch (Precede(GetTop(S1), c)) {
				case '<':
					Push(S1, c);
					c = getchar();
					break;
				case '>':
					while ('>' == Precede(GetTop(S1), c)) {
						Pop(S1, temp);
						Push(S2, temp);
					}
					Push(S1, c);
					c = getchar();
					break;
				}
			}
		}
		if ('#' == c) {
			while ('#' != GetTop(S1)) {
				Pop(S1, temp);
				Push(S2, temp);
			}
			Pop(S1, temp);
		}
	
	}
}