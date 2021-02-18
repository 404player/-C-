/* �鱾�ϵ������㷨ʵ�� */
#include <stdio.h>
#include <stdlib.h>

#include "type_def.h"
#include "sq_stack.h"
#include "aglorithm.h"

int count = 0;   //hanoi�����ƶ����ӵĴ���

/**
 * �㷨3.1, ����ת����10����ת8����
 */
void conversion()
{
	int n;
	SElemType e;
	SqStack S;
	InitStack(S);
	printf("Input: ");
	scanf("%d", &n);
	while (n) {
		Push(S, n%8);
		n /= 8;
	}
	printf("Output: ");
	while (!StackEmpty(S)) {
		Pop(S, e);
		printf("%d", e);
	}
	printf("\n");
}

/**
 * P.49ҳ��3.2.2 ����ƥ��ļ���, ƥ�䷵��OK����ƥ�䷵��ERROR
 */
Status chectBracket(char *expr)
{
	int i = 0;
	SqStack S;
	InitStack(S);
	SElemType e;
	while ('\0' != *(expr+i)) {
		switch (*(expr+i)) {
		case '(':
			Push(S, -1);
			break;
		case '[':
			Push(S, -2);
			break;
		case '{':
			Push(S, -3);
			break;
		case ')':
			if (OK == GetTop(S, e)) {		//ջ�ǿգ��õ�ջ��Ԫ��
				if (-1 == e)			//ջ��Ԫ���롮����ƥ��
					Pop(S, e);		// ɾ��ջ��Ԫ��
				else				// ��ƥ�䣬����ERROR
					return ERROR;
			} else 
				return ERROR;
			break;
		case ']':
			if (OK == GetTop(S, e)) { 
				if (-2 == e)
					Pop(S, e);
				else
					return ERROR;
			} else 
				return ERROR;
			break;
		case '}':
			if (OK == GetTop(S, e)) {
				if (-3 == e)
					Pop(S, e);
				else
					return ERROR;
			} else
				return ERROR;
			break;
		default:
			break;
		} //switch

		i++;
	} // while

	if (StackEmpty(S))
		return OK;
	else
		return ERROR;
}

/**
 * �㷨3.2���б༭����#: �˸�@: ��ո���, EOF: �˳�
 */
void LineEdit()
{
	char ch;	//�û�������ַ�
	int c;
	SqStack S;
	InitStack(S);
	ch = getchar();
	while (EOF != ch) {   //EOFΪȫ�Ľ�����, windows ��Ϊctrl+Z
		while (EOF != ch && '\n' != ch) {
			switch (ch) {
			case '#': 
				Pop(S, c);
				break;
			case '@':
				ClearStack(S);
				break;
			default:
				Push(S, ch);
				break;
			}
			ch = getchar();	
		}
		StackTraverse(S, display_char);
		printf("\n");
		ClearStack(S);
		if (EOF != ch)
			ch = getchar();
	} //while
}
Status display_char(SElemType e)
{
	printf("%c", e);
	return OK;
}

/**
 * �㷨3.3 ��chapter3_Maze����
 */


/**
 * +������*��/���ȼ��жϣ����P53
 */
char Precede(char c1, char c2)
{
	switch (c1) {
	case '+':
	case '-':
		switch (c2) {
		case '+':
		case '-':
		case ')':
		case '#':
			return '>';
			break;
		case '*':
		case '/':
		case '(':
			return '<';
			break;
		default:
			break;
		}
		break;
	case '*':
	case '/':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case ')':
		case '#':
			return '>';
			break;
		case '(':
			return '<';
			break;
		default:
			break;
		}
		break;
	case '(':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
			return '<';
			break;
		case ')':
			return '=';
			break;
		default:
			break;
		}
		break;
	case ')':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case ')':
		case '#':
			return '>';
			break;
		default:
			break;
		}
		break;
	case '#':
		switch (c2) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
			return '<';
			break;
		case '#':
			return '=';
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

/**
 * �ж��ַ�c�Ƿ�Ϊ���������Ƿ���true,���Ƿ���false
 */
bool In(char c)
{
	if ('+' == c || '-' == c || '/' == c || '*' == c 
		|| '(' == c || ')' == c || '#' == c)
		return true;
	return false;
}

/**
 * ����
 */
int Operate(int a, char theta, int b)
{
	switch (theta) {
	case '+':
		return a+b;
		break;
	case '-':
		return a-b;
		break;
	case '*':
		return a*b;
		break;
	case '/':
		return a/b;
		break;
	default:
		break;
	}
	return ERROR;
}

/**
 * �㷨3.4���������ʽ��ֵ
 */
int EvaluateExpression()
{
	SqStack OPTR, OPND;
	InitStack(OPTR);
	Push(OPTR, '#');
	InitStack(OPND);
	int c, x;
	int theta;
	int a, b;
	c = getchar();
	while ('#' != c || GetTop(OPTR) != '#') {
		if (!In(c)) {     // c���ǲ�����
			c = c - '0';
			Push(OPND, c);
			c = getchar();
		} else {
			switch (Precede(GetTop(OPTR), c)) {
			case '<':   //ջ��Ԫ�����ȼ���
				Push(OPTR, c);
				c = getchar();
				break;
			case '=':   // ������
				Pop(OPTR, x);
				c = getchar();
				break;
			case '>':    //ջ��Ԫ�����ȼ��ߣ�Ҫ���㣬��ջ������������ջ
				Pop(OPTR, theta);
				Pop(OPND, b);
				Pop(OPND, a);
				Push(OPND, Operate(a, theta, b));
				break;
			default:
				break;
			}
		} //else
	} //while
	return GetTop(OPND);       
}

/**
 * �ƶ�����, �����Ϊn�����Ӵ�x�ƶ���y
 */
void move(int &count, char x, int n, char y)
{
	count++;
	printf("%d. Move %d from %c to %c.\n", count, n, x, y);
}

/**
 * �㷨��3.5������Ŵ�1��n�����Ӵ�x�ƶ���z
 */
void hanoi(int n, char x, char y, char z)
{
	if (1 == n)
		move(count, x, 1, z);
	else {
		hanoi(n-1, x, z, y);
		move(count, x, n, z);
		hanoi(n-1, y, x, z);
	}
}