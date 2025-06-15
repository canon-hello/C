#pragma once
status InitList(SqList* L, const char* name) {
    L->elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    strncpy(L->name, name, MAX_NAME_LENGTH - 1);
    L->name[MAX_NAME_LENGTH - 1] = '\0'; // ȷ���ַ����Կ��ַ���β
    return OK;
}


status DestroyList(SqList* L) {
    if (L->elem == NULL)
        return INFEASTABLE;
    else {
        free(L->elem);
        L->elem = NULL;
        L->length = 0;
        L->listsize = 0;
        // �������������Ա�����
        memset(L->name, 0, MAX_NAME_LENGTH);
        return OK;
    }
}
status ClearList(SqList* L) {
    if (L->elem == NULL)
        return INFEASTABLE;
    else {
        L->length = 0;
        return OK;
    }
}

status ListEmpty(SqList L) {
    if (L.elem == NULL)
        return INFEASTABLE;
    if (L.length == 0)
        return TRUE;
    else return FALSE;
}

int ListLength(SqList L) {
    if (L.elem == NULL)
        return INFEASTABLE;
    else {
        return L.length;
    }
}

status GetElem(SqList L, int i, ElemType* e) {
    if (L.elem == NULL)    //���Ա�����
        return INFEASTABLE;
    if (i > L.length || i <= 0)   //i���Ϸ�
        return ERROR;
    *e = L.elem[i - 1];
    return OK;
}

int LocateElem(SqList L, ElemType e) {
    if (L.elem == NULL)
        return INFEASTABLE;
    for (int i = 0; i < L.length; i++) {
        if (L.elem[i] == e) {
            return i + 1;
        }
    }
    return 0;
}

status PriorElem(SqList L, ElemType e, ElemType* pre) {
    if (L.elem == NULL)
        return INFEASTABLE;
    for (int i = 1; i < L.length; i++) {
        if (L.elem[i] == e) {
            *pre = L.elem[i - 1];
            return OK;
        }
    }
    return ERROR;
}

status NextElem(SqList L, ElemType e, ElemType* next) {
    if (L.elem == NULL)
        return INFEASTABLE;
    for (int i = 0; i < L.length - 1; i++) {
        if (L.elem[i] == e) {
            *next = L.elem[i + 1];
            return OK;
        }
    }
    return ERROR;
}

status ListInsert(SqList* L, int i, ElemType e) {
    if (L->elem == NULL)
        return INFEASTABLE;
    if (i < 1 || i > L->length + 1) {
        return ERROR;
    }
    if (L->length >= L->listsize) {
        ElemType* newbase = (ElemType*)realloc(L->elem, sizeof(ElemType) * (L->listsize + LISTINCREMENT));
        if (!newbase) {
            return OVERFLOW;
        }
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    for (int j = L->length; j >= i; j--) {
        L->elem[j] = L->elem[j - 1];
    }
    L->elem[i - 1] = e;
    L->length++;
    return OK;
}

status ListDelete(SqList* L, int i, ElemType* e) {
    if (L->elem == NULL) {
        return INFEASTABLE;
    }
    // ���ɾ��λ���Ƿ�Ϸ�
    if (i < 1 || i > L->length) {
        return ERROR;
    }
    // ��ȡҪɾ����Ԫ��
    *e = L->elem[i - 1];
    // �������Ԫ������ǰ��
    for (int j = i; j < L->length; j++) {
        L->elem[j - 1] = L->elem[j];
    }
    // ���Ա��ȼ� 1
    L->length--;
    return OK;
}

status ListTrabverse(SqList L) {
    int i;
    printf("\n-----------all elements -----------------------\n");
    printf("���Ա� '%s' ��Ԫ�أ�\n", L.name);
    for (i = 0; i < L.length; i++) printf("%d ", L.elem[i]);
    printf("\n------------------ end ------------------------\n");
    return L.length;
}

int MaxSubArray(SqList L) {
    if (L.elem == NULL || L.length == 0) return INFEASTABLE;

    int maxSum = L.elem[0];
    int currentSum = L.elem[0];

    for (int i = 1; i < L.length; i++) {
        currentSum = (currentSum + L.elem[i]) > L.elem[i] ? (currentSum + L.elem[i]) : L.elem[i];
        maxSum = currentSum > maxSum ? currentSum : maxSum;
    }

    return maxSum;
}

int SubArrayNum(SqList L, int k) {
    if (L.elem == NULL || L.length == 0) return INFEASTABLE;

    int count = 0;

    for (int i = 0; i < L.length; i++) {
        int sum = 0;
        for (int j = i; j < L.length; j++) {
            sum += L.elem[j];
            if (sum == k) {
                count++;
            }
        }
    }

    return count;
}

status sortList(SqList* L) {
    if (L->elem == NULL) return INFEASTABLE;

    // ʹ��ð������ʵ��
    for (int i = 0; i < L->length - 1; i++) {
        for (int j = 0; j < L->length - i - 1; j++) {
            if (L->elem[j] > L->elem[j + 1]) {
                // ����Ԫ��
                ElemType temp = L->elem[j];
                L->elem[j] = L->elem[j + 1];
                L->elem[j + 1] = temp;
            }
        }
    }

    return OK;
}

status saveListToFile(SqList L, const char* filename) {
    if (L.elem == NULL) return INFEASTABLE;

    FILE* file = fopen(filename, "wb");
    if (file == NULL) return ERROR;

    // д�����Ա���
    fwrite(&L.length, sizeof(int), 1, file);

    // д��Ԫ��
    fwrite(L.elem, sizeof(ElemType), L.length, file);

    fclose(file);
    return OK;
}

status loadListFromFile(SqList* L, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) return ERROR;

    // ���ͷ�ԭ���ڴ�
    if (L->elem != NULL) {
        free(L->elem);
        L->elem = NULL;
    }

    // ��ȡ���Ա���
    int length;
    fread(&length, sizeof(int), 1, file);

    // �����ڴ�
    L->elem = (ElemType*)malloc(length * sizeof(ElemType));
    if (L->elem == NULL) {
        fclose(file);
        return OVERFLOW;
    }

    // ��ȡԪ��
    fread(L->elem, sizeof(ElemType), length, file);

    L->length = length;
    L->listsize = length;  // �򻯴�����listsize���ڵ�ǰ����

    fclose(file);
    return OK;
}

status initMultiListManager(MultiListManager* manager) {
    manager->count = 0;
    manager->current = -1;
    return OK;
}

status addNewList(MultiListManager* manager, const char* name) {
    if (manager->count >= MAX_LISTS) return ERROR;

    SqList* newList = &manager->lists[manager->count];

    if (InitList(newList, name) == OK) {
        manager->count++;
        manager->current = manager->count - 1;  // �л����´������б�
        return OK;
    }
    else {
        return ERROR;
    }
}

status removeList(MultiListManager* manager, int index) {
    if (index < 0 || index >= manager->count) return ERROR;

    // ����ָ�����Ա�
    DestroyList(&manager->lists[index]);

    // ����������Ա�ǰ��
    for (int i = index; i < manager->count - 1; i++) {
        manager->lists[i] = manager->lists[i + 1];
    }

    // �������һ��λ�õ����Ա���Ϣ�������Ѿ���Ч��
    memset(&manager->lists[manager->count - 1], 0, sizeof(SqList));

    // �������Ա����
    manager->count--;

    // ������ǰ����
    if (manager->current >= manager->count) {
        manager->current = manager->count - 1;
        if (manager->current < 0) manager->current = -1;  // ���û���б��ˣ���Ϊ-1
    }

    return OK;
}

int findListIndexByName(MultiListManager* manager, const char* name) {
    for (int i = 0; i < manager->count; i++) {
        if (strcmp(manager->lists[i].name, name) == 0) {
            return i;
        }
    }
    return -1; // û�ҵ�
}

status switchToListByName(MultiListManager* manager, const char* name) {
    int index = findListIndexByName(manager, name);
    if (index == -1) return ERROR;

    manager->current = index;
    return OK;
}

void printListNames(MultiListManager* manager) {
    printf("\n�������Ա����ƣ�\n");
    for (int i = 0; i < manager->count; i++) {
        printf("%d. %s\n", i + 1, manager->lists[i].name);
    }
    printf("\n");
}
void searchList(MultiListManager* manager) {
    char listName[MAX_NAME_LENGTH];
    printf("������Ҫ�����ı������: ");
    scanf("%s", listName);
    int index = findListIndexByName(manager, listName);
    if (index != -1) {
        printf("�ҵ���Ϊ'%s'�ı�������Ϊ %d\n", listName, index+1);
    }
    else {
        printf("δ�ҵ���Ϊ'%s'�ı�\n", listName);
    }
}