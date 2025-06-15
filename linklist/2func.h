#pragma once


status Compare(ElemType e, ElemType elem)
{
    if (elem == e)
        return OK;
    return ERROR;
}

void visit(ElemType elem)
{
    printf("%d ", elem);
}

status InitList(LinkList& L)
{
    if (L != NULL)
        return INFEASIBLE;
    else
    {
        L = (LNode*)malloc(sizeof(LNode));
        L->next = NULL;
        return OK;
    }
}

status DestroyList(LinkList& L)
{
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        LNode* p = NULL;
        while (L)
        {
            p = L;
            L = L->next;
            free(p);
        }
        L = NULL;
        return OK;
    }
}

status ClearList(LinkList& L)
{
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        LNode* p = L->next, * q = NULL;

        while (p)
        {
            q = p;
            p = p->next;
            free(q);
        }
        L->next = NULL;
        return OK;
    }
}

status ListEmpty(LinkList L)
{
    if (L == NULL)
        return INFEASIBLE;
    else if (L->next == NULL)
        return TRUE;
    return FALSE;
}

int ListLength(LinkList L)
{
    int num = 0;
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        for (LNode* p = L->next; p != NULL; p = p->next)
            num++;
        return num;
    }
}

status GetElem(LinkList L, int i, ElemType& e)
{
    int j = 1;
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        if (L->next == NULL)
            return ERROR;
        if (i < 1)
            return ERROR;
        for (LNode* p = L->next; j <= i; p = p->next, j++)
        {
            if (p == NULL)
                return ERROR;
            if (j == i)
            {
                e = p->data;
                return OK;
            }
        }
    }
}

int LocateElem(LinkList L, ElemType e, status(*CompareArr)(ElemType, ElemType))
{
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        LNode* p = L->next;
        for (int i = 1; p != NULL; p = p->next, i++)
            if (p->data == e)
                return i;
        return ERROR;
    }
}

status PriorElem(LinkList L, ElemType e, ElemType& pre)
{
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        LNode* p = L->next, * q = L;
        for (; p != NULL; p = p->next, q = q->next)
            if (p->data == e && q != L)
            {
                pre = q->data;
                return OK;
            }
        return ERROR;
    }
}

status NextElem(LinkList L, ElemType e, ElemType& next)
{
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        if (L->next == NULL)
            return ERROR;
        LNode* p = L->next, * q = L->next->next;
        for (; q != NULL; p = p->next, q = q->next)
            if (p->data == e && q != NULL)
            {
                next = q->data;
                return OK;
            }
        return ERROR;
    }
}

status ListInsert(LinkList& L, int i, ElemType e)
{
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        int j = 1;
        for (LNode* p = L->next; p != NULL; p = p->next)
        {
            j++;
            if (j == i)
            {
                LNode* q = (LNode*)malloc(sizeof(LNode));
                q->data = e;
                q->next = p->next;
                p->next = q;
                return OK;
            }
        }
        return ERROR;
    }
}

status ListDelete(LinkList& L, int i, ElemType& e)
{
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        int j = 1;
        for (LNode* p = L->next, *pre = L; p != NULL; p = p->next, pre = pre->next, j++)
            if (j == i)
            {
                e = p->data;
                if (p->next != NULL)
                    pre->next = p->next;
                else
                    pre->next = NULL;
                free(p);
                return OK;
            }
        return ERROR;
    }
}

status ListTraverse(LinkList L, void (*visitArr) (ElemType))
{
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        printf("\n-------------- all elements -------------------\n");
        for (LNode* p = L->next; p != NULL; p = p->next)
            if (p != L)
                visit(p->data);
        printf("\n------------------ end ------------------------\n");
        return OK;
    }
}

status reverseList(LinkList& L)
{
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        LinkList p;
        LNode* q, * pnext = NULL;
        p = (LNode*)malloc(sizeof(LNode));
        p->next = pnext;
        for (q = L->next; q != NULL; q = q->next)
        {
            p->data = q->data;
            pnext = p;
            p = (LNode*)malloc(sizeof(LNode));
            p->next = pnext;
        }
        L = p;
        return OK;
    }
}

int RemoveNthFromEnd(LinkList& L, int n)
{
    if (L == NULL)
        return INFEASIBLE;
    else if (ListEmpty(L) == TRUE)
        return ERROR;
    else
    {
        int len, m, node;
        len = ListLength(L);
        if (n > len)
            return ERROR;
        m = len + 1 - n;
        ListDelete(L, m, n);
        return n;
    }
}

status sortList(LinkList& L)
{
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        LNode* p, * q;
        for (p = L->next; p != NULL; p = p->next)
            for (q = p->next; q != NULL; q = q->next)
                if (q->data < p->data)
                {
                    int tmp = q->data;
                    q->data = p->data;
                    p->data = tmp;
                }
        return OK;
    }
}

status SaveList(LinkList L, char FileName[])
{
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        FILE* fp = fopen(FileName, "w");
        for (LNode* p = L->next; p != NULL; p = p->next)
            fprintf(fp, "%d ", p->data);
        fclose(fp);
        return OK;
    }
}

status LoadList(LinkList& L, char FileName[])
{
    if (L != NULL)
        return INFEASIBLE;
    else
    {
        int tmp;
        FILE* fp = fopen(FileName, "r");
        L = (LNode*)malloc(sizeof(LNode));
        L->next = NULL;
        LNode* q = L;
        while (fscanf(fp, "%d", &tmp) == 1)
        {
            LNode* p = (LNode*)malloc(sizeof(LNode));
            p->data = tmp;
            q->next = p;
            p->next = NULL;
            q = p;
        }
        fclose(fp);
        return OK;
    }
}

status AddList(LISTS& Lists, char ListName[])
{
    for (int i = 0; i < Lists.length; i++)
        if (!strcmp(Lists.elem[i].name, ListName))
        {
            printf("???????????????? %s ?????????\n", ListName);
            return ERROR;
        }
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L = (LNode*)malloc(sizeof(LNode));
    Lists.elem[Lists.length].L->next = NULL;
    Lists.length++;
    return OK;
}

status RemoveList(LISTS& Lists, char ListName[])
{
    int i;
    for (i = 0; i < Lists.length; i++)
        if (!strcmp(Lists.elem[i].name, ListName))
            break;
    if (i == Lists.length)
        return ERROR;
    else
    {
        DestroyList(Lists.elem[i].L);
        memset(Lists.elem[i].name, 0, strlen(Lists.elem[i].name));
        Lists.length--;
        for (int j = i; j < Lists.length; j++)
            Lists.elem[j] = Lists.elem[j + 1];
        return OK;
    }
}

int LocateList(LISTS Lists, char ListName[])
{
    for (int i = 0; i < Lists.length; i++)
        if (!strcmp(Lists.elem[i].name, ListName))
            return (i + 1);
    return ERROR;
}

status ListsTraverse(LISTS Lists)
{
    if (Lists.length == 0)
        return ERROR;
    for (int n = 0; n < Lists.length; n++)
    {
        printf("????? %s ??????¡ì??", Lists.elem[n].name);
        ListTraverse(Lists.elem[n].L, visit);
        putchar('\n');
    }
    return OK;
}

LinkList* ChooseList(LinkList* L, LISTS& Lists, int i)
{
    if (i > Lists.length || i < 1)
        return NULL;
    else
    {
        L = &(Lists.elem[i - 1].L);
        return L;
    }
}