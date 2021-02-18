#ifndef	_GRAPH_H_
#define	_GRAPH_H_

#define MAX_VERTEX_NUM 20			//ͼ��󶥵����
typedef enum {DG, DN, UDG, UDN} GraphKind;	//����ͼ��������������ͼ��������
typedef char InfoType;				//�������Ϣ��ָ��
typedef char VertexType;			//��������

/* ͼ������(�ڽӾ���)�洢��ʾ */
#define INFINITY INT_MAX			//���ֵ
typedef int VRType;				//�����ϵ���ͣ�����Ȩͼ����0��1��ʾ���ڷ񣬶Դ�Ȩͼ����ʾȨֵ����
typedef struct ArcCell {
	VRType	adj;				//Ȩֵ
	InfoType *info;		
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct {
	VertexType vexs[MAX_VERTEX_NUM];	//��������
	AdjMatrix arcs;				//�ڽӾ���
	int vexnum, arcnum;			//ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind;				//ͼ�������־
}MGraph;

/* ͼ���ڽӱ�(Adjacency List)�洢��ʾ */
typedef struct ArcNode {
	int adjvex;				//�û���ָ��Ķ����λ��
	struct ArcNode *nextarc;		//ָ����һ������ָ��
	InfoType *info;				//�û������Ϣ��ָ��
}ArcNode;
typedef struct VNode {				//ͷ���
	VertexType data;			//������Ϣ
	ArcNode *firstarc;			//ָ�������ö���ĵ�һ������ָ��
}VNode, AdjList[MAX_VERTEX_NUM];
typedef struct {
	AdjList vertices;			//���ͷ��������
	int vexnum, arcnum;			//ͼ�Ķ������ͻ���
	GraphKind kind;				//ͼ������
}ALGraph;

/* ����ͼ��ʮ������(Orthogonal List)��ʾ */
typedef struct ArcBox {
	int tailvex, headvex;			//�û���β��ͷ�����λ��
	struct ArcBox *hlink, *tlink;		//�ֱ�Ϊ��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
	InfoType *info;				//�û��������Ϣָ��
}ArcBox;
typedef struct VexNode {			//ͷ���
	VertexType data;			//������Ϣ
	ArcBox *firstin, *firstout;		//�ֱ�ָ��ö���ĵ�һ���뻡�ͳ���
}VexNode;
typedef struct {
	VexNode xlist[MAX_VERTEX_NUM];		//��ͷ����
	int vexnum, arcnum;			//����ͼ�Ķ������ͻ���
}OLGraph;

/* ����ͼ���ڽӶ��ر�洢��ʾ��ʽ */
typedef enum {unvisited, visited} VisitIf;
typedef struct EBox {
	VisitIf mark;				//���ʱ��
	int ivex, jvex;				//�ñ����������������λ��
	struct EBox *ilink, *jlink;		//�ֱ�ָ�������������������һ����
	InfoType *info;				//�ñ���Ϣָ��
}EBox;
typedef struct VexBox {
	VertexType data;
	EBox *firstedge;			//ָ���һ�������ö���ı�
}VexBox;
typedef struct {
	VexBox adjmulist[MAX_VERTEX_NUM];	//����ͼ��������
	int vexnum, edgenum;			//����ͼ�ĵ�ǰ�������ͱ���
}AMLGraph;

/* �������� */
Status CreateUDN(MGraph &G);
Status CreateDN(MGraph &G);
int LocateVex(MGraph G, VertexType u);
int LocateVex(OLGraph G, VertexType u);
void Input(InfoType * &info);
Status CreateDG(OLGraph &G);
Status CreateDN(ALGraph &G);
Status CreateUDG(ALGraph &G);
Status CreateDG(ALGraph &G);
int FirstAdjVex(ALGraph G, int v);
int NextAdjVex(ALGraph G, int v, int w);
VertexType GetVex(ALGraph G, int v);
#endif