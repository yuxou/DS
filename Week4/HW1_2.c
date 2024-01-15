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

void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
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

	while (current != NULL) {
		if (current->data == key) {
			if (pre == NULL) //첫번째 노드 삭제
				head = delete_first(head);
			else //중간 또는 끝 노드 삭제
				head = delete(head, pre);
			
			break;
		}
		pre = current;
		current = current->link;
	}
	
	return head;
	/*
	   ListNode* temp = head;
ListNode* pre = NULL;

while (temp != NULL) {
   if (temp->data == key) {
      pre->link = temp->link;
      break;
   }

   pre = temp;
   temp = temp->link;
}

return head;
*/
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

int main(void)
{
	ListNode* list1 = NULL, * list2 = NULL, * list3 = NULL;

	//list1 = 30->20->10-> 만들고, 10, 20, 30의 순으로 노드 삽입
	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);
	
	//list1 출력
	printf("list1 = ");
	print_list(list1);

	//list1 맨 앞 노드 삭제, list1 = 20->10->
	list1 = delete_first(list1);
	
	//list1 출력
	printf("list1 = ");
	print_list(list1);

	//list2 = 11->22->33->44-> 만들고, 44, 33, 22, 11의 순으로 노드 삽입
	list2 = insert_first(list2, 44);
	list2 = insert_first(list2, 33);
	list2 = insert_first(list2, 22);
	list2 = insert_first(list2, 11);
	
	//list2 출력
	printf("list2 = ");
	print_list(list2);

	//list2 맨 뒤 노드 삭제, list2 = 11->22->33->
	list2 = delete(list2, list2->link->link);
	
	//list2 출력
	printf("list2 = ");
	print_list(list2);

	//list2를 역순으로 바꾼 리스트가 list3, list3 = 33->22->11->
	//list2의 첫번째 노드부터 삽입
	while (list2 != NULL) {
		list3 = insert_first(list3, list2->data);
		list2 = list2->link;
	}
	
	//list3 출력
	printf("list3 = ");
	print_list(list3);

	//list1 = 20->10->33->22->11->, 즉, list1과 list3을 합쳐서 list1을 가리키게
	ListNode* current = list1;
	while (current->link != NULL) {
		current = current->link;
	}
	current->link = list3;

	//list1 출력
	printf("list1 = ");
	print_list(list1);

	//새로 추가한 함수들 테스트
	printf("list1에 20이 있으면 1, 없으면 0, 결과는? %d\n", is_in_list(list1, 20));
	
	printf("list1에 존재하는 노드의 수는? %d\n", get_length(list1));
	
	printf("list1의 모든 데이터 값을 더한 합은? %d\n", get_total(list1));

	printf("list1의 2번째에 있는 값은? (0부터 시작) %d\n", get_entry(list1, 2));

	//list1의 key 33을 삭제한 후, list1 출력
	list1 = delete_by_key(list1, 33);
	//list1 출력
	printf("33을 삭제한 후, list1 = ");
	print_list(list1);

	//pos 위치에 value 갖는 노드 추가
	element value = 99;
	list1 = insert_pos(list1, 2, value);
	//list1 출력
	printf("2번째에 99를 추가한 후 (0부터 시작), list1 = " );
	print_list(list1);

	//pos 위치의 노드 삭제, pos = 3;
	list1 = delete_pos(list1, 3);
	//list1 출력
	printf("3번째의 노드 삭제한 후 (0부터 시작), list1 = ");
	print_list(list1);
}