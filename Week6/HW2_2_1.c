#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct StackNode {
    element data;
    struct StackNode *link;
} StackNode;

typedef struct {
    StackNode* top;
} LinkedStackType;

//�ʱ�ȭ �Լ�
void init(LinkedStackType *s)
{
    s->top = NULL;
}
//���� ���� ���� �Լ�
int is_empty(LinkedStackType *s)
{
    return s->top == NULL;
}
//��ȭ ���� ���� �Լ�, �� ������ ���� ����
int is_full(LinkedStackType *s)
{
    return 0;
}
//�����Լ�
void push(LinkedStackType *s, element item)
{
    StackNode *temp = (StackNode*)malloc(sizeof(StackNode));

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
element peek(LinkedStackType *s)
{
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else
        return s->top->data;
}

void stack_print(LinkedStackType *s)
{
    if (is_empty(s))
        printf("<empty>\n");
   
    for (StackNode *p = s->top; p != NULL; p = p->link) {
        printf("%d", p->data);
        if (p == s->top)
            printf(" <- top");
        printf("\n");
    }
    printf("--\n");
}
int main(void)
{
    LinkedStackType s;

    init(&s);
    stack_print(&s);

    //10 ����
    push(&s, 10);
    stack_print(&s);

    //20 ����
    push(&s, 20);
    stack_print(&s);

    //30 ����
    push(&s, 30);
    stack_print(&s);

    //40 ����
    push(&s, 40);
    stack_print(&s);

    //����
    pop(&s);
    stack_print(&s);

    //50 ����
    push(&s, 50);
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