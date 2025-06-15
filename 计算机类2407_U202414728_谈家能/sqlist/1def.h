#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define MAX_NAME_LENGTH 20

typedef struct {  //顺序表（顺序结构）的定义
    ElemType* elem;
    int length;
    int listsize;
    char name[MAX_NAME_LENGTH];
} SqList;

/*-----新增多线性表管理结构-----*/
#define MAX_LISTS 100
typedef struct {
    SqList lists[MAX_LISTS];
    int count;
    int current;
    // 当前操作的线性表索引
} MultiListManager;
