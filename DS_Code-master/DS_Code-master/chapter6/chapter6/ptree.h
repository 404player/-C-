/* ����˫�ױ�ʾ����P135*/

#ifndef _PTREE_H_
#define _PTREE_H_

#define MAX_TREE_SIZE 100
typedef struct PTNode {	//���ṹ
	TElemType data;
	int parent;	//˫��λ��
}PTNode;
typedef struct {	//���ṹ
	PTNode nodes[MAX_TREE_SIZE];	
	int r, n;	//����λ�úͽ����
}PTree;

#endif