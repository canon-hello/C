#include "3def.h"
#include "3func.h"


/* ������� */
status Compare(KeyType e, TElemType elem);  //�ȽϺ���
void visit(BiTree elem);                    //���ʺ���
int max(int x, int y);                      //��ϴ�ֵ����

/* �������ָ�� */
status(*CompareArr)(KeyType e, TElemType elem) = Compare;
void (*visitArr)(BiTree elem) = visit;

/* ���в������� */
void iniQueue(QUEUE& Q);
status enQueue(QUEUE& Q, ElemType e);
status deQueue(QUEUE& Q, ElemType& e);

/* ���������������� */
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

/*ѡ����������*/
int MaxPathSum(BiTree T);
BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2);
status InvertTree(BiTree& T);

/*�ļ���д����*/
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree& T, char FileName[]);

/*������������*/
status AddTree(LISTS& Trees, char ListName[]);
status RemoveTree(LISTS& Trees, char ListName[]);
int LocateTree(LISTS Trees, char ListName[]);
status ListsTraverse(LISTS Trees);
BiTree* ChooseTree(BiTree* T, LISTS& Trees, int i);










/*---------------------main����-----------------------*/
int main(void)
{
    //���嵥������ʼ��
    BiTree T1 = NULL;
    BiTree* T = &T1;

    //����������ʼ��
    LISTS Trees;
    Trees.length = 0, Trees.listsize = 10;

    int op = 1, flag = 0, j = 0;     //op��¼����ѡ�������flag��¼�����������
    char FileName[30], ListName[30]; //�����ļ��������
    BiTNode* BTN = NULL;             //������ʱ������
    TElemType definition[100];       //����ǰ���������
    memset(definition, 0, 100 * sizeof(TElemType));
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("       Menu for Binary Tree On BiLinked Structure \n");
        printf("------------------------------------------------------\n");
        printf("    	  1. ����         13. �������\n");
        printf("    	  2. ����         14. �������\n");
        printf("    	  3. ���         15. �����·����\n");
        printf("    	  4. �п�         16. �������������\n");
        printf("    	  5. ����         17. ��ת������\n");
        printf("    	  6. ���ҽ��     18. д���ļ�\n");
        printf("    	  7. ��㸳ֵ     19. ��ȡ�ļ�\n");
        printf("    	  8. ��ȡ�ֵ�     20. ���Ӷ�����\n");
        printf("    	  9. ������     21. ɾ��������\n");
        printf("    	 10. ɾ�����     22. ���Ҷ�����\n");
        printf("    	 11. ǰ�����     23. �����ܱ�\n");
        printf("    	 12. �������     24. ѡ�������в���\n");
        printf("    	  0. �˳�\n");
        printf("------------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~24]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1://����
            if (*T != NULL)
                printf("�������Ѵ��ڣ��޷��ٴ�����\n");
            else
            {
                flag_create = 0, k = 0;//����static����
                printf("������ǰ��������У�");
                do
                {
                    scanf("%d %s", &definition[j].key, definition[j].others);
                } while (definition[j++].key != -1);
                flag = CreateBiTree(*T, definition);
                if (flag == OK)
                    printf("�����������ɹ���\n����һ��������ڶ����ĵ���������Զ�������1~19������\n");
                else if (flag == ERROR)
                    printf("�ؼ��ʲ�Ψһ������������ʧ�ܣ�\n");
            }
            getchar();getchar();
            break;
        case 2://����
            flag = DestroyBiTree(*T);
            if (flag == OK)
                printf("�ɹ����ٶ��������ͷ�����Ԫ�صĿռ䣡\n");
            else
                printf("���ܶԲ����ڵĶ������������ٲ�����\n");
            getchar();getchar();
            break;
        case 3://���
            flag = ClearBiTree(*T);
            if (flag == OK)
                printf("�ɹ���ն�������\n");
            else
                printf("���ܶԲ����ڵĶ�����������ղ�����\n");
            getchar();getchar();
            break;
        case 4://�п�
            flag = BiTreeEmpty(*T);
            if (flag == TRUE)
                printf("������Ϊ�գ�\n");
            else if (flag == FALSE)
                printf("��������Ϊ�գ�\n");
            else
                printf("���ܶԲ����ڵĶ����������пղ�����\n");
            getchar();getchar();
            break;
        case 5://����
            // if(*T == NULL)
            //     printf("���ܶԲ����ڵĶ������������������\n");
            // else
        {
            flag = BiTreeDepth(*T);
            printf("�����������Ϊ %d��\n", flag);
        }
        getchar();getchar();
        break;
        case 6://���ҽ��
            if (*T == NULL)
                printf("���ܶԲ����ڵĶ��������в��ҽ�������\n");
            else
            {
                int e = 0;//�洢�ؼ���
                BTN = NULL;//�洢������
                printf("��������Ҫ���ҵĽ��Ĺؼ��֣�");
                scanf("%d", &e);
                BTN = LocateNode(*T, e);
                if (BTN == NULL)
                    printf("����ʧ�ܣ������ڹؼ���Ϊ %d �Ľ�㣡\n", e);
                else
                    printf("���ҳɹ����ý��ؼ���Ϊ %d������Ϊ %s��\n", BTN->data.key, BTN->data.others);
            }
            getchar();getchar();
            break;
        case 7://��㸳ֵ
            if (*T == NULL)
                printf("���ܶԲ����ڵĶ��������н�㸳ֵ������\n");
            else
            {

                int e = 0;//�洢�ؼ���
                TElemType value[5];//�洢�¹ؼ���������
                memset(value, 0, 5 * sizeof(TElemType));//��ʼ��
                printf("��������Ҫ��ֵ�Ľ��Ĺؼ��֣�");
                scanf("%d", &e);
                printf("�����뽫���Ĺؼ��������ݣ�");
                scanf("%d %s", &value->key, value->others);
                flag = Assign(*T, e, *value);
                if (flag == OK)
                    printf("��ֵ�ɹ���\n");
                else
                    printf("��ֵʧ�ܣ��ؼ����Ѵ��ڣ�\n");
            }
            getchar();getchar();
            break;
        case 8://��ȡ�ֵ�
            if (*T == NULL)
                printf("���ܶԲ����ڵĶ��������л�ȡ�ֵܲ�����\n");
            else
            {
                p = NULL;//����static����
                int e = 0;//�洢�ؼ���
                BTN = NULL;//�洢������
                printf("��������Ҫ��ȡ���ֵܽ��Ľ��Ĺؼ��֣�");
                scanf("%d", &e);
                BTN = GetSibling(*T, e);
                if (BTN == NULL)
                    printf("��ȡʧ�ܣ������ڹؼ���Ϊ %d �Ľ���ý��û���ֵܣ�\n", e);
                else
                    printf("��ȡ�ɹ����ý����ֵܽ��Ĺؼ���Ϊ %d������Ϊ %s��\n", BTN->data.key, BTN->data.others);
            }
            getchar();getchar();
            break;
        case 9://������
            if (*T == NULL)
                printf("���ܶԲ����ڵĶ��������в����������\n");
            else
            {
                int e = 0, LR = 0;//�洢�ؼ�������뷽ʽ
                printf("��������Ҫ����Ľ��ĸ����Ĺؼ��֣�");
                scanf("%d", &e);
                printf("LR = 0 ��Ϊ����\nLR = 1 ��Ϊ�Һ���\nLR = -1 ��Ϊ�����\n");
                printf("��������뷽ʽ��");
                scanf("%d", &LR);
                if (LR == -1 || LR == 0 || LR == 1)
                {
                    TElemType c[5];//�洢�¹ؼ���������
                    memset(c, 0, 5 * sizeof(TElemType));//��ʼ��
                    printf("�����뽫����Ĺؼ��������ݣ�");
                    scanf("%d %s", &c[0].key, c[0].others);
                    flag = InsertNode(*T, e, LR, c[0]);
                    if (flag == OK)
                        printf("����ɹ���\n");
                    else
                        printf("����ʧ�ܣ��ؼ����Ѵ��ڣ�\n");
                }
                else
                    printf("����ʧ�ܣ����뷽ʽ��������\n");
            }
            getchar();getchar();
            break;
        case 10://ɾ�����
            if (*T == NULL)
                printf("���ܶԲ����ڵĶ��������в����������\n");
            else
            {
                flag1 = 0;//����static����
                int e = 0;//�洢�ؼ���
                printf("��������ɾ���Ľ��Ĺؼ��֣�");
                scanf("%d", &e);
                flag = DeleteNode(*T, e);
                if (flag == OK)
                    printf("ɾ���ɹ���\n");
                else
                    printf("ɾ��ʧ�ܣ�\n");
            }
            getchar();getchar();
            break;
        case 11://ǰ�����
            if (*T == NULL)
                printf("���ܶԲ����ڵĶ���������ǰ�����������\n");
            else
            {
                printf("\n-------------- all elements -------------------\n");
                PreOrderTraverse(*T, visit);
                printf("\n------------------ end ------------------------\n");
            }
            getchar();getchar();
            break;
        case 12://�������
            if (*T == NULL)
                printf("���ܶԲ����ڵĶ����������������������\n");
            else
            {
                printf("\n-------------- all elements -------------------\n");
                InOrderTraverse(*T, visit);
                printf("\n------------------ end ------------------------\n");
            }
            getchar();getchar();
            break;
        case 13://�������
            if (*T == NULL)
                printf("���ܶԲ����ڵĶ��������к������������\n");
            else
            {
                printf("\n-------------- all elements -------------------\n");
                PostOrderTraverse(*T, visit);
                printf("\n------------------ end ------------------------\n");
            }
            getchar();getchar();
            break;
        case 14://�������
            if (*T == NULL)
                printf("���ܶԲ����ڵĶ��������в������������\n");
            else
            {
                printf("\n-------------- all elements -------------------\n");
                LevelOrderTraverse(*T, visit);
                printf("\n------------------ end ------------------------\n");
            }
            getchar();getchar();
            break;
        case 15://�����·����
            if (*T == NULL)
                printf("���ܶԲ����ڵĶ��������иò�����\n");
            else
            {
                flag = MaxPathSum(*T);
                printf("�ö��������·����Ϊ %d��", flag);
            }
            getchar();getchar();
            break;
        case 16://�������������
            if (*T == NULL)
                printf("���ܶԲ����ڵĶ��������иò�����\n");
            else
            {
                int e1 = 0, e2 = 0;//�洢�ؼ���
                BTN = NULL;//�洢������
                printf("��������������������Ĺؼ��֣�\n");
                scanf("%d %d", &e1, &e2);
                BTN = LowestCommonAncestor(*T, e1, e2);
                if (BTN == NULL)
                    printf("����ʧ�ܣ��ؼ�����������\n");
                else
                    printf("�ؼ���Ϊ %d �� %d ���������������������Ϊ %d %s��\n", e1, e2, BTN->data.key, BTN->data.others);
            }
            getchar();getchar();
            break;
        case 17://��ת������
            if (*T == NULL)
                printf("���ܶԲ����ڵĶ��������иò�����\n");
            else
                if (InvertTree(*T) == OK)
                    printf("��������ת�ɹ���");
            getchar();getchar();
            break;
        case 18://д���ļ�
            if (*T == NULL)
                printf("���ܶԲ����ڵĶ��������иò�����\n");
            else
            {
                printf("�������ļ����ƣ�");
                scanf("%s", FileName);
                flag = SaveBiTree(*T, FileName);
                if (flag == ERROR)
                    printf("�ļ���ʧ�ܣ�\n");
                else if (flag == OK)
                    printf("�������������Ѿ����Ƶ�����Ϊ %s ���ļ��У�\n", FileName);
            }
            getchar();getchar();
            break;
        case 19://��ȡ�ļ�
            printf("�������ļ����ƣ�");
            scanf("%s", FileName);
            flag = LoadBiTree(*T, FileName);
            if (flag == ERROR)
                printf("�ļ���ʧ�ܣ�\n");
            else if (flag == OK)
                printf("����Ϊ %s ���ļ��е������Ѹ��Ƶ��������У�\n", FileName);
            else if (flag == INFEASIBLE)
                printf("���ܶ��Ѵ��ڵĶ��������н��ж��ļ��������������ٶ�������\n");
            else if (flag == OVERFLOW)
                printf("�����\n");
            getchar();getchar();
            break;
        case 20://���Ӷ�����
            flag_create = 0, k = 0;
            printf("���������������������ƣ�");
            scanf("%s", ListName);
            flag = AddTree(Trees, ListName);
            if (flag == OK)
                printf("�ɹ���������Ϊ %s �Ķ�������\n", ListName);
            else
                printf("����ʧ�ܣ�\n");
            getchar();getchar();
            break;
        case 21://ɾ��������
            if (Trees.length)
            {
                printf("\n---------------- all trees --------------------\n");
                for (int i = 0; i < Trees.length; i++)
                    printf("%d %s\n", i + 1, Trees.elem[i].name);
                printf("------------------ end ------------------------\n");
            }
            else
            {
                printf("�������ļ���Ϊ�գ��޷����д˲�����\n");
                getchar();getchar();
                break;
            }
            printf("��������Ҫɾ���Ķ����������ƣ�");
            scanf("%s", ListName);
            flag = RemoveTree(Trees, ListName);
            if (flag == OK)
                printf("�ɹ�ɾ������Ϊ %s �Ķ�������\n", ListName);
            else if (flag == ERROR)
                printf("ɾ��ʧ�ܣ�\n");
            getchar();getchar();
            break;
        case 22://���Ҷ�����
        {
            if (!Trees.length)
            {
                printf("�������ļ���Ϊ�գ��޷����д˲�����\n");
                getchar();getchar();
                break;
            }
            int loc = 0;
            printf("��������Ҫ���ҵĶ����������ƣ�");
            scanf("%s", ListName);
            loc = LocateTree(Trees, ListName);
            if (loc == 0)
                printf("����������Ϊ %s �Ķ�������\n", ListName);
            else
                printf("����Ϊ %s �Ķ����������Ϊ %d ��\n", ListName, loc);
            getchar();getchar();
            break;
        }
        case 23://�����ܱ�
            flag = ListsTraverse(Trees);
            if (flag == ERROR)
                printf("�������ļ���Ϊ�գ�\n");
            getchar();getchar();
            break;
        case 24://ѡ�������в���
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
                printf("�������ļ���Ϊ�գ��޷����д˲�����\n");
                getchar();getchar();
                break;
            }
            int e = 0;
            printf("��������Ҫ���в����Ķ���������ţ���1��ʼ����");
            scanf("%d", &e);
            getchar();
            T = ChooseTree(T, Trees, e);
            if (T == NULL)
                printf("�������Ų��Ϸ����������ÿգ�\n");
            else
                printf("����ɶԶ��������������Ϊ %d �Ķ��������в�����\n", e);
            getchar();getchar();
            break;
        }
        case 0:
            break;
        }
    }
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}
/*---------------------main����-----------------------*/











