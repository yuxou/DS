#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// 노드 타입
	element data;
	struct ListNode* link;
} ListNode;

// 리스트의 항목 출력
void print_list(ListNode* head)
{
	ListNode* p;

	if (head == NULL) return;
	p = head->link;
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head->link);
	printf("리스트의 끝\n");
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
	return head;	// 변경된 헤드 포인터를 반환한다. 
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
	return head;	// 변경된 헤드 포인터를 반환한다. 
}

ListNode* delete_first(ListNode* head)
{
	ListNode* temp;
	if (head == NULL) {
		printf("리스트가 비어 삭제를 못함\n");
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
//리스트의 마지막 노드 삭제하고 헤드노드 반환
ListNode* delete_last(ListNode* head)
{
	ListNode* temp = head;
	
	if (head == NULL) {
		printf("리스트가 비어 삭제를 못함\n");
		return NULL;
	}
	else if (head->link == head) { //헤드만 있는 경우
		head = NULL;
		free(temp);
		return NULL;
	}
	else {
		while (temp->link != head)
			temp = temp->link;
		temp->link = head->link; //마지막 노드 link를 head link로 설정

		head = temp; //헤드 포인터를 마지막 노드로
		temp = NULL; 
	}
	return head;
}
//data를 가지고 있는 첫번째 노드를 찾아 반환
ListNode* search(ListNode* head, element data)
{
	if (head == NULL) {
		printf("리스트가 비어 검색을 못함\n");
		return NULL;
	}

	ListNode* current = head->link;

	while (current != head) {
		if (current->data == data) {
			printf("%d를 찾음\n", data);
			return current;
		}
		current = current->link;
	}

	printf("%d를 찾을 수 없음\n", data);
	return NULL;
}
//리스트의 길이 반환
int get_size(ListNode* head)
{
	if (head == NULL) {
		printf("리스트가 비어 있음\n");
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

// 원형 연결 리스트 테스트 프로그램
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

	printf("리스트의 크기: %d\n", get_size(head));

	search(head, 20);

	return 0;
}