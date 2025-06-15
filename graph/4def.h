#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* status */
#define TRUE 1       //�ж����Ϊ��ȷ
#define FALSE 0      //�ж����Ϊ����
#define OK 1         //������������
#define ERROR 0      //���ܳ��ִ����޷�����
#define INFEASIBLE -1//�������󲻴���
#define OVERFLOW -2  //�ڴ����

#define MAX_VERTEX_NUM 20

typedef int status;
typedef int KeyType;
typedef enum { DG, DN, UDG, UDN } GraphKind; //ͼ����:����ͼ,������,����ͼ,������

/* �������� */
typedef struct {
    KeyType key;        //�ؼ���
    char others[20];    //����
} VertexType;

/* �������� */
typedef struct ArcNode {
    int adjvex;                //����λ�ñ�� 
    struct ArcNode* nextarc;   //��һ������ָ��
} ArcNode;

/* ͷ��㼰���������� */
typedef struct VNode {
    VertexType data;    //������Ϣ
    ArcNode* firstarc;  //ָ���һ����
} VNode, AdjList[MAX_VERTEX_NUM];

/* �ڽӱ����� */
typedef  struct {
    AdjList vertices;    //ͷ�������
    int vexnum, arcnum;  //������������
    GraphKind kind;      //ͼ������
} ALGraph;

/* ͼ�Ĺ���� */
typedef struct {
    struct {
        char name[30];  //ͼ����
        ALGraph G;
    }elem[10];
    int length;         //������ȣ�ͼ��Ŀ��
    int listsize;       //���������
}LISTS;

/* ѭ������Ԫ������ */
typedef int ElemType;

/* ѭ���������� */
#define MAXLENGTH 100

/* ѭ�����нṹ */
typedef struct QUEUE {
    ElemType elem[MAXLENGTH];   //ѭ������Ԫ��
    int front, length;          //ѭ�����ж�λ�ñ���
} QUEUE;

