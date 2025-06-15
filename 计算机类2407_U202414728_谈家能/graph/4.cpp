#include "4def.h"
#include "4func.h"

/* 零件函数 */
void visit(VertexType v);
void DFS(ALGraph G, int v, void (*visit)(VertexType));

///* 队列操作函数 */
void iniQueue(QUEUE& Q);
status enQueue(QUEUE& Q, ElemType e);
status deQueue(QUEUE& Q, ElemType& e);

/* 单图基础操作函数 */
status CreateCraph(ALGraph& G, VertexType V[], KeyType VR[][2]);
status DestroyGraph(ALGraph& G);
int LocateVex(ALGraph G, KeyType u);
status PutVex(ALGraph& G, KeyType u, VertexType value);
int FirstAdjVex(ALGraph G, KeyType u);
int NextAdjVex(ALGraph G, KeyType v, KeyType w);
status InsertVex(ALGraph& G, VertexType v);
status DeleteVex(ALGraph& G, KeyType v);
status InsertArc(ALGraph& G, KeyType v, KeyType w);
status DeleteArc(ALGraph& G, KeyType v, KeyType w);
status DFSTraverse(ALGraph& G, void (*visit)(VertexType));
status BFSTraverse(ALGraph& G, void (*visit)(VertexType));

/*选做操作函数*/
VNode* VerticesSetLessThanK(ALGraph G, KeyType v, int k);
int ShortestPathLength(ALGraph G, KeyType v, KeyType w);
int ConnectedComponentsNums(ALGraph G);

/*文件读写函数*/
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph& G, char FileName[]);

/*多图操作函数*/
status AddGragh(LISTS& Lists, char ListName[]);
status RemoveGragh(LISTS& Lists, char ListName[]);
int LocateGragh(LISTS Lists, char ListName[]);
status ListsTraverse(LISTS Lists);
ALGraph* ChooseGragh(ALGraph* L, LISTS& Lists, int i);













/*---------------------main函数-----------------------*/
int main(void)
{
    //定义单图并初始化
    ALGraph G1;
    ALGraph* G = &G1;
    G->arcnum = 0;
    G->vexnum = 0;
    memset(G->vertices, 0, MAX_VERTEX_NUM * sizeof(VNode));

    //定义管理表并初始化
    LISTS Lists;
    Lists.length = 0, Lists.listsize = 10;

    //op记录功能选择情况,flag记录功能运行情况,i与k存储int型过程量,u与v存储关键字过程量
    int op = 1, flag = 0, i = 0, k = 0, u = 0, v = 0;
    char FileName[30], ListName[30]; //储存文件名与表名
    VertexType value;   //存储顶点过程量
    VertexType V[30];   //存储顶点序列
    KeyType VR[100][2]; //存储关系对序列
    VNode* VN = NULL;   //存储顶点集合过程量，用于main函数中接收函数13的返回值 

    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Undirected Graph On Adjacency List   \n");
        printf("------------------------------------------------------\n");
        printf("          1. 创建            12. 广搜遍历\n");
        printf("          2. 销毁            13. 求距离小于k的顶点集合\n");
        printf("          3. 查找顶点        14. 求顶点间最短路径长度\n");
        printf("          4. 顶点赋值        15. 求连通分量个数\n");
        printf("          5. 获得第一邻接点  16. 写入文件\n");
        printf("          6. 获得下一邻接点  17. 读取文件\n");
        printf("          7. 插入顶点        18. 增加图\n");
        printf("          8. 删除顶点        19. 删除图\n");
        printf("          9. 插入弧          20. 查找图\n");
        printf("         10. 删除弧          21. 遍历总表\n");
        printf("         11. 深搜遍历        22. 选择单图进行操作\n");
        printf("          0. 退出\n");
        printf("------------------------------------------------------\n");
        printf("    请选择你的操作[0~22]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1://创建
            if (G->vexnum)
                printf("创建失败!图已存在!\n");
            else
            {
                i = 0;
                printf("顶点格式示例: 1 线性表 3 二叉树\n");
                printf("以-1 nil作为结束标记\n");
                printf("空图不予创建\n");
                printf("请据此输入将建图中的顶点序列:");
                do {
                    scanf("%d %s", &V[i].key, V[i].others);
                } while (V[i++].key != -1);
                i = 0;
                printf("关系对格式示例: 1 3\n");
                printf("以-1 -1作为结束标记\n");
                printf("请据此输入将建图中的关系对序列:");
                do {
                    scanf("%d %d", &VR[i][0], &VR[i][1]);
                } while (VR[i++][0] != -1);
                flag = CreateCraph(*G, V, VR);
                if (flag == OK)
                    printf("无向图创建成功!\n这是一个与独立于多图的单图,你可以对它进行1~17操作!\n");
                else
                    printf("创建失败!顶点序列或关系对序列输入有误!\n");
            }
            getchar();getchar();
            break;
        case 2://销毁
            flag = DestroyGraph(*G);
            if (flag == OK)
                printf("成功销毁无向图并释放数据元素的空间!\n");
            else if (flag == INFEASIBLE)
                printf("不能对不存在的无向图进行销毁操作!\n");
            getchar();getchar();
            break;
        case 3://查找顶点
            if (!G->vexnum)
                printf("不能对不存在的无向图进行查找操作!\n");
            else
            {
                printf("请输入想要查找的关键字:");
                scanf("%d", &u);
                flag = LocateVex(*G, u);
                if (flag == -1)
                    printf("含关键字 %d 的顶点不存在!\n", u);
                else
                    printf("含关键字 %d 的顶点位序为 %d!", u, flag);
            }
            getchar();getchar();
            break;
        case 4://顶点赋值
            if (!G->vexnum)
                printf("不能对不存在的无向图进行赋值操作!\n");
            else
            {
                printf("请输入想要赋值的顶点的关键字用于查找:");
                scanf("%d", &u);
                printf("请输入将赋的关键字与内容:");
                scanf("%d%s", &value.key, value.others);
                flag = PutVex(*G, u, value);
                if (flag == OK)
                    printf("赋值成功!\n");
                else
                    printf("赋值失败!关键字不存在或将赋关键字不唯一!\n");
            }
            getchar();getchar();
            break;
        case 5://获得第一邻接点
            if (!G->vexnum)
                printf("不能对不存在的无向图进行该操作!\n");
            else
            {
                printf("请输入想要求第一邻接点的顶点的关键字:");
                scanf("%d", &u);
                flag = FirstAdjVex(*G, u);
                if (flag == -1)
                    printf("操作失败!关键字不存在或该顶点不存在邻接点!\n");
                else
                    printf("关键字为 %d 的顶点的第一邻接点是位序为 %d 的 %d %s!\n", u, flag, G->vertices[flag].data.key, G->vertices[flag].data.others);
            }
            getchar();getchar();
            break;
        case 6://获得下一邻接点
            if (!G->vexnum)
                printf("不能对不存在的无向图进行该操作!\n");
            else
            {
                printf("请输入一个顶点和它的一个邻接点的关键字:");
                scanf("%d%d", &u, &v);
                flag = NextAdjVex(*G, u, v);
                if (flag == -1)
                    printf("操作失败!关键字不存在或该邻接点已是最后一个!\n");
                else
                    printf("顶点 %d 的邻接点 %d 的下一邻接点是位序为 %d 的 %d %s!\n", u, v, flag, G->vertices[flag].data.key, G->vertices[flag].data.others);
            }
            getchar();getchar();
            break;
        case 7://插入顶点
            if (!G->vexnum)
                printf("不能对不存在的无向图进行该操作!\n");
            else
            {
                printf("请输入将插入的关键字与内容:");
                scanf("%d%s", &value.key, value.others);
                flag = InsertVex(*G, value);
                if (flag == OK)
                    printf("插入成功!\n");
                else
                    printf("插入失败!顶点数目已达最大值或关键字已存在!\n");
            }
            getchar();getchar();
            break;
        case 8://删除顶点
            if (!G->vexnum)
                printf("不能对不存在的无向图进行该操作!\n");
            else
            {
                printf("请输入将删除的结点的关键字:");
                scanf("%d", &u);
                flag = DeleteVex(*G, u);
                if (flag == OK)
                    printf("删除成功!与该顶点相关的弧已删除!\n");
                else
                    printf("删除失败!关键字不存在或顶点数目为1!\n");
            }
            getchar();getchar();
            break;
        case 9://插入弧
            if (!G->vexnum)
                printf("不能对不存在的无向图进行该操作!\n");
            else
            {
                printf("请分别输入将插入的弧的两个顶点的关键字:");
                scanf("%d%d", &u, &v);
                flag = InsertArc(*G, u, v);
                if (flag == OK)
                    printf("插入成功!\n");
                else
                    printf("插入失败!关键字不存在或弧已存在!\n");
            }
            getchar();getchar();
            break;
        case 10://删除弧
            if (!G->vexnum)
                printf("不能对不存在的无向图进行该操作!\n");
            else
            {
                printf("请分别输入将删除的弧的两个顶点的关键字:");
                scanf("%d%d", &u, &v);
                flag = DeleteArc(*G, u, v);
                if (flag == OK)
                    printf("删除成功!\n");
                else
                    printf("删除失败!关键字不存在或弧不存在!\n");
            }
            getchar();getchar();
            break;
        case 11://深搜遍历
            if (!G->vexnum)
                printf("不能对不存在的无向图进行遍历操作!\n");
            else
                DFSTraverse(*G, visit);
            getchar();getchar();
            break;
        case 12://广搜遍历
            if (!G->vexnum)
                printf("不能对不存在的无向图进行遍历操作!\n");
            else
                BFSTraverse(*G, visit);
            getchar();getchar();
            break;
        case 13://求距离小于k的顶点集合
            if (!G->vexnum)
                printf("不能对不存在的无向图进行该操作!\n");
            else
            {
                printf("请输入一个顶点的关键字:");
                scanf("%d", &u);
                printf("请输入距离k:");
                scanf("%d", &k);
                VN = VerticesSetLessThanK(*G, u, k);
                if (VN == NULL)
                    printf("操作失败!关键字输入有误!\n");
                else
                {
                    if (VN[0].data.key == 0)
                        printf("集合为空!");
                    else
                    {
                        printf("与关键字为 %d 的顶点距离小于 %d 的顶点集合为:", u, k);
                        for (i = 0; VN[i].data.key != 0; i++)
                            printf("%d %s ", VN[i].data.key, VN[i].data.others);
                    }
                }
            }
            getchar();getchar();
            break;
        case 14://求顶点间最短路径长度
            if (!G->vexnum)
                printf("不能对不存在的无向图进行该操作!\n");
            else
            {
                printf("请输入两个顶点的关键字:");
                scanf("%d%d", &u, &v);
                flag = ShortestPathLength(*G, u, v);
                if (flag == -1)
                    printf("操作失败!关键字不存在或两顶点间不存在路径!\n");
                else
                    printf("关键字为 %d 和 %d 的顶点间最短路径长度为 %d!\n", u, v, flag);
            }
            getchar();getchar();
            break;
        case 15://求连通分量个数
            if (!G->vexnum)
                printf("不能对不存在的无向图进行该操作!\n");
            else
            {
                flag = ConnectedComponentsNums(*G);
                printf("\n该图的连通分量个数为 %d!\n", flag);
            }
            getchar();getchar();
            break;
        case 16://写入文件
            if (!G->vexnum)
                printf("不能对不存在的无向图进行该操作!\n");
            else
            {
                printf("请输入文件名称:");
                scanf("%s", FileName);
                flag = SaveGraph(*G, FileName);
                if (flag == ERROR)
                    printf("文件打开失败!\n");
                else
                    printf("无向图的内容已经复制到名称为 %s 的文件中!\n", FileName);
            }
            getchar();getchar();
            break;
        case 17://读取文件
            if (G->vexnum)
                printf("不能对已存在的无向图进行读文件操作!请先销毁无向图!\n");
            else
            {
                printf("请输入文件名称:");
                scanf("%s", FileName);
                flag = LoadGraph(*G, FileName);
                if (flag == ERROR)
                    printf("文件打开失败!\n");
                else
                    printf("名称为 %s 的文件中内容已复制到无向图中!\n", FileName);
            }
            getchar();getchar();
            break;
        case 18://增加图
            printf("请输入新增无向图的名称:");
            scanf("%s", ListName);
            flag = AddGragh(Lists, ListName);
            if (flag == OK)
                printf("成功新增名称为 %s 的无向图!\n", ListName);
            else
                printf("新增失败!\n");
            getchar();getchar();
            break;
        case 19://删除图
            if (Lists.length)
            {
                printf("\n--------------- all graphs --------------------\n");
                for (int i = 0; i < Lists.length; i++)
                    printf("%d %s\n", i + 1, Lists.elem[i].name);
                printf("------------------ end ------------------------\n");
            }
            else
            {
                printf("无向图的集合为空!无法进行此操作!\n");
                getchar();getchar();
                break;
            }
            printf("请输入想要删除的无向图的名称:");
            scanf("%s", ListName);
            flag = RemoveGragh(Lists, ListName);
            if (flag == OK)
                printf("成功删除名称为 %s 的无向图!\n", ListName);
            else
                printf("删除失败!\n");
            getchar();getchar();
            break;
        case 20://查找图
            if (!Lists.length)
            {
                printf("无向图的集合为空!无法进行此操作!\n");
                getchar();getchar();
                break;
            }
            printf("请输入想要查找的无向图的名称:");
            scanf("%s", ListName);
            flag = LocateGragh(Lists, ListName);
            if (!flag)
                printf("不存在名称为 %s 的无向图!\n", ListName);
            else
                printf("名称为 %s 的无向图的序号为 %d!\n", ListName, flag);
            getchar();getchar();
            break;
        case 21://遍历总表
            if (ListsTraverse(Lists) == ERROR)
                printf("无向图的集合为空!\n");
            getchar();getchar();
            break;
        case 22://选择单图进行操作
            if (Lists.length)
            {
                printf("\n--------------- all grapghs --------------------\n");
                for (int i = 0; i < Lists.length; i++)
                    printf("%d %s\n", i + 1, Lists.elem[i].name);
                printf("------------------ end ------------------------\n");
            }
            else
            {
                printf("无向图的集合为空!无法进行此操作!\n");
                getchar();getchar();
                break;
            }
            printf("请输入想要操作的无向图的序号(从1开始):");
            scanf("%d", &flag);
            G = ChooseGragh(G, Lists, flag);
            if (G == NULL)
                printf("输入序号不合法!单图已置空!\n");
            else
                printf("下面可对无向图集合中序号为 %d 的无向图进行操作!\n", flag);
            getchar();getchar();
            break;
        case 0:
            break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}
/*---------------------main函数-----------------------*/
