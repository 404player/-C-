#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_headers.h"

/**
 * �㷨7.2, �������飨�ڽӾ��󣩱�ʾ��������������G
 */
Status CreateUDN(MGraph &G)
{
	int IncInfo;
	int i, j, k;
	VertexType v1, v2;
	VRType w;
	printf("���붥����������������Ϣ��־���ո�ָ���: ");	
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);	//IncInfoΪ1��ʾ���������Ϣ
	getchar();	//�������Ļ��з�
	printf("����%d������������", G.vexnum);
	for (i = 0; i < G.vexnum; i++) {		//���춥������
		scanf("%c", &G.vexs[i]);
		getchar();	//�������Ļ��з�
	}
	for (i = 0; i < G.vexnum; i++) {		//��ʼ���ڽӾ���
		for (j = 0; j < G.vexnum; j++) {
			G.arcs[i][j].adj = INFINITY;
			G.arcs[i][j].info = NULL;
		}
	}
	printf("����%d���ߣ�\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++) {		//�����ڽӾ���
		printf("�����%d���������Ķ��㼰Ȩֵ��", k+1);
		scanf("%c %c %d", &v1, &v2, &w);
		getchar();	//�������Ļ��з�
		i = LocateVex(G, v1);			//ȷ��v1,v2��G�е�λ��
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;			//��<v1, v2>��Ȩֵ
		if (IncInfo)				//������������Ϣ������
			Input(G.arcs[i][j].info);
		G.arcs[j][i] = G.arcs[i][j];		//��<v1, v2>�ĶԳƻ�<v2, v1>
	}
	return OK;
}

/**
 * �������飨�ڽӾ��󣩱�ʾ��������������G
 */
Status CreateDN(MGraph &G)
{
	int IncInfo;
	int i, j, k;
	VertexType v1, v2;
	VRType w;
	printf("���붥����������������Ϣ��־���ո�ָ���: ");	
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);	//IncInfoΪ1��ʾ���������Ϣ
	getchar();	//�������Ļ��з�
	printf("����%d������������", G.vexnum);
	for (i = 0; i < G.vexnum; i++) {		//���춥������
		scanf("%c", &G.vexs[i]);
		getchar();	//�������Ļ��з�
	}
	for (i = 0; i < G.vexnum; i++) {		//��ʼ���ڽӾ���
		for (j = 0; j < G.vexnum; j++) {
			G.arcs[i][j].adj = INFINITY;
			G.arcs[i][j].info = NULL;
		}
	}
	printf("����%d���ߣ�\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++) {		//�����ڽӾ���
		printf("�����%d���������Ķ��㼰Ȩֵ��", k+1);
		scanf("%c %c %d", &v1, &v2, &w);
		getchar();	//�������Ļ��з�
		i = LocateVex(G, v1);			//ȷ��v1,v2��G�е�λ��
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;			//��<v1, v2>��Ȩֵ
		if (IncInfo)				//������������Ϣ������
			Input(G.arcs[i][j].info);
	}
	return OK;
}

/**
 * ��G�ж���u���ڣ����ظö�����ͼ�е�λ�ã����򷵻�ERROR
 * ����G�Ķ��������в���u��λ��
 */
int LocateVex(MGraph G, VertexType u)
{
	int i;
	for (i = 0; i < G.vexnum; i++) {
		if (u == G.vexs[i])
			return i;
	}
	return ERROR;
}

int LocateVex(OLGraph G, VertexType u)
{
	int i;
	for (i = 0; i < G.vexnum; i++) {
		if (u == G.xlist[i].data)
			return i;
	}
	return ERROR;
}

int LocateVex(ALGraph G, VertexType u)
{
	int i;
	for (i = 0; i < G.vexnum; i++) {
		if (u == G.vertices[i].data)
			return i;
	}
	return ERROR;
}

/**
 * ���뻡�������Ϣ
 */
void Input(InfoType * &info)
{
	info = (InfoType *)malloc(50 * sizeof(InfoType));
	printf("���뻡����Ϣ��");
	gets(info);
}

/**
 * �㷨7.3������ʮ������洢��ʾ������ͼ
 */
Status CreateDG(OLGraph &G)
{
	int i, j, k, IncInfo;
	VertexType v1, v2;
	ArcBox *p;
	printf("��������ͼ�������ͻ��������Ƿ���Ϣ(0/1)��");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);
	getchar();					//ȥ����
	printf("����%d������(�ո�ָ�)��", G.vexnum);
	for (i = 0; i < G.vexnum; i++) {			//�����ͷ����
		scanf("%c", &G.xlist[i].data);
		G.xlist[i].firstin = NULL;
		G.xlist[i].firstout = NULL;
		getchar();
	}
	for (k = 0; k < G.arcnum; k++) {
		printf("����һ�����������յ㣺");
		scanf("%c %c", &v1, &v2);
		getchar();
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		p = (ArcBox *)malloc(sizeof(ArcBox));
		if (!p)
			return ERROR;
		(*p).headvex = j;
		(*p).tailvex = i;
		(*p).hlink = G.xlist[j].firstin;
		(*p).tlink = G.xlist[i].firstout;
		(*p).info = NULL;
		G.xlist[i].firstout = G.xlist[j].firstin = p;
		if (IncInfo)
			Input((*p).info);
	}
	return OK;
}

/**
 * �����ڽӱ�洢������ͼ
 */
Status CreateUDG(ALGraph &G)
{
	int i, j, k, IncInfo;
	ArcNode *p;
	VertexType v1, v2;
	G.kind = UDG;		//ͼ������Ϊ����ͼ
	printf("������ͼ�Ķ�����������������Ϣ��־��");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);
	getchar();
	printf("����%d�����㣺", G.vexnum);
	for (i = 0; i < G.vexnum; i++) {
		scanf("%c", &G.vertices[i].data);
		getchar();
		G.vertices[i].firstarc = NULL;
	}
	printf("����%d����\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++) {
		printf("�����%d������", k+1);
		scanf("%c %c", &v1, &v2);
		getchar();
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		p = (ArcNode *)malloc(sizeof(ArcNode));
		if (!p)
			return ERROR;
		p->nextarc = G.vertices[i].firstarc;
		p->adjvex = j;
		G.vertices[i].firstarc = p;
		p = (ArcNode *)malloc(sizeof(ArcNode));
		if (!p)
			return ERROR;
		p->nextarc = G.vertices[j].firstarc;
		p->adjvex = i;
		G.vertices[j].firstarc = p;
		if (IncInfo) {
			Input(p->info);
			G.vertices[i].firstarc->info = p->info;
		}
	}

	return OK;
}

/**
 * �����ڽӱ�洢������ͼ
 */
Status CreateDG(ALGraph &G)
{
	int i, j, k, IncInfo;
	ArcNode *p;
	VertexType v1, v2;
	G.kind = DG;		//ͼ������Ϊ����ͼ
	printf("����������ͼ�Ķ�����������������Ϣ��־��");
	scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);
	getchar();
	printf("����%d�����㣺", G.vexnum);
	for (i = 0; i < G.vexnum; i++) {
		scanf("%c", &G.vertices[i].data);
		getchar();
		G.vertices[i].firstarc = NULL;
	}
	printf("����%d����������\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++) {
		printf("�����%d������", k+1);
		scanf("%c %c", &v1, &v2);
		getchar();
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		p = (ArcNode *)malloc(sizeof(ArcNode));
		if (!p)
			return ERROR;
		p->nextarc = G.vertices[i].firstarc;
		p->adjvex = j;
		G.vertices[i].firstarc = p;
		if (IncInfo) {
			Input(p->info);
			G.vertices[i].firstarc->info = p->info;
		}
	}

	return OK;
}

/**
 * �����ڽӱ�洢��������������Ϣ��ΪȨֵ
 */
Status CreateDN(ALGraph &G)
{
	int i, j, k, IncInfo;
	ArcNode *p;
	char value[10];		//Ȩֵ��Ϣ
	VertexType v1, v2;
	G.kind = DG;		//ͼ������Ϊ����ͼ
	printf("�������������Ķ�������������");
	scanf("%d %d", &G.vexnum, &G.arcnum);
	getchar();
	printf("����%d�����㣺", G.vexnum);
	for (i = 0; i < G.vexnum; i++) {
		scanf("%c", &G.vertices[i].data);
		getchar();
		G.vertices[i].firstarc = NULL;
	}
	printf("����%d����������\n", G.arcnum);
	for (k = 0; k < G.arcnum; k++) {
		printf("�����%d������Ȩֵ(�ո�ָ�)��", k+1);
		scanf("%c %c %s", &v1, &v2, value);
		getchar();
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		p = (ArcNode *)malloc(sizeof(ArcNode));
		if (!p)
			return ERROR;
		p->nextarc = G.vertices[i].firstarc;
		p->adjvex = j;
		G.vertices[i].firstarc = p;
		G.vertices[i].firstarc->info = (char *)malloc(50 * sizeof(char));
		strcpy(G.vertices[i].firstarc->info, value);
	}

	return OK;
}


/**
 * �ڽӱ�洢��ʾ������ͼG���ڣ�v��G�еĶ���
 * ����ָ����v������ĵ�һ���ڽӶ����λ�ã���������G�в������ڽӶ��㣬����-1
 */
int FirstAdjVex(ALGraph G, int v)
{
	if (NULL != G.vertices[v].firstarc) {
		return G.vertices[v].firstarc->adjvex;
	} else {
		return -1;
	}
}

/**
 * �ڽӱ�洢��ʾ������ͼG���ڣ�v��G�еĶ��㣬 w��v���ڽӶ���
 * ����v����һ��(�����w)���ڽӶ����λ�ã���w�����һ�����򷵻�-1
 */
int NextAdjVex(ALGraph G, int v, int w)
{
	ArcNode *p;	//��ָ��
	p = G.vertices[v].firstarc;
	while (p) {					//����w��v���ڽӱ������е�λ��
		if (p->adjvex == w) {
			p = p->nextarc;
			if (NULL != p) {		//v����һ���������w���ڽӵ����
				return p->adjvex;
			} else {
				return -1;
			}
		} else {
			p = p->nextarc;
		}
	}
}
/**
 * �����ڽӱ��ʾ�ĵ�v��������Ϣ
 */
VertexType GetVex(ALGraph G, int v)
{
	return G.vertices[v].data;
}