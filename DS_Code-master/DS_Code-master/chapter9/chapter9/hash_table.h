#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

/* ���Ŷ�ַ��ϣ��Ĵ洢�ṹ */

typedef struct {
	ElemType *elem;		//����Ԫ�ػ�ַ
	int count;		//��ǰ����Ԫ�ظ���
	int sizeindex;		//hashsize[sizeindex]Ϊ��ǰ����
}HashTable;

#define NULLKEY UINT_MAX	//��ϣ���λ��Ϊ�յı�־
#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1


Status SearchHash(HashTable &H, KeyType K, int &p, int &c);
int Hash(KeyType K, int p);
Status collision(int &p, int c, int len);
Status InsertHash(HashTable &H, ElemType e);
Status RecreateHashTable(HashTable &H);
Status InitHashTable(HashTable &H);
void DisplayHashTable(HashTable H);
Status CreateHashTable(HashTable &H, char *filename);

#endif