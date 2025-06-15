#pragma once
int visited[MAX_VERTEX_NUM];    //����ʱ��¼�����Ƿ��ѷ���
int PathLength[MAX_VERTEX_NUM]; //��¼���ж��㵽ĳһ��������·������
VNode vn[MAX_VERTEX_NUM];       //�洢���㼯�Ϲ�����,���ں���13�� 

// ����5 ��õ�һ�ڽӵ�
// ����u��ͼG�в��Ҷ���,���ҳɹ����ض���u�ĵ�һ�ڽӶ���λ��,���򷵻�-1
int FirstAdjVex(ALGraph G, KeyType u)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
        if (u == G.vertices[i].data.key && G.vertices[i].firstarc != NULL)
            return G.vertices[i].firstarc->adjvex;
    return -1;
}

// ����6 �����һ�ڽӵ�
// v��ӦG��һ������,w��Ӧv���ڽӶ���
// ��������Ƿ���v��(�����w)��һ���ڽӶ����λ��
// ���w�����һ���ڽӶ���,��v,w��Ӧ���㲻����,�򷵻�-1
int NextAdjVex(ALGraph G, KeyType v, KeyType w)
{
    int i, flag1 = -1, flag2 = -1;
    for (i = 0; i < G.vexnum; i++)
    {
        if (v == G.vertices[i].data.key)
            flag1 = i;
        if (w == G.vertices[i].data.key)
            flag2 = i;
    }
    if (flag1 == -1 || flag2 == -1)
        return -1;
    ArcNode* a = G.vertices[flag1].firstarc;
    while (a)
    {
        if (flag2 == a->adjvex && a->nextarc != NULL)
            return a->nextarc->adjvex;
        a = a->nextarc;
    }
    return -1;
}

// ���ʺ���
void visit(VertexType v)
{
    printf(" %d %s", v.key, v.others);
}

// ����ʵ�ֺ���
void DFS(ALGraph G, int v, void (*visit)(VertexType))
{
    int w = -1;
    visited[v] = 1;
    visit(G.vertices[v].data);
    for (w = FirstAdjVex(G, G.vertices[v].data.key); w >= 0; w = NextAdjVex(G, G.vertices[v].data.key, G.vertices[w].data.key))
        if (!visited[w])
            DFS(G, w, visit);
}




// ��ʼ������Q
void iniQueue(QUEUE& Q)
{
    Q.front = 0;
    Q.length = 0;   //���г���Ϊ0
}

// Ԫ�����
status enQueue(QUEUE& Q, ElemType e)
{
    if (Q.length >= MAXLENGTH)   //�������
        return ERROR;
    Q.elem[(Q.front + Q.length++) % MAXLENGTH] = e;
    return OK;
}

// Ԫ�س���
// ��Q����Ԫ�س��ӣ���ֵ��e���ɹ����ӷ���1�����򷵻�0
status deQueue(QUEUE& Q, ElemType& e)
{
    if (Q.length == 0)   //����Ϊ��
        return ERROR;
    e = Q.elem[Q.front];
    Q.front = (Q.front + 1) % MAXLENGTH;
    Q.length--;
    return OK;
}



// ����1 ����
// ����V��VR����ͼT������OK,���V��VR����ȷ,����ERROR,�������ͬ�Ĺؼ���,����ERROR
status CreateCraph(ALGraph& G, VertexType V[], KeyType VR[][2])
{
    if (V[0].key == -1)
        return ERROR;
    int a, i, j, flag1 = 0, flag2 = 0;
    KeyType keys[30];
    for (a = 0; a < 20; a++)
        keys[a] = 0;
    a = 0;
    for (i = 0; V[i].key != -1; i++)
    {
        if (i >= MAX_VERTEX_NUM)
            return ERROR;
        keys[a++] = V[i].key;
        for (j = i + 1; V[j].key != -1; j++)
            if (V[i].key == V[j].key)
                return ERROR;
    }
    for (i = 0; VR[i][0] != -1; i++)
    {
        flag1 = 0, flag2 = 0;
        for (a = 0; keys[a] != 0; a++)
        {
            if (VR[i][0] == keys[a])
                flag1 = 1;
            if (VR[i][1] == keys[a])
                flag2 = 1;
        }
        if (!flag1 || !flag2)
            return ERROR;
    }
    G.kind = UDG;
    G.vexnum = 0;
    G.arcnum = 0;
    for (i = 0; V[i].key != -1 && i < MAX_VERTEX_NUM; i++)
    {
        G.vertices[i].data = V[i];
        G.vertices[i].firstarc = NULL;
        G.vexnum++;
    }
    for (i = 0; VR[i][0] != -1; i++)
    {
        flag1 = 0, flag2 = 0;
        for (a = 0; keys[a] != 0; a++)
        {
            if (VR[i][0] == keys[a])
                flag1 = a;
            if (VR[i][1] == keys[a])
                flag2 = a;
        }
        ArcNode* a1 = (ArcNode*)malloc(sizeof(ArcNode));
        a1->adjvex = flag2;
        a1->nextarc = G.vertices[flag1].firstarc;
        G.vertices[flag1].firstarc = a1;
        ArcNode* a2 = (ArcNode*)malloc(sizeof(ArcNode));
        a2->adjvex = flag1;
        a2->nextarc = G.vertices[flag2].firstarc;
        G.vertices[flag2].firstarc = a2;
        G.arcnum++;
    }
    return OK;
}

// ����2 ����
// ��������ͼG,ɾ��G��ȫ������ͱ�
status DestroyGraph(ALGraph& G)
{
    if (!G.vexnum)
        return INFEASIBLE;
    int i;
    ArcNode* a = NULL, * pre = NULL;
    for (i = 0; i < G.vexnum; i++)
    {
        a = G.vertices[i].firstarc;
        while (a)
        {
            pre = a;
            a = a->nextarc;
            free(pre);
        }
        G.vertices[i].firstarc = NULL;
    }
    memset(G.vertices, 0, G.vexnum);
    G.arcnum = 0;
    G.vexnum = 0;
    return OK;
}

// ����3 ���Ҷ���
// ����u��ͼG�в��Ҷ���,���ҳɹ�����λ��,���򷵻�-1
int LocateVex(ALGraph G, KeyType u)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
        if (u == G.vertices[i].data.key)
            return i;
    return -1;
}

// ����4 ���㸳ֵ
// ����u��ͼG�в��Ҷ���,���ҳɹ����ö���ֵ�޸ĳ�value,����OK
// �������ʧ�ܻ�ؼ��ֲ�Ψһ,����ERROR
status PutVex(ALGraph& G, KeyType u, VertexType value)
{
    int i, j;
    for (i = 0; i < G.vexnum; i++)
        if (u == G.vertices[i].data.key)
            break;
    if (i == G.vexnum)
        return ERROR;
    for (j = 0; j < G.vexnum; j++)
        if (value.key == G.vertices[j].data.key && value.key != u)
            return ERROR;
    G.vertices[i].data = value;
    return OK;
}



// ����7 ���붥��
// ��ͼG�в��붥��v,�ɹ�����OK,���򷵻�ERROR
status InsertVex(ALGraph& G, VertexType v)
{
    if (G.vexnum == MAX_VERTEX_NUM)
        return ERROR;
    int i;
    for (i = 0; i < G.vexnum; i++)
        if (v.key == G.vertices[i].data.key)
            return ERROR;
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
}

// ����8 ɾ������
// ��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ�,�ɹ�����OK,���򷵻�ERROR
status DeleteVex(ALGraph& G, KeyType v)
{
    if (G.vexnum == 1)
        return ERROR;
    int i, j = 0, k;
    for (i = 0; i < G.vexnum; i++)
        if (v == G.vertices[i].data.key)
            break;
    if (i == G.vexnum)
        return ERROR;
    ArcNode* a = G.vertices[i].firstarc, * pre = NULL;
    while (a)
    {
        pre = a;
        a = a->nextarc;
        ArcNode* b = G.vertices[pre->adjvex].firstarc, * preb = NULL;
        if (b->adjvex == i)
        {
            G.vertices[pre->adjvex].firstarc = b->nextarc;
            free(b);
        }
        else
            while (b)
            {
                preb = b;
                b = b->nextarc;
                if (b->adjvex == i)
                {
                    preb->nextarc = b->nextarc;
                    free(b);
                    break;
                }
            }
        free(pre);
        G.arcnum--;
    }
    G.vertices[i].firstarc = NULL;
    ArcNode* c = NULL;
    for (j = 0; j < G.vexnum; j++)
    {
        c = G.vertices[j].firstarc;
        while (c != NULL)
        {
            if (c->adjvex > i)
                c->adjvex--;
            c = c->nextarc;
        }
    }
    for (k = i + 1; k < G.vexnum; i++, k++)
    {
        G.vertices[i].data = G.vertices[k].data;
        G.vertices[i].firstarc = G.vertices[k].firstarc;
    }
    G.vexnum--;
    return OK;
}

// ����9 ���뻡
// ��ͼG�����ӻ�<v,w>,�ɹ�����OK,���򷵻�ERROR
status InsertArc(ALGraph& G, KeyType v, KeyType w)
{
    int i, flag1 = -1, flag2 = -1;
    for (i = 0; i < G.vexnum; i++)
    {
        if (v == G.vertices[i].data.key)
            flag1 = i;
        if (w == G.vertices[i].data.key)
            flag2 = i;
    }
    if (flag1 == -1 || flag2 == -1)
        return ERROR;

    ArcNode* a = G.vertices[flag1].firstarc;
    while (a)
    {
        if (a->adjvex == flag2)
            return ERROR;
        a = a->nextarc;
    }

    ArcNode* a1 = (ArcNode*)malloc(sizeof(ArcNode));
    a1->adjvex = flag2;
    a1->nextarc = G.vertices[flag1].firstarc;
    G.vertices[flag1].firstarc = a1;
    ArcNode* a2 = (ArcNode*)malloc(sizeof(ArcNode));
    a2->adjvex = flag1;
    a2->nextarc = G.vertices[flag2].firstarc;
    G.vertices[flag2].firstarc = a2;
    G.arcnum++;
    return OK;
}

// ����10 ɾ����
// ��ͼG��ɾ����<v,w>,�ɹ�����OK,���򷵻�ERROR
status DeleteArc(ALGraph& G, KeyType v, KeyType w)
{
    int i, flag1 = -1, flag2 = -1, flag = 0;
    for (i = 0; i < G.vexnum; i++)
    {
        if (v == G.vertices[i].data.key)
            flag1 = i;
        if (w == G.vertices[i].data.key)
            flag2 = i;
    }
    if (flag1 == -1 || flag2 == -1)
        return ERROR;

    ArcNode* a = G.vertices[flag1].firstarc;
    while (a)
    {
        if (a->adjvex == flag2)
            flag = 1;
        a = a->nextarc;
    }
    if (!flag)
        return ERROR;

    ArcNode* a1 = G.vertices[flag1].firstarc, * pre1 = NULL;
    if (a1->adjvex == flag2)
    {
        G.vertices[flag1].firstarc = a1->nextarc;
        free(a1);
    }
    else
        while (a1)
        {
            pre1 = a1;
            a1 = a1->nextarc;
            if (a1->adjvex == flag2)
            {
                pre1->nextarc = a1->nextarc;
                free(a1);
                break;
            }
        }

    ArcNode* a2 = G.vertices[flag2].firstarc, * pre2 = NULL;
    if (a2->adjvex == flag1)
    {
        G.vertices[flag2].firstarc = a2->nextarc;
        free(a2);
    }
    else
        while (a2)
        {
            pre2 = a2;
            a2 = a2->nextarc;
            if (a2->adjvex == flag1)
            {
                pre2->nextarc = a2->nextarc;
                free(a2);
                break;
            }
        }
    G.arcnum--;
    return OK;
}

// ����11 ���ѱ���
// ��ͼG�������������������,���ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ��,�ҽ�����һ��
status DFSTraverse(ALGraph& G, void (*visit)(VertexType))
{
    int v;
    for (v = 0; v < G.vexnum; v++)
        visited[v] = 0;
    for (v = 0; v < G.vexnum; v++)
        if (!visited[v])
            DFS(G, v, visit);
    return OK;
}

// ����12 ���ѱ���
// ��ͼG���й��������������,���ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ��,�ҽ�����һ��
status BFSTraverse(ALGraph& G, void (*visit)(VertexType))
{
    int v, u, w = -1;
    QUEUE Q;
    for (v = 0; v < G.vexnum; v++)
        visited[v] = 0;
    iniQueue(Q);
    for (v = 0; v < G.vexnum; v++)
        if (!visited[v])
        {
            visited[v] = 1;
            visit(G.vertices[v].data);
            enQueue(Q, v);
            while (Q.length)
            {
                deQueue(Q, u);
                for (w = FirstAdjVex(G, G.vertices[u].data.key); w >= 0; w = NextAdjVex(G, G.vertices[u].data.key, G.vertices[w].data.key))
                    if (!visited[w])
                    {
                        visited[w] = 1;
                        visit(G.vertices[w].data);
                        enQueue(Q, w);
                    }
            }
        }
    return OK;
}

// ���ӹ���13 �����С��k�Ķ��㼯��
// ��ʼ������ͼG����;��������Ƿ����붥��v����С��k�Ķ��㼯��
VNode* VerticesSetLessThanK(ALGraph G, KeyType v, int k)
{
    int i, j, u, x = -1, len = 0, times = 0;
    int flag1 = -1, flag2 = -1;
    for (i = 0; i < MAX_VERTEX_NUM; i++)
        vn[i].data.key = 0;
    for (i = 0; i < G.vexnum; i++)
        if (v == G.vertices[i].data.key)
            flag1 = i;
    if (flag1 == -1)
        return NULL;
    int length[MAX_VERTEX_NUM];
    for (i = 0; i < MAX_VERTEX_NUM; i++)
        length[i] = 0;
    QUEUE Q;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = 0;
    iniQueue(Q);
    for (i = flag1; times < G.vexnum; i++, times++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            length[i] = len;
            enQueue(Q, i);
            while (Q.length)
            {
                len++;
                deQueue(Q, u);
                for (x = FirstAdjVex(G, G.vertices[u].data.key); x >= 0; x = NextAdjVex(G, G.vertices[u].data.key, G.vertices[x].data.key))
                {
                    if (!visited[x])
                    {
                        visited[x] = 1;
                        length[x] = len;
                        enQueue(Q, x);
                    }
                }
            }
        }
        if (i + 1 == G.vexnum)
            i = -1;
        break;
    }
    for (i = 0, j = 0; i < G.vexnum; i++)
        if (length[i] > 0 && length[i] < k)
            vn[j++] = G.vertices[i];
    return vn;
}

// ���ӹ���14 �󶥵�����·������
// ��ʼ������ͼG����;��������Ƿ��ض���v�붥��w�����·���ĳ���
int ShortestPathLength(ALGraph G, KeyType v, KeyType w)
{
    int i, u, x = -1, len = 0, times = 0;
    int flag1 = -1, flag2 = -1;
    for (i = 0; i < G.vexnum; i++)
    {
        if (v == G.vertices[i].data.key)
            flag1 = i;
        if (w == G.vertices[i].data.key)
            flag2 = i;
    }
    if (flag1 == -1 || flag2 == -1)
        return -1;
    int length[MAX_VERTEX_NUM];
    for (i = 0; i < MAX_VERTEX_NUM; i++)
        length[i] = -1;
    QUEUE Q;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = 0;
    iniQueue(Q);
    for (i = flag1; times < G.vexnum; i++, times++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            length[i] = len;
            enQueue(Q, i);
            while (Q.length)
            {
                len++;
                deQueue(Q, u);
                for (x = FirstAdjVex(G, G.vertices[u].data.key); x >= 0; x = NextAdjVex(G, G.vertices[u].data.key, G.vertices[x].data.key))
                {
                    if (!visited[x])
                    {
                        visited[x] = 1;
                        length[x] = len;
                        enQueue(Q, x);
                    }
                }
            }
        }
        if (i + 1 == G.vexnum)
            i = -1;
        break;
    }
    return length[flag2];
}

// ���ӹ���15 ��ͼ��ͨ��������
// ��ʼ������ͼG����;��������Ƿ���ͼG��������ͨ�����ĸ���
int ConnectedComponentsNums(ALGraph G)
{
    int i, nums = 0;
    for (i = 0; i < G.vexnum; i++)
        visited[i] = 0;
    for (i = 0; i < G.vexnum; i++)
        if (!visited[i])
        {
            nums++;
            DFS(G, i, visit);
        }
    return nums;
}

// ���ӹ���16 д���ļ�
// ��ͼ������д�뵽�ļ�FileName��
status SaveGraph(ALGraph G, char FileName[])
{
    FILE* fp = fopen(FileName, "w");

    for (int i = 0; i < G.vexnum; i++)
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
    fprintf(fp, "%d %s ", -1, "nil");
    int a1[30], a2[30];
    for (int i = 0; i < 30; i++)
        a1[i] = 0, a2[i] = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        KeyType k1 = G.vertices[i].data.key, k2 = -1;
        ArcNode* a = G.vertices[i].firstarc;
        int j = 0, flag = 0;
        while (a)
        {
            flag = 0;
            k2 = G.vertices[a->adjvex].data.key;
            a = a->nextarc;
            for (j = 0; a1[j] != 0; j++)
                if (k1 == a2[j] && k2 == a1[j])
                    flag = 1;
            if (flag)
                continue;
            else
            {
                a1[j] = k1;
                a2[j] = k2;
            }
        }
    }
    for (int i = 0; a1[i] != 0; i++)
        if (a2[i] < a1[i])
        {
            int tmp = a2[i];
            a2[i] = a1[i];
            a1[i] = tmp;
        }
    for (int i = 0; a1[i] != 0; i++)
    {
        for (int j = i + 1; a1[j] != 0; j++)
        {
            if ((a1[i] > a1[j]) || (a1[i] == a1[j] && a2[i] > a2[j]))
            {
                int tmp1 = a1[i];
                a1[i] = a1[j];
                a1[j] = tmp1;
                int tmp2 = a2[i];
                a2[i] = a2[j];
                a2[j] = tmp2;
            }
        }
    }
    for (int i = 0; a1[i] != 0; i++)
        fprintf(fp, "%d %d ", a1[i], a2[i]);
    fprintf(fp, "%d %d ", -1, -1);
    fclose(fp);
    return OK;
}

// ����17 ��ȡ�ļ�
// �����ļ�FileName��ͼ���ݣ�����ͼ���ڽӱ�
status LoadGraph(ALGraph& G, char FileName[])
{
    FILE* fp = fopen(FileName, "r");
    G.kind = UDG;
    G.vexnum = 0;
    G.arcnum = 0;
    VertexType V[21];
    KeyType VR[100][2], keys[30];
    for (int k = 0; k < 30; k++)
        keys[k] = 0;
    int i = 0, flag1 = -1, flag2 = -1;
    do {
        fscanf(fp, "%d %s ", &V[i].key, V[i].others);
        keys[i] = V[i].key;
    } while (V[i++].key != -1);
    i = 0;
    do {
        fscanf(fp, "%d %d ", &VR[i][0], &VR[i][1]);
    } while (VR[i++][0] != -1);

    for (i = 0; V[i].key != -1 && i < MAX_VERTEX_NUM; i++)
    {
        G.vertices[i].data = V[i];
        G.vertices[i].firstarc = NULL;
        G.vexnum++;
    }
    for (i = 0; VR[i][0] != -1; i++)
    {
        flag1 = 0, flag2 = 0;
        for (int a = 0; keys[a] != 0; a++)
        {
            if (VR[i][0] == keys[a])
                flag1 = a;
            if (VR[i][1] == keys[a])
                flag2 = a;
        }
        ArcNode* a1 = (ArcNode*)malloc(sizeof(ArcNode));
        a1->adjvex = flag2;
        a1->nextarc = G.vertices[flag1].firstarc;
        G.vertices[flag1].firstarc = a1;
        ArcNode* a2 = (ArcNode*)malloc(sizeof(ArcNode));
        a2->adjvex = flag1;
        a2->nextarc = G.vertices[flag2].firstarc;
        G.vertices[flag2].firstarc = a2;
        G.arcnum++;
    }
    fclose(fp);
    return OK;
}

// ���ӹ���18 ������ͼ����:������ͼ
// ��Lists������һ������ΪGraphName������ͼ
status AddGragh(LISTS& Lists, char ListName[])
{
    for (int i = 0; i < Lists.length; i++)
        if (!strcmp(Lists.elem[i].name, ListName))
        {
            printf("�������Ѵ�������Ϊ %s ������ͼ!\n", ListName);
            return ERROR;
        }
    strcpy(Lists.elem[Lists.length].name, ListName);
    VertexType V1[30];
    KeyType VR1[100][2];
    int m = 0, flag1 = 0;
    printf("�����ʽʾ��: 1 ���Ա�  3 ������\n");
    printf("��-1 nil��Ϊ�������\n");
    printf("��ͼ���贴��\n");
    printf("��ݴ����뽫��ͼ�еĶ�������:");
    do {
        scanf("%d%s", &V1[m].key, V1[m].others);
    } while (V1[m++].key != -1);
    m = 0;
    printf("��ϵ�Ը�ʽʾ��: 1 3\n");
    printf("��-1 -1��Ϊ�������\n");
    printf("��ݴ����뽫��ͼ�еĹ�ϵ������:");
    do {
        scanf("%d%d", &VR1[m][0], &VR1[m][1]);
    } while (VR1[m++][0] != -1);
    flag1 = CreateCraph(Lists.elem[Lists.length].G, V1, VR1);
    if (flag1 == OK)
        printf("����Ϊ %s ������ͼ�����ɹ�!\n", Lists.elem[Lists.length++].name);
    else
        printf("����ʧ��!�������л��ϵ��������������!\n");
    return OK;
}

// ���ӹ���19 ������ͼ����:ɾ��ͼ
status RemoveGragh(LISTS& Lists, char ListName[])
{
    int i;
    for (i = 0; i < Lists.length; i++)
        if (!strcmp(Lists.elem[i].name, ListName))  //ƥ�����
            break;
    if (i == Lists.length)
        return ERROR;
    else
    {
        DestroyGraph(Lists.elem[i].G);
        memset(Lists.elem[i].name, 0, strlen(Lists.elem[i].name));
        Lists.length--;
        for (int j = i; j < Lists.length; j++)
            Lists.elem[j] = Lists.elem[j + 1];
        return OK;
    }
}

// ���ӹ���20 ������ͼ����:����ͼ
int LocateGragh(LISTS Lists, char ListName[])
{
    for (int i = 0; i < Lists.length; i++)
        if (!strcmp(Lists.elem[i].name, ListName))  //ƥ�����
            return (i + 1);
    return ERROR;
}

// ���ӹ���21 ������ͼ����:�����ܱ�
status ListsTraverse(LISTS Lists)
{
    if (Lists.length == 0)
        return ERROR;
    for (int n = 0; n < Lists.length; n++)
    {
        printf("����Ϊ %s ������ͼ���ڽӱ����ѱ�����:\n", Lists.elem[n].name);
        DFSTraverse(Lists.elem[n].G, visit);
        printf("\n---------------------------------------\n");
    }
    return OK;
}

// ���ӹ���22 ������ͼ����:ѡ��ͼ���в���
ALGraph* ChooseGragh(ALGraph* G, LISTS& Lists, int i)
{
    if (i > Lists.length || i < 1)
        return NULL;
    else
    {
        G = &(Lists.elem[i - 1].G);  //���ݵ�ַ��ͬʱ�Ķ���ͼ���ͼ�еĴ�ͼ    
        return G;
    }
}
