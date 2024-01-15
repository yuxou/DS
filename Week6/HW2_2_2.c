#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING_SIZE 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int num;
    char str[MAX_STRING_SIZE];
} element;

typedef struct StackNode {
    element data;
    int top;
    struct StackNode* link;
} StackNode;

typedef struct {
    StackNode* top;
} LinkedStackType;

//���� �ʱ�ȭ �Լ�
void init(LinkedStackType* s)
{
    s->top = NULL;
}

//���� ���� ���� �Լ�
int is_empty(LinkedStackType* s)
{
    return s->top == NULL;
}

//��ȭ ���� ���� �Լ�
int is_full(LinkedStackType* s)
{
    return 0;
}

//�����Լ�
void push(LinkedStackType* s, element item)
{
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));

    if (temp == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        return;
    }
    else {
        temp->data = item;
        temp->link = s->top;
        s->top = temp;
    }
}

//���� �Լ�
element pop(LinkedStackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else {
        StackNode* temp = s->top;
        element item = temp->data;
        s->top = s->top->link;
        free(temp);
        return item;
    }
}

//��ũ �Լ�
element peek(LinkedStackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else
        return s->top->data;
}

void stack_print(LinkedStackType* s)
{
    if (is_empty(s))
        printf("<empty>\n");

    for (StackNode* p = s->top; p != NULL; p = p->link) {
        printf("[%d, %s] ", p->data.num, p->data.str);
        if (p == s->top)
            printf(" <- top");
        printf("\n");
    }
    printf("--\n");
}

int main(void)
{
    LinkedStackType s;
    element item;

    init(&s);
    stack_print(&s);

    //10 ����
    item.num = 10;
    strcpy(item.str, "ten");
    push(&s, item);
    stack_print(&s);

    //20 ����
    item.num = 20;
    strcpy(item.str, "twenty");
    push(&s, item);
    stack_print(&s);

    //30 ����
    item.num = 30;
    strcpy(item.str, "thirty");
    push(&s, item);
    stack_print(&s);

    //40 ����
    item.num = 40;
    strcpy(item.str, "forty");
    push(&s, item);
    stack_print(&s);

    //���� 
    pop(&s);
    stack_print(&s);

    //50 ����
    item.num = 50;
    strcpy(item.str, "fifty");
    push(&s, item);
    stack_print(&s);

    //����
    pop(&s);
    stack_print(&s);

    //����
    pop(&s);
    stack_print(&s);

    //����
    pop(&s);
    stack_print(&s);

    //����
    pop(&s);
    stack_print(&s);
}