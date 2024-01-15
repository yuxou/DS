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
//���� ó�� �Լ�
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

//pos��ġ�� value�� ���� ��� �߰�
ListNode* insert_pos(ListNode* head, int pos, element value)
{
    int i;
    ListNode* p = head;
    ListNode* temp = (ListNode*)malloc(sizeof(ListNode));

    if (pos < 0 || pos > get_length(head))
        error("��ȿ���� ���� pos");

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
//pos��ġ�� ��� ����
ListNode* delete_pos(ListNode* head, int pos)
{
    ListNode* p = head;
    ListNode* removed;
    int i;

    if (pos < 0 || pos >= get_length(head)) 
        error("��ȿ���� ���� pos");

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
//text editor�� ���� ����
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
    printf("a: �ؽ�Ʈ ���� ���� �߰�\n");
    printf("i: ���� ��ȣ�� ���� �߰�\n");
    printf("d: ���� ��ȣ�� ���� ����\n");
    printf("v: ���� ��ȣ�� �ش� ���� ���\n");
    printf("p: ��ü �ؽ�Ʈ ���\n");
    printf("q: ��\n");

    printf("�޴� ����: ");
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
            printf("�ؽ�Ʈ ���� ������ ����: ");
            while (getchar() != '\n');
            fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

            list = insert_last(list, newElement);
            display_te(list);

            break;
        case 'i':
            printf("������ ���� ��ȣ: ");
            scanf("%d", &lineNb);

            printf("������ ����: ");
            while (getchar() != '\n');
            fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);

            list = insert_pos(list, lineNb - 1, newElement);
            display_te(list);

            break;
        case 'd':
            printf("������ ���� ��ȣ: ");
            scanf("%d", &lineNb);

            list = delete_pos(list, lineNb - 1);
            display_te(list);

            while (getchar() != '\n');

            break;
        case 'v':
            printf("����� ���� ��ȣ: ");
            scanf("%d", &lineNb);

            print_list(list, lineNb);

            while (getchar() != '\n');

            break;
        case 'p':
            display_te(list);

            while (getchar() != '\n');

            break;
        default:
            printf("�߸��� �Է�\n");

            break;
        }
        //while (getchar() != '\n'); //���� ����
    }
}