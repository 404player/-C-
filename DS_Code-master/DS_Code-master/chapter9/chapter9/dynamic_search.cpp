#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "my_headers.h"

/**
 * �㷨9.5��a�����ڸ�ָ����ָ�Ķ����������еݹ�ز��ҹؼ��ֵ���key������Ԫ��,
 * ���ؿձ�ʾû���ҵ���pr���ؿգ����򷵻�ָ���ҵ��Ľ���ָ��, pr�����ҵ��Ľ��ĸ����.
 */
BiTNode* SearchBSTa(BiTree T, KeyType key, BiTree f, BiTree &pr)
{
	BiTNode *p;
	if (NULL == T) {					//���ҽ���, û���ҵ�
		pr = NULL;
		return NULL;
	} else if (EQ(key, T->data.key)) {			//���ҽ������ҵ�
		pr = f;
		return (T);
	} else if (LT(key, T->data.key)) {			//����������Ѱ��
		p = SearchBSTa(T->lchild, key, T, pr);
		return (p);
	} else {						//����������Ѱ��
		p = SearchBSTa(T->rchild, key, T, pr);
		return (p);
	}
}

/**
 * �㷨9.5��b��, ���㷨9.5��a���Ļ��������Ӳ���û���ҵ���Ԫ�صĹ���;
 * �����ҳɹ���p�����ҵ�������Ԫ�ؽ�㣬������true������ָ��pָ�����·���Ϸ��ʵ����
 * һ����㣬������false��ָ��fָ��T��˫�ף���ʼʱΪNULL
 */
bool SearchBSTb(BiTree T, KeyType key, BiTree f, BiTree &p)
{
	if (NULL == T) {			//��ʾû���ҵ�������ʧ��
		p = f;
		return false;
	} else if (EQ(key, T->data.key)) {	//���ҳɹ�
		p = T;
		return true;
	} else if (LT(key, T->data.key)) {	//������������
		return (SearchBSTb(T->lchild, key, T, p));
	} else {				//������������
		return (SearchBSTb(T->rchild, key, T, p));
	}
}

/**
 * �㷨9.6�����Ҳ����벻���ڵ�Ԫ�أ�������������T�в����ڹؼ��ֵ���e.key������Ԫ��ʱ��
 * ����e������true�����򷵻�false.
 */
bool InsertBST(BiTree &T, ElemType e)
{
	BiTree p;
	BiTNode *s;
	if (!SearchBSTb(T, e.key, NULL, p)) {		//���Ҳ��ɹ�
		s = (BiTNode *)malloc(sizeof(BiTNode));	//�½�һ��Ҫ����Ľ��
		s->data = e;
		s->lchild = NULL;
		s->rchild = NULL;
		if (NULL == p) {			//�²���Ľ��Ϊ�����
			T = s;
		} else if (LT(e.key, p->data.key)) {	//���뵽������
			p->lchild = s;
		} else {				//���뵽������
			p ->rchild = s;
		}
		return true;
	} else {
		return false;
	}
}

/**
 * �㷨9.7��������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ�㣬
 * ������true�����򷵻�false.
 */
bool DeleteNodeBST(BiTree &T, KeyType key)
{
	BiTree pr, p;
	pr = NULL;
	p = SearchBSTa(T, key, NULL, pr);
	if (NULL != p) {				//���ҳɹ�
		DeleteNode(T, p, pr);
		return true;
	} else {					//����ʧ��
		return false;
	}
}

/**
 * �㷨9.8���Ӷ���������T��ɾ�����p�����ؽ��������������, prָ��p�ĸ���㡣
 */
Status DeleteNode(BiTree &T, BiTree &p, BiTree pr)
{
	BiTree s;
	if (NULL == p->lchild && NULL == p->rchild) {		//������������
		if (pr != NULL) {				//p��㲻Ϊ�����ʱ
			if (pr->lchild == p) {
				pr->lchild = NULL;
			} else {
				pr->rchild = NULL;
			}
		}
		free(p);
		p = NULL;
	} else if (NULL != p->lchild && NULL == p->rchild) {	//���������գ���������
		if (pr != NULL) {
			if (pr->lchild == p) {
				pr->lchild = p->lchild;
			} else {
				pr->rchild = p->lchild;
			}
		} else {					//p���Ϊ�����ʱ
			T = p->lchild;
		}
		
		free(p);
		p = NULL;
	} else if (NULL == p->lchild && NULL != p->rchild) {	//�������գ�����������
		if (pr != NULL) {
			if (pr->lchild == p) {
				pr->lchild = p->rchild;
			} else {
				pr->rchild = p->rchild;
			}
		} else {
			T = p->rchild;
		}
		
		free(p);
		p = NULL;
	} else {				//��������������
		s = p->lchild;
		while (NULL != s->rchild) {		//s�ߵ����ұ߾���p�����������ֱ��ǰ����
			s = s->rchild;
		}

		s->rchild = p->rchild;		//����p����������
		if (pr != NULL) {
			if (pr->lchild == p) {
				pr->lchild = p->lchild;
			} else {
				pr->rchild = p->lchild;
			}
		} else {
			T = p->lchild;
		}
		
		free(p);
		p = NULL;
	}

	return OK;
}

/**
 * �㷨9.9������*pΪ���Ķ�����������������������֮��pָ���µ�������㣬
 * ����ת����֮ǰ���������ĸ���㡣
 */
void R_Rotate(BSTree &p)
{
	BSTree lc;
	lc = p->lchild;			//lcָ��p��������
	p->lchild = lc->rchild;		//lc������������p����������
	lc->rchild = p;			//p����lc����������
	p = lc;				//pָ���µĸ����
}

/**
 * �㷨9.10����������
 */
void L_Rotate(BSTree &p)
{
	BSTree rc;
	rc = p->rchild;
	p->rchild = rc->lchild;
	rc->lchild = p;
	p = rc;
}

/**
 * �㷨9.11����ƽ��Ķ���������T�в����ں�e����ͬ�ؼ��ֵĽ�㣬�����һ������Ԫ��Ϊe
 * �Ľ�㣬������1�����򷵻�0������˲����ʹ����������ʧȥƽ�⣬����ƽ����ת����, 
 * tallerָʾ��������Ƿ����ӡ��õݹ�ķ���Ѱ��Ҫ�����λ�ã������ƽ�����������Ӧ��
 * ��ת�ı仯������Ϊ��ת֮�����������ʵ�Ͳ���ǰ��û�б仯�ģ�
 * ���������ݹ��������ʵֻ����С��ƽ��������Ҫ����תƽ������������㶼��������ת������
 */
Status InsertAVL(BSTree &T, ElemType e, bool &taller)
{
	if (NULL == T) {	//������������e����������ӣ���tallerΪtrue
		T = (BSTree)malloc(sizeof(BSTNode));
		T->data = e;
		T->lchild = NULL;
		T->rchild = NULL;
		T->bf = EH;
		taller = true;
	} else {
		if (EQ(e.key, T->data.key)) {		//���д��ڸ�Ԫ�أ����ٲ���
			taller = false;
			return 0;
		} else if (LT(e.key, T->data.key)) {		//Ԫ��С�ڸ���㣬��Ӧ�ڸ�����������м���Ѱ��
			if (0 == InsertAVL(T->lchild, e, taller)) {	//���������и�Ԫ�أ���δ����
				return 0;
			} else {		//Ԫ�ز��뵽��������
				if (taller) {	//�Ѳ�������������������������ӣ����������ߵ��������Ҫ����
					switch (T->bf) {	//���T��ƽ���
					case LH:		//ԭ�����������������ߣ���Ҫ����ƽ�⴦��
						LeftBalance(T);
						taller = false;
						break;
					case EH:		//ԭ�����������ȸߣ���������������ʹ������
						T->bf = LH;
						taller = true;
						break;
					case RH:		//ԭ���������ߣ������������ȸߣ����߲�����
						T->bf = EH;
						taller = false;
						break;
					}
				}
			}
		} else {			//Ӧ��T���������н�������
			if (0 == InsertAVL(T->rchild, e, taller)) {	//δ����
				return 0;
			} else {
				if (taller) {		//�Ѳ��뵽������������������
					switch (T->bf) {	//���T��ƽ���
					case LH:
						T->bf = EH;
						taller = false;
						break;
					case EH:
						T->bf = RH;
						taller = true;
						break;
					case RH:	//������ƽ�⴦��
						RightBalance(T);
						taller = false;
						break;
					}
				}
			}
		}
	}

	return 1;
}

/**
 * �㷨9.12������ָ��T��ָ���Ϊ���Ķ���������ƽ�⴦�����㷨����ʱ��ָ��Tָ��
 * �µĸ���㣻
 * ��ƽ�������ָ��T������������������������֮�����2ʱ����Ҫ�����Ĳ�����
 */
void LeftBalance(BSTree &T)
{
	BSTree lc, rd;
	lc = T->lchild;		//lcָ��T�������������
	switch (lc->bf) {	//���T����������ƽ���
	case LH:		//�½�������T�����ӵ��������ϣ�Ҫ������������
		T->bf = lc->bf = EH;
		R_Rotate(T);
		break;
	case RH:		//�½�������T�����ӵ��������ϣ�Ҫ��˫������
		rd = lc->rchild;	//rdָ��T�����ӵ��������ĸ�
		switch (rd->bf) {	//�޸�T�������ӵ�ƽ������
		case LH:
			T->bf = RH;
			lc->bf = EH;
			break;
		case EH:
			T->bf = EH;
			lc->bf = EH;
			break;
		case RH:
			T->bf = EH;
			lc->bf = LH;
			break;
		}
		rd->bf = EH;
		L_Rotate(T->lchild);
		R_Rotate(T);
	}
	
}

/**
 * ����ָ��T��ָ���Ϊ���Ķ���������ƽ�⴦�����㷨����ʱ��ָ��Tָ���µĸ����
 */
void RightBalance(BSTree &T)
{
	BSTree rc, ld;
	rc = T->rchild;		//rcָ��T�������������
	switch (rc->bf) {	//���T����������ƽ���
	case RH:		//�½�������T���Һ��ӵ��������ϣ�Ҫ������������
		T->bf = rc->bf = EH;
		L_Rotate(T);
		break;
	case LH:		//�½�������T���Һ��ӵ��������ϣ�Ҫ��˫������
		ld = rc->lchild;	//ldָ��T���Һ��ӵ������������
		switch (ld->bf) {
		case LH:
			T->bf = EH;
			rc->bf = RH;
			break;
		case EH:
			T->bf = EH;
			rc->bf = EH;
			break;
		case RH:
			T->bf = LH;
			rc->bf = EH;
			break;
		}
		ld->bf = EH;
		R_Rotate(T->rchild);
		L_Rotate(T);
	}
}

/**
 * �㷨9.13����m��B-��T�ϲ��ҹؼ���K�����ؽ����pt, i, tag���������ҳɹ���
 * ������ֵtag = 1��ָ��pt��ָ����е�i���ؼ��ֵ���K����������ֵtag = 0��
 * ����K�Ĺؼ���Ӧ������ָ��pt��ָ����е�i�͵�i+1���ؼ���֮�䡣
 */
Result SearchBTree(BTree T, KeyType K)
{
	int i;
	Result r;
	BTree p, q;
	bool found;
	p = T;
	q = NULL;
	i = 0;
	found = false;
	while (p != NULL && !found) {
		i = Search(p, K);
		if (i > 0 && K == p->Key[i]) {	//�ҵ�����ؼ���
			found = true;
		} else {
			q = p;
			p = p->ptr[i];
		}
	}
	if (found) {	//���ҳɹ�
		r.pt = p;
		r.i = i;
		r.tag = 1;
	} else {	//���Ҳ��ɹ�������K�Ĳ���λ����Ϣ
		r.pt = q;
		r.i = i;
		r.tag = 0;	
	}
	return r;
}

/**
 * ��p->Key[1...keynum]�в���i��ʹp->Key[i] <= K < p->Key[i+1]����K < p->Key[1]ʱ��
 * i = 0, �����ҵ���i.
 */
int Search(BTree p, KeyType K)
{
	int i, j;
	if (K < p->Key[1]) {
		i = 0;
	} else if (K >= p->Key[p->keynum]) {
		i = p->keynum;	
	} else {
		for (j = 1; j <= (p->keynum) - 1; j++) {
			if (K >= p->Key[j] && K < p->Key[j + 1]) {
				i = j;
				break;
			}
		}
	}
	return i;
}

/**
 * �㷨9.14�����Ȳ���m��B�����Ƿ��йؼ���K�����򲻲��룬����0��������m��B-������ؼ���K
 * ������1�����������������˫�������б�Ҫ�Ľ����ѵ�����ʹT����m��B-����
 */
Status InsertBTree(BTree &T, KeyType K)
{
	int s;				// Ҫ���뵽������еĹؼ��ֵ�λ��
	KeyType x = K;
	BTree ap = NULL;		//���ѳ��Ľ��
	bool finished = false;		//�����Ƿ���ɱ�־
	Result res;
	BTree q;
	res = SearchBTree(T, K);
	int i;
	q = res.pt;
	i = res.i;
	if (1 == res.tag) {
		return 0;
	} else {
		while (q != NULL && !finished) {	//Ҫ����Ľ�㲻Ϊ���ҷ��ѻ�û�����
			Insert(q, i, x, ap);	//����ؼ���x��ָ��ap��q->Key[i+1], q->ptr[i+1]
			if (q->keynum < m) {		//����С���ʣ���������
				finished = true;
			} else {			//���ѽ��*q
				s = (int) ceil(m / 2.0);	//�м�ؼ���λ��
				split(q, s, ap);		//��sǰ�Ĺؼ��ֱ�����q�У�s����Ĺؼ��ַ��ѳ�ȥ���µĽ��ap��
				x = q->Key[s];
				q = q->parent;
				if (q != NULL) {
					i = Search(q, x);	//��˫�׽���в��Ҳ���x��λ��
				}
			}
		}

		if (!finished) {		//T�ǿ��������߸�����ѷ���
			NewRoot(T, q, x, ap);	//���ɺ���Ϣ(T, x, ap)���µĸ����*T��ԭT��apΪ����ָ��
		}
		return 1;
	}
}

/**
 * ���ؼ���x��ָ��ap�ֱ���뵽p->Key[i+1]��p->ptr[i+1]�У�ע����ؼ��ִ�С
 * p->keynumҪ��1.
 */
Status Insert(BTree p, int i, KeyType x, BTree ap)
{
	int j;
	for (j = p->keynum; j >= i + 1 ; j--) {
		p->Key[j + 1] = p->Key[j];
		p->ptr[j + 1] = p->ptr[j];		
	}
	p->Key[i + 1] = x;
	p->ptr[i + 1] = ap;
	p->keynum++;
	if (ap != NULL) {
		ap->parent = p;
	}
	return OK;
}

/**
 * ���ѽ��*p����sλ��Ϊ�ֽ���ѣ�ap->Key[] = p->Key[s+1...m], 
 * ap->ptr[] = p->ptr[s...m], p->Key[] = p->Key[1...s-1], 
 * p->ptr[] = p->ptr[0...s-1]��ע���޸��½����ap�ĸ���㡣
 */
Status split(BTree p, int s, BTree &ap)
{
	int i, j;
	p->keynum = s - 1;

	ap = (BTree)malloc(sizeof(BTNode));	//����һ���½��
	for (i = s + 1, j = 1; i <= m; i++, j++) {
		ap->Key[j] = p->Key[i];
	}
	for (i = s, j = 0; i <= m; i++, j++) {
		ap->ptr[j] = p->ptr[i];
		if (ap->ptr[j] != NULL) {		//���½��ĸ���㣬��һ������debug�˺þã�markһ��
			ap->ptr[j]->parent = ap;
		}
	}
	ap->keynum = m - s;
	ap->parent = p->parent;

	return OK;
}

/**
 * �����µĸ����, �������ϢΪKey[1] = x, ptr[0, 1] = (q, ap)
 */
Status NewRoot(BTree &T, BTree q, int x, BTree ap)
{
	BTree root;
	root = (BTree)malloc(sizeof(BTNode));
	root->Key[1] = x;
	root->ptr[0] = T;
	root->ptr[1] = ap;
	root->keynum = 1;
	root->parent = NULL;
	if (T != NULL) {
		T->parent = root;
	}
	if (ap != NULL) {
		ap->parent = root;
	}
	T = root;
	return OK;
}

/**
 * ���ļ�filename�е���Ϣ����B-��������B-����ֻ�йؼ�����Ϣ��
 */
Status CreateBTree(BTree &T, char *filename)
{
	FILE *pf;
	KeyType e;
	pf = fopen(filename, "r");
	if (NULL == pf) {
		printf("���ļ�%sʧ�ܣ�", filename);
		return ERROR;
	}
	while (EOF != fscanf(pf, "%d", &e)) {
		InsertBTree(T, e);
	}
	fclose(pf);
	return OK;
}

/**
 * ��ӡB-����������˳��
 */
Status DisplayBTree(BTree T)
{
	int i;
	
	if (T != NULL) {
		for (i = 0; i <= T->keynum; i++) {
			if (i < T->keynum) {
				DisplayBTree(T->ptr[i]);
				printf("%d ", T->Key[i+1]);
			} else {
				DisplayBTree(T->ptr[i]);
			}
		}
	}
	return OK;
}

/**
 * �㷨9.15���ڷǿ�˫����T�в��ҹؼ��ֵ���K�ļ�¼�������ڣ��򷵻ز��ҹ�����ָ�����һ��
 * ����ָ�룬���򷵻ؿ�ָ�롣
 */
DLTree SearchDLTree(DLTree T, KeysType K)
{
	DLTree p, q; 
	int i = 0;
	bool finished = false;
	p = T->first;
	while (p != NULL && i < K.num) {
		while (p != NULL && p->symbol != K.ch[i]) {	
			//���ҹؼ��ֵ�iλ
			p = p->next;
		}
		if (p != NULL && i < K.num - 1) {	//׼��������һλ
			p = p->first;
		}
		++i;
	}
	if (p != NULL) {	//�ж�Ҫ���ҵĹؼ����Ƿ������йؼ��ֵ����Ӽ�
		q = p->first;
		while (q->kind != LEAF) {
			q = q->next;
		}
		if (q != NULL) {
			finished = true;
		}
	}
	if (finished) {		//Ҫ���ҵĹؼ��ֲ������йؼ��ֵ����Ӽ�
		return p;
	} else {
		return NULL;
	}
}