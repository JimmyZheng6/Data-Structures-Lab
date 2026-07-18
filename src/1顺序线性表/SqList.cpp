//
//  SqList.cpp
//  practice
//
//  Created by 郑耀涵 on 2026/4/30.
//
#include "SqList.h"

// ========== 多表全局变量初始化 ==========
SqList g_TableList[MAX_TABLE_NUM];
int g_CurTableIdx = -1;   // -1表示暂无表
int g_TableCount = 0;

// 原有基础函数 完全不变
status InitList(SqList& L){
    L.elem = (ElemType *)malloc( LIST_INIT_SIZE * sizeof (ElemType));
    if(!L.elem) exit(OVERFLOW);
    L.length=0;
    L.listsize=LIST_INIT_SIZE;
    return OK;
}

status DestroyList(SqList& L)
{
    if(L.elem)
    {
        free(L.elem);
        L.elem = NULL;
        L.length = 0;
        L.listsize = 0;
        return OK;
    }
    return INFEASIBLE;
}

status ClearList(SqList& L)
{
    if(L.elem)
    {
        L.length = 0;
        return OK;
    }
    return INFEASIBLE;
}

status ListEmpty(SqList L)
{
    if(L.elem)
        return L.length == 0 ? TRUE : FALSE;
    return INFEASIBLE;
}

int ListLength(SqList L)
{
    if(L.elem)
        return L.length;
    return INFEASIBLE;
}

status GetElem(SqList L,int i,ElemType& e)
{
    if(!L.elem) return INFEASIBLE;
    if(i < 1 || i > L.length) return ERROR;
    e = L.elem[i-1];
    return OK;
}

int LocateElem(SqList L,ElemType e)
{
    if(!L.elem) return INFEASIBLE;
    for(int i=0; i<L.length; i++)
    {
        if(L.elem[i] == e)
            return i+1;
    }
    return 0;
}

status PriorElem(SqList L,ElemType cur,ElemType& pre_e)
{
    if(!L.elem) return INFEASIBLE;
    for(int i=1; i<L.length; i++)
    {
        if(L.elem[i] == cur)
        {
            pre_e = L.elem[i-1];
            return OK;
        }
    }
    return ERROR;
}

status NextElem(SqList L,ElemType cur,ElemType& next_e)
{
    if(!L.elem) return INFEASIBLE;
    for(int i=0; i<L.length-1; i++)
    {
        if(L.elem[i] == cur)
        {
            next_e = L.elem[i+1];
            return OK;
        }
    }
    return ERROR;
}

status ListInsert(SqList& L,int i,ElemType e)
{
    if(!L.elem) return INFEASIBLE;
    if(i < 1 || i > L.length + 1) return ERROR;
    if(L.length >= L.listsize)
    {
        ElemType* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!newbase) exit(OVERFLOW);
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    for(int j = L.length - 1; j >= i - 1; j--)
        L.elem[j+1] = L.elem[j];
    L.elem[i-1] = e;
    L.length++;
    return OK;
}

status ListDelete(SqList& L,int i,ElemType& e)
{
    if(!L.elem) return INFEASIBLE;
    if(i < 1 || i > L.length) return ERROR;
    e = L.elem[i-1];
    for(int j = i; j < L.length; j++)
        L.elem[j-1] = L.elem[j];
    L.length--;
    return OK;
}

status ListTrabverse(SqList L){
    int i;
    printf("\n-----------all elements -----------------------\n");
    for(i=0;i<L.length;i++) printf("%d ",L.elem[i]);
    printf("\n------------------ end ------------------------\n");
    return L.length;
}

// 原有附加函数 完全不变
int MaxSubArray(SqList L) {
    if (!L.elem || L.length == 0) return INFEASIBLE;
    int max_sum = L.elem[0], cur_sum = L.elem[0];
    for (int i = 1; i < L.length; i++) {
        cur_sum = (L.elem[i] > cur_sum + L.elem[i]) ? L.elem[i] : cur_sum + L.elem[i];
        max_sum = (max_sum > cur_sum) ? max_sum : cur_sum;
    }
    return max_sum;
}

int SubArrayNum(SqList L, int k) {
    if (!L.elem || L.length == 0) return INFEASIBLE;
    int count = 0;
    for (int i = 0; i < L.length; i++) {
        int sum = 0;
        for (int j = i; j < L.length; j++) {
            sum += L.elem[j];
            if (sum == k) count++;
        }
    }
    return count;
}

void sortList(SqList& L) {
    if (!L.elem) return;
    for (int i = 0; i < L.length - 1; i++) {
        for (int j = 0; j < L.length - 1 - i; j++) {
            if (L.elem[j] > L.elem[j + 1]) {
                ElemType temp = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = temp;
            }
        }
    }
}

status SaveList(SqList L, const char FileName[]) {
    if (!L.elem) return INFEASIBLE;
    FILE* fp = fopen(FileName, "w");
    if (!fp) return INFEASIBLE;
    fprintf(fp, "%d\n", L.length);
    for (int i = 0; i < L.length; i++) fprintf(fp, "%d ", L.elem[i]);
    fclose(fp);
    return OK;
}

status LoadList(SqList& L, const char FileName[]) {
    if (L.elem) DestroyList(L);
    FILE* fp = fopen(FileName, "r");
    if (!fp) return INFEASIBLE;
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem) { fclose(fp); return OVERFLOW; }
    L.listsize = LIST_INIT_SIZE;
    L.length = 0;
    int n; fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++) {
        ElemType e; fscanf(fp, "%d", &e);
        if (L.length >= L.listsize) {
            ElemType* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
            if (!newbase) { fclose(fp); return OVERFLOW; }
            L.elem = newbase;
            L.listsize += LISTINCREMENT;
        }
        L.elem[L.length++] = e;
    }
    fclose(fp);
    return OK;
}

// ========== 新增：多表管理函数实现 ==========
// 创建新表
int CreateNewTable()
{
    if(g_TableCount >= MAX_TABLE_NUM)
    {
        printf("已达到最大表数量！\n");
        return -1;
    }
    int idx = g_TableCount;
    if(InitList(g_TableList[idx]) == OK)
    {
        g_TableCount++;
        g_CurTableIdx = idx;  // 新建后自动切到新表
        return idx;
    }
    return -1;
}

// 切换当前表
void SwitchTable(int idx)
{
    if(idx < 0 || idx >= g_TableCount)
    {
        printf("表下标无效！\n");
        return;
    }
    g_CurTableIdx = idx;
    printf("已切换到第 %d 号线性表\n", idx+1);
}

// 显示当前表信息
void ShowTableInfo()
{
    printf("===== 线性表信息 =====\n");
    printf("当前操作表序号：%d / 总表数：%d\n", g_CurTableIdx+1, g_TableCount);
    if(g_CurTableIdx != -1)
    {
        printf("当前表元素个数：%d\n", g_TableList[g_CurTableIdx].length);
    }
    printf("======================\n");
}
