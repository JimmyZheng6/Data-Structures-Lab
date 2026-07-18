//
//  linked_list.h
//  2链表线性表
//
//  Created by 郑耀涵 on 2026/5/14.
//
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义数据元素类型
typedef int ElemType;

// 定义单链表节点结构
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

// 12项基本运算[span_1](start_span)[span_1](end_span)
bool InitList(LinkList *L);
void DestroyList(LinkList *L);
void ClearList(LinkList L);
bool ListEmpty(LinkList L);
int ListLength(LinkList L);
bool GetElem(LinkList L, int i, ElemType *e);
int LocateElem(LinkList L, ElemType e, bool (*compare)(ElemType, ElemType));
bool PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e);
bool NextElem(LinkList L, ElemType cur_e, ElemType *next_e);
bool ListInsert(LinkList L, int i, ElemType e);
bool ListDelete(LinkList L, int i, ElemType *e);
void ListTraverse(LinkList L, void (*visit)(ElemType));

// 附加功能[span_2](start_span)[span_2](end_span)
void reverseList(LinkList L);
void RemoveNthFromEnd(LinkList L, int n);
void sortList(LinkList L);
bool SaveToFile(LinkList L, const char *filename);
bool LoadFromFile(LinkList L, const char *filename);

// 多线性表管理辅助[span_3](start_span)[span_3](end_span)
typedef struct {
    char name[30];
    LinkList list;
} ListManager;

// 辅助函数声明[span_4](start_span)[span_4](end_span)
bool compare_equal(ElemType a, ElemType b);
void print_elem(ElemType e);

#endif

