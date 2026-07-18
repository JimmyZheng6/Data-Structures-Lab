#include "BiTree.h"
#ifdef _WIN32

#include <windows.h>

#endif

TreeNode trees[MAX_TREE_NUM];

int treeCount=0;

int current=-1;



void visit(BiTree T)
{
    printf("%d,%s ",
           T->data.key,
           T->data.others);
}



void showMainMenu()
{
    printf("\n");
    printf("========= 多二叉树管理系统 =========\n");

    printf("1. 创建二叉树\n");
    printf("2. 查看所有二叉树\n");
    printf("3. 切换当前二叉树\n");
    printf("4. 销毁二叉树\n");

    printf("5. 插入结点\n");
    printf("6. 删除结点\n");
    printf("7. 查找结点\n");
    printf("8. 结点赋值\n");
    printf("9. 获取兄弟结点\n");

    printf("10. 求树深度\n");

    printf("11. 先序遍历\n");
    printf("12. 中序遍历\n");
    printf("13. 后序遍历\n");
    printf("14. 层序遍历\n");

    printf("15. 保存二叉树\n");
    printf("16. 加载二叉树\n");

    printf("17. 翻转二叉树\n");
    printf("18. 最大路径和\n");
    printf("19. 最近公共祖先\n");
    printf("20. 清空二叉树\n");
    printf("21. 判空\n");

    printf("0. 退出系统\n");

    printf("===================================\n");
}



bool checkCurrent()
{
    if(current==-1)
    {
        printf("请先切换二叉树\n");
        return false;
    }

    return true;
}



int main()
{
#ifdef _WIN32

    SetConsoleOutputCP(CP_UTF8);

    SetConsoleCP(CP_UTF8);

#endif
    int choice;
    
    while(1)
    {
        showMainMenu();
        
        printf("请输入功能编号：");
        
        scanf("%d",&choice);
        
        if(choice==0)
        {
            printf("系统退出\n");
            break;
        }
        
        
        
        switch(choice)
        {
                
                /*================ 创建树 ================*/
                
            case 1:
            {
                if(treeCount>=MAX_TREE_NUM)
                {
                    printf("树数量已满\n");
                    break;
                }
                
                printf("输入树名称：");
                
                scanf("%s",
                      trees[treeCount].name);
                
                trees[treeCount].T=NULL;
                
                printf("创建成功，编号=%d\n",
                       treeCount);
                
                treeCount++;
                
                break;
            }
                
                
                
                /*================ 查看树 ================*/
                
            case 2:
            {
                if(treeCount==0)
                {
                    printf("暂无二叉树\n");
                    break;
                }
                
                for(int i=0;i<treeCount;i++)
                {
                    printf("%d. %s",
                           i,
                           trees[i].name);
                    
                    if(i==current)
                        printf("  [当前树]");
                    
                    printf("\n");
                }
                
                break;
            }
                
                
                
                /*================ 切换树 ================*/
                
            case 3:
            {
                int id;
                
                printf("输入树编号：");
                
                scanf("%d",&id);
                
                if(id<0 || id>=treeCount)
                {
                    printf("编号错误\n");
                }
                else
                {
                    current=id;
                    
                    printf("当前树=%s\n",
                           trees[current].name);
                }
                
                break;
            }
                
                
                
                /*================ 删除树 ================*/
                
            case 4:
            {
                int id;
                
                printf("输入销毁编号：");
                
                scanf("%d",&id);
                
                if(id<0 || id>=treeCount)
                {
                    printf("编号错误\n");
                    break;
                }
                
                DestroyBiTree(trees[id].T);
                
                for(int i=id;i<treeCount-1;i++)
                {
                    trees[i]=trees[i+1];
                }
                
                treeCount--;
                
                if(current==id)
                    current=-1;
                
                printf("销毁成功\n");
                
                break;
            }
                
                
                
                /*================ 插入结点 ================*/
                
            case 5:
            {
                if(!checkCurrent())
                    break;
                
                TElemType x;
                
                int e,LR;
                
                printf("输入新结点key和others：");
                
                scanf("%d%s",
                      &x.key,
                      x.others);
                
                printf("输入父节点key：");
                
                scanf("%d",&e);
                
                printf("输入LR(-1根 0左 1右)：");
                
                scanf("%d",&LR);
                
                if(InsertNode(
                              trees[current].T,
                              e,
                              LR,
                              x)==OK)
                    
                    printf("插入成功\n");
                
                else
                    
                    printf("插入失败\n");
                
                break;
            }
                
                
                
                /*================ 删除结点 ================*/
                
            case 6:
            {
                if(!checkCurrent())
                    break;
                
                int e;
                
                printf("输入key：");
                
                scanf("%d",&e);
                
                if(DeleteNode(
                              trees[current].T,
                              e)==OK)
                    
                    printf("删除成功\n");
                
                else
                    
                    printf("删除失败\n");
                
                break;
            }
                
                
                
                /*================ 查找结点 ================*/
                
            case 7:
            {
                if(!checkCurrent())
                    break;
                
                int e;
                
                printf("输入key：");
                
                scanf("%d",&e);
                
                BiTree p=
                LocateNode(
                           trees[current].T,
                           e);
                
                if(p)
                {
                    printf("找到：");
                    
                    printf("%d,%s\n",
                           p->data.key,
                           p->data.others);
                }
                else
                {
                    printf("未找到\n");
                }
                
                break;
            }
                
                
                
                /*================ 结点赋值 ================*/
                
            case 8:
            {
                if(!checkCurrent())
                    break;
                
                int e;
                
                TElemType x;
                
                printf("输入要修改的key：");
                
                scanf("%d",&e);
                
                printf("输入新key和others：");
                
                scanf("%d%s",
                      &x.key,
                      x.others);
                
                if(Assign(
                          trees[current].T,
                          e,
                          x)==OK)
                    
                    printf("赋值成功\n");
                
                else
                    
                    printf("赋值失败\n");
                
                break;
            }
                
                
                
                /*================ 获取兄弟 ================*/
                
            case 9:
            {
                if(!checkCurrent())
                    break;
                
                int e;
                
                printf("输入key：");
                
                scanf("%d",&e);
                
                BiTree p=
                GetSibling(
                           trees[current].T,
                           e);
                
                if(p)
                {
                    printf("兄弟结点：");
                    
                    printf("%d,%s\n",
                           p->data.key,
                           p->data.others);
                }
                else
                {
                    printf("无兄弟结点\n");
                }
                
                break;
            }
                
                
                
                /*================ 树深度 ================*/
                
            case 10:
            {
                if(!checkCurrent())
                    break;
                
                printf("树深度=%d\n",
                       BiTreeDepth(
                                   trees[current].T));
                
                break;
            }
                
                
                
                /*================ 先序遍历 ================*/
                
            case 11:
            {
                if(!checkCurrent())
                    break;
                
                PreOrderTraverse(
                                 trees[current].T,
                                 visit);
                
                printf("\n");
                
                break;
            }
                
                
                
                /*================ 中序遍历 ================*/
                
            case 12:
            {
                if(!checkCurrent())
                    break;
                
                InOrderTraverse(
                                trees[current].T,
                                visit);
                
                printf("\n");
                
                break;
            }
                
                
                
                /*================ 后序遍历 ================*/
                
            case 13:
            {
                if(!checkCurrent())
                    break;
                
                PostOrderTraverse(
                                  trees[current].T,
                                  visit);
                
                printf("\n");
                
                break;
            }
                
                
                
                /*================ 层序遍历 ================*/
                
            case 14:
            {
                if(!checkCurrent())
                    break;
                
                LevelOrderTraverse(
                                   trees[current].T,
                                   visit);
                
                printf("\n");
                
                break;
            }
                
                
                
                /*================ 保存 ================*/
                
            case 15:
            {
                if(!checkCurrent())
                    break;
                
                char filename[50];
                
                printf("输入文件名：");
                
                scanf("%s",filename);
                
                if(SaveBiTree(trees[current].T,filename)==OK)
                    printf("保存成功\n");
                else
                    printf("保存失败\n");
                
                break;
            }
                
                
                
                /*================ 加载 ================*/
                
            case 16:
            {
                if(!checkCurrent())
                    break;
                
                char filename[50];
                
                printf("输入文件名：");
                
                scanf("%s",filename);
                
                if(LoadBiTree(trees[current].T,filename)==OK)
                    printf("加载成功\n");
                else
                    printf("加载失败\n");
                break;
            }
                
                
                
                /*================ 翻转 ================*/
                
            case 17:
            {
                if(!checkCurrent())
                    break;
                
                InvertTree(
                           trees[current].T);
                
                printf("翻转完成\n");
                
                break;
            }
                
                
                
                /*================ 最大路径和 ================*/
                
            case 18:
            {
                if(!checkCurrent())
                    break;
                
                printf("最大路径和=%d\n",
                       MaxPathSum(
                                  trees[current].T));
                
                break;
            }
                
                
                
                /*================ 最近公共祖先 ================*/
                
            case 19:
            {
                if(!checkCurrent())
                    break;
                
                int a,b;
                
                printf("输入两个key：");
                
                scanf("%d%d",&a,&b);
                
                BiTree p=
                LowestCommonAncestor(
                                     trees[current].T,
                                     a,
                                     b);
                
                if(p)
                {
                    printf("最近公共祖先=");
                    
                    printf("%d,%s\n",
                           p->data.key,
                           p->data.others);
                }
                else
                {
                    printf("不存在\n");
                }
                
                break;
            }
                
            case 20:{
                int id;
                
                printf("输入清空编号：");
                
                scanf("%d",&id);
                
                if(id<0 || id>=treeCount)
                {
                    printf("编号错误\n");
                    break;
                }
                
                ClearBiTree(trees[id].T);
                printf("清空成功\n");
                break;
            }
                
            case 21:
            {
                int id;
                
                printf("输入判空编号：");
                
                scanf("%d",&id);
                
                if(id<0 || id>=treeCount)
                {
                    printf("编号错误\n");
                    break;
                }
                if(BiTreeEmpty(trees[id].T)) printf("二叉树为空\n");
                else printf("二叉树不为空\n");
                break;
            }
                
            default:
            {
                printf("输入错误\n");
            }
                
        }
    }
        return 0;
    }
    

