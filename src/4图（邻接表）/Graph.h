#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
#define MAX_GRAPH_NUM 10

typedef int status;
typedef int KeyType;
typedef enum {DG, DN, UDG, UDN} GraphKind;

// 顶点类型定义
typedef struct {
     KeyType key;
     char others[20];
} VertexType;

// 表结点类型定义（边/弧）
typedef struct ArcNode {
     int adjvex;              // 顶点位置编号
     struct ArcNode *nextarc; // 下一个表结点指针
} ArcNode;

// 头结点类型定义
typedef struct VNode {
     VertexType data;         // 顶点信息
     ArcNode *firstarc;       // 指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];

// 邻接表的类型定义（单图）
typedef struct {
    AdjList vertices;         // 头结点数组
    int vexnum, arcnum;       // 顶点数、弧数
    GraphKind kind;           // 图的类型
} ALGraph;

// 多图管理结构体
typedef struct {
    ALGraph graphs[MAX_GRAPH_NUM]; // 存储多个图
    char names[MAX_GRAPH_NUM][30]; // 存储每个图的名字
    int count;                     // 当前管理的图的数量
} GraphManager;

// ==================== 12种基本运算声明 ====================
status CreateGraph(ALGraph &G, VertexType V[], int v_num, KeyType VR[][2], int r_num); // (1)创建图
status DestroyGraph(ALGraph &G);                                                      // (2)销毁图
int LocateVex(ALGraph G, KeyType u);                                                  // (3)查找顶点
status PutVex(ALGraph &G, KeyType u, const char* value);                              // (4)顶点赋值
int FirstAdjVex(ALGraph G, int u);                                                    // (5)获得第一邻接点
int NextAdjVex(ALGraph G, int v, int w);                                              // (6)获得下一邻接点
status InsertVex(ALGraph &G, VertexType v);                                           // (7)插入顶点
status DeleteVex(ALGraph &G, KeyType v);                                              // (8)删除顶点
status InsertArc(ALGraph &G, KeyType v, KeyType w);                                   // (9)插入弧
status DeleteArc(ALGraph &G, KeyType v, KeyType w);                                   // (10)删除弧
void DFSTraverse(ALGraph G, void (*visit)(VertexType));                               // (11)深度优先遍历
void BFSTraverse(ALGraph G, void (*visit)(VertexType));                               // (12)广度优先遍历

// ==================== 附加功能声明 ====================
void VerticesSetLessThanK(ALGraph G, KeyType v, int k);                               // (1)距离小于k的顶点集
int ShortestPathLength(ALGraph G, KeyType v, KeyType w);                              // (2)顶点间最短路径长度
int ConnectedComponentsNums(ALGraph G);                                               // (3)图的连通分量个数
status SaveGraph(ALGraph G, const char FileName[]);                                   // (4)图的文件保存
status LoadGraph(ALGraph &G, const char FileName[]);                                   // (4)图的文件加载

// 辅助打印函数
void printVertex(VertexType v);
void DisplayGraph(ALGraph G);

#endif
