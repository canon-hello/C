#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1     
#define FALSE 0   
#define OK 1      
#define ERROR 0    
#define INFEASIBLE -1
#define OVERFLOW -2 

typedef int status;
typedef int ElemType;

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;

typedef struct {
    struct {
        char name[30];
        LinkList L;
    }elem[10];
    int length;
    int listsize;
}LISTS;