#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;

// ���� ó�� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* insert_first(ListNode* head, int value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));	//(1)
	p->data = value;					// (2)
	p->link = head;	// ��� �������� ���� ����	//(3)
	head = p;	// ��� ������ ����		//(4)
	return head;	// ����� ��� ������ ��ȯ
}
// ��� pre �ڿ� ���ο� ��� ����
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));	//(1)
	p->data = value;		//(2)
	p->link = pre->link;	//(3)	
	pre->link = p;		//(4)	
	return head;		//(5)	
}

ListNode* delete_first(ListNode* head)
{
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;	// (1)
	head = removed->link;	// (2)
	free(removed);		// (3)
	return head;		// (4)
}
// pre�� ����Ű�� ����� ���� ��带 �����Ѵ�. 
ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;		// (2)
	free(removed);			// (3)
	return head;			// (4)
}

void display(ListNode* head)
{
	printf("< ");
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d ", p->data);
	printf(" >\n");
}
//item�� ����Ʈ�� ������ 1, ������ 0 ��ȯ
int is_in_list(ListNode* head, element item)
{
	ListNode* current = head;

	while (current != NULL) {
		if (current->data == item)
			return 1;
		current = current->link;
	}
	return 0;
}
//�ܼ����Ḯ��Ʈ�� �����ϴ� ����� ���� ��ȯ
int get_length(ListNode* head)
{
	ListNode* current = head;
	int count = 0;

	while (current != NULL) {
		count++;
		current = current->link;
	}
	return count;
}
//�ܼ����Ḯ��Ʈ�� ��� ������ ���� ���� ���� ��ȯ
int get_total(ListNode* head)
{
	ListNode* current = head;
	int total = 0;

	while (current != NULL) {
		total += current->data;
		current = current->link;
	}
	return total;
}
//pos��ġ�� �ִ� ����� data ��ȯ
element get_entry(ListNode* head, int pos)
{
	if (pos < 0) {
		error("��ȿ���� ���� pos");
		return -1;
	}

	ListNode* current = head;
	int index = 0;

	while (current != NULL) {
		if (index == pos)
			return current->data;
		index++;
		current = current->link;
	}
	error("��ȿ���� ���� pos");
	return -1;
}

ListNode* delete_by_key(ListNode* head, int key)
{
	ListNode* current = head;
	ListNode* pre = NULL;
	int found = 0; //Ű ����

	while (current != NULL) {
		if (current->data == key) {
			found = 1;
			if (pre == NULL) //ù��° ��� ����
				head = delete_first(head);
			else //�߰� �Ǵ� �� ��� ����
				head = delete(head, pre);

			break;
		}
		pre = current;
		current = current->link;
	}

	if (!found)
		printf("������ %d�� �����ϰ� ���� �ʽ��ϴ�.\n", key);

	return head;
}
//pos��ġ�� value�� ���� ��� �߰�
ListNode* insert_pos(ListNode* head, int pos, element value)
{
	if (pos < 0) {
		error("��ȿ���� ���� pos");
		return head;
	}

	if (pos == 0)
		head = insert_first(head, value);
	else {
		int index = 0;
		ListNode* current = head;
		ListNode* pre = NULL;

		while (current != NULL) {
			if (index == pos) {
				head = insert(head, pre, value);
				break;
			}

			index++;
			pre = current;
			current = current->link;
		}

		if (index < pos)
			printf("Error\n");
	}
	return head;
}
//pos��ġ�� ��� ����
ListNode* delete_pos(ListNode* head, int pos)
{
	if (pos < 0) {
		error("��ȿ���� ���� pos");
		return head;
	}

	if (pos == 0)
		head = delete_first(head);
	else {
		int index = 0;
		ListNode* current = head;
		ListNode* pre = NULL;

		while (current != NULL) {
			if (index == pos) {
				head = delete(head, pre);
				break;
			}

			index++;
			pre = current;
			current = current->link;
		}
	}
	return head;
}
//������ �߰� �Լ�
void add_item(ListNode** phead, int new_item)
{
	ListNode* current = *phead;
	int total = 0;

	while (current != NULL) {
		total += current->data;
		current = current->link;
	}

	if (total + new_item > 100) {
		printf("�ִ� ���� <100kg> �ʰ��� ������ %d�� �߰��� �� ����\n", new_item);
		return;
	}

	ListNode* new = (ListNode*)malloc(sizeof(ListNode));

	new->data = new_item;
	new->link = *phead;
	*phead = new;
}

int main(void)
{
	ListNode* list = NULL;
	char choice = 'b';
	int item;

	while (choice != 'q') {
		printf("enter a<dd>, d<elete> or q<uit>: ");
		scanf("%c", &choice);

		switch (choice) {
		case 'a':
			printf("enter the weight of the item: ");
			scanf("%d", &item);

			add_item(&list, item);
			display(list);
			
			break;
		case 'd':
			printf("enter the weight of the item: ");
			scanf("%d", &item);

			list = delete_by_key(list, item);
			display(list);
			break;
		case 'q':
			break;
		} 
		while (getchar() != '\n'); //���� ����
	} 
}