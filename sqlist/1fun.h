#pragma once
status InitList(SqList* L, const char* name) {
    L->elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    strncpy(L->name, name, MAX_NAME_LENGTH - 1);
    L->name[MAX_NAME_LENGTH - 1] = '\0'; // 确保字符串以空字符结尾
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
        // 新增：重置线性表名称
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
    if (L.elem == NULL)    //线性表不存在
        return INFEASTABLE;
    if (i > L.length || i <= 0)   //i不合法
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
    // 检查删除位置是否合法
    if (i < 1 || i > L->length) {
        return ERROR;
    }
    // 获取要删除的元素
    *e = L->elem[i - 1];
    // 将后面的元素依次前移
    for (int j = i; j < L->length; j++) {
        L->elem[j - 1] = L->elem[j];
    }
    // 线性表长度减 1
    L->length--;
    return OK;
}

status ListTrabverse(SqList L) {
    int i;
    printf("\n-----------all elements -----------------------\n");
    printf("线性表 '%s' 的元素：\n", L.name);
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

    // 使用冒泡排序实现
    for (int i = 0; i < L->length - 1; i++) {
        for (int j = 0; j < L->length - i - 1; j++) {
            if (L->elem[j] > L->elem[j + 1]) {
                // 交换元素
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

    // 写入线性表长度
    fwrite(&L.length, sizeof(int), 1, file);

    // 写入元素
    fwrite(L.elem, sizeof(ElemType), L.length, file);

    fclose(file);
    return OK;
}

status loadListFromFile(SqList* L, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) return ERROR;

    // 先释放原有内存
    if (L->elem != NULL) {
        free(L->elem);
        L->elem = NULL;
    }

    // 读取线性表长度
    int length;
    fread(&length, sizeof(int), 1, file);

    // 分配内存
    L->elem = (ElemType*)malloc(length * sizeof(ElemType));
    if (L->elem == NULL) {
        fclose(file);
        return OVERFLOW;
    }

    // 读取元素
    fread(L->elem, sizeof(ElemType), length, file);

    L->length = length;
    L->listsize = length;  // 简化处理，让listsize等于当前长度

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
        manager->current = manager->count - 1;  // 切换到新创建的列表
        return OK;
    }
    else {
        return ERROR;
    }
}

status removeList(MultiListManager* manager, int index) {
    if (index < 0 || index >= manager->count) return ERROR;

    // 销毁指定线性表
    DestroyList(&manager->lists[index]);

    // 将后面的线性表前移
    for (int i = index; i < manager->count - 1; i++) {
        manager->lists[i] = manager->lists[i + 1];
    }

    // 重置最后一个位置的线性表信息（现在已经无效）
    memset(&manager->lists[manager->count - 1], 0, sizeof(SqList));

    // 减少线性表计数
    manager->count--;

    // 调整当前索引
    if (manager->current >= manager->count) {
        manager->current = manager->count - 1;
        if (manager->current < 0) manager->current = -1;  // 如果没有列表了，设为-1
    }

    return OK;
}

int findListIndexByName(MultiListManager* manager, const char* name) {
    for (int i = 0; i < manager->count; i++) {
        if (strcmp(manager->lists[i].name, name) == 0) {
            return i;
        }
    }
    return -1; // 没找到
}

status switchToListByName(MultiListManager* manager, const char* name) {
    int index = findListIndexByName(manager, name);
    if (index == -1) return ERROR;

    manager->current = index;
    return OK;
}

void printListNames(MultiListManager* manager) {
    printf("\n所有线性表名称：\n");
    for (int i = 0; i < manager->count; i++) {
        printf("%d. %s\n", i + 1, manager->lists[i].name);
    }
    printf("\n");
}
void searchList(MultiListManager* manager) {
    char listName[MAX_NAME_LENGTH];
    printf("请输入要搜索的表的名称: ");
    scanf("%s", listName);
    int index = findListIndexByName(manager, listName);
    if (index != -1) {
        printf("找到名为'%s'的表，其索引为 %d\n", listName, index+1);
    }
    else {
        printf("未找到名为'%s'的表\n", listName);
    }
}