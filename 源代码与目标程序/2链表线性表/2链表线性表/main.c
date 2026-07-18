#include <stdio.h>
#include "linked_list.h"
#ifdef _WIN32

#include <windows.h>

#endif

#define MAX_LISTS 10

void showMenu(void) {
    printf("\n--- 线性表实验演示系统 ---\n");
    printf("1. 初始化/重置表   2. 插入元素       3. 删除元素\n");
    printf("4. 获取元素       5. 查找元素位序    6. 获取前驱\n");
    printf("7. 获取后继       8. 遍历表         9. 求表长\n");
    printf("10. 清空表        11. 判定空表       12. 销毁表\n");
    printf("13. 链表翻转       14. 删除倒数第N     15. 排序链表\n");
    printf("16. 保存到文件     17. 从文件加载      18. 切换/管理多线性表\n");
    printf("0. 退出\n");
    printf("选择操作: ");
}

int main(void) {
#ifdef _WIN32
    
    SetConsoleOutputCP(CP_UTF8);
    
    SetConsoleCP(CP_UTF8);
    
#endif
    ListManager managers[MAX_LISTS];
    for(int i=0; i<MAX_LISTS; i++) {
        managers[i].list = NULL;
        sprintf(managers[i].name, "未命名表_%d", i);
    }
    
    int current_idx = 0;
    InitList(&managers[current_idx].list);
    
    int choice;
    ElemType e, e2;
    int i, n;
    char filename[100];

    while (1) {
        printf("\n[当前管理: %s]", managers[current_idx].name);
        showMenu();
        scanf(" %d", &choice);

        switch (choice) {
            case 1:
                if(managers[current_idx].list) DestroyList(&managers[current_idx].list);
                InitList(&managers[current_idx].list);
                printf("表已初始化。\n");
                break;
            case 2:
                printf("输入插入位置和值: ");
                scanf("%d %d", &i, &e);
                if (ListInsert(managers[current_idx].list, i, e)) printf("插入成功。\n");
                else printf("插入失败。\n");
                break;
            case 3:
                printf("输入删除位置: ");
                scanf("%d", &i);
                if (ListDelete(managers[current_idx].list, i, &e)) printf("删除成功，值为: %d\n", e);
                else printf("删除失败。\n");
                break;
            case 4:
                printf("输入获取位置: ");
                scanf("%d", &i);
                if (GetElem(managers[current_idx].list, i, &e)) printf("第%d个元素为: %d\n", i, e);
                else printf("位置无效。\n");
                break;
            case 5:
                printf("输入查找的值: ");
                scanf("%d", &e);
                i = LocateElem(managers[current_idx].list, e, compare_equal);
                if (i) printf("元素位序为: %d\n", i);
                else printf("未找到元素。\n");
                break;
            case 6:
                printf("输入当前值查找前驱: ");
                scanf("%d", &e);
                if (PriorElem(managers[current_idx].list, e, &e2)) printf("前驱为: %d\n", e2);
                else printf("无前驱或表不存在该值。\n");
                break;
            case 7:
                printf("输入当前值查找后继: ");
                scanf("%d", &e);
                if (NextElem(managers[current_idx].list, e, &e2)) printf("后继为: %d\n", e2);
                else printf("无后继或表不存在该值。\n");
                break;
            case 8:
                printf("线性表内容: ");
                ListTraverse(managers[current_idx].list, print_elem);
                break;
            case 9:
                printf("表长度: %d\n", ListLength(managers[current_idx].list));
                break;
            case 10:
                ClearList(managers[current_idx].list);
                printf("表已清空。\n");
                break;
            case 11:
                if (ListEmpty(managers[current_idx].list)) printf("表为空。\n");
                else printf("表不为空。\n");
                break;
            case 12:
                DestroyList(&managers[current_idx].list);
                printf("表已销毁。\n");
                break;
            case 13: case 'a':
                reverseList(managers[current_idx].list);
                printf("链表已翻转。\n");
                break;
            case 14: case 'b':
                printf("输入倒数位置n: ");
                scanf("%d", &n);
                RemoveNthFromEnd(managers[current_idx].list, n);
                printf("操作完成。\n");
                break;
            case 15: case 'c':
                sortList(managers[current_idx].list);
                printf("链表已排序。\n");
                break;
            case 16: case 's':
                printf("输入保存文件名: ");
                scanf("%s", filename);
                if (SaveToFile(managers[current_idx].list, filename)) printf("保存成功。\n");
                else printf("保存失败。\n");
                break;
            case 17: case 'l':
                printf("输入读取文件名: ");
                scanf("%s", filename);
                if (LoadFromFile(managers[current_idx].list, filename)) printf("读取成功。\n");
                else printf("读取失败。\n");
                break;
            case 18: case 'm':
                printf("输入索引(0-%d)切换管理位: ", MAX_LISTS-1);
                scanf("%d", &i);
                if(i >= 0 && i < MAX_LISTS) {
                    current_idx = i;
                    if(!managers[current_idx].list) InitList(&managers[current_idx].list);
                    printf("已切换到表 %d。\n", i);
                } else printf("索引无效。\n");
                break;
            case 0:
                for(int j=0; j<MAX_LISTS; j++) if(managers[j].list) DestroyList(&managers[j].list);
                return 0;
            default:
                printf("无效选择。\n");
        }
    }
    return 0;
}
