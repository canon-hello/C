#include "4def.h"
#include "4func.h"

/* ������� */
void visit(VertexType v);
void DFS(ALGraph G, int v, void (*visit)(VertexType));

///* ���в������� */
void iniQueue(QUEUE& Q);
status enQueue(QUEUE& Q, ElemType e);
status deQueue(QUEUE& Q, ElemType& e);

/* ��ͼ������������ */
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

/*ѡ����������*/
VNode* VerticesSetLessThanK(ALGraph G, KeyType v, int k);
int ShortestPathLength(ALGraph G, KeyType v, KeyType w);
int ConnectedComponentsNums(ALGraph G);

/*�ļ���д����*/
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph& G, char FileName[]);

/*��ͼ��������*/
status AddGragh(LISTS& Lists, char ListName[]);
status RemoveGragh(LISTS& Lists, char ListName[]);
int LocateGragh(LISTS Lists, char ListName[]);
status ListsTraverse(LISTS Lists);
ALGraph* ChooseGragh(ALGraph* L, LISTS& Lists, int i);













/*---------------------main����-----------------------*/
int main(void)
{
    //���嵥ͼ����ʼ��
    ALGraph G1;
    ALGraph* G = &G1;
    G->arcnum = 0;
    G->vexnum = 0;
    memset(G->vertices, 0, MAX_VERTEX_NUM * sizeof(VNode));

    //����������ʼ��
    LISTS Lists;
    Lists.length = 0, Lists.listsize = 10;

    //op��¼����ѡ�����,flag��¼�����������,i��k�洢int�͹�����,u��v�洢�ؼ��ֹ�����
    int op = 1, flag = 0, i = 0, k = 0, u = 0, v = 0;
    char FileName[30], ListName[30]; //�����ļ��������
    VertexType value;   //�洢���������
    VertexType V[30];   //�洢��������
    KeyType VR[100][2]; //�洢��ϵ������
    VNode* VN = NULL;   //�洢���㼯�Ϲ�����������main�����н��պ���13�ķ���ֵ 

    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Undirected Graph On Adjacency List   \n");
        printf("------------------------------------------------------\n");
        printf("          1. ����            12. ���ѱ���\n");
        printf("          2. ����            13. �����С��k�Ķ��㼯��\n");
        printf("          3. ���Ҷ���        14. �󶥵�����·������\n");
        printf("          4. ���㸳ֵ        15. ����ͨ��������\n");
        printf("          5. ��õ�һ�ڽӵ�  16. д���ļ�\n");
        printf("          6. �����һ�ڽӵ�  17. ��ȡ�ļ�\n");
        printf("          7. ���붥��        18. ����ͼ\n");
        printf("          8. ɾ������        19. ɾ��ͼ\n");
        printf("          9. ���뻡          20. ����ͼ\n");
        printf("         10. ɾ����          21. �����ܱ�\n");
        printf("         11. ���ѱ���        22. ѡ��ͼ���в���\n");
        printf("          0. �˳�\n");
        printf("------------------------------------------------------\n");
        printf("    ��ѡ����Ĳ���[0~22]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1://����
            if (G->vexnum)
                printf("����ʧ��!ͼ�Ѵ���!\n");
            else
            {
                i = 0;
                printf("�����ʽʾ��: 1 ���Ա� 3 ������\n");
                printf("��-1 nil��Ϊ�������\n");
                printf("��ͼ���贴��\n");
                printf("��ݴ����뽫��ͼ�еĶ�������:");
                do {
                    scanf("%d %s", &V[i].key, V[i].others);
                } while (V[i++].key != -1);
                i = 0;
                printf("��ϵ�Ը�ʽʾ��: 1 3\n");
                printf("��-1 -1��Ϊ�������\n");
                printf("��ݴ����뽫��ͼ�еĹ�ϵ������:");
                do {
                    scanf("%d %d", &VR[i][0], &VR[i][1]);
                } while (VR[i++][0] != -1);
                flag = CreateCraph(*G, V, VR);
                if (flag == OK)
                    printf("����ͼ�����ɹ�!\n����һ��������ڶ�ͼ�ĵ�ͼ,����Զ�������1~17����!\n");
                else
                    printf("����ʧ��!�������л��ϵ��������������!\n");
            }
            getchar();getchar();
            break;
        case 2://����
            flag = DestroyGraph(*G);
            if (flag == OK)
                printf("�ɹ���������ͼ���ͷ�����Ԫ�صĿռ�!\n");
            else if (flag == INFEASIBLE)
                printf("���ܶԲ����ڵ�����ͼ�������ٲ���!\n");
            getchar();getchar();
            break;
        case 3://���Ҷ���
            if (!G->vexnum)
                printf("���ܶԲ����ڵ�����ͼ���в��Ҳ���!\n");
            else
            {
                printf("��������Ҫ���ҵĹؼ���:");
                scanf("%d", &u);
                flag = LocateVex(*G, u);
                if (flag == -1)
                    printf("���ؼ��� %d �Ķ��㲻����!\n", u);
                else
                    printf("���ؼ��� %d �Ķ���λ��Ϊ %d!", u, flag);
            }
            getchar();getchar();
            break;
        case 4://���㸳ֵ
            if (!G->vexnum)
                printf("���ܶԲ����ڵ�����ͼ���и�ֵ����!\n");
            else
            {
                printf("��������Ҫ��ֵ�Ķ���Ĺؼ������ڲ���:");
                scanf("%d", &u);
                printf("�����뽫���Ĺؼ���������:");
                scanf("%d%s", &value.key, value.others);
                flag = PutVex(*G, u, value);
                if (flag == OK)
                    printf("��ֵ�ɹ�!\n");
                else
                    printf("��ֵʧ��!�ؼ��ֲ����ڻ򽫸��ؼ��ֲ�Ψһ!\n");
            }
            getchar();getchar();
            break;
        case 5://��õ�һ�ڽӵ�
            if (!G->vexnum)
                printf("���ܶԲ����ڵ�����ͼ���иò���!\n");
            else
            {
                printf("��������Ҫ���һ�ڽӵ�Ķ���Ĺؼ���:");
                scanf("%d", &u);
                flag = FirstAdjVex(*G, u);
                if (flag == -1)
                    printf("����ʧ��!�ؼ��ֲ����ڻ�ö��㲻�����ڽӵ�!\n");
                else
                    printf("�ؼ���Ϊ %d �Ķ���ĵ�һ�ڽӵ���λ��Ϊ %d �� %d %s!\n", u, flag, G->vertices[flag].data.key, G->vertices[flag].data.others);
            }
            getchar();getchar();
            break;
        case 6://�����һ�ڽӵ�
            if (!G->vexnum)
                printf("���ܶԲ����ڵ�����ͼ���иò���!\n");
            else
            {
                printf("������һ�����������һ���ڽӵ�Ĺؼ���:");
                scanf("%d%d", &u, &v);
                flag = NextAdjVex(*G, u, v);
                if (flag == -1)
                    printf("����ʧ��!�ؼ��ֲ����ڻ���ڽӵ��������һ��!\n");
                else
                    printf("���� %d ���ڽӵ� %d ����һ�ڽӵ���λ��Ϊ %d �� %d %s!\n", u, v, flag, G->vertices[flag].data.key, G->vertices[flag].data.others);
            }
            getchar();getchar();
            break;
        case 7://���붥��
            if (!G->vexnum)
                printf("���ܶԲ����ڵ�����ͼ���иò���!\n");
            else
            {
                printf("�����뽫����Ĺؼ���������:");
                scanf("%d%s", &value.key, value.others);
                flag = InsertVex(*G, value);
                if (flag == OK)
                    printf("����ɹ�!\n");
                else
                    printf("����ʧ��!������Ŀ�Ѵ����ֵ��ؼ����Ѵ���!\n");
            }
            getchar();getchar();
            break;
        case 8://ɾ������
            if (!G->vexnum)
                printf("���ܶԲ����ڵ�����ͼ���иò���!\n");
            else
            {
                printf("�����뽫ɾ���Ľ��Ĺؼ���:");
                scanf("%d", &u);
                flag = DeleteVex(*G, u);
                if (flag == OK)
                    printf("ɾ���ɹ�!��ö�����صĻ���ɾ��!\n");
                else
                    printf("ɾ��ʧ��!�ؼ��ֲ����ڻ򶥵���ĿΪ1!\n");
            }
            getchar();getchar();
            break;
        case 9://���뻡
            if (!G->vexnum)
                printf("���ܶԲ����ڵ�����ͼ���иò���!\n");
            else
            {
                printf("��ֱ����뽫����Ļ�����������Ĺؼ���:");
                scanf("%d%d", &u, &v);
                flag = InsertArc(*G, u, v);
                if (flag == OK)
                    printf("����ɹ�!\n");
                else
                    printf("����ʧ��!�ؼ��ֲ����ڻ��Ѵ���!\n");
            }
            getchar();getchar();
            break;
        case 10://ɾ����
            if (!G->vexnum)
                printf("���ܶԲ����ڵ�����ͼ���иò���!\n");
            else
            {
                printf("��ֱ����뽫ɾ���Ļ�����������Ĺؼ���:");
                scanf("%d%d", &u, &v);
                flag = DeleteArc(*G, u, v);
                if (flag == OK)
                    printf("ɾ���ɹ�!\n");
                else
                    printf("ɾ��ʧ��!�ؼ��ֲ����ڻ򻡲�����!\n");
            }
            getchar();getchar();
            break;
        case 11://���ѱ���
            if (!G->vexnum)
                printf("���ܶԲ����ڵ�����ͼ���б�������!\n");
            else
                DFSTraverse(*G, visit);
            getchar();getchar();
            break;
        case 12://���ѱ���
            if (!G->vexnum)
                printf("���ܶԲ����ڵ�����ͼ���б�������!\n");
            else
                BFSTraverse(*G, visit);
            getchar();getchar();
            break;
        case 13://�����С��k�Ķ��㼯��
            if (!G->vexnum)
                printf("���ܶԲ����ڵ�����ͼ���иò���!\n");
            else
            {
                printf("������һ������Ĺؼ���:");
                scanf("%d", &u);
                printf("���������k:");
                scanf("%d", &k);
                VN = VerticesSetLessThanK(*G, u, k);
                if (VN == NULL)
                    printf("����ʧ��!�ؼ�����������!\n");
                else
                {
                    if (VN[0].data.key == 0)
                        printf("����Ϊ��!");
                    else
                    {
                        printf("��ؼ���Ϊ %d �Ķ������С�� %d �Ķ��㼯��Ϊ:", u, k);
                        for (i = 0; VN[i].data.key != 0; i++)
                            printf("%d %s ", VN[i].data.key, VN[i].data.others);
                    }
                }
            }
            getchar();getchar();
            break;
        case 14://�󶥵�����·������
            if (!G->vexnum)
                printf("���ܶԲ����ڵ�����ͼ���иò���!\n");
            else
            {
                printf("��������������Ĺؼ���:");
                scanf("%d%d", &u, &v);
                flag = ShortestPathLength(*G, u, v);
                if (flag == -1)
                    printf("����ʧ��!�ؼ��ֲ����ڻ�������䲻����·��!\n");
                else
                    printf("�ؼ���Ϊ %d �� %d �Ķ�������·������Ϊ %d!\n", u, v, flag);
            }
            getchar();getchar();
            break;
        case 15://����ͨ��������
            if (!G->vexnum)
                printf("���ܶԲ����ڵ�����ͼ���иò���!\n");
            else
            {
                flag = ConnectedComponentsNums(*G);
                printf("\n��ͼ����ͨ��������Ϊ %d!\n", flag);
            }
            getchar();getchar();
            break;
        case 16://д���ļ�
            if (!G->vexnum)
                printf("���ܶԲ����ڵ�����ͼ���иò���!\n");
            else
            {
                printf("�������ļ�����:");
                scanf("%s", FileName);
                flag = SaveGraph(*G, FileName);
                if (flag == ERROR)
                    printf("�ļ���ʧ��!\n");
                else
                    printf("����ͼ�������Ѿ����Ƶ�����Ϊ %s ���ļ���!\n", FileName);
            }
            getchar();getchar();
            break;
        case 17://��ȡ�ļ�
            if (G->vexnum)
                printf("���ܶ��Ѵ��ڵ�����ͼ���ж��ļ�����!������������ͼ!\n");
            else
            {
                printf("�������ļ�����:");
                scanf("%s", FileName);
                flag = LoadGraph(*G, FileName);
                if (flag == ERROR)
                    printf("�ļ���ʧ��!\n");
                else
                    printf("����Ϊ %s ���ļ��������Ѹ��Ƶ�����ͼ��!\n", FileName);
            }
            getchar();getchar();
            break;
        case 18://����ͼ
            printf("��������������ͼ������:");
            scanf("%s", ListName);
            flag = AddGragh(Lists, ListName);
            if (flag == OK)
                printf("�ɹ���������Ϊ %s ������ͼ!\n", ListName);
            else
                printf("����ʧ��!\n");
            getchar();getchar();
            break;
        case 19://ɾ��ͼ
            if (Lists.length)
            {
                printf("\n--------------- all graphs --------------------\n");
                for (int i = 0; i < Lists.length; i++)
                    printf("%d %s\n", i + 1, Lists.elem[i].name);
                printf("------------------ end ------------------------\n");
            }
            else
            {
                printf("����ͼ�ļ���Ϊ��!�޷����д˲���!\n");
                getchar();getchar();
                break;
            }
            printf("��������Ҫɾ��������ͼ������:");
            scanf("%s", ListName);
            flag = RemoveGragh(Lists, ListName);
            if (flag == OK)
                printf("�ɹ�ɾ������Ϊ %s ������ͼ!\n", ListName);
            else
                printf("ɾ��ʧ��!\n");
            getchar();getchar();
            break;
        case 20://����ͼ
            if (!Lists.length)
            {
                printf("����ͼ�ļ���Ϊ��!�޷����д˲���!\n");
                getchar();getchar();
                break;
            }
            printf("��������Ҫ���ҵ�����ͼ������:");
            scanf("%s", ListName);
            flag = LocateGragh(Lists, ListName);
            if (!flag)
                printf("����������Ϊ %s ������ͼ!\n", ListName);
            else
                printf("����Ϊ %s ������ͼ�����Ϊ %d!\n", ListName, flag);
            getchar();getchar();
            break;
        case 21://�����ܱ�
            if (ListsTraverse(Lists) == ERROR)
                printf("����ͼ�ļ���Ϊ��!\n");
            getchar();getchar();
            break;
        case 22://ѡ��ͼ���в���
            if (Lists.length)
            {
                printf("\n--------------- all grapghs --------------------\n");
                for (int i = 0; i < Lists.length; i++)
                    printf("%d %s\n", i + 1, Lists.elem[i].name);
                printf("------------------ end ------------------------\n");
            }
            else
            {
                printf("����ͼ�ļ���Ϊ��!�޷����д˲���!\n");
                getchar();getchar();
                break;
            }
            printf("��������Ҫ����������ͼ�����(��1��ʼ):");
            scanf("%d", &flag);
            G = ChooseGragh(G, Lists, flag);
            if (G == NULL)
                printf("������Ų��Ϸ�!��ͼ���ÿ�!\n");
            else
                printf("����ɶ�����ͼ���������Ϊ %d ������ͼ���в���!\n", flag);
            getchar();getchar();
            break;
        case 0:
            break;
        }
    }
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}
/*---------------------main����-----------------------*/
