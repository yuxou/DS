#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

HeapType* create()
{
    return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h)
{
    h->heap_size = 0;
}

void insert_max_heap(HeapType* h, element item)
{
    int i;
    i = ++(h->heap_size);

    while ((i != 1) && (item.key > h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

element delete_max_heap(HeapType* h)
{
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if ((child < h->heap_size) &&
            (h->heap[child].key) < h->heap[child + 1].key)
            child++;
        if (temp.key >= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

void preorder(HeapType* h, int root)
{
    if (root <= h->heap_size) {
        printf("%d ", h->heap[root].key);
        preorder(h, root * 2);
        preorder(h, root * 2 + 1);
    }
}

void print_heap(HeapType* h)
{
    int n = 4;

    printf("%d\n", h->heap[1].key);

    for (int i = 2; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);

        if ((i + 1) == n) {
            printf("\n");
            n *= 2;
        }
    }
    printf("\n");
}
//key 값을 포함하는 element를 찾아 그 index를 반환하는 함수
int find(HeapType* h, int root, int key)
{
    while (root <= h->heap_size) {
        if (h->heap[root].key == key)
            return root;

        int right = root * 2 + 1;
        int left = root * 2;

        //왼쪽 자식에서 찾은 경우
        if (left <= h->heap_size && h->heap[left].key == key)
            return left;
        //오른쪽 자식에서 찾은 경우
        if (right <= h->heap_size && h->heap[right].key == key)
            return right;

        root++;
    }
    return 0;
}

void print_sorted_value(HeapType* h)
{
    element n[100];
    int size = h->heap_size;

    for (int i = 0; i < size; i++) {
        n[i] = delete_max_heap(h);
        printf("%d ", n[i].key);
    }
    for (int i = 0; i < size; i++) {
        insert_max_heap(h, n[i]);
    }
    printf("\n");
}

//old를 갖고 있는 element를 찾아 key값을 new로 바꿔야 한다.
//함수 수행 이후에 최대 heap의 조건을 만족해야 한다.
void modify_priority(HeapType* h, int old, int new)
{
    if (old == new)
        return;

    int index = find(h, 1, old);

    if (index == 0)
        return;

    if (new > old) {
        while ((index != 1) && (new > h->heap[index / 2].key)) {
            h->heap[index] = h->heap[index / 2];
            index /= 2;
        } 
        h->heap[index].key = new;
    }
    else {
        int parent = index / 2;

        while ((parent >= 1) && (new > h->heap[parent].key)) {
            h->heap[index] = h->heap[parent];
            index = parent;
            parent = index / 2;
        }
        h->heap[index].key = new;
    }
}

int main(void)
{
    element e1 = { 10 }, e2 = { 5 }, e3 = { 30 }, eA = { 9 }, eB = { 19 }, eC = { 39 };
    element e4, e5, e6;
    int index;
    int key, oldKey, newKey;
    HeapType heap;

    init(&heap);

    printf("Step1: 삽입된 10, 5, 30에 추가적으로 9, 19, 39를 <삽입>한다\n");
    insert_max_heap(&heap, e1);
    insert_max_heap(&heap, e2);
    insert_max_heap(&heap, e3);
    insert_max_heap(&heap, eA);
    insert_max_heap(&heap, eB);
    insert_max_heap(&heap, eC);

    printf("\nStep2: preorder, print_heap 함수 테스트\n");
    preorder(&heap, 1);
    printf("\n");
    print_heap(&heap);

    e4 = delete_max_heap(&heap);
    printf("\n삭제: %d 루트가 삭제됨\n", e4.key);
    print_heap(&heap);

    printf("\nStep3: find 함수 테스트\n");
    printf("찾을 key 입력(-1 for exit): ");
    scanf("%d", &key);
    while (key != -1) {
        if ((index = find(&heap, 1, key)) == 0)
            printf("%d는 없음\n", key);
        else
            printf("%d는 [%d]에 있음\n", key, index);
        printf("찾을 key 입력(-1 for exit): ");
        scanf("%d", &key);
    }

    printf("\nStep4: print_sorted value 함수 테스트:\n");
    print_sorted_value(&heap);

    printf("\nStep5: modify_priority 함수 테스트\n");
    printf("바꿀 key 입력(-1 for exit): ");
    scanf("%d", &oldKey);
    while (oldKey != -1) {
        printf("새 key 입력: ");
        scanf("%d", &newKey);
        modify_priority(&heap, oldKey, newKey);
        print_heap(&heap);

        printf("바꿀 key 입력(-1 for exit): ");
        scanf("%d", &oldKey);
    }
}