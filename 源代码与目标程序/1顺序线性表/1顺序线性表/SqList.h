//
//  SqList.h
//  practice
//
//  Created by 郑耀涵 on 2026/4/30.
//
#ifndef __SQLIST_H__
#define __SQLIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

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

// 单个顺序表结构
typedef struct{
    ElemType * elem;
    int length;
    int listsize;
} SqList;

// ========== 新增：多表全局变量 ==========
#define MAX_TABLE_NUM 10    // 最多支持10个线性表
extern SqList g_TableList[MAX_TABLE_NUM];  // 所有线性表数组
extern int g_CurTableIdx;                  // 当前操作的表下标
extern int g_TableCount;                   // 已创建的表总数

// 原有基础功能（操作当前表）
status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList& L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L,int i,ElemType& e);
int LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType cur,ElemType& pre_e);
status NextElem(SqList L,ElemType cur,ElemType& next_e);
status ListInsert(SqList& L,int i,ElemType e);
status ListDelete(SqList& L,int i,ElemType& e);
status ListTrabverse(SqList L);

// 原有附加功能
int MaxSubArray(SqList L);
int SubArrayNum(SqList L, int k);
void sortList(SqList& L);
status SaveList(SqList L, const char FileName[]);
status LoadList(SqList& L, const char FileName[]);

// ========== 新增：多表管理函数 ==========
int CreateNewTable();                // 创建新表，返回下标
void SwitchTable(int idx);           // 切换当前表
void ShowTableInfo();                // 显示当前表信息、总表数

#endif
