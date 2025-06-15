#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

/* status */
#define TRUE 1       //�ж����Ϊ��ȷ
#define FALSE 0      //�ж����Ϊ����
#define OK 1         //������������
#define ERROR 0      //���ܳ��ִ����޷�����
#define INFEASIBLE -1//�������󲻴���
#define OVERFLOW -2  //�ڴ����

/* ����Ԫ������ */
typedef int status;  //״̬
typedef int KeyType; //�ؼ�������

/* ������������� */
typedef struct {
    KeyType key;     //�ؼ���
    char others[20]; //����
}TElemType;

/* ���������� */
typedef struct BiTNode {
    TElemType  data;                //������
    struct BiTNode* lchild, * rchild; //ָ����(�������Һ���)
}BiTNode, * BiTree;

/* ѭ������Ԫ������ */
typedef BiTNode* ElemType;

/* ѭ���������� */
#define MAXLENGTH 100

/* ѭ�����нṹ */
typedef struct QUEUE {
    ElemType elem[MAXLENGTH];   //ѭ������Ԫ��
    int front, length;          //ѭ�����ж�λ�ñ���
}QUEUE;

/* �������Ĺ���� */
typedef struct {
    struct {
        char name[30];  //����������
        BiTree T;
    }elem[10];
    int length;         //�������(����������)
    int listsize;       //���������
}LISTS;


static int flag_create = 0, k = 0;      //flag_create, k���ڴ��������ı��
static BiTNode* p = NULL;   //p��pt���ڲ����ֵܺͽ�㸳ֵʱ��ʱ������
static int flag1 = 0;        //flag1��flag3����ɾ�����ͽ�㸳ֵʱ���б��
