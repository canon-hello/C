#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* status */
#define TRUE 1       //判定结果为正确
#define FALSE 0      //判定结果为错误
#define OK 1         //功能运行正常
#define ERROR 0      //功能出现错误无法运行
#define INFEASIBLE -1//操作对象不存在
#define OVERFLOW -2  //内存溢出

#define MAX_VERTEX_NUM 20

typedef int status;
typedef int KeyType;
typedef enum { DG, DN, UDG, UDN } GraphKind; //图类型:有向图,有向网,无向图,无向网

/* 顶点类型 */
typedef struct {
    KeyType key;        //关键字
    char others[20];    //内容
} VertexType;

/* 表结点类型 */
typedef struct ArcNode {
    int adjvex;                //顶点位置编号 
    struct ArcNode* nextarc;   //下一个表结点指针
} ArcNode;

/* 头结点及其数组类型 */
typedef struct VNode {
    VertexType data;    //顶点信息
    ArcNode* firstarc;  //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];

/* 邻接表类型 */
typedef  struct {
    AdjList vertices;    //头结点数组
    int vexnum, arcnum;  //顶点数、弧数
    GraphKind kind;      //图的类型
} ALGraph;

/* 图的管理表 */
typedef struct {
    struct {
        char name[30];  //图名称
        ALGraph G;
    }elem[10];
    int length;         //管理表长度（图数目）
    int listsize;       //管理表容量
}LISTS;

/* 循环队列元素类型 */
typedef int ElemType;

/* 循环队列容量 */
#define MAXLENGTH 100

/* 循环队列结构 */
typedef struct QUEUE {
    ElemType elem[MAXLENGTH];   //循环队列元素
    int front, length;          //循环队列定位用变量
} QUEUE;

