//
//  linked_list.c
//  2链表线性表
//
//  Created by 郑耀涵 on 2026/5/14.
//
#include "linked_list.h"
#include <string.h>

// 1. 初始化表：构造一个带头节点的空链表[span_6](start_span)[span_6](end_span)
bool InitList(LinkList *L) {
    *L = (LinkList)malloc(sizeof(LNode));
    if (!(*L)) return false;
    (*L)->next = NULL;
    return true;
}

// 2. 销毁表[span_7](start_span)[span_7](end_span)
void DestroyList(LinkList *L) {
    ClearList(*L);
    free(*L);
    *L = NULL;
}

// 3. 清空表[span_8](start_span)[span_8](end_span)
void ClearList(LinkList L) {
    LNode *p = L->next, *q;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    L->next = NULL;
}

// 4. 判定空表[span_9](start_span)[span_9](end_span)
bool ListEmpty(LinkList L) {
    return (L->next == NULL);
}

// 5. 求表长[span_10](start_span)[span_10](end_span)
int ListLength(LinkList L) {
    int count = 0;
    LNode *p = L->next;
    while (p) {
        count++;
        p = p->next;
    }
    return count;
}

// 6. 获得元素[span_11](start_span)[span_11](end_span)
bool GetElem(LinkList L, int i, ElemType *e) {
    LNode *p = L->next;
    int j = 1;
    while (p && j < i) {
        p = p->next;
        j++;
    }
    if (!p || j > i) return false;
    *e = p->data;
    return true;
}

// 7. 查找元素位序[span_12](start_span)[span_12](end_span)
int LocateElem(LinkList L, ElemType e, bool (*compare)(ElemType, ElemType)) {
    int i = 1;
    LNode *p = L->next;
    while (p) {
        if (compare(p->data, e)) return i;
        p = p->next;
        i++;
    }
    return 0;
}

// 8. 获得前驱[span_13](start_span)[span_13](end_span)
bool PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e) {
    LNode *p = L->next;
    if (!p || p->data == cur_e) return false;
    while (p->next) {
        if (p->next->data == cur_e) {
            *pre_e = p->data;
            return true;
        }
        p = p->next;
    }
    return false;
}

// 9. 获得后继[span_14](start_span)[span_14](end_span)
bool NextElem(LinkList L, ElemType cur_e, ElemType *next_e) {
    LNode *p = L->next;
    while (p && p->next) {
        if (p->data == cur_e) {
            *next_e = p->next->data;
            return true;
        }
        p = p->next;
    }
    return false;
}

// 10. 插入元素[span_15](start_span)[span_15](end_span)
bool ListInsert(LinkList L, int i, ElemType e) {
    LNode *p = L;
    int j = 0;
    while (p && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!p || j > i - 1) return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

// 11. 删除元素[span_16](start_span)[span_16](end_span)
bool ListDelete(LinkList L, int i, ElemType *e) {
    LNode *p = L;
    int j = 0;
    while (p->next && j < i - 1) {
        p = p->next;
        j++;
    }
    if (!(p->next) || j > i - 1) return false;
    LNode *q = p->next;
    *e = q->data;
    p->next = q->next;
    free(q);
    return true;
}

// 12. 遍历表[span_17](start_span)[span_17](end_span)
void ListTraverse(LinkList L, void (*visit)(ElemType)) {
    LNode *p = L->next;
    while (p) {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
}

// 附加功能 (1): 链表翻转[span_18](start_span)[span_18](end_span)
void reverseList(LinkList L) {
    if (!L->next || !L->next->next) return;
    LNode *p = L->next, *q;
    L->next = NULL;
    while (p) {
        q = p->next;
        p->next = L->next;
        L->next = p;
        p = q;
    }
}

// 附加功能 (2): 删除倒数第n个节点[span_19](start_span)[span_19](end_span)
void RemoveNthFromEnd(LinkList L, int n) {
    if (n <= 0) return;
    LNode *fast = L, *slow = L;
    for (int i = 0; i < n; i++) {
        if (fast->next) fast = fast->next;
        else return;
    }
    while (fast->next) {
        fast = fast->next;
        slow = slow->next;
    }
    LNode *temp = slow->next;
    slow->next = temp->next;
    free(temp);
}

// 附加功能 (3): 链表排序[span_20](start_span)[span_20](end_span)
void sortList(LinkList L) {
    if (!L->next || !L->next->next) return;
    bool swapped;
    LNode *ptr1;
    LNode *lptr = NULL;
    do {
        swapped = false;
        ptr1 = L->next;
        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                ElemType temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// 附加功能 (4): 文件保存与加载[span_21](start_span)[span_21](end_span)
bool SaveToFile(LinkList L, const char *filename) {
    printf("文件保存到：%s\n",filename);
    
    FILE *fp = fopen(filename, "w");
    if (!fp) return false;
    LNode *p = L->next;
    while (p) {
        fprintf(fp, "%d ",p->data);
        p = p->next;
    }
    fclose(fp);
    return true;
}

bool LoadFromFile(LinkList L, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return false;
    ClearList(L);
    ElemType e;
    LNode *tail = L;
    while (fscanf(fp, "%d",&e)==1) {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = e;
        s->next = NULL;
        tail->next = s;
        tail = s;
    }
    fclose(fp);
    return true;
}

// 辅助函数[span_22](start_span)[span_22](end_span)
bool compare_equal(ElemType a, ElemType b) { return a == b; }
void print_elem(ElemType e) { printf("%d ", e); }

