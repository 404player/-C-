#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "my_headers.h"

/**
 * ��ʼ������
 */
Status InitArray(Array &A, int dim, ...)
{
	va_list ap;
	int i;
	int elemtotal = 1;	//���������Ԫ�ظ���
	if (dim < 1 || dim > MAX_ARRAY_DIM)
		return ERROR;
	A.dim = dim;
	A.bounds = (int *)malloc(dim*sizeof(int));
	if (!A.bounds)
		return ERROR;
	va_start(ap, dim);
	for (i=0; i<dim; i++) {
		A.bounds[i] = va_arg(ap, int);	//����һ���䳤����
		if (A.bounds[i] < 0)
			return ERROR;
		elemtotal *= A.bounds[0];
	}

	va_end(ap);
	A.base = (ElemType *)malloc(elemtotal*sizeof(ElemType));
	if (!A.base)
		return ERROR;
	//������ӳ����ci,������A.constants[i-1], i=1,...,dim
	A.constants = (int *)malloc(dim*sizeof(int));
	if (!A.constants)
		return ERROR;
	A.constants[dim-1] = 1;	//L=1��ָ���������Ԫ�صĴ�СΪ��λ
	for (i=dim-2; i>=0; i--)
		A.constants[i] = A.bounds[i+1] * A.constants[i+1];

	return OK;
}

/**
 * ��������A
 */
Status DestroyArray(Array &A)
{
	if (!A.base)
		return ERROR;
	free(A.base);
	A.base = NULL;
	if (!A.bounds)
		return ERROR;
	free(A.bounds);
	A.bounds = NULL;
	if (!A.constants)
		return ERROR;
	free(A.constants);
	A.constants = NULL;

	return OK;
}

/**
 * ��apָʾ�ĸ��±�ֵ�Ϸ����������Ԫ����A�е���Ե�ַoff
 */
Status Locate(Array A, va_list ap, int &off)
{
	int i, ind;
	off = 0;
	for (i=0; i<A.dim; i++) {
		ind = va_arg(ap, int);
		if (ind <0 || ind >= A.bounds[i])
			return ERROR;
		off += A.constants[i] * ind;
	}

	return OK;
}

/**
 * A��nά���飬eΪԪ�ر����������n���±�ֵ�����±겻Խ�磬ûe��ֵΪ��ָ����A��Ԫ��ֵ��������OK
 */
Status Value(Array A, ElemType &e, ...)
{
	int result;
	int off;
	va_list ap;
	va_start(ap, e);
	result = Locate(A, ap, off);
	if (ERROR == result)
		return ERROR;
	e = *(A.base+off);
	return OK;
}

/**
 * ��eֵ������ָ����A��Ԫ�أ�������OK
 */
Status Assign(Array &A, ElemType e, ...)
{
	int result, off;
	va_list ap;
	va_start(ap, e);
	result = Locate(A, ap, off);
	if (ERROR == result)
		return ERROR;
	*(A.base+off) = e;
	return OK;
}