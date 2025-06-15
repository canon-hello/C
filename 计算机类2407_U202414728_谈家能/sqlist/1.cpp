#include "1def.h"
#include "1fun.h"

/*-----page 19 on textbook ---------*/
status InitList(SqList* L, const char* name);
status DestroyList(SqList* L);
status ClearList(SqList* L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L, int i, ElemType* e);
int LocateElem(SqList L, ElemType e); //�򻯹�
status PriorElem(SqList L, ElemType e, ElemType* pre);
status NextElem(SqList L, ElemType e, ElemType* next);
status ListInsert(SqList* L, int i, ElemType e);
status ListDelete(SqList* L, int i, ElemType* e);
status ListTrabverse(SqList L);  //�򻯹�

/*-----�������ܺ�������-----*/
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
    //addNewList(&manager);  // Ĭ�ϴ���һ�����Ա�

    int op = 1,i;
    ElemType e, pre, next;
    int k, index;
    char filename[100];
    char listName[MAX_NAME_LENGTH];

    while (op) {
        system("cls"); printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1.  ��ʼ����\n");
        printf("    	  2.  ���ٱ�\n");
        printf("    	  3.  ��ձ� \n");
        printf("    	  4.  �жϿձ� \n");
        printf("    	  5.  �����\n");
        printf("    	  6.  ��ȡԪ�� \n");
        printf("    	  7.  ����Ԫ��λ�� \n");
        printf("    	  8.  ��ȡǰ��Ԫ�� \n");
        printf("    	  9.  ��ȡ���Ԫ�� \n");
        printf("    	  10. ����Ԫ��\n");
        printf("    	  11. ɾ��Ԫ��\n");
        printf("    	  12. ������\n");
        printf("    	  13. ����������\n");
        printf("    	  14. ��ΪK��������\n");
        printf("    	  15. �����\n");
        printf("    	  16. ���浽�ļ�\n");
        printf("    	  17. ���ļ�����\n");
        printf("    	  18. �����\n");
        printf("    	  0.  �˳�\n");
        printf("-------------------------------------------------\n");
        if (manager.current >= 0 && manager.current < manager.count) {
            printf("��ǰ��: %s, ��ĸ�����: %d\n", manager.lists[manager.current].name, manager.count);
        }
        else {
            printf("��ǰû��ѡ�еı�, ��ĸ�����: %d\n", manager.count);
        }
        printf("    ��ѡ����Ĳ���[0~18]:");
        scanf("%d", &op);

        SqList* currentList = NULL;
        if (manager.current >= 0 && manager.current < manager.count) {
            currentList = &manager.lists[manager.current];
        }

        switch (op) {
        case 1:
            printf("���������Ա������: ");
            scanf("%s", listName);
            if (addNewList(&manager, listName) == OK) {
                printf("���Ա����ɹ���\n");
            }
            else {
                printf("���Ա���ʧ�ܣ�\n");
            }
            getchar();getchar();
            break;
        case 2:
            if (manager.count == 0) {
                printf("û�����Ա�����٣�\n");
            }
            else {
                if (removeList(&manager, manager.current) == OK) {
                    printf("���Ա����ٳɹ���\n");
                }
                else {
                    printf("���Ա�����ʧ�ܣ�\n");
                }
            }
            getchar();getchar();
            break;
        case 3:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else {
                if (ClearList(currentList) == OK) {
                    printf("���Ա�����Ԫ��ɾ���ɹ���\n");
                }
                else {
                    printf("���Ա�����Ԫ��ɾ��ʧ�ܣ�\n");
                }
            }
            getchar();getchar();
            break;
        case 4:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else {
                if (ListEmpty(*currentList) == TRUE) {
                    printf("���Ա�Ϊ�գ�\n");
                }
                else {
                    printf("���Ա�Ϊ�գ�\n");
                }
            }
            getchar();getchar();
            break;
        case 5:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else {
                if (ListLength(*currentList) > 0) {
                    printf("���Ա���Ϊ%d\n", ListLength(*currentList));
                }
                else {
                    printf("���Ա�Ϊ��\n");
                }
            }
            getchar();getchar();
            break;
        case 6:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else {
                printf("��������Ҫ��ȡ�����Ա�ĵڼ���Ԫ�أ�");
                int i;
                scanf("%d", &i);
                if (GetElem(*currentList, i, &e) == OK) {
                    printf("\n���Ա��%d��Ԫ��Ϊ%d\n", i, e);
                }
                else if (GetElem(*currentList, i, &e) == ERROR) {
                    printf("\n���Ա���С��%d\n", i);
                }
                else {
                    printf("\n���Ա�����");
                }
            }
            getchar();getchar();
            break;
        case 7:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else {
                printf("���������������һ��Ԫ�ص�λ�ã�");
                scanf("%d", &e);
                if (LocateElem(*currentList, e) > 0) {
                    printf("\nԪ��%d�����Ա�ĵ�%d��λ��\n", e, LocateElem(*currentList, e));
                }
                else if (LocateElem(*currentList, e) == 0) {
                    printf("��Ԫ�ز�����\n");
                }
                else {
                    printf("���Ա�����");
                }
            }
            getchar();getchar();
            break;
        case 8:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else {
                printf("���������������һ��Ԫ�ص�ǰ����");
                scanf("%d", &e);
                if (PriorElem(*currentList, e, &pre) == OK) {
                    printf("\nԪ��%d�����Ա��ǰ����%d\n", e, pre);
                }
                else if (PriorElem(*currentList, e, &pre) == ERROR) {
                    printf("û��ǰ��\n");
                }
                else {
                    printf("���Ա�����");
                }
            }
            getchar();getchar();
            break;
        case 9:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else {
                printf("���������������һ��Ԫ�صĺ�̣�");
                scanf("%d", &e);
                if (NextElem(*currentList, e, &next) == OK) {
                    printf("\nԪ��%d�����Ա�ĺ����%d\n", e, next);
                }
                else if (NextElem(*currentList, e, &next) == ERROR) {
                    printf("û�к��\n");
                }
                else {
                    printf("���Ա�����");
                }
            }
            getchar();getchar();
            break;
        case 10:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else {
                printf("������Ԫ��e��ֵ��");
                scanf("%d", &e);
                printf("\n��������������Ԫ�ز��뵽���Ա�ĵڼ���Ԫ��֮ǰ��");
                scanf("%d", &i);
                if (ListInsert(currentList, i, e) == OK) {
                    printf("\n����ɹ���\n");
                }
                else if (ListInsert(currentList, i, e) == ERROR) {
                    printf("����λ�ò���ȷ\n");
                }
                else {
                    printf("���Ա�����");
                }
            }
            getchar();getchar();
            break;
        case 11:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else {
                printf("\n����������ɾ�����Ա�ĵڼ���Ԫ�أ�");
                scanf("%d", &i);
                if (ListDelete(currentList, i, &e) == OK) {
                    printf("\nɾ���ɹ���\n");
                }
                else if (ListDelete(currentList, i, &e) == ERROR) {
                    printf("ɾ��λ�ò���ȷ\n");
                }
                else {
                    printf("���Ա�����");
                }
            }
            getchar();getchar();
            break;
        case 12:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else {
                if (!ListTrabverse(*currentList)) {
                    printf("���Ա��ǿձ�\n");
                }
            }
            getchar();getchar();
            break;
        case 13:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else if (ListLength(*currentList) <= 0) {
                printf("���Ա����ڻ�Ϊ�գ�\n");
            }
            else {
                printf("��������������Ϊ��%d\n", MaxSubArray(*currentList));
            }
            getchar();getchar();
            break;
        case 14:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else if (ListLength(*currentList) <= 0) {
                printf("���Ա����ڻ�Ϊ�գ�\n");
            }
            else {
                printf("������k��ֵ��");
                scanf("%d", &k);
                printf("��Ϊ%d�����������Ϊ��%d\n", k, SubArrayNum(*currentList, k));
            }
            getchar();getchar();
            break;
        case 15:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else {
                if (sortList(currentList) == OK) {
                    printf("���Ա�����ɹ���\n");
                }
                else {
                    printf("���Ա�����ʧ�ܣ�\n");
                }
            }
            getchar();getchar();
            break;
        case 16:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else {
                printf("�������ļ�����");
                scanf("%s", filename);
                if (saveListToFile(*currentList, filename) == OK) {
                    printf("���Ա���ɹ���\n");
                }
                else {
                    printf("���Ա���ʧ�ܣ�\n");
                }
            }
            getchar();getchar();
            break;
        case 17:
            if (currentList == NULL) {
                printf("��ǰû��ѡ�еı�\n");
            }
            else {
                printf("�������ļ�����");
                scanf("%s", filename);
                if (loadListFromFile(currentList, filename) == OK) {
                    printf("���Ա���سɹ���\n");
                }
                else {
                    printf("���Ա����ʧ�ܣ�\n");
                }
            }
            getchar();getchar();
            break;
        case 18:
            while (op) {
                system("cls");
                printf("      ���Ա�Ĺ��� \n");
                printf("-------------------------------------------------\n");
                printf("    	  1.  ����±� \n");
                printf("    	  2.  �Ƴ��� \n");
                printf("    	  3.  �л��� \n");
                printf("    	  4.  ��ʾ���б��� \n");
                printf("    	  5.  ������ \n");
                printf("    	  0.  �˳�\n");
                printf("-------------------------------------------------\n");
                printf("��ǰ��ĸ�����: %d\n", manager.count);
                if (manager.current >= 0 && manager.current < manager.count) {
                    printf("��ǰ��: %s\n", manager.lists[manager.current].name);
                }
                printf("    ��ѡ����Ĳ���[0~4]:");
                scanf("%d", &op);
                switch (op) {
                case 1:
                    printf("�����������Ա������: ");
                    scanf("%s", listName);
                    if (addNewList(&manager, listName) == OK) {
                        printf("�����Ա����ɹ�����ǰ����%d�����Ա�\n", manager.count);
                    }
                    else {
                        printf("���������Ա�ʧ�ܣ�\n");
                    }
                    getchar();getchar();
                    break;
                case 2:
                    printListNames(&manager);
                    printf("������Ҫɾ�������Ա����ƣ�");
                    scanf("%s", listName);
                    index = findListIndexByName(&manager, listName);
                    if (index != -1) {
                        if (removeList(&manager, index) == OK) {
                            printf("���Ա�ɾ���ɹ�����ǰ����%d�����Ա�\n", manager.count);
                        }
                        else {
                            printf("ɾ�����Ա�ʧ�ܣ�\n");
                        }
                    }
                    else {
                        printf("�Ҳ�����Ϊ'%s'�����Ա�\n", listName);
                    }
                    getchar();getchar();
                    break;
                case 3:
                    printListNames(&manager);
                    printf("������Ҫ�л��������Ա����ƣ�");
                    scanf("%s", listName);
                    if (switchToListByName(&manager, listName) == OK) {
                        printf("���л������Ա�'%s'��\n", listName);
                    }
                    else {
                        printf("�л����Ա�ʧ�ܣ��Ҳ�����Ϊ'%s'�����Ա�\n", listName);
                    }
                    getchar();getchar();
                    break;
                case 4:
                    printListNames(&manager);
                    getchar();getchar();
                    break;
                case 5: // ������������������߼�
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
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
}

