#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

/* status */
#define TRUE 1       //判定结果为正确
#define FALSE 0      //判定结果为错误
#define OK 1         //功能运行正常
#define ERROR 0      //功能出现错误无法运行
#define INFEASIBLE -1//操作对象不存在
#define OVERFLOW -2  //内存溢出

/* 数据元素类型 */
typedef int status;  //状态
typedef int KeyType; //关键字类型

/* 二叉树结点类型 */
typedef struct {
    KeyType key;     //关键字
    char others[20]; //内容
}TElemType;

/* 二叉链表结点 */
typedef struct BiTNode {
    TElemType  data;                //数据域
    struct BiTNode* lchild, * rchild; //指针域(左孩子与右孩子)
}BiTNode, * BiTree;

/* 循环队列元素类型 */
typedef BiTNode* ElemType;

/* 循环队列容量 */
#define MAXLENGTH 100

/* 循环队列结构 */
typedef struct QUEUE {
    ElemType elem[MAXLENGTH];   //循环队列元素
    int front, length;          //循环队列定位用变量
}QUEUE;

/* 二叉树的管理表 */
typedef struct {
    struct {
        char name[30];  //二叉树名称
        BiTree T;
    }elem[10];
    int length;         //管理表长度(二叉树棵数)
    int listsize;       //管理表容量
}LISTS;


static int flag_create = 0, k = 0;      //flag_create, k用于创建函数的标记
static BiTNode* p = NULL;   //p与pt用于查找兄弟和结点赋值时临时储存结点
static int flag1 = 0;        //flag1与flag3用于删除结点和结点赋值时进行标记
