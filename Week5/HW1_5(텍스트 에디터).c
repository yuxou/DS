#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_CHAR_PER_LINE 100

typedef struct {
    char line[MAX_CHAR_PER_LINE];
}element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
}ListNode;
//오류 처리 함수
void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

ListNode* insert_last(ListNode* head, element value)
{
    ListNode* temp = head;
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));

    p->data = value;
    p->link = NULL;

    if (head == NULL)
        head = p;
    else {
        while (temp->link != NULL)
            temp = temp->link;
        temp->link = p;
    }
    return head;
}

int get_length(ListNode* head)
{
    ListNode* current;
    int count = 0;

    for (current = head; current != NULL; current = current->link)
        count++;
    return count;
}

void print_list(ListNode* head, int pos)
{
    ListNode* p = head;
    int i;

    for (i = 1; i < pos; i++)
        p = p->link;
    printf("( %d ) %s", i++, p->data.line);
}

//pos위치에 value를 갖는 노드 추가
ListNode* insert_pos(ListNode* head, int pos, element value)
{
    int i;
    ListNode* p = head;
    ListNode* temp = (ListNode*)malloc(sizeof(ListNode));

    if (pos < 0 || pos > get_length(head))
        error("유효하지 않은 pos");

    temp->data = value;
    for (i = 0; i < pos - 1; i++)
        p = p->link;
    temp->link = p->link;
    p->link = temp;
    
    return head;
}

ListNode* delete_first(ListNode* head)
{
    ListNode* removed;
    if (head == NULL) return NULL;
    removed = head;   // (1)
    head = removed->link;   // (2)
    free(removed);      // (3)
    return head;      // (4)
}
//pos위치의 노드 삭제
ListNode* delete_pos(ListNode* head, int pos)
{
    ListNode* p = head;
    ListNode* removed;
    int i;

    if (pos < 0 || pos >= get_length(head)) 
        error("유효하지 않은 pos");

    if (pos == 0)
        head = delete_first(head);
    else {
        for (i = 0; i < pos - 1; i++)
            p = p->link;
        removed = p->link;
        p->link = removed->link;
        free(removed);
    }
    return head;
}
//text editor을 위해 변경
void display_te(ListNode* head)
{
    int i = 1;

    printf("----------text edited--------- \n");
    for (ListNode* p = head; p != NULL; p = p->link) {
        printf(" ( %d ) %s", i, p->data.line);
        i++;
    }
}

char askChoice(void)
{
    char choice;
    printf("-----------------------------\n");
    printf("a: 텍스트 끝에 라인 추가\n");
    printf("i: 라인 번호로 라인 추가\n");
    printf("d: 라인 번호로 라인 삭제\n");
    printf("v: 라인 번호로 해당 라인 출력\n");
    printf("p: 전체 텍스트 출력\n");
    printf("q: 끝\n");

    printf("메뉴 선택: ");
    scanf("%c", &choice);
    return choice;
}

int main(void)
{
    ListNode* list = NULL;
    char choice;
    int lineNb;
    element newElement;;

    while ((choice = askChoice()) != 'q') {
        switch (choice) {
        case 'a':
            printf("텍스트 끝에 삽입할 라인: ");
            while (getchar() != '\n');
            fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

            list = insert_last(list, newElement);
            display_te(list);

            break;
        case 'i':
            printf("삽입할 라인 번호: ");
            scanf("%d", &lineNb);

            printf("삽입할 라인: ");
            while (getchar() != '\n');
            fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

            list = insert_pos(list, lineNb - 1, newElement);
            display_te(list);

            break;
        case 'd':
            printf("삭제할 라인 번호: ");
            scanf("%d", &lineNb);

            list = delete_pos(list, lineNb - 1);
            display_te(list);

            while (getchar() != '\n');

            break;
        case 'v':
            printf("출력할 라인 번호: ");
            scanf("%d", &lineNb);

            print_list(list, lineNb);

            while (getchar() != '\n');

            break;
        case 'p':
            display_te(list);

            while (getchar() != '\n');

            break;
        default:
            printf("잘못된 입력\n");

            break;
        }
        //while (getchar() != '\n'); //버퍼 비우기
    }
}