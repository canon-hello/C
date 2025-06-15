#include "3def.h"
#include "3func.h"


/* 零件函数 */
status Compare(KeyType e, TElemType elem);  //比较函数
void visit(BiTree elem);                    //访问函数
int max(int x, int y);                      //求较大值函数

/* 零件函数指针 */
status(*CompareArr)(KeyType e, TElemType elem) = Compare;
void (*visitArr)(BiTree elem) = visit;

/* 队列操作函数 */
void iniQueue(QUEUE& Q);
status enQueue(QUEUE& Q, ElemType e);
status deQueue(QUEUE& Q, ElemType& e);

/* 单树基础操作函数 */
status CreateBiTree(BiTree& T, TElemType definition[]);
status ClearBiTree(BiTree& T);
status DestroyBiTree(BiTree& T);
status ClearBiTree(BiTree& T);
status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T, KeyType e);
status Assign(BiTree& T, KeyType e, TElemType value);
BiTNode* GetSibling(BiTree T, KeyType e);
status InsertNode(BiTree& T, KeyType e, int LR, TElemType c);
status DeleteNode(BiTree& T, KeyType e);
status PreOrderTraverse(BiTree T, void (*visit)(BiTree));
status InOrderTraverse(BiTree T, void (*visit)(BiTree));
status PostOrderTraverse(BiTree T, void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));

/*选做操作函数*/
int MaxPathSum(BiTree T);
BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2);
status InvertTree(BiTree& T);

/*文件读写函数*/
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree& T, char FileName[]);

/*多树操作函数*/
status AddTree(LISTS& Trees, char ListName[]);
status RemoveTree(LISTS& Trees, char ListName[]);
int LocateTree(LISTS Trees, char ListName[]);
status ListsTraverse(LISTS Trees);
BiTree* ChooseTree(BiTree* T, LISTS& Trees, int i);










/*---------------------main函数-----------------------*/
int main(void)
{
    //定义单树并初始化
    BiTree T1 = NULL;
    BiTree* T = &T1;

    //定义管理表并初始化
    LISTS Trees;
    Trees.length = 0, Trees.listsize = 10;

    int op = 1, flag = 0, j = 0;     //op记录功能选择情况，flag记录功能运行情况
    char FileName[30], ListName[30]; //储存文件名与表名
    BiTNode* BTN = NULL;             //储存临时二叉结点
    TElemType definition[100];       //储存前序遍历序列
    memset(definition, 0, 100 * sizeof(TElemType));
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("       Menu for Binary Tree On BiLinked Structure \n");
        printf("------------------------------------------------------\n");
        printf("    	  1. 创建         13. 后序遍历\n");
        printf("    	  2. 销毁         14. 层序遍历\n");
        printf("    	  3. 清空         15. 求最大路径和\n");
        printf("    	  4. 判空         16. 求最近公共祖先\n");
        printf("    	  5. 求深         17. 翻转二叉树\n");
        printf("    	  6. 查找结点     18. 写入文件\n");
        printf("    	  7. 结点赋值     19. 读取文件\n");
        printf("    	  8. 获取兄弟     20. 增加二叉树\n");
        printf("    	  9. 插入结点     21. 删除二叉树\n");
        printf("    	 10. 删除结点     22. 查找二叉树\n");
        printf("    	 11. 前序遍历     23. 遍历总表\n");
        printf("    	 12. 中序遍历     24. 选择单树进行操作\n");
        printf("    	  0. 退出\n");
        printf("------------------------------------------------------\n");
        printf("    请选择你的操作[0~24]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1://创建
            if (*T != NULL)
                printf("二叉树已存在！无法再创建！\n");
            else
            {
                flag_create = 0, k = 0;//重置static变量
                printf("请输入前序遍历序列：");
                do
                {
                    scanf("%d %s", &definition[j].key, definition[j].others);
                } while (definition[j++].key != -1);
                flag = CreateBiTree(*T, definition);
                if (flag == OK)
                    printf("二叉树创建成功！\n这是一个与独立于多树的单树，你可以对它进行1~19操作！\n");
                else if (flag == ERROR)
                    printf("关键词不唯一！二叉树创建失败！\n");
            }
            getchar();getchar();
            break;
        case 2://销毁
            flag = DestroyBiTree(*T);
            if (flag == OK)
                printf("成功销毁二叉树并释放数据元素的空间！\n");
            else
                printf("不能对不存在的二叉树进行销毁操作！\n");
            getchar();getchar();
            break;
        case 3://清空
            flag = ClearBiTree(*T);
            if (flag == OK)
                printf("成功清空二叉树！\n");
            else
                printf("不能对不存在的二叉树进行清空操作！\n");
            getchar();getchar();
            break;
        case 4://判空
            flag = BiTreeEmpty(*T);
            if (flag == TRUE)
                printf("二叉树为空！\n");
            else if (flag == FALSE)
                printf("二叉树不为空！\n");
            else
                printf("不能对不存在的二叉树进行判空操作！\n");
            getchar();getchar();
            break;
        case 5://求深
            // if(*T == NULL)
            //     printf("不能对不存在的二叉树进行求深操作！\n");
            // else
        {
            flag = BiTreeDepth(*T);
            printf("二叉树的深度为 %d！\n", flag);
        }
        getchar();getchar();
        break;
        case 6://查找结点
            if (*T == NULL)
                printf("不能对不存在的二叉树进行查找结点操作！\n");
            else
            {
                int e = 0;//存储关键字
                BTN = NULL;//存储所求结点
                printf("请输入想要查找的结点的关键字：");
                scanf("%d", &e);
                BTN = LocateNode(*T, e);
                if (BTN == NULL)
                    printf("查找失败！不存在关键字为 %d 的结点！\n", e);
                else
                    printf("查找成功！该结点关键字为 %d，内容为 %s！\n", BTN->data.key, BTN->data.others);
            }
            getchar();getchar();
            break;
        case 7://结点赋值
            if (*T == NULL)
                printf("不能对不存在的二叉树进行结点赋值操作！\n");
            else
            {

                int e = 0;//存储关键字
                TElemType value[5];//存储新关键字与内容
                memset(value, 0, 5 * sizeof(TElemType));//初始化
                printf("请输入想要赋值的结点的关键字：");
                scanf("%d", &e);
                printf("请输入将赋的关键字与内容：");
                scanf("%d %s", &value->key, value->others);
                flag = Assign(*T, e, *value);
                if (flag == OK)
                    printf("赋值成功！\n");
                else
                    printf("赋值失败！关键词已存在！\n");
            }
            getchar();getchar();
            break;
        case 8://获取兄弟
            if (*T == NULL)
                printf("不能对不存在的二叉树进行获取兄弟操作！\n");
            else
            {
                p = NULL;//重置static变量
                int e = 0;//存储关键字
                BTN = NULL;//存储所求结点
                printf("请输入想要获取其兄弟结点的结点的关键字：");
                scanf("%d", &e);
                BTN = GetSibling(*T, e);
                if (BTN == NULL)
                    printf("获取失败！不存在关键字为 %d 的结点或该结点没有兄弟！\n", e);
                else
                    printf("获取成功！该结点的兄弟结点的关键字为 %d，内容为 %s！\n", BTN->data.key, BTN->data.others);
            }
            getchar();getchar();
            break;
        case 9://插入结点
            if (*T == NULL)
                printf("不能对不存在的二叉树进行插入结点操作！\n");
            else
            {
                int e = 0, LR = 0;//存储关键字与插入方式
                printf("请输入想要插入的结点的父结点的关键字：");
                scanf("%d", &e);
                printf("LR = 0 作为左孩子\nLR = 1 作为右孩子\nLR = -1 作为根结点\n");
                printf("请输入插入方式：");
                scanf("%d", &LR);
                if (LR == -1 || LR == 0 || LR == 1)
                {
                    TElemType c[5];//存储新关键字与内容
                    memset(c, 0, 5 * sizeof(TElemType));//初始化
                    printf("请输入将插入的关键字与内容：");
                    scanf("%d %s", &c[0].key, c[0].others);
                    flag = InsertNode(*T, e, LR, c[0]);
                    if (flag == OK)
                        printf("插入成功！\n");
                    else
                        printf("插入失败！关键词已存在！\n");
                }
                else
                    printf("插入失败！插入方式输入有误！\n");
            }
            getchar();getchar();
            break;
        case 10://删除结点
            if (*T == NULL)
                printf("不能对不存在的二叉树进行插入结点操作！\n");
            else
            {
                flag1 = 0;//重置static变量
                int e = 0;//存储关键字
                printf("请输入想删除的结点的关键字：");
                scanf("%d", &e);
                flag = DeleteNode(*T, e);
                if (flag == OK)
                    printf("删除成功！\n");
                else
                    printf("删除失败！\n");
            }
            getchar();getchar();
            break;
        case 11://前序遍历
            if (*T == NULL)
                printf("不能对不存在的二叉树进行前序遍历操作！\n");
            else
            {
                printf("\n-------------- all elements -------------------\n");
                PreOrderTraverse(*T, visit);
                printf("\n------------------ end ------------------------\n");
            }
            getchar();getchar();
            break;
        case 12://中序遍历
            if (*T == NULL)
                printf("不能对不存在的二叉树进行中序遍历操作！\n");
            else
            {
                printf("\n-------------- all elements -------------------\n");
                InOrderTraverse(*T, visit);
                printf("\n------------------ end ------------------------\n");
            }
            getchar();getchar();
            break;
        case 13://后序遍历
            if (*T == NULL)
                printf("不能对不存在的二叉树进行后序遍历操作！\n");
            else
            {
                printf("\n-------------- all elements -------------------\n");
                PostOrderTraverse(*T, visit);
                printf("\n------------------ end ------------------------\n");
            }
            getchar();getchar();
            break;
        case 14://层序遍历
            if (*T == NULL)
                printf("不能对不存在的二叉树进行层序遍历操作！\n");
            else
            {
                printf("\n-------------- all elements -------------------\n");
                LevelOrderTraverse(*T, visit);
                printf("\n------------------ end ------------------------\n");
            }
            getchar();getchar();
            break;
        case 15://求最大路径和
            if (*T == NULL)
                printf("不能对不存在的二叉树进行该操作！\n");
            else
            {
                flag = MaxPathSum(*T);
                printf("该二叉树最大路径和为 %d！", flag);
            }
            getchar();getchar();
            break;
        case 16://求最近公共祖先
            if (*T == NULL)
                printf("不能对不存在的二叉树进行该操作！\n");
            else
            {
                int e1 = 0, e2 = 0;//存储关键字
                BTN = NULL;//存储所求结点
                printf("请输入二叉树中两个结点的关键字：\n");
                scanf("%d %d", &e1, &e2);
                BTN = LowestCommonAncestor(*T, e1, e2);
                if (BTN == NULL)
                    printf("操作失败！关键字输入有误！\n");
                else
                    printf("关键字为 %d 和 %d 的两个结点的最近公共祖先为 %d %s！\n", e1, e2, BTN->data.key, BTN->data.others);
            }
            getchar();getchar();
            break;
        case 17://翻转二叉树
            if (*T == NULL)
                printf("不能对不存在的二叉树进行该操作！\n");
            else
                if (InvertTree(*T) == OK)
                    printf("二叉树翻转成功！");
            getchar();getchar();
            break;
        case 18://写入文件
            if (*T == NULL)
                printf("不能对不存在的二叉树进行该操作！\n");
            else
            {
                printf("请输入文件名称：");
                scanf("%s", FileName);
                flag = SaveBiTree(*T, FileName);
                if (flag == ERROR)
                    printf("文件打开失败！\n");
                else if (flag == OK)
                    printf("二叉树的内容已经复制到名称为 %s 的文件中！\n", FileName);
            }
            getchar();getchar();
            break;
        case 19://读取文件
            printf("请输入文件名称：");
            scanf("%s", FileName);
            flag = LoadBiTree(*T, FileName);
            if (flag == ERROR)
                printf("文件打开失败！\n");
            else if (flag == OK)
                printf("名称为 %s 的文件中的内容已复制到二叉树中！\n", FileName);
            else if (flag == INFEASIBLE)
                printf("不能对已存在的二叉树进行进行读文件操作！请先销毁二叉树！\n");
            else if (flag == OVERFLOW)
                printf("溢出！\n");
            getchar();getchar();
            break;
        case 20://增加二叉树
            flag_create = 0, k = 0;
            printf("请输入新增二叉树的名称：");
            scanf("%s", ListName);
            flag = AddTree(Trees, ListName);
            if (flag == OK)
                printf("成功新增名称为 %s 的二叉树！\n", ListName);
            else
                printf("新增失败！\n");
            getchar();getchar();
            break;
        case 21://删除二叉树
            if (Trees.length)
            {
                printf("\n---------------- all trees --------------------\n");
                for (int i = 0; i < Trees.length; i++)
                    printf("%d %s\n", i + 1, Trees.elem[i].name);
                printf("------------------ end ------------------------\n");
            }
            else
            {
                printf("二叉树的集合为空！无法进行此操作！\n");
                getchar();getchar();
                break;
            }
            printf("请输入想要删除的二叉树的名称：");
            scanf("%s", ListName);
            flag = RemoveTree(Trees, ListName);
            if (flag == OK)
                printf("成功删除名称为 %s 的二叉树！\n", ListName);
            else if (flag == ERROR)
                printf("删除失败！\n");
            getchar();getchar();
            break;
        case 22://查找二叉树
        {
            if (!Trees.length)
            {
                printf("二叉树的集合为空！无法进行此操作！\n");
                getchar();getchar();
                break;
            }
            int loc = 0;
            printf("请输入想要查找的二叉树的名称：");
            scanf("%s", ListName);
            loc = LocateTree(Trees, ListName);
            if (loc == 0)
                printf("不存在名称为 %s 的二叉树！\n", ListName);
            else
                printf("名称为 %s 的二叉树的序号为 %d ！\n", ListName, loc);
            getchar();getchar();
            break;
        }
        case 23://遍历总表
            flag = ListsTraverse(Trees);
            if (flag == ERROR)
                printf("二叉树的集合为空！\n");
            getchar();getchar();
            break;
        case 24://选择单树进行操作
        {
            if (Trees.length)
            {
                printf("\n---------------- all lists --------------------\n");
                for (int i = 0; i < Trees.length; i++)
                    printf("%d %s\n", i + 1, Trees.elem[i].name);
                printf("------------------ end ------------------------\n");
            }
            else
            {
                printf("二叉树的集合为空！无法进行此操作！\n");
                getchar();getchar();
                break;
            }
            int e = 0;
            printf("请输入想要进行操作的二叉树的序号（从1开始）：");
            scanf("%d", &e);
            getchar();
            T = ChooseTree(T, Trees, e);
            if (T == NULL)
                printf("输入的序号不合法！单表已置空！\n");
            else
                printf("下面可对二叉树集合中序号为 %d 的二叉树进行操作！\n", e);
            getchar();getchar();
            break;
        }
        case 0:
            break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}
/*---------------------main函数-----------------------*/











