/*==============================
 * ����
 *
 * �����㷨: 6.8��6.9��6.10��6.11
 ===============================*/

#ifndef MFSET_H
#define MFSET_H

#include <stdio.h>
#include <stdlib.h>     // �ṩ malloc��free ԭ��
#include <string.h>     // �ṩ memset��strcmp ԭ��
#include <math.h>       //
#include "Status.h"     //**��01 ����**//

/* �����������������ָʾ�Ӽ�������� */
#define MAX_TREE_SIZE 1024

/* ��Ԫ��ϵ������ */
#define MAX_PAIR_SIZE 100

/*
 * (˫��)���Ľ�㶨��
 *
 *��ע��
 * 1.���ս̲ĵ�ͼʾ��˫�����ڼ��ϵ�Ӧ���У���ģ���ѱ��򻯣���˫�׽�㲻�ٱ���������
 * 2.��������������ʾ������һ���Ӽ���������Ϊ�����Ӽ���һ��Ԫ�ش��ڡ�
 * 3.ȷ��ĳ���Ӽ�����S���ĸ�������Ӽ�ʱ����Ҫ����׷�ݵ������Ӽ��ĸ���
 * 4.ʵ��ʹ���У�ÿ���Ӽ�������ܶ�����Ԫ�أ���ʱ���Խ�ÿ������Ԫ�������������Ӽ�����������ϵ
 *   ����ÿ������Ԫ���뼯��S�и�����������������
 */
typedef struct PTNode {
    int parent;         // ˫��λ��������ָʾ�ý���������Ӽ�
} PTNode;

/*
 * (˫��)�����Ͷ���
 *
 *��ע��
 * 1.���н����nodes��"����"�洢��û�п�϶
 * 2.���Ӽ�����ʱ������r����Ϊ1����������r����Ϊ0
 * 3.��������⣬����������ΰ�����˳�Ÿ������������
 * 5.�������nodes�ռ����㹻��ģ��������������Ϊ��̬����洢
 */
typedef struct {
    PTNode nodes[MAX_TREE_SIZE];    // �洢���н��
    int r;  // ����λ��(����)����������ָʾ��һ���Ӽ���
    int n;  // ���Ľ��������������ָʾ����
} PTree;

/* �������Ͷ��� */
typedef PTree MFSet;

/* ������Ԫ��ϵ�� */
typedef struct {
    int i;
    int j;
} Pair;

/* �����ڵĵȼ۹�ϵ */
typedef struct {
    Pair pairs[MAX_PAIR_SIZE];  // �㹻��Ŀռ�洢��Ԫ��ϵ
    int n;                      // ��֪�ĵȼ۹�ϵ����
} Relation;


/*
 * ��ʼ��һ���ɶ���Ӽ���ÿ���Ӽ�ֻ����������Ա�����ɵļ���S��
 *
 *
 *����ע��
 *
 * �̲���Ĭ�ϴӿ���̨��ȡ���ݡ�
 * ����Ϊ�˷�����ԣ�����ÿ�����ж��ֶ��������ݣ�
 * �������ѡ���Ԥ����ļ�path�ж�ȡ�������ݡ�
 *
 * �����Ҫ�ӿ���̨��ȡ���ݣ���pathΪNULL����Ϊ�մ���
 * �����Ҫ���ļ��ж�ȡ���ݣ�����Ҫ��path����д�ļ�����Ϣ��
 */
Status initial_mfset(MFSet* S, char* path);

/*
 * ��ʼ�����ϵĶ�Ԫ�ȼ۹�ϵ
 */
Status initial_relation(Relation* R, char* path);

/*
 * ���������������� �㷨6.9 ����������������
 *
 * �����������ཻ���Ӽ�Si���Ӽ�Sj�Ĳ�����
 */
Status merge_mfset(MFSet* S, int i, int j);

/*
 * ���������������� �㷨6.8 ����������������
 *
 * �ڼ���S�в���Ԫ��i��ǰ�������Ӽ���
 */
int find_mfset(MFSet S, int i);

/*
 * ���������������� �㷨6.10 ����������������
 *
 * �����������ཻ���Ӽ�Si���Ӽ�Sj�Ĳ�����
 *
 * ���㷨�ǡ��㷨6.9���ĸĽ����Ľ�֮�����ڣ�
 * 1.�Ӽ������ľ���ֵΪ���Ӽ�Ԫ�ص�����
 * 2.��ֽ���ģС�ļ��Ϻϲ�����ģ��ļ�����
 */
Status mix_mfset(MFSet* S, int i, int j);

/*
 * ���������������� �㷨6.11 ����������������
 *
 * �ڼ���S�в���Ԫ��i��ǰ�������Ӽ���
 *
 * ���㷨�ǡ��㷨6.8���ĸĽ����Ľ�֮�����ڣ�
 * ������ɺ󣬻�����ĸ߶Ƚ���̯ƽ����������Ԫ��ֱ�ӹ��ص��Ӽ�������ϡ�
 *
 *��ע��
 * �ò�����Լ�����ɸĶ�
 */
int fix_mfset(MFSet* S, int i);

/*
 * ���ݵȼ۹�ϵR������/��������S�е�Ԫ��(�Ӽ�)��
 *
 *��ע��
 * �÷�����bix_relation����Ŀ��һ�£�
 * ���÷������õ��ǡ��㷨6.8���͡��㷨6.9����
 * ��δ�Ż��İ汾��
 */
Status build_mfset(MFSet* S, Relation R);

/*
 * ���ݵȼ۹�ϵR������/��������S�е�Ԫ��(�Ӽ�)��
 *
 *��ע��
 * �÷�����build_relation����Ŀ��һ�£�
 * ���÷������õ��ǡ��㷨6.10���͡��㷨6.11����
 * ���Ż���İ汾��
 */
Status bix_mfset(MFSet* S, Relation R);


/*�������������������������������������������� �����ڲ�ʹ�õĺ��� ��������������������������������������������*/

// �������ϵ��ڲ�����
static void mfset(MFSet* S, FILE* fp);

// �������ϵĶ�Ԫ��ϵ�ڲ�����
static void relation(Relation* R, FILE* fp);


/*�������������������������������������������� ͼ�λ���� ��������������������������������������������*/

// ��ͼ�λ���ʽ�����ǰ����
void PrintSet(MFSet S);

// ͼ�λ�����������нṹ�������ڲ�����ʹ��
static void PrintFramework(MFSet S);

#endif