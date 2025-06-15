#include "1def.h"
#include "1fun.h"

/*-----page 19 on textbook ---------*/
status InitList(SqList* L, const char* name);
status DestroyList(SqList* L);
status ClearList(SqList* L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L, int i, ElemType* e);
int LocateElem(SqList L, ElemType e); //简化过
status PriorElem(SqList L, ElemType e, ElemType* pre);
status NextElem(SqList L, ElemType e, ElemType* next);
status ListInsert(SqList* L, int i, ElemType e);
status ListDelete(SqList* L, int i, ElemType* e);
status ListTrabverse(SqList L);  //简化过

/*-----新增功能函数声明-----*/
int MaxSubArray(SqList L);
int SubArrayNum(SqList L, int k);
status sortList(SqList* L);
status saveListToFile(SqList L, const char* filename);
status loadListFromFile(SqList* L, const char* filename);
status initMultiListManager(MultiListManager* manager);
status addNewList(MultiListManager* manager, const char* name);
status removeList(MultiListManager* manager, int index);
status switchToListByName(MultiListManager* manager, const char* name);
int findListIndexByName(MultiListManager* manager, const char* name);
void printListNames(MultiListManager* manager);
void searchList(MultiListManager* manager);
/*--------------------------------------------*/
void main(void) {
    MultiListManager manager;
    initMultiListManager(&manager);
    //addNewList(&manager);  // 默认创建一个线性表

    int op = 1,i;
    ElemType e, pre, next;
    int k, index;
    char filename[100];
    char listName[MAX_NAME_LENGTH];

    while (op) {
        system("cls"); printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1.  初始化表\n");
        printf("    	  2.  销毁表\n");
        printf("    	  3.  清空表 \n");
        printf("    	  4.  判断空表 \n");
        printf("    	  5.  求表长度\n");
        printf("    	  6.  获取元素 \n");
        printf("    	  7.  查找元素位置 \n");
        printf("    	  8.  获取前驱元素 \n");
        printf("    	  9.  获取后继元素 \n");
        printf("    	  10. 插入元素\n");
        printf("    	  11. 删除元素\n");
        printf("    	  12. 遍历表\n");
        printf("    	  13. 最大子数组和\n");
        printf("    	  14. 和为K的子数组\n");
        printf("    	  15. 排序表\n");
        printf("    	  16. 保存到文件\n");
        printf("    	  17. 从文件加载\n");
        printf("    	  18. 管理表\n");
        printf("    	  0.  退出\n");
        printf("-------------------------------------------------\n");
        if (manager.current >= 0 && manager.current < manager.count) {
            printf("当前表: %s, 表的个数有: %d\n", manager.lists[manager.current].name, manager.count);
        }
        else {
            printf("当前没有选中的表, 表的个数有: %d\n", manager.count);
        }
        printf("    请选择你的操作[0~18]:");
        scanf("%d", &op);

        SqList* currentList = NULL;
        if (manager.current >= 0 && manager.current < manager.count) {
            currentList = &manager.lists[manager.current];
        }

        switch (op) {
        case 1:
            printf("请输入线性表的名称: ");
            scanf("%s", listName);
            if (addNewList(&manager, listName) == OK) {
                printf("线性表创建成功！\n");
            }
            else {
                printf("线性表创建失败！\n");
            }
            getchar();getchar();
            break;
        case 2:
            if (manager.count == 0) {
                printf("没有线性表可销毁！\n");
            }
            else {
                if (removeList(&manager, manager.current) == OK) {
                    printf("线性表销毁成功！\n");
                }
                else {
                    printf("线性表销毁失败！\n");
                }
            }
            getchar();getchar();
            break;
        case 3:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else {
                if (ClearList(currentList) == OK) {
                    printf("线性表所有元素删除成功！\n");
                }
                else {
                    printf("线性表所有元素删除失败！\n");
                }
            }
            getchar();getchar();
            break;
        case 4:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else {
                if (ListEmpty(*currentList) == TRUE) {
                    printf("线性表为空！\n");
                }
                else {
                    printf("线性表不为空！\n");
                }
            }
            getchar();getchar();
            break;
        case 5:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else {
                if (ListLength(*currentList) > 0) {
                    printf("线性表长度为%d\n", ListLength(*currentList));
                }
                else {
                    printf("线性表为空\n");
                }
            }
            getchar();getchar();
            break;
        case 6:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else {
                printf("请输入你要获取的线性表的第几个元素：");
                int i;
                scanf("%d", &i);
                if (GetElem(*currentList, i, &e) == OK) {
                    printf("\n线性表第%d个元素为%d\n", i, e);
                }
                else if (GetElem(*currentList, i, &e) == ERROR) {
                    printf("\n线性表长度小于%d\n", i);
                }
                else {
                    printf("\n线性表不存在");
                }
            }
            getchar();getchar();
            break;
        case 7:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else {
                printf("请输入你想查找哪一个元素的位置：");
                scanf("%d", &e);
                if (LocateElem(*currentList, e) > 0) {
                    printf("\n元素%d在线性表的第%d个位置\n", e, LocateElem(*currentList, e));
                }
                else if (LocateElem(*currentList, e) == 0) {
                    printf("该元素不存在\n");
                }
                else {
                    printf("线性表不存在");
                }
            }
            getchar();getchar();
            break;
        case 8:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else {
                printf("请输入你想查找哪一个元素的前驱：");
                scanf("%d", &e);
                if (PriorElem(*currentList, e, &pre) == OK) {
                    printf("\n元素%d在线性表的前驱是%d\n", e, pre);
                }
                else if (PriorElem(*currentList, e, &pre) == ERROR) {
                    printf("没有前驱\n");
                }
                else {
                    printf("线性表不存在");
                }
            }
            getchar();getchar();
            break;
        case 9:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else {
                printf("请输入你想查找哪一个元素的后继：");
                scanf("%d", &e);
                if (NextElem(*currentList, e, &next) == OK) {
                    printf("\n元素%d在线性表的后继是%d\n", e, next);
                }
                else if (NextElem(*currentList, e, &next) == ERROR) {
                    printf("没有后继\n");
                }
                else {
                    printf("线性表不存在");
                }
            }
            getchar();getchar();
            break;
        case 10:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else {
                printf("请输入元素e的值：");
                scanf("%d", &e);
                printf("\n请输入你想把这个元素插入到线性表的第几个元素之前：");
                scanf("%d", &i);
                if (ListInsert(currentList, i, e) == OK) {
                    printf("\n插入成功！\n");
                }
                else if (ListInsert(currentList, i, e) == ERROR) {
                    printf("插入位置不正确\n");
                }
                else {
                    printf("线性表不存在");
                }
            }
            getchar();getchar();
            break;
        case 11:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else {
                printf("\n请输入你想删除线性表的第几个元素：");
                scanf("%d", &i);
                if (ListDelete(currentList, i, &e) == OK) {
                    printf("\n删除成功！\n");
                }
                else if (ListDelete(currentList, i, &e) == ERROR) {
                    printf("删除位置不正确\n");
                }
                else {
                    printf("线性表不存在");
                }
            }
            getchar();getchar();
            break;
        case 12:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else {
                if (!ListTrabverse(*currentList)) {
                    printf("线性表是空表！\n");
                }
            }
            getchar();getchar();
            break;
        case 13:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else if (ListLength(*currentList) <= 0) {
                printf("线性表不存在或为空！\n");
            }
            else {
                printf("最大连续子数组和为：%d\n", MaxSubArray(*currentList));
            }
            getchar();getchar();
            break;
        case 14:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else if (ListLength(*currentList) <= 0) {
                printf("线性表不存在或为空！\n");
            }
            else {
                printf("请输入k的值：");
                scanf("%d", &k);
                printf("和为%d的子数组个数为：%d\n", k, SubArrayNum(*currentList, k));
            }
            getchar();getchar();
            break;
        case 15:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else {
                if (sortList(currentList) == OK) {
                    printf("线性表排序成功！\n");
                }
                else {
                    printf("线性表排序失败！\n");
                }
            }
            getchar();getchar();
            break;
        case 16:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else {
                printf("请输入文件名：");
                scanf("%s", filename);
                if (saveListToFile(*currentList, filename) == OK) {
                    printf("线性表保存成功！\n");
                }
                else {
                    printf("线性表保存失败！\n");
                }
            }
            getchar();getchar();
            break;
        case 17:
            if (currentList == NULL) {
                printf("当前没有选中的表！\n");
            }
            else {
                printf("请输入文件名：");
                scanf("%s", filename);
                if (loadListFromFile(currentList, filename) == OK) {
                    printf("线性表加载成功！\n");
                }
                else {
                    printf("线性表加载失败！\n");
                }
            }
            getchar();getchar();
            break;
        case 18:
            while (op) {
                system("cls");
                printf("      线性表的管理 \n");
                printf("-------------------------------------------------\n");
                printf("    	  1.  添加新表 \n");
                printf("    	  2.  移除表 \n");
                printf("    	  3.  切换表 \n");
                printf("    	  4.  显示所有表名 \n");
                printf("    	  5.  搜索表 \n");
                printf("    	  0.  退出\n");
                printf("-------------------------------------------------\n");
                printf("当前表的个数有: %d\n", manager.count);
                if (manager.current >= 0 && manager.current < manager.count) {
                    printf("当前表: %s\n", manager.lists[manager.current].name);
                }
                printf("    请选择你的操作[0~4]:");
                scanf("%d", &op);
                switch (op) {
                case 1:
                    printf("请输入新线性表的名称: ");
                    scanf("%s", listName);
                    if (addNewList(&manager, listName) == OK) {
                        printf("新线性表创建成功！当前共有%d个线性表\n", manager.count);
                    }
                    else {
                        printf("创建新线性表失败！\n");
                    }
                    getchar();getchar();
                    break;
                case 2:
                    printListNames(&manager);
                    printf("请输入要删除的线性表名称：");
                    scanf("%s", listName);
                    index = findListIndexByName(&manager, listName);
                    if (index != -1) {
                        if (removeList(&manager, index) == OK) {
                            printf("线性表删除成功！当前共有%d个线性表\n", manager.count);
                        }
                        else {
                            printf("删除线性表失败！\n");
                        }
                    }
                    else {
                        printf("找不到名为'%s'的线性表！\n", listName);
                    }
                    getchar();getchar();
                    break;
                case 3:
                    printListNames(&manager);
                    printf("请输入要切换到的线性表名称：");
                    scanf("%s", listName);
                    if (switchToListByName(&manager, listName) == OK) {
                        printf("已切换到线性表'%s'！\n", listName);
                    }
                    else {
                        printf("切换线性表失败！找不到名为'%s'的线性表\n", listName);
                    }
                    getchar();getchar();
                    break;
                case 4:
                    printListNames(&manager);
                    getchar();getchar();
                    break;
                case 5: // 新增：处理搜索表的逻辑
                    searchList(&manager);
                    getchar();getchar();
                    break;
                case 0:
                    break;
                }
            }
            op = 1;
            break;
        case 0:
            break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
}

