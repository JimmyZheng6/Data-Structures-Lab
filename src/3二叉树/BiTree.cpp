//
//  BiTree.cpp
//  3二叉树
//
//  Created by 郑耀涵 on 2026/5/21.
//
#include "BiTree.h"

/*================ 清空二叉树 ================*/

status ClearBiTree(BiTree &T)
{
    if(T==NULL)
        return OK;

    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);

    free(T);

    T=NULL;

    return OK;
}

/*================ 求深度 ================*/

int BiTreeDepth(BiTree T)
{
    if(T==NULL)
        return 0;

    int l=BiTreeDepth(T->lchild);
    int r=BiTreeDepth(T->rchild);

    return (l>r?l:r)+1;
}

/*================ 查找结点 ================*/

BiTNode* LocateNode(BiTree T,KeyType e)
{
    if(T==NULL)
        return NULL;

    if(T->data.key==e)
        return T;

    BiTNode *p=LocateNode(T->lchild,e);

    if(p!=NULL)
        return p;

    return LocateNode(T->rchild,e);
}

/*================ 赋值 ================*/

status Assign(BiTree &T,KeyType e,TElemType value)
{
    if(value.key!=e && LocateNode(T,value.key)!=NULL)
        return ERROR;

    BiTNode *p=LocateNode(T,e);

    if(p==NULL)
        return ERROR;

    p->data=value;

    return OK;
}

/*================ 获取兄弟 ================*/

BiTNode* GetSibling(BiTree T,KeyType e)
{
    if(T==NULL)
        return NULL;

    if(T->lchild && T->lchild->data.key==e)
        return T->rchild;

    if(T->rchild && T->rchild->data.key==e)
        return T->lchild;

    BiTNode *p=GetSibling(T->lchild,e);

    if(p!=NULL)
        return p;

    return GetSibling(T->rchild,e);
}

/*================ 插入结点 ================*/

status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
{
    if(LocateNode(T,c.key)!=NULL)
        return ERROR;

    BiTree s=(BiTree)malloc(sizeof(BiTNode));

    s->data=c;
    s->lchild=NULL;
    s->rchild=NULL;

    if(LR==-1)
    {
        s->rchild=T;
        T=s;
        return OK;
    }

    BiTree p=LocateNode(T,e);

    if(p==NULL)
    {
        free(s);
        return ERROR;
    }

    if(LR==0)
    {
        s->rchild=p->lchild;
        p->lchild=s;
    }
    else
    {
        s->rchild=p->rchild;
        p->rchild=s;
    }

    return OK;
}

/*================ 删除结点 ================*/

status DeleteNode(BiTree &T,KeyType e)
{
    if(T==NULL)
        return ERROR;

    if(T->data.key==e)
    {
        BiTree q;

        // 度为0
        if(T->lchild==NULL && T->rchild==NULL)
        {
            free(T);
            T=NULL;
        }

        // 只有右孩子
        else if(T->lchild==NULL)
        {
            q=T;
            T=T->rchild;
            free(q);
        }

        // 只有左孩子
        else if(T->rchild==NULL)
        {
            q=T;
            T=T->lchild;
            free(q);
        }

        // 度为2
        else
        {
            q=T;

            BiTree p=T->lchild;

            while(p->rchild!=NULL)
            {
                p=p->rchild;
            }

            p->rchild=T->rchild;

            T=T->lchild;

            free(q);
        }

        return OK;
    }

    if(DeleteNode(T->lchild,e)==OK)
        return OK;

    return DeleteNode(T->rchild,e);
}

/*================ 先序遍历 ================*/

status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(T==NULL)
        return OK;

    visit(T);

    PreOrderTraverse(T->lchild,visit);

    PreOrderTraverse(T->rchild,visit);

    return OK;
}

/*================ 中序遍历 ================*/

status InOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(T==NULL)
        return OK;

    InOrderTraverse(T->lchild,visit);

    visit(T);

    InOrderTraverse(T->rchild,visit);

    return OK;
}

/*================ 后序遍历 ================*/

status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(T==NULL)
        return OK;

    PostOrderTraverse(T->lchild,visit);

    PostOrderTraverse(T->rchild,visit);

    visit(T);

    return OK;
}

/*================ 层序遍历 ================*/

status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(T==NULL)
        return OK;

    BiTree queue[100];

    int front=0,rear=0;

    queue[rear++]=T;

    while(front<rear)
    {
        BiTree p=queue[front++];

        visit(p);

        if(p->lchild)
            queue[rear++]=p->lchild;

        if(p->rchild)
            queue[rear++]=p->rchild;
    }

    return OK;
}

/*================ 文件保存 ================*/

TElemType data[100];
int used[100];

void Save(BiTree T,FILE *fp,int index)
{
    if(T==NULL)
        return;

    fprintf(fp,"%d %d %s\n",
            index,
            T->data.key,
            T->data.others);

    Save(T->lchild,fp,index*2);

    Save(T->rchild,fp,index*2+1);
}

status SaveBiTree(BiTree T,const char FileName[])
{
    FILE *fp=fopen(FileName,"w");

    if(fp==NULL)
        return ERROR;

    Save(T,fp,1);

    fprintf(fp,"0 0 null\n");

    fclose(fp);

    return OK;
}

void Create(BiTree &T,int index)
{
    if(used[index]==0)
    {
        T=NULL;
        return;
    }

    T=(BiTree)malloc(sizeof(BiTNode));

    T->data=data[index];

    Create(T->lchild,index*2);

    Create(T->rchild,index*2+1);
}

status LoadBiTree(BiTree &T,const char FileName[])
{
    FILE *fp=fopen(FileName,"r");

    if(fp==NULL)
        return ERROR;

    for(int i=0;i<100;i++)
        used[i]=0;

    int index;

    TElemType x;

    while(fscanf(fp,"%d%d%s",
                 &index,
                 &x.key,
                 x.others)!=EOF)
    {
        if(index==0)
            break;

        data[index]=x;

        used[index]=1;
    }

    fclose(fp);

    Create(T,1);

    return OK;
}

void DestroyBiTree(BiTree &T){
    if(T==NULL) return;
    DestroyBiTree(T->lchild);
    DestroyBiTree(T->rchild);
    free(T);
    T=NULL;
}
/*================ 最大路径和 ================*/

int MaxPathSum(BiTree T)
{
    if(T==NULL)
        return 0;

    int l=MaxPathSum(T->lchild);
    int r=MaxPathSum(T->rchild);

    return T->data.key+(l>r?l:r);
}

/*================ 最近公共祖先 ================*/

BiTree LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2)
{
    if(T==NULL)
        return NULL;

    if(T->data.key==e1 || T->data.key==e2)
        return T;

    BiTree l=LowestCommonAncestor(T->lchild,e1,e2);
    BiTree r=LowestCommonAncestor(T->rchild,e1,e2);

    if(l && r)
        return T;

    return l?l:r;
}

/*================ 翻转二叉树 ================*/

void InvertTree(BiTree T)
{
    if(T==NULL)
        return;

    BiTree temp=T->lchild;

    T->lchild=T->rchild;

    T->rchild=temp;

    InvertTree(T->lchild);

    InvertTree(T->rchild);
}

bool BiTreeEmpty(BiTree T)
{
    return T == nullptr;
}

