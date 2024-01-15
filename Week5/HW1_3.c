#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// 노드 타입
	element data;
	struct ListNode* link;
} ListNode;

// 오류 처리 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* insert_first(ListNode* head, int value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));	//(1)
	p->data = value;					// (2)
	p->link = head;	// 헤드 포인터의 값을 복사	//(3)
	head = p;	// 헤드 포인터 변경		//(4)
	return head;	// 변경된 헤드 포인터 반환
}
// 노드 pre 뒤에 새로운 노드 삽입
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
// pre가 가리키는 노드의 다음 노드를 삭제한다. 
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
//item이 리스트에 있으면 1, 없으면 0 반환
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
//단순연결리스트에 존재하는 노드의 수를 반환
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
//단순연결리스트의 모든 데이터 값을 더한 합을 반환
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
//pos위치에 있는 노드의 data 반환
element get_entry(ListNode* head, int pos)
{
	if (pos < 0) {
		error("유효하지 않은 pos");
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
	error("유효하지 않은 pos");
	return -1;
}

ListNode* delete_by_key(ListNode* head, int key)
{
	ListNode* current = head;
	ListNode* pre = NULL;
	int found = 0; //키 여부

	while (current != NULL) {
		if (current->data == key) {
			found = 1;
			if (pre == NULL) //첫번째 노드 삭제
				head = delete_first(head);
			else //중간 또는 끝 노드 삭제
				head = delete(head, pre);

			break;
		}
		pre = current;
		current = current->link;
	}

	if (!found)
		printf("아이템 %d는 보유하고 있지 않습니다.\n", key);

	return head;
}
//pos위치에 value를 갖는 노드 추가
ListNode* insert_pos(ListNode* head, int pos, element value)
{
	if (pos < 0) {
		error("유효하지 않은 pos");
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
//pos위치의 노드 삭제
ListNode* delete_pos(ListNode* head, int pos)
{
	if (pos < 0) {
		error("유효하지 않은 pos");
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
//아이템 추가 함수
void add_item(ListNode** phead, int new_item)
{
	ListNode* current = *phead;
	int total = 0;

	while (current != NULL) {
		total += current->data;
		current = current->link;
	}

	if (total + new_item > 100) {
		printf("최대 무게 <100kg> 초과로 아이템 %d를 추가할 수 없음\n", new_item);
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
		while (getchar() != '\n'); //버퍼 비우기
	} 
}