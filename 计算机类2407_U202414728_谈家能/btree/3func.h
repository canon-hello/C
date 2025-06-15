#pragma once

// ������
status Compare(KeyType e, TElemType elem)
{
    if (elem.key == e)
        return OK;
    return ERROR;
}

// ���ʺ���
void visit(BiTree elem)
{
    printf("| %d %s |", elem->data.key, elem->data.others);
}

// �����ֵ����
int max(int x, int y)
{
    return (x >= y) ? x : y;
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
// ���ݴ���֦�Ķ������ȸ���������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK���������ͬ�Ĺؼ��֣�����ERROR��
status CreateBiTree(BiTree& T, TElemType definition[])
{
    if (flag_create == 0)
    {
        int i = 0, j = 0;   //�ؼ��ּ��ѭ���ñ���
        for (i = 0; definition[i].key != -1; i++)
        {
            if (definition[i].key == 0)
                continue;
            for (j = i + 1;definition[j].key != -1;j++)
                if (definition[j].key != 0)
                    if (definition[i].key == definition[j].key)
                        return ERROR;
        }
        flag_create = 1;    //����Ѿ����йؼ��ּ�飬�����ݹ������ٴμ��
    }

    if (flag_create == 1)
    {
        if (definition[k].key == 0) //�ؼ���Ϊ0ʱ��NULL
        {
            T = NULL;
            k++;    //definition��ǰ�ƽ�����һ���
        }
        else    //�ؼ��ֲ�Ϊ0ʱ���ɽ��
        {
            if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
                return OVERFLOW;
            T->data = definition[k];
            k++;    //definition��ǰ�ƽ�����һ���
            CreateBiTree(T->lchild, definition);//�ݹ�����������
            CreateBiTree(T->rchild, definition);//�ݹ�����������
        }
        return OK;
    }

    // ���Ĭ�Ϸ���ֵ������ flag_create ������ 0 �� 1 �����
    return ERROR;
}

// ����2 ����
// ��ʼ�����Ƕ�����T�Ѵ��ڣ�������������ٶ�����T��
status DestroyBiTree(BiTree& T)
{
    if (T)
    {
        DestroyBiTree(T->lchild);//�ݹ�����������
        DestroyBiTree(T->rchild);//�ݹ�����������
        free(T);    //���ٷ���Ŀռ�
        T = NULL;   //�����ÿգ�free��ָ����ָ��ԭ��
        return OK;
    }
    return ERROR;
}

// ����3 ���
// ��ʼ�����Ƕ�����T���ڣ���������ǽ�������T��ա�
status ClearBiTree(BiTree& T)
{
    if (T)
    {
        ClearBiTree(T->lchild);//�ݹ����������
        ClearBiTree(T->rchild);//�ݹ����������
        memset(T, 0, sizeof(BiTNode));//��ղ�����
        return OK;
    }
    return ERROR;
}

// ����4 �п�
// ��ʼ�����Ƕ�����T���ڣ������������TΪ�ն������򷵻�TRUE�����򷵻�FALSE��
status BiTreeEmpty(BiTree T)
{
    if (T == NULL)   //������������
        return INFEASIBLE;
    else if (T->data.key == 0)
        return TRUE;
    return FALSE;
}

// ����5 ����
// ��ʼ�����Ƕ�����T���ڣ���������Ƿ���T����ȡ�
int BiTreeDepth(BiTree T)
{
    int depthL = 0, depthR = 0;
    if (T == NULL)
        return 0;
    depthL = BiTreeDepth(T->lchild);//�ݹ������������
    depthR = BiTreeDepth(T->rchild);//�ݹ������������
    if (depthL > depthR)
        return (depthL + 1);
    else
        return (depthR + 1);
}

// ����6 ���ҽ��
// ��ʼ�����Ƕ�����T�Ѵ��ڣ�e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��
// ��������Ƿ��ز��ҵ��Ľ��ָ�룬���޹ؼ���Ϊe�Ľ�㣬����NULL��
BiTNode* LocateNode(BiTree T, KeyType e)
{
    BiTNode* p = NULL, * q = NULL;//�������������������в��ҵ��Ľ��
    if (T == NULL)
        return NULL;
    if (T->data.key == e)
        return T;
    p = LocateNode(T->lchild, e);//�ݹ����������
    q = LocateNode(T->rchild, e);//�ݹ����������
    if (p != NULL)//����������������
        return p;
    if (q != NULL)//����������������
        return q;
    return NULL;
}

// ����7 ��㸳ֵ
// ��ʼ�����Ƕ�����T�Ѵ��ڣ�e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��
// ��������ǹؼ���Ϊe�Ľ�㸳ֵΪvalue��
status Assign(BiTree& T, KeyType e, TElemType value)
{
    static BiTNode* pt = NULL;
    static int flag3 = 0;
    if (T == NULL)
        return OK;
    if (T->data.key == value.key && T->data.key != e)//�ؼ��ʳ�ͻ
    {
        pt = NULL;
        flag3 = 1;
        return ERROR;
    }
    if (T->data.key == e && !flag3)
    {
        pt = T;
        return OK;
    }
    Assign(T->lchild, e, value);//�ݹ����������
    Assign(T->rchild, e, value);//�ݹ����������
    if (pt != NULL)
    {
        pt->data.key = value.key;
        strcpy(pt->data.others, value.others);
        return OK;
    }
    else
        return ERROR;
}

// ����8 ��ȡ�ֵ�
// ��ʼ�����Ƕ�����T���ڣ�e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��
// ��������Ƿ��عؼ���Ϊe�Ľ��ģ�����ң��ֵܽ��ָ�롣���ؼ���Ϊe�Ľ�����ֵܣ��򷵻�NULL��
BiTNode* GetSibling(BiTree T, KeyType e)
{

    if (T == NULL)
        return NULL;
    if (T->data.key == e)
        return T;
    if (GetSibling(T->lchild, e) != NULL && !p)
        p = T->rchild;
    if (GetSibling(T->rchild, e) != NULL && !p)
        p = T->lchild;
    return p;
}

// ����9 ������
// ��ʼ�����Ƕ�����T���ڣ�e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��LRΪ0��1��c�Ǵ������㡣
// ��������Ǹ���LRΪ0����1��������c��T�У���Ϊ�ؼ���Ϊe�Ľ�������Һ��ӽ�㣬���e��ԭ������������������Ϊ���c����������
// LRΪ-1ʱ����Ϊ�������룬ԭ�������Ϊc����������
status InsertNode(BiTree& T, KeyType e, int LR, TElemType c)
{
    static BiTNode* p = NULL;
    if (LR == -1)//��Ϊ��������
    {
        p = (BiTNode*)malloc(sizeof(BiTNode));
        p->data = c;
        p->lchild = NULL;
        p->rchild = T;
        T = p;
        return OK;
    }
    if (T == NULL)
        return OK;
    if (T->data.key == c.key)
        return ERROR;
    if (T->data.key == e)
    {
        p = (BiTNode*)malloc(sizeof(BiTNode));
        p->data = c;
        if (!LR)//��Ϊ����������
        {
            p->rchild = T->lchild;
            T->lchild = p;
            p->lchild = NULL;
        }
        else//��Ϊ����������
        {
            p->rchild = T->rchild;
            T->rchild = p;
            p->lchild = NULL;
        }
        return OK;
    }
    InsertNode(T->lchild, e, LR, c);
    InsertNode(T->rchild, e, LR, c);
    if (p != NULL)
        return OK;
    else
        return ERROR;
}

// ����10 ɾ�����
// ��ʼ�����Ƕ�����T���ڣ�e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��
// ���������ɾ��T�йؼ���Ϊe�Ľ�㣻ͬʱ������ؼ���Ϊe�Ľ���Ϊ0��ɾ�����ɡ�
// ��ؼ���Ϊe�Ľ���Ϊ1���ùؼ���Ϊe�Ľ�㺢�Ӵ��汻ɾ����eλ�á�
// ��ؼ���Ϊe�Ľ���Ϊ2����e�����Ӵ��汻ɾ����eλ�ã�e����������Ϊe�������������ҽ�����������
status DeleteNode(BiTree& T, KeyType e)
{
    if (T == NULL)
        return OK;
    if (T->data.key == e)
    {
        flag1 = 1;
        if (T->lchild == NULL && T->rchild == NULL)//��Ϊ0��ֱ��ɾ��
        {
            free(T);
            T = NULL;
            return OK;
        }
        else if (T->lchild != NULL && T->rchild == NULL)//��Ϊ1���ú��Ӵ���e
        {
            BiTNode* p = T->lchild;
            free(T);
            T = p;
            return OK;
        }
        else if (T->lchild == NULL && T->rchild != NULL)//��Ϊ1���ú��Ӵ���e
        {
            BiTNode* p = T->rchild;
            free(T);
            T = p;
            return OK;
        }
        else//��Ϊ2�������Ӵ���e����������Ϊ�����������ҽ���������
        {
            BiTNode* p = T->lchild;
            BiTNode* q = T->rchild;
            free(T);
            T = p;
            BiTNode* tmp = T;
            for (; tmp->rchild != NULL; tmp = tmp->rchild)
                ;
            tmp->rchild = q;
            return OK;
        }
    }
    DeleteNode(T->lchild, e);
    DeleteNode(T->rchild, e);
    if (!flag1)
        return ERROR;
    else
        return OK;
}

// ����11 ǰ�����
// ��ʼ�����Ƕ�����T���ڣ�Visit��һ������ָ����βΣ���ʹ�øú����Խ���������
// ��������������������ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ�ܡ�
status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    if (T)
    {
        visit(T);//���ʵ�ǰ���
        PreOrderTraverse(T->lchild, visit);//�ݹ����������
        PreOrderTraverse(T->rchild, visit);//�ݹ����������
    }
    return OK;
}

// ����12 �������
// ��ʼ�����Ƕ�����T���ڣ�Visit��һ������ָ����βΣ���ʹ�øú����Խ���������
// ����������������t����ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ�ܡ�
status InOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    if (T)
    {
        InOrderTraverse(T->lchild, visit);//�ݹ����������
        visit(T);//���ʵ�ǰ���
        InOrderTraverse(T->rchild, visit);//�ݹ����������
        return OK;
    }
    else
        return OK;
}

// ����13 �������
// ��ʼ�����Ƕ�����T���ڣ�Visit��һ������ָ����βΣ���ʹ�øú����Խ���������
// ��������Ǻ������t����ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ��
status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    if (T)
    {
        PostOrderTraverse(T->lchild, visit);//�ݹ����������
        PostOrderTraverse(T->rchild, visit);//�ݹ����������
        visit(T);//���ʵ�ǰ���
        return OK;
    }
    else
        return OK;
}

// ����14 �������
// ��ʼ�����Ƕ�����T���ڣ�Visit�ǶԽ�������Ӧ�ú�����
// ��������ǲ������t����ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ�ܡ�
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    BiTNode* p = NULL;
    QUEUE qu;
    iniQueue(qu);
    enQueue(qu, T);
    while (qu.length)
    {
        deQueue(qu, p);
        visit(p);
        if (p->lchild != NULL)
            enQueue(qu, p->lchild);//���ӽ���
        if (p->rchild != NULL)
            enQueue(qu, p->rchild);//�Һ��ӽ���
    }
    return OK;
}

// ���ӹ���15 �����·����
// ��ʼ�����Ƕ�����T���ڣ���������Ƿ��ظ��ڵ㵽Ҷ�ӽ������·���͡�
int MaxPathSum(BiTree T)
{
    if (T == NULL)
        return 0;
    else
        return max(T->data.key + MaxPathSum(T->lchild), T->data.key + MaxPathSum(T->rchild));
}

// ���ӹ���16 �������������
// ��ʼ�����Ƕ�����T���ڣ���������Ǹö�������e1�ڵ��e2�ڵ������������ȡ�
BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2)
{
    if (T == NULL)
        return NULL;
    if (T->data.key == e1 || T->data.key == e2)
        return T;
    BiTNode* left = LowestCommonAncestor(T->lchild, e1, e2);
    BiTNode* right = LowestCommonAncestor(T->rchild, e1, e2);
    if (left == NULL)
        return right;
    if (right == NULL)
        return left;
    return T;
}

// ���ӹ���17 ��ת������
// ��ʼ���������Ա�L�Ѵ��ڣ���������ǽ�T��ת��ʹ�����нڵ�����ҽڵ㻥����
status InvertTree(BiTree& T)
{
    if (T == NULL)
        return OK;
    InvertTree(T->lchild);//�ݹ鷭ת������
    InvertTree(T->rchild);//�ݹ鷭ת������
    BiTree tmp = NULL;//�������ҽ��ʱ����ʱ�洢���
    tmp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tmp;
    return OK;
}

// ���ӹ���18 д���ļ�
// ���������T���ڣ���������T�ĵ�Ԫ��д��FileName�ļ��У�����OK��
status SaveBiTree(BiTree T, char FileName[])
{
    static FILE* fp1 = fopen(FileName, "w");
    if (T == NULL)
    {
        fprintf(fp1, "%d %s ", 0, "null");
        return OK;
    }
    else
    {
        fprintf(fp1, "%d %s ", T->data.key, T->data.others);
        SaveBiTree(T->lchild, FileName);
        SaveBiTree(T->rchild, FileName);
    }
    if (T->data.key == 1)
        fclose(fp1);
    return OK;
}

// ���ӹ���19 ��ȡ�ļ�
// ���������T�����ڣ���FileName�ļ��е����ݶ��뵽������T�У�����OK��
status LoadBiTree(BiTree& T, char FileName[])
{
    static FILE* fp2 = fopen(FileName, "r");
    int t = 0;  //�洢�ؼ���
    char s[20]; //�洢����
    memset(s, 0, 20);
    if (feof(fp2))
        return OK;
    fscanf(fp2, "%d%s", &t, s);
    if (t == 0)
        T = NULL;
    else
    {
        T = (BiTNode*)malloc(sizeof(BiTNode));//��������
        T->data.key = t;
        strcpy(T->data.others, s);
        LoadBiTree(T->lchild, FileName);//�ݹ齨��������
        LoadBiTree(T->rchild, FileName);//�ݹ齨��������
    }
    if (feof(fp2))
        fclose(fp2);
    return OK;
}

// ���ӹ���20 ����������������¶�����
// ��Lists������һ������ΪTreeName�Ķ�������
status AddTree(LISTS& Trees, char ListName[])
{
    for (int i = 0; i < Trees.length; i++)
        if (!strcmp(Trees.elem[i].name, ListName))
        {
            printf("�������Ѵ�������Ϊ %s �Ķ�������\n", ListName);
            return ERROR;
        }
    strcpy(Trees.elem[Trees.length].name, ListName);
    TElemType defi[100];
    memset(defi, 0, 100 * sizeof(TElemType));
    int j = 0, flag3 = 0;
    printf("������ǰ��������У�");
    do
    {
        scanf("%d %s", &defi[j].key, defi[j].others);
    } while (defi[j++].key != -1);
    flag3 = CreateBiTree(Trees.elem[Trees.length].T, defi);
    if (flag3 == OK)
    {
        printf("����Ϊ %s �Ķ����������ɹ���\n", Trees.elem[Trees.length].name);
        Trees.length++;
    }
    else if (flag3 == ERROR)
        printf("�ؼ��ʲ�Ψһ������������ʧ�ܣ�\n");
    return OK;
}

// ���ӹ���21 �����������:ɾ��������
// ��Lists��ɾ��һ������ΪTreeName�Ķ�������
status RemoveTree(LISTS& Trees, char ListName[])
{
    int i;
    for (i = 0; i < Trees.length; i++)
        if (!strcmp(Trees.elem[i].name, ListName))  //ƥ�����
            break;
    if (i == Trees.length)
        return ERROR;
    else
    {
        DestroyBiTree(Trees.elem[i].T);
        memset(Trees.elem[i].name, 0, strlen(Trees.elem[i].name));
        Trees.length--;
        for (int j = i; j < Trees.length; j++)
            Trees.elem[j] = Trees.elem[j + 1];
        return OK;
    }
}

// ���ӹ���22 �����������:���Ҷ�����
// ��Lists�в���һ������ΪTreeName�Ķ��������ɹ������߼���ţ����򷵻�0
int LocateTree(LISTS Trees, char ListName[])
{
    for (int i = 0; i < Trees.length; i++)
        if (!strcmp(Trees.elem[i].name, ListName))  //ƥ�����
            return (i + 1);
    return ERROR;
}

// ���ӹ���23 �����������:�����������
// ��ʼ������trees�Ѵ��ڣ���������Ƕ����еı���������
status ListsTraverse(LISTS Trees)
{
    if (Trees.length == 0)
        return ERROR;
    for (int n = 0; n < Trees.length; n++)
    {
        printf("����Ϊ %s ��Ԫ���У�", Trees.elem[n].name);
        PreOrderTraverse(Trees.elem[n].T, visit);
        putchar('\n');
    }
    return OK;
}

// ���ӹ���24 �����������:ѡ��һ������������������ţ������ɶ�����в���
BiTree* ChooseTree(BiTree* T, LISTS& Trees, int i)
{
    if (i > Trees.length || i < 1)
        return NULL;
    else
    {
        T = &(Trees.elem[i - 1].T);  //���ݵ�ַ��ͬʱ�Ķ�����������еĴ���    
        return T;
    }
}
