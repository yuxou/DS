#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 3
#define MAX_STRING_SIZE 100

typedef struct {
    int num;
    char str[MAX_STRING_SIZE];
} element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

//���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
    s->top = -1;
}

//���� ���� ���� �Լ�
int is_empty(StackType* s)
{
    return (s->top == -1);
}

//��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}

//�����Լ�
void push(StackType* s, element item)
{
    if (is_full(s)) {
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    else s->data[++(s->top)] = item;
}

//���� �Լ�
element pop(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else
        return s->data[(s->top)--];
}

//��ũ �Լ�
element peek(StackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else return s->data[s->top];
}

void stack_print(StackType* s)
{
    if (is_empty(s)) 
        printf("<empty>\n");
    else {
        printf("[%d, %s] <- top\n", s->data[s->top].num, s->data[s->top].str);
        for (int i = s->top - 1; i >= 0; i--) 
            printf("[%d, %s]\n", s->data[i].num, s->data->str);
    }

    printf("--\n");
}

int main(void)
{
    StackType s;
    element item;

    init_stack(&s);
    stack_print(&s);
    
    //10 ����
    item.num = 10;
    strcpy(item.str, "\"ten\"");
    push(&s, item);
    stack_print(&s);
    
    //20 ����
    item.num = 20;
    strcpy(item.str, "\"twenty\"");
    push(&s, item);
    stack_print(&s);
 
    //30 ����
    item.num = 30;
    strcpy(item.str, "\"thirty\"");
    push(&s, item);
    stack_print(&s);
 
    //40 ����
    item.num = 40;
    strcpy(item.str, "\"forty\"");
    push(&s, item);
    stack_print(&s);
 
    //���� 
    pop(&s);
    stack_print(&s);

    //50 ����
    item.num = 50;
    strcpy(item.str, "\"fifty\"");
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
}