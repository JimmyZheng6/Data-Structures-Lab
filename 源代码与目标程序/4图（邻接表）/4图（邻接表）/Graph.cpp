#include "Graph.h"

// 打印顶点的辅助访问函数
void printVertex(VertexType v) {
    printf("[%d: %s] ", v.key, v.others);
}

// 打印整张邻接表的结构
void DisplayGraph(ALGraph G) {
    if (G.vexnum == 0) {
        printf("当前图为空！\n");
        return;
    }
    for (int i = 0; i < G.vexnum; i++) {
        printf("%d %s -> ", G.vertices[i].data.key, G.vertices[i].data.others);
        ArcNode *p = G.vertices[i].firstarc;
        while (p != NULL) {
            printf("%d ", p->adjvex);
            p = p->nextarc;
        }
        printf("\n");
    }
}

// (3)查找顶点位置位序
int LocateVex(ALGraph G, KeyType u) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].data.key == u) return i;
    }
    return -1;
}

// (1)创建图 (通过调用InsertVex和InsertArc构建)
status CreateGraph(ALGraph &G, VertexType V[], int v_num, KeyType VR[][2], int r_num) {
    G.kind = UDG;
    G.vexnum = 0;
    G.arcnum = 0;

    for (int i = 0; i < v_num; i++) {
        InsertVex(G, V[i]);
    }
    for (int i = 0; i < r_num; i++) {
        InsertArc(G, VR[i][0], VR[i][1]);
    }
    return OK;
}

// (2)销毁图
status DestroyGraph(ALGraph &G) {
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while (p) {
            ArcNode *q = p->nextarc;
            free(p);
            p = q;
        }
        G.vertices[i].firstarc = NULL;
    }
    G.vexnum = 0;
    G.arcnum = 0;
    return OK;
}

// (4)顶点赋值
status PutVex(ALGraph &G, KeyType u, const char* value) {
    int i = LocateVex(G, u);
    if (i == -1) return ERROR;
    strcpy(G.vertices[i].data.others, value);
    return OK;
}

// (5)获得第一邻接点位序
int FirstAdjVex(ALGraph G, int u) {
    if (u < 0 || u >= G.vexnum || !G.vertices[u].firstarc) return -1;
    return G.vertices[u].firstarc->adjvex;
}

// (6)获得下一邻接点位序
int NextAdjVex(ALGraph G, int v, int w) {
    if (v < 0 || v >= G.vexnum) return -1;
    ArcNode *p = G.vertices[v].firstarc;
    while (p && p->adjvex != w) {
        p = p->nextarc;
    }
    if (p && p->nextarc) return p->nextarc->adjvex;
    return -1;
}

// (7)插入顶点
status InsertVex(ALGraph &G, VertexType v) {
    if (G.vexnum >= MAX_VERTEX_NUM) return OVERFLOW;
    if (LocateVex(G, v.key) != -1) return ERROR; // 保持唯一性
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
}

// (8)删除顶点及关联的弧
status DeleteVex(ALGraph &G, KeyType v) {
    int id = LocateVex(G, v);
    if (id == -1) return ERROR;

    // 1. 删除所有以该节点为终点的边，并动态调整超出被删位序的 adjvex 值
    for (int i = 0; i < G.vexnum; i++) {
        if (i == id) continue;
        ArcNode *p = G.vertices[i].firstarc;
        ArcNode *pre = NULL;
        while (p) {
            if (p->adjvex == id) { // 找到关联边并摘除
                ArcNode *q = p->nextarc;
                if (!pre) G.vertices[i].firstarc = q;
                else pre->nextarc = q;
                free(p);
                p = q;
            } else {
                if (p->adjvex > id) p->adjvex--; // 后面节点前移后，物理下标要 -1
                pre = p;
                p = p->nextarc;
            }
        }
    }

    // 2. 释放该顶点自身的边链表
    ArcNode *p = G.vertices[id].firstarc;
    int local_arcs = 0;
    while (p) {
        ArcNode *q = p->nextarc;
        free(p);
        p = q;
        local_arcs++;
    }
    G.arcnum -= local_arcs; // 更新全局边数计数

    // 3. 顶点表前移覆盖
    for (int i = id; i < G.vexnum - 1; i++) {
        G.vertices[i] = G.vertices[i + 1];
    }
    G.vexnum--;
    return OK;
}

// (9)插入弧（首插法）
status InsertArc(ALGraph &G, KeyType v, KeyType w) {
    int i = LocateVex(G, v);
    int j = LocateVex(G, w);
    if (i == -1 || j == -1 || i == j) return ERROR;

    // 检查边是否已经存在
    ArcNode *check = G.vertices[i].firstarc;
    while (check) {
        if (check->adjvex == j) return ERROR;
        check = check->nextarc;
    }

    // 挂载 i -> j
    ArcNode *p1 = (ArcNode*)malloc(sizeof(ArcNode));
    if (!p1) return OVERFLOW;
    p1->adjvex = j;
    p1->nextarc = G.vertices[i].firstarc;
    G.vertices[i].firstarc = p1;

    // 挂载 j -> i
    ArcNode *p2 = (ArcNode*)malloc(sizeof(ArcNode));
    if (!p2) return OVERFLOW;
    p2->adjvex = i;
    p2->nextarc = G.vertices[j].firstarc;
    G.vertices[j].firstarc = p2;

    G.arcnum++;
    return OK;
}

// (10)删除弧
status DeleteArc(ALGraph &G, KeyType v, KeyType w) {
    int i = LocateVex(G, v);
    int j = LocateVex(G, w);
    if (i == -1 || j == -1) return ERROR;

    bool found1 = false, found2 = false;

    // 断开 i -> j
    ArcNode *p = G.vertices[i].firstarc;
    ArcNode *pre = NULL;
    while (p) {
        if (p->adjvex == j) {
            if (!pre) G.vertices[i].firstarc = p->nextarc;
            else pre->nextarc = p->nextarc;
            free(p);
            found1 = true;
            break;
        }
        pre = p;
        p = p->nextarc;
    }

    // 断开 j -> i
    p = G.vertices[j].firstarc;
    pre = NULL;
    while (p) {
        if (p->adjvex == i) {
            if (!pre) G.vertices[j].firstarc = p->nextarc;
            else pre->nextarc = p->nextarc;
            free(p);
            found2 = true;
            break;
        }
        pre = p;
        p = p->nextarc;
    }

    if (found1 && found2) {
        G.arcnum--;
        return OK;
    }
    return ERROR;
}

// DFS内部递归函数
static void DFS(ALGraph G, int v, bool visited[], void (*visit)(VertexType)) {
    visited[v] = true;
    visit(G.vertices[v].data);
    for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
        if (!visited[w]) DFS(G, w, visited, visit);
    }
}

// (11)深度优先搜索遍历
void DFSTraverse(ALGraph G, void (*visit)(VertexType)) {
    bool visited[MAX_VERTEX_NUM] = {false};
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) DFS(G, i, visited, visit);
    }
    printf("\n");
}

// (12)广度优先搜索遍历
void BFSTraverse(ALGraph G, void (*visit)(VertexType)) {
    bool visited[MAX_VERTEX_NUM] = {false};
    int queue[MAX_VERTEX_NUM];
    int front = 0, rear = 0;

    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            visited[i] = true;
            visit(G.vertices[i].data);
            queue[rear++] = i;

            while (front < rear) {
                int v = queue[front++];
                for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
                    if (!visited[w]) {
                        visited[w] = true;
                        visit(G.vertices[w].data);
                        queue[rear++] = w;
                    }
                }
            }
        }
    }
    printf("\n");
}

// 附加功能 (1): 距离小于 k 的顶点集合
void VerticesSetLessThanK(ALGraph G, KeyType v, int k) {
    int start = LocateVex(G, v);
    if (start == -1 || k <= 0) return;

    bool visited[MAX_VERTEX_NUM] = {false};
    int queue[MAX_VERTEX_NUM];
    int dist[MAX_VERTEX_NUM] = {0};
    int front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;
    dist[start] = 0;

    printf("与顶点 %d 距离小于 %d 的顶点集合为: ", v, k);
    while (front < rear) {
        int cur = queue[front++];
        if (dist[cur] > 0 && dist[cur] < k) {
            printf("%d(%s) ", G.vertices[cur].data.key, G.vertices[cur].data.others);
        }
        for (int w = FirstAdjVex(G, cur); w >= 0; w = NextAdjVex(G, cur, w)) {
            if (!visited[w]) {
                visited[w] = true;
                dist[w] = dist[cur] + 1;
                queue[rear++] = w;
            }
        }
    }
    printf("\n");
}

// 附加功能 (2): 最短路径长度
int ShortestPathLength(ALGraph G, KeyType v, KeyType w) {
    int start = LocateVex(G, v);
    int end = LocateVex(G, w);
    if (start == -1 || end == -1) return -1;
    if (start == end) return 0;

    bool visited[MAX_VERTEX_NUM] = {false};
    int queue[MAX_VERTEX_NUM];
    int dist[MAX_VERTEX_NUM] = {0};
    int front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    while (front < rear) {
        int cur = queue[front++];
        if (cur == end) return dist[cur];

        for (int next = FirstAdjVex(G, cur); next >= 0; next = NextAdjVex(G, cur, next)) {
            if (!visited[next]) {
                visited[next] = true;
                dist[next] = dist[cur] + 1;
                queue[rear++] = next;
            }
        }
    }
    return -1;
}

// 附加功能 (3): 连通分量个数
int ConnectedComponentsNums(ALGraph G) {
    bool visited[MAX_VERTEX_NUM] = {false};
    int count = 0;
    auto dummyVisit = [](VertexType) {};
    for (int i = 0; i < G.vexnum; i++) {
        if (!visited[i]) {
            count++;
            DFS(G, i, visited, dummyVisit);
        }
    }
    return count;
}

// 辅助递归：逆序导出边信息，消除首插法逆序效应
static void SaveArcReverse(FILE *fp, ArcNode *p, int src_key, ALGraph G) {
    if (p == NULL) return;
    SaveArcReverse(fp, p->nextarc, src_key, G);
    fprintf(fp, "%d %d\n", src_key, G.vertices[p->adjvex].data.key);
}

// 附加功能 (4): 图的文件保存
status SaveGraph(ALGraph G, const char FileName[]) {
    FILE *fp = fopen(FileName, "w");
    if (!fp) return ERROR;

    fprintf(fp, "%d %d\n", G.vexnum, G.arcnum);
    for (int i = 0; i < G.vexnum; i++) {
        fprintf(fp, "%d %s\n", G.vertices[i].data.key, G.vertices[i].data.others);
    }
    for (int i = 0; i < G.vexnum; i++) {
        SaveArcReverse(fp, G.vertices[i].firstarc, G.vertices[i].data.key, G);
    }
    fclose(fp);
    return OK;
}

// 附加功能 (4): 图的文件加载
status LoadGraph(ALGraph &G, const char FileName[]) {
    FILE *fp = fopen(FileName, "r");
    if (!fp) return ERROR;

    DestroyGraph(G);

    if (fscanf(fp, "%d %d", &G.vexnum, &G.arcnum) == EOF) {
        fclose(fp);
        return ERROR;
    }
    G.kind = UDG;

    for (int i = 0; i < G.vexnum; i++) {
        fscanf(fp, "%d %s", &G.vertices[i].data.key, G.vertices[i].data.others);
        G.vertices[i].firstarc = NULL;
    }

    KeyType k1, k2;
    while (fscanf(fp, "%d %d", &k1, &k2) != EOF) {
        int i = LocateVex(G, k1);
        int j = LocateVex(G, k2);
        if (i != -1 && j != -1) {
            ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
            if (p) {
                p->adjvex = j;
                p->nextarc = G.vertices[i].firstarc;
                G.vertices[i].firstarc = p;
            }
        }
    }
    fclose(fp);
    return OK;
}
