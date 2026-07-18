//
//  main.cpp
//  practice
//
//  Created by 郑耀涵 on 2026/4/30.
//
#include "SqList.h"
#ifdef _WIN32

#include <windows.h>

#endif

int main(void){
#ifdef _WIN32

    SetConsoleOutputCP(CP_UTF8);

    SetConsoleCP(CP_UTF8);

#endif
    int op=1;
    while(op){
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("        1. 创建新线性表    7. 按值查找元素\n");
        printf("        2. 销毁当前表      8. 获取前驱元素\n");
        printf("        3. 清空当前表      9. 获取后继元素\n");
        printf("        4. 判断表是否空   10. 插入元素\n");
        printf("        5. 获取当前表长度 11. 删除元素\n");
        printf("        6. 按位置取元素   12. 遍历当前表\n");
        printf("        13.最大子数组和   14.和为k子数组数\n");
        printf("        15.排序当前表     16.保存当前表\n");
        printf("        17.加载文件到当前表\n");
        printf("        18.切换线性表     19.查看表信息\n");
        printf("        0. 退出程序\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~19]:");
        scanf("%d",&op);

        // 拿到当前表的引用（所有操作都用这个）
        SqList& L = g_TableList[g_CurTableIdx];

        switch(op){
            // ========== 多表管理 ==========
            case 1:{
                int idx = CreateNewTable();
                if(idx != -1)
                    printf("创建新线性表成功！当前为第%d号表\n", idx+1);
                else
                    printf("创建失败！\n");
                getchar();getchar();
                break;
            }
            case 18:{
                int idx;
                printf("请输入要切换到的表序号(1~%d):", g_TableCount);
                scanf("%d", &idx);
                SwitchTable(idx-1);
                getchar();getchar();
                break;
            }
            case 19:
                ShowTableInfo();
                getchar();getchar();
                break;

            // ========== 原有基础功能（自动作用在当前表） ==========
            case 2:
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                if(DestroyList(L)==OK) printf("线性表销毁成功！\n");
                else printf("线性表销毁失败！\n");
                getchar();getchar();
                break;
            case 3:
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                if(ClearList(L)==OK) printf("线性表清空成功！\n");
                else printf("线性表清空失败！\n");
                getchar();getchar();
                break;
            case 4:
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                if(ListEmpty(L)==TRUE) printf("线性表为空！\n");
                else printf("线性表非空！\n");
                getchar();getchar();
                break;
            case 5:
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                printf("线性表当前长度: %d\n", ListLength(L));
                getchar();getchar();
                break;
            case 6:{
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                int i; ElemType e;
                printf("请输入要获取的位置：");
                scanf("%d", &i);
                if(GetElem(L, i, e)==OK) printf("第%d个元素是：%d\n", i, e);
                else printf("获取元素失败！\n");
                getchar();getchar();
                break;
            }
            case 7:{
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                ElemType e;
                printf("请输入要查找的元素：");
                scanf("%d", &e);
                int pos = LocateElem(L, e);
                if(pos) printf("元素位置：%d\n", pos);
                else printf("未找到该元素！\n");
                getchar();getchar();
                break;
            }
            case 8:{
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                ElemType cur, pre_e;
                printf("请输入要查找前驱的元素：");
                scanf("%d", &cur);
                if(PriorElem(L, cur, pre_e)==OK) printf("前驱元素：%d\n", pre_e);
                else printf("查找前驱失败！\n");
                getchar();getchar();
                break;
            }
            case 9:{
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                ElemType cur, next_e;
                printf("请输入要查找后继的元素：");
                scanf("%d", &cur);
                if(NextElem(L, cur, next_e)==OK) printf("后继元素：%d\n", next_e);
                else printf("查找后继失败！\n");
                getchar();getchar();
                break;
            }
            case 10:{
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                int i; ElemType e;
                printf("请输入插入位置和值：");
                scanf("%d %d", &i, &e);
                if(ListInsert(L, i, e)==OK) printf("插入成功！\n");
                else printf("插入失败！\n");
                getchar();getchar();
                break;
            }
            case 11:{
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                int i; ElemType e;
                printf("请输入删除位置：");
                scanf("%d", &i);
                if(ListDelete(L, i, e)==OK) printf("删除成功，被删元素：%d\n", e);
                else printf("删除失败！\n");
                getchar();getchar();
                break;
            }
            case 12:
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                if(!ListTrabverse(L)) printf("线性表是空表！\n");
                getchar();getchar();
                break;
            case 13:
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                printf("最大连续子数组和：%d\n", MaxSubArray(L));
                getchar();getchar();
                break;
            case 14:{
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                int k;
                printf("请输入目标和k：");
                scanf("%d", &k);
                printf("和为%d的子数组个数：%d\n", k, SubArrayNum(L, k));
                getchar();getchar();
                break;
            }
            case 15:
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                sortList(L);
                printf("顺序表排序完成！\n");
                getchar();getchar();
                break;
            case 16:
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                if(SaveList(L, "/Users/zhengyaohan/Desktop/数据结构/list.dat2")==OK) printf("保存到文件成功！\n");
                else printf("保存失败！\n");
                getchar();getchar();
                break;
            case 17:
                if(g_CurTableIdx == -1){printf("请先创建表！\n");break;}
                if(LoadList(L, "/Users/zhengyaohan/Desktop/数据结构/list.dat2")==OK) printf("从文件加载成功！\n");
                else printf("加载失败！\n");
                getchar();getchar();
                break;
            case 0:
                op = 0;
                break;
            default:
                printf("无效选项！\n");
                getchar();getchar();
                break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}
