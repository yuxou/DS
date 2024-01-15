#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;

// ����Ʈ�� �׸� ���
void print_list(ListNode* head)
{
	ListNode* p;

	if (head == NULL) return;
	p = head->link;
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head->link);
	printf("����Ʈ�� ��\n");
}

ListNode* insert_first(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;	// (1)
		head->link = node;		// (2)
	}
	return head;	// ����� ��� �����͸� ��ȯ�Ѵ�. 
}

ListNode* insert_last(ListNode* head, element data)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;	// (1)
		head->link = node;		// (2)
		head = node;		// (3)
	}
	return head;	// ����� ��� �����͸� ��ȯ�Ѵ�. 
}

ListNode* delete_first(ListNode* head)
{
	ListNode* temp;
	if (head == NULL) {
		printf("����Ʈ�� ��� ������ ����\n");
		return NULL;
	}

	if (head->link == head) {
		temp = head;
		head = NULL;
		free(temp);
	}
	else {
		temp = head->link;
		head->link = temp->link;
		free(temp);
	}
	return head;
}
//����Ʈ�� ������ ��� �����ϰ� ����� ��ȯ
ListNode* delete_last(ListNode* head)
{
	ListNode* temp = head;
	
	if (head == NULL) {
		printf("����Ʈ�� ��� ������ ����\n");
		return NULL;
	}
	else if (head->link == head) { //��常 �ִ� ���
		head = NULL;
		free(temp);
		return NULL;
	}
	else {
		while (temp->link != head)
			temp = temp->link;
		temp->link = head->link; //������ ��� link�� head link�� ����

		head = temp; //��� �����͸� ������ ����
		temp = NULL; 
	}
	return head;
}
//data�� ������ �ִ� ù��° ��带 ã�� ��ȯ
ListNode* search(ListNode* head, element data)
{
	if (head == NULL) {
		printf("����Ʈ�� ��� �˻��� ����\n");
		return NULL;
	}

	ListNode* current = head->link;

	while (current != head) {
		if (current->data == data) {
			printf("%d�� ã��\n", data);
			return current;
		}
		current = current->link;
	}

	printf("%d�� ã�� �� ����\n", data);
	return NULL;
}
//����Ʈ�� ���� ��ȯ
int get_size(ListNode* head)
{
	if (head == NULL) {
		printf("����Ʈ�� ��� ����\n");
		return 0;
	}

	int count = 0;
	ListNode* current = head->link;
	
	count++;
	while (current != head) {
		count++;
		current = current->link;
	}
	return count;
}

// ���� ���� ����Ʈ �׽�Ʈ ���α׷�
int main(void)
{
	ListNode* head = NULL;

	// list = 10->20->30->40
	head = insert_last(head, 20);
	print_list(head);

	head = insert_last(head, 30);
	print_list(head);
	
	head = insert_last(head, 40);
	print_list(head);
	
	head = insert_first(head, 10);
	print_list(head);

	//20->30->40
	head = delete_first(head);
	print_list(head);

	//20->30
	head = delete_last(head);
	print_list(head);

	printf("����Ʈ�� ũ��: %d\n", get_size(head));

	search(head, 20);

	return 0;
}