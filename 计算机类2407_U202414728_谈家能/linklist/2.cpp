#include "2def.h"
#include "2func.h"
status Compare(ElemType e, ElemType elem);
void visit(ElemType elem);

status(*CompareArr)(ElemType e, ElemType elem) = Compare;
void (*visitArr)(ElemType elem) = visit;

status InitList(LinkList& L);
status DestroyList(LinkList& L);
status ClearList(LinkList& L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L, int i, ElemType& e);
int LocateElem(LinkList L, ElemType e, status(*CompareArr)(ElemType, ElemType));
status PriorElem(LinkList L, ElemType cur, ElemType& pre_e);
status NextElem(LinkList L, ElemType cur, ElemType& next_e);
status ListInsert(LinkList& L, int i, ElemType e);
status ListDelete(LinkList& L, int i, ElemType& e);
status ListTraverse(LinkList L, void (*visitArr)(ElemType));
status reverseList(LinkList& L);
int RemoveNthFromEnd(LinkList& L, int n);
status sortList(LinkList& L);
status SaveList(LinkList L, char FileName[]);
status LoadList(LinkList& L, char FileName[]);
status AddList(LISTS& Lists, char ListName[]);
status RemoveList(LISTS& Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);
status ListsTraverse(LISTS Lists);
LinkList* ChooseList(LinkList* L, LISTS& Lists, int i);



int main(void)
{
    //定义单表并初始化
    LinkList L1 = NULL;
    LinkList* L = &L1;

    //定义管理表并初始化
    LISTS Lists;
    Lists.length = 0, Lists.listsize = 0;

    int op = 1, len, flag, i, e, pre, next, num, k;
    char FileName[30], ListName[30];
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("       Menu for Linear Table On Linked Structure \n");
        printf("------------------------------------------------------\n");
        printf("          1. 创建         12. 遍历\n");
        printf("          2. 销毁         13. 翻转链表\n");
        printf("          3. 清空         14. 删除链表倒数第n个结点\n");
        printf("          4. 判空         15. 排序\n");
        printf("          5. 求长         16. 写入文件\n");
        printf("          6. 获取元素     17. 读取文件\n");
        printf("          7. 查找元素     18. 增加线性表\n");
        printf("          8. 获取前驱     19. 删除线性表\n");
        printf("          9. 获取后继     20. 查找线性表\n");
        printf("         10. 输入元素     21. 遍历总表\n");
        printf("         11. 删除元素     22. 选择单表进行操作\n");
        printf("          0. 退出\n");
        printf("------------------------------------------------------\n");
        printf("    请选择你的操作[0~22]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1://创建
            if (InitList(*L) == OK)
                printf("线性表创建成功！\n这是一个与独立于多表的单表，你可以对它进行1~17操作！\n");
            else
                printf("线性表创建失败！\n");
            getchar();getchar();
            break;
        case 2://销毁
            if (DestroyList(*L) == OK)
                printf("成功销毁线性表并释放数据元素的空间！\n");
            else
                printf("不能对不存在的线性表进行销毁操作！\n");
            getchar();getchar();
            break;
        case 3://清空
            if (ClearList(*L) == OK)
                printf("成功删除线性表中所有的元素！\n");
            else
                printf("不能对不存在的线性表进行清空操作！\n");
            getchar();getchar();
            break;
        case 4://判空
            flag = ListEmpty(*L);
            if (flag == TRUE)
                printf("线性表为空！\n");
            else if (flag == FALSE)
                printf("线性表非空！\n");
            else
                printf("不能对不存在的线性表判空！\n");
            getchar();getchar();
            break;
        case 5://求长
            len = ListLength(*L);
            if (len >= 0)
                printf("线性表的长度为%d！\n", len);
            else
                printf("不能对不存在的线性表求长！\n");
            getchar();getchar();
            break;
        case 6://获取元素
            printf("请输入想要从线性表中获取的元素序号：");
            scanf("%d", &i);
            getchar();
            flag = GetElem(*L, i, e);
            if (flag == OK)
                printf("线性表中第%d个元素为%d！\n", i, e);
            else if (flag == ERROR)
                printf("输入的序号不合法！\n");
            else
                printf("不能对不存在的线性表进行此操作！\n");
            getchar();getchar();
            break;
        case 7://查找元素
            printf("请输入想要在线性表中查找的元素：");
            scanf("%d", &e);
            getchar();
            flag = LocateElem(*L, e, Compare);
            if (flag == 0)
                printf("线性表中不存在%d这个元素。\n", e);
            else if (flag == INFEASIBLE)
                printf("不能对不存在的线性表进行此操作！\n");
            else
                printf("元素%d在线性表中的序号为%d\n", e, flag);
            getchar();getchar();
            break;
        case 8://查找前驱
            printf("请输入想要在线性表中查找其前驱的元素：");
            scanf("%d", &e);
            getchar();
            flag = PriorElem(*L, e, pre);
            if (flag == OK)
                printf("元素%d在线性表中的前驱为%d！\n", e, pre);
            else if (flag == ERROR)
                printf("元素%d在线性表中没有前驱！\n", e);
            else
                printf("不能对不存在的线性表进行此操作！\n");
            getchar();getchar();
            break;
        case 9://查找后继
            printf("请输入想要在线性表中查找其后继的元素：");
            scanf("%d", &e);
            getchar();
            flag = NextElem(*L, e, next);
            if (flag == OK)
                printf("元素%d在线性表中的后继为%d！\n", e, next);
            else if (flag == ERROR)
                printf("元素%d在线性表中没有后继！\n", e);
            else
                printf("不能对不存在的线性表进行此操作！\n");
            getchar();getchar();
            break;
        case 10://输入元素
            printf("1.插入单个元素\n2.在表尾输入多个元素\n请选择将要进行的操作：");
            scanf("%d", &flag);
            getchar();
            switch (flag)
            {
            case 1:
                printf("请输入该元素：");
                scanf("%d", &e);
                getchar();
                printf("请输入想要它作为第几个元素：");
                scanf("%d", &i);
                getchar();
                flag = ListInsert(*L, i, e);
                if (flag == OK)
                    printf("元素已插入线性表中！\n");
                else if (flag == ERROR)
                    printf("位置插入非法！\n");
                else
                    printf("不能对不存在的线性表进行插入！\n");
                break;
            case 2:
                printf("请输入元素个数：");
                scanf("%d", &num);
                getchar();
                printf("请输入这些元素，以空格间隔：");
                LNode* p = *L;
                for (; p->next != NULL; p = p->next)
                    ;
                for (int i = 0; i < num; i++)
                {
                    p->next = (LNode*)malloc(sizeof(LNode));
                    p = p->next;
                    scanf("%d", &p->data);
                    p->next = NULL;
                }
                getchar();
                printf("元素已输入于线性表中！\n");
                break;
            }
            getchar();getchar();
            break;
        case 11://删除元素
            printf("请输入想要删除的元素序号：");
            scanf("%d", &i);
            getchar();
            flag = ListDelete(*L, i, e);
            if (flag == OK)
                printf("序号为 %d 的元素 %d 已经从线性表中删除！\n", i, e);
            else if (flag == ERROR)
                printf("位置输入非法！\n");
            else
                printf("不能对不存在的线性表进行删除！\n");
            getchar();getchar();
            break;
        case 12://遍历
            if (ListTraverse(*L, visit) == INFEASIBLE)
                printf("不能对不存在的线性表进行遍历！\n");
            getchar();getchar();
            break;
        case 13://翻转链表
            flag = reverseList(*L);
            if (flag == OK)
                printf("当前链表已翻转！\n");
            else
                printf("不能对不存在的线性表进行翻转！\n");
            getchar();getchar();
            break;
        case 14://删除倒数第n个结点
            int n;
            printf("本功能实现删除链表倒数第n个结点，请输入n：");
            scanf("%d", &n);
            flag = RemoveNthFromEnd(*L, n);
            if (flag == INFEASIBLE)
                printf("不能对不存在的线性表进行删除操作！\n");
            else if (flag == ERROR)
                printf("不能对空线性表进行删除操作或n不合法！\n");
            else
                printf("链表倒数第 %d 个元素 %d 已被删除！\n", n, flag);
            getchar();getchar();
            break;
        case 15://排序
            flag = sortList(*L);
            if (flag == INFEASIBLE)
                printf("不能对不存在的线性表进行排序！\n");
            else
                printf("线性表已从小到大排序！\n");
            getchar();getchar();
            break;
        case 16://写入文件
            printf("请输入文件名称：");
            scanf("%s", FileName);
            flag = SaveList(*L, FileName);
            if (flag == ERROR)
                printf("文件打开失败！\n");
            else if (flag == OK)
                printf("线性表的内容已经复制到名称为 %s 的文件中！\n", FileName);
            else if (flag == INFEASIBLE)
                printf("不能对不存在的线性表进行进行写文件操作！\n");
            getchar();getchar();
            break;
        case 17://读取文件
            printf("请输入文件名称：");
            scanf("%s", FileName);
            flag = LoadList(*L, FileName);
            if (flag == ERROR)
                printf("文件打开失败！\n");
            else if (flag == OK)
                printf("名称为 %s 的文件中的内容已复制到线性表中！\n", FileName);
            else if (flag == INFEASIBLE)
                printf("不能对已存在的线性表进行进行读文件操作！请先销毁线性表！\n");
            else if (flag == OVERFLOW)
                printf("溢出！\n");
            getchar();getchar();
            break;
        case 18://新增线性表
            printf("请输入新增线性表的名称：");
            scanf("%s", ListName);
            flag = AddList(Lists, ListName);
            if (flag == OK)
                printf("成功新增名称为 %s 的线性表！\n", ListName);
            else
                printf("新增失败！\n");
            getchar();getchar();
            break;
        case 19://删除线性表
            if (Lists.length)
            {
                printf("\n---------------- all lists --------------------\n");
                for (int i = 0; i < Lists.length; i++)
                    printf("%d %s\n", i + 1, Lists.elem[i].name);
                printf("------------------ end ------------------------\n");
            }
            else
            {
                printf("线性表的集合为空！无法进行此操作！\n");
                getchar();getchar();
                break;
            }
            printf("请输入想要删除的线性表的名称：");
            scanf("%s", ListName);
            flag = RemoveList(Lists, ListName);
            if (flag == OK)
                printf("成功删除名称为 %s 的线性表！\n", ListName);
            else if (flag == ERROR)
                printf("删除失败！\n");
            getchar();getchar();
            break;
        case 20://查找线性表
            if (!Lists.length)
            {
                printf("线性表的集合为空！无法进行此操作！\n");
                getchar();getchar();
                break;
            }
            printf("请输入想要查找的线性表的名称：");
            scanf("%s", ListName);
            i = LocateList(Lists, ListName);
            if (i == 0)
                printf("不存在名称为 %s 的线性表！\n", ListName);
            else printf("名称为 %s 的线性表的序号为 %d ！\n", ListName, i);
            getchar();getchar();
            break;
        case 21://遍历总表
            flag = ListsTraverse(Lists);
            if (flag == ERROR)
                printf("线性表的集合为空！\n");
            getchar();getchar();
            break;
        case 22://选择多表中的表进行单独操作
            if (Lists.length)
            {
                printf("\n---------------- all lists --------------------\n");
                for (int i = 0; i < Lists.length; i++)
                    printf("%d %s\n", i + 1, Lists.elem[i].name);
                printf("------------------ end ------------------------\n");
            }
            else
            {
                printf("线性表的集合为空！无法进行此操作！\n");
                getchar();getchar();
                break;
            }
            printf("请输入想要进行操作的线性表的序号（从1开始）：");
            scanf("%d", &i);
            getchar();
            L = ChooseList(L, Lists, i);
            if (L == NULL)
                printf("输入的序号不合法！单表已置空！\n");
            else
                printf("下面可对线性表集合中序号为 %d 的线性表进行操作！\n", i);
            getchar();getchar();
            break;
        case 0:
            break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}

