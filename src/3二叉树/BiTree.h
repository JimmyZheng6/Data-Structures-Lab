//
//  BiTree.h
//  3二叉树
//
//  Created by 郑耀涵 on 2026/5/21.
//
#ifndef BITREE_H
#define BITREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int status;
typedef int KeyType;

typedef struct{
    KeyType key;
    char others[20];
}TElemType;

typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

/* 基本操作 */

status ClearBiTree(BiTree &T);

int BiTreeDepth(BiTree T);

BiTNode* LocateNode(BiTree T,KeyType e);

status Assign(BiTree &T,KeyType e,TElemType value);

BiTNode* GetSibling(BiTree T,KeyType e);

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);

status DeleteNode(BiTree &T,KeyType e);

status PreOrderTraverse(BiTree T,void (*visit)(BiTree));

status InOrderTraverse(BiTree T,void (*visit)(BiTree));

status PostOrderTraverse(BiTree T,void (*visit)(BiTree));

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));

status SaveBiTree(BiTree T,const char FileName[]);

status LoadBiTree(BiTree &T,const char FileName[]);

void DestroyBiTree(BiTree &T);

bool BiTreeEmpty(BiTree T);

/* 附加功能 */

int MaxPathSum(BiTree T);

BiTNode* LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2);

void InvertTree(BiTree T);

#define MAX_TREE_NUM 10

typedef struct
{
    char name[20];

    BiTree T;

}TreeNode;

#endif
