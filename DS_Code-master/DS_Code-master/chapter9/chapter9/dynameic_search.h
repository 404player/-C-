/* ��̬���ұ� */

#ifndef _DYNAMIC_SEARCH_H_
#define _DYNAMIC_SEARCH_H_

/* AVLƽ���� */
typedef BiTree BSTree;			//����ƽ�������
typedef BiTNode BSTNode;		//ƽ����������
#define LH +1				//���
#define EH 0				//�ȸ�
#define RH -1				//�Ҹ�

/* B-�� */
#define m 3				// B-���Ľ�
#define RECORD_MAX_SIZE	100		//��¼���ַ������ֵ
typedef char Record[RECORD_MAX_SIZE];

typedef struct BTNode {			//����B-���Ľ��
	int keynum;			//����йؼ��ֵĸ���
	struct BTNode *parent;		//ָ��˫�׽��
	KeyType Key[m + 1];		//�ؼ���������0�ŵ�Ԫδ��
	struct BTNode *ptr[m + 1];	//����ָ��������0�ŵ�Ԫʹ��
	Record recptr[m + 1];		//��¼ָ��������0�ŵ�Ԫδ��
}BTNode, *BTree;

typedef struct {
	BTNode *pt;			//ָ���ҵ��Ľ��
	int i;				//1...m, �ڽ���еĹؼ������
	int tag;			//1�����ҳɹ���0������ʧ��
}Result;				//B-���Ĳ��ҽ������

/* ������˫�����洢��ʾ */
#define MAXKEYLEN 16			//�ؼ�����󳤶�
typedef struct {
	char ch[MAXKEYLEN];
	int num;			//�ؼ��ֳ���
}KeysType;				//�ؼ�������
typedef enum {LEAF, BRANCH} NodeKind;	//������ͣ�{Ҷ�ӣ���֧}
typedef struct DLTNode {
	char symbol;			//�ؼ����ַ�
	struct DLTNode *next;		//ָ����һ���ֵܽ��
	NodeKind kind;
	union {
		Record infoptr;		//Ҷ�ӽ��ļ�¼ָ��
		struct DLTNode *first;	//��֧���ĵ�һ�����ӽ��
	};
}DLTNode, *DLTree;

BiTNode* SearchBSTa(BiTree T, KeyType key, BiTree f, BiTree &pr);
bool SearchBSTb(BiTree T, KeyType key, BiTree f, BiTree &p);
bool InsertBST(BiTree &T, ElemType e);
bool DeleteNodeBST(BiTree &T, KeyType key);
Status DeleteNode(BiTree &T, BiTree &p, BiTree pr);
void R_Rotate(BSTree &p);
void L_Rotate(BSTree &p);
Status InsertAVL(BSTree &T, ElemType e, bool &taller);
void LeftBalance(BSTree &T);
void RightBalance(BSTree &T);
Result SearchBTree(BTree T, KeyType K);
int Search(BTree T, KeyType K);
Status InsertBTree(BTree &T, KeyType K);
Status Insert(BTree p, int i, KeyType x, BTree ap);
Status split(BTree p, int s, BTree &ap);
Status NewRoot(BTree &T, BTree q, int x, BTree ap);
Status CreateBTree(BTree &T, char *filename);
Status DisplayBTree(BTree T);
DLTree SearchDLTree(DLTree T, KeysType K);

#endif