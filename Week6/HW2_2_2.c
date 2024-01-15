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

//스택 초기화 함수
void init(LinkedStackType* s)
{
    s->top = NULL;
}

//공백 상태 검출 함수
int is_empty(LinkedStackType* s)
{
    return s->top == NULL;
}

//포화 상태 검출 함수
int is_full(LinkedStackType* s)
{
    return 0;
}

//삽입함수
void push(LinkedStackType* s, element item)
{
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));

    if (temp == NULL) {
        fprintf(stderr, "메모리 할당 에러\n");
        return;
    }
    else {
        temp->data = item;
        temp->link = s->top;
        s->top = temp;
    }
}

//삭제 함수
element pop(LinkedStackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
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

//피크 함수
element peek(LinkedStackType* s)
{
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
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

    //10 삽입
    item.num = 10;
    strcpy(item.str, "ten");
    push(&s, item);
    stack_print(&s);

    //20 삽입
    item.num = 20;
    strcpy(item.str, "twenty");
    push(&s, item);
    stack_print(&s);

    //30 삽입
    item.num = 30;
    strcpy(item.str, "thirty");
    push(&s, item);
    stack_print(&s);

    //40 삽입
    item.num = 40;
    strcpy(item.str, "forty");
    push(&s, item);
    stack_print(&s);

    //삭제 
    pop(&s);
    stack_print(&s);

    //50 삽입
    item.num = 50;
    strcpy(item.str, "fifty");
    push(&s, item);
    stack_print(&s);

    //삭제
    pop(&s);
    stack_print(&s);

    //삭제
    pop(&s);
    stack_print(&s);

    //삭제
    pop(&s);
    stack_print(&s);

    //삭제
    pop(&s);
    stack_print(&s);
}