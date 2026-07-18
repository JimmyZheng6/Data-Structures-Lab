#include "Graph.h"
#ifdef _WIN32

#include <windows.h>

#endif

void ShowMenu() {
    printf("\n========= 基于邻接表的图操作演示系统 =========\n");
    printf("1. 创建图\t\t\t2. 销毁/清空当前图\n");
    printf("3. 查找顶点 (获取位序)\t\t4. 顶点赋值 (修改附加名)\n");
    printf("5. 获取第一邻接点\t\t6. 获取下一邻接点\n");
    printf("7. 插入新顶点\t\t\t8. 删除顶点及关联边\n");
    printf("9. 插入无向边\t\t\t10. 删除无向边\n");
    printf("11. 深度优先搜索遍历(DFS)\t12. 广度优先搜索遍历(BFS)\n");
    printf("---------------------------------------------\n");
    printf("13. 附加：求距离小于 K 的顶点集\t14. 附加：两顶点间最短路径\n");
    printf("15. 附加：计算连通分量个数\t16. 附加：保存当前图到文件\n");
    printf("17. 附加：从文件加载恢复图\n");
    printf("---------------------------------------------\n");
    printf("18. 多图管理：查看所有图\t19. 多图管理：新建并切换图\n");
    printf("20. 多图管理：移除某个图\t0. 退出系统\n");
    printf("=============================================\n");
}

int main() {
#ifdef _WIN32

    SetConsoleOutputCP(CP_UTF8);

    SetConsoleCP(CP_UTF8);

#endif
    GraphManager manager;
    manager.count = 1;
    int current_idx = 0;

    // 初始化唯一的初始空图 Graph_1
    strcpy(manager.names[0], "Graph_1");
    ALGraph *curG = &manager.graphs[0];
    curG->vexnum = 0;
    curG->arcnum = 0;
    curG->kind = UDG;

    int choice;
    while (1) {
        curG = &manager.graphs[current_idx];

        printf("\n>>> 当前正在操作的图为: 【%s】 (顶点数:%d, 边数:%d) <<<\n",
               manager.names[current_idx], curG->vexnum, curG->arcnum);
        DisplayGraph(*curG);
        ShowMenu();
        printf("请输入选项(0-20): ");
        if (scanf("%d", &choice) == EOF) break;

        if (choice == 0) {
            for(int i = 0; i < manager.count; i++) DestroyGraph(manager.graphs[i]);
            printf("系统已安全退出。\n");
            break;
        }

        switch (choice) {
            case 1: { // 纯正交互式手动：创建图
                int v_num, r_num;
                printf("请输入要创建的 [顶点总数] 和 [边总数] (例如: 3 2): ");
                scanf("%d %d", &v_num, &r_num);

                if (v_num > MAX_VERTEX_NUM || v_num <= 0) {
                    printf("顶点数量非法或超出最大限制！\n");
                    break;
                }

                // 清空当前图避免数据重叠
                DestroyGraph(*curG);

                VertexType* V = (VertexType*)malloc(v_num * sizeof(VertexType));
                KeyType (*VR)[2] = (KeyType(*)[2])malloc(r_num * 2 * sizeof(KeyType));

                printf("\n--- 开始输入 %d 个顶点信息 ---\n", v_num);
                for (int i = 0; i < v_num; i++) {
                    printf("请输入第 %d 个顶点的 [Key] 和 [描述信息] (如 10 A): ", i + 1);
                    scanf("%d %s", &V[i].key, V[i].others);
                }

                printf("\n--- 开始输入 %d 条无向边关系 ---\n", r_num);
                for (int i = 0; i < r_num; i++) {
                    printf("请输入第 %d 条边的 [起点Key] 和 [终点Key] (如 10 20): ", i + 1);
                    scanf("%d %d", &VR[i][0], &VR[i][1]);
                }

                // 调用标准的 CreateGraph 函数
                if (CreateGraph(*curG, V, v_num, VR, r_num) == OK) {
                    printf("\n图创建成功，邻接表已成功建立！\n");
                } else {
                    printf("\n图创建失败，请核对输入数据。\n");
                }

                free(V);
                free(VR);
                break;
            }
            case 2:
                DestroyGraph(*curG);
                printf("当前图已成功清空销毁。\n");
                break;
            case 3: {
                KeyType u;
                printf("请输入要查找的顶点Key: ");
                scanf("%d", &u);
                int pos = LocateVex(*curG, u);
                if (pos != -1) printf("顶点 %d 的物理存储位序(数组下标)为: %d\n", u, pos);
                else printf("该顶点不存在！\n");
                break;
            }
            case 4: {
                KeyType u; char str[20];
                printf("请输入要修改的顶点Key 和 新值(字符串): ");
                scanf("%d %s", &u, str);
                if (PutVex(*curG, u, str) == OK) printf("赋值成功。\n");
                else printf("顶点不存在，修改失败。\n");
                break;
            }
            case 5: {
                int u;
                printf("请输入顶点的物理位序(下标): ");
                scanf("%d", &u);
                int first = FirstAdjVex(*curG, u);
                if (first != -1) printf("第一邻接点的物理位序为: %d\n", first);
                else printf("无邻接点或位序非法。\n");
                break;
            }
            case 6: {
                int v, w;
                printf("请输入当前顶点位序v 和 相对邻接点位序w: ");
                scanf("%d %d", &v, &w);
                int next = NextAdjVex(*curG, v, w);
                if (next != -1) printf("相对于 %d 的下一个邻接点位序为: %d\n", w, next);
                else printf("不存在下一个邻接点。\n");
                break;
            }
            case 7: {
                VertexType v;
                printf("请输入新顶点的Key 和 描述信息(例如: 10 栈): ");
                scanf("%d %s", &v.key, v.others);
                if (InsertVex(*curG, v) == OK) printf("新顶点插入成功。\n");
                else printf("顶点Key重复或空间已满，插入失败。\n");
                break;
            }
            case 8: {
                KeyType u;
                printf("请输入要删除的顶点Key: ");
                scanf("%d", &u);
                if (DeleteVex(*curG, u) == OK) printf("顶点及相关弧已彻底删除。\n");
                else printf("顶点不存在，删除失败。\n");
                break;
            }
            case 9: {
                KeyType v, w;
                printf("请输入要连接的两个顶点Key (v w): ");
                scanf("%d %d", &v, &w);
                if (InsertArc(*curG, v, w) == OK) printf("无向边连接成功。\n");
                else printf("边已存在或顶点不存在，连接失败。\n");
                break;
            }
            case 10: {
                KeyType v, w;
                printf("请输入要断开的两个顶点Key (v w): ");
                scanf("%d %d", &v, &w);
                if (DeleteArc(*curG, v, w) == OK) printf("无向边断开成功。\n");
                else printf("边不存在，断开失败。\n");
                break;
            }
            case 11:
                printf("深度优先搜索(DFS)结果: ");
                DFSTraverse(*curG, printVertex);
                break;
            case 12:
                printf("广度优先搜索(BFS)结果: ");
                BFSTraverse(*curG, printVertex);
                break;
            case 13: {
                KeyType u; int k;
                printf("请输入中心顶点Key 和 阈值距离K: ");
                scanf("%d %d", &u, &k);
                VerticesSetLessThanK(*curG, u, k);
                break;
            }
            case 14: {
                KeyType v, w;
                printf("请输入起点Key 和 终点Key: ");
                scanf("%d %d", &v, &w);
                int len = ShortestPathLength(*curG, v, w);
                if (len != -1) printf("顶点 %d 到 %d 的最短路径长度为: %d\n", v, w, len);
                else printf("两点不连通或顶点不存在！\n");
                break;
            }
            case 15:
                printf("当前图的连通分量个数为: %d\n", ConnectedComponentsNums(*curG));
                break;
            case 16: {
                char fname[40];
                printf("请输入保存的文件名(如 mygraph.txt): ");
                scanf("%s", fname);
                if (SaveGraph(*curG, fname) == OK) printf("当前图已成功导出到文件。\n");
                else printf("文件写入失败。\n");
                break;
            }
            case 17: {
                char fname[40];
                printf("请输入要加载的文件名(如 mygraph.txt): ");
                scanf("%s", fname);
                if (LoadGraph(*curG, fname) == OK) printf("图已成功从文件加载并重建完成。\n");
                else printf("文件读取失败。\n");
                break;
            }
            case 18:
                printf("--- 现有图列表 ---\n");
                for (int i = 0; i < manager.count; i++) {
                    printf("[%d] 图名称: %s (V:%d, E:%d)%s\n",
                           i + 1, manager.names[i], manager.graphs[i].vexnum, manager.graphs[i].arcnum,
                           (i == current_idx) ? " *当前活跃*" : "");
                }
                break;
            case 19: {
                if (manager.count >= MAX_GRAPH_NUM) {
                    printf("图管理数量已达上限！\n");
                    break;
                }
                char gname[30];
                printf("请输入全新图的名称: ");
                scanf("%s", gname);
                strcpy(manager.names[manager.count], gname);
                
                manager.graphs[manager.count].vexnum = 0;
                manager.graphs[manager.count].arcnum = 0;
                manager.graphs[manager.count].kind = UDG;
                
                current_idx = manager.count;
                manager.count++;
                printf("已成功创建并切换至全新的空图 【%s】。\n", gname);
                break;
            }
            case 20: {
                if (manager.count <= 1) {
                    printf("只剩最后一个空图，无法继续移除！\n");
                    break;
                }
                int idx;
                printf("请输入要移除的图序号(1-%d): ", manager.count);
                scanf("%d", &idx);
                if (idx < 1 || idx > manager.count) {
                    printf("序号非法。\n");
                    break;
                }
                idx--;
                DestroyGraph(manager.graphs[idx]);
                
                for (int i = idx; i < manager.count - 1; i++) {
                    manager.graphs[i] = manager.graphs[i + 1];
                    strcpy(manager.names[i], manager.names[i + 1]);
                }
                manager.count--;
                
                if (current_idx >= manager.count) {
                    current_idx = manager.count - 1;
                }
                printf("移除成功，已自动切换到剩余的活跃图中。\n");
                break;
            }
            default:
                printf("非法输入，请重新选择。\n");
        }
    }
    return 0;
}
