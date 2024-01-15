#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// 노드 타입
	element number;
	struct ListNode* link;
} ListNode;

//6)반복을 이용하여 노드리스트 출력
	//1 -> 10 -> 20 -> 30 -> 44 ->
void displayList1(ListNode* head)
{
	ListNode* temp = head;

	while (temp != NULL) {
		printf("%d -> ", temp->number);
		temp = temp->link;
	}
}

//7) 순환을 이용하여 노드리스트 출력
void displayList2(ListNode* head)
{
	if (head == NULL) {
		return;
	}

	printf("%d -> ", head->number);
	displayList2(head->link);
}

int main(void)
{
	ListNode* head, * newNode, * temp;

	//1) ListNode 타입의 노드를 생성한 후 newNode가 가르키게 하고,
	//10과 NULL을 넣어 노드값을 채우고 이를 head가 가르키게 한다.
	//즉 head --> 10, NULL
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 10;
	newNode->link = NULL;
	head = newNode;

	//2) 같은 방법으로 newNode가 가르키는 노드를 생성한 후,
	//20과 NULL을 넣어 노드값을 채우고 아래처럼 되게 한다.
	//즉 노드리스트 끝에 새로운 노드 삽입 
	//head --> 10, --> 20, NULL
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 20;
	newNode->link = NULL;
	head->link = newNode; //newNode 연결

	//3) 다시 newNode가 가리키는 노드 생성 후 , 30과 NULL 삽입
	//즉 노드리스트 끝에 새로운 노드 삽입
	//head --> 10, --> 20, --> 30, NULL
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 30;
	newNode->link = NULL;
	head->link->link = newNode; //newNode 연결

	//4) head --> 10, --> 20, --> 30, --> 44, NULL
	//노드리스트 끝에 새로운 노드를 삽입할 때, temp 포인터를 사용하여 head가 가리키는 노드리스트의 마지막을 가리키게 한 후
	//temp를 사용하여 새 노드(44, NULL)을 끝에 연결
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 44;
	newNode->link = NULL;
	
	temp = head;
	while (temp->link != NULL)
		temp = temp->link;
	temp->link = newNode;

	//5) head --> 1, --> 10, --> 20, --> 30, --> 44, NULL
	//노드리스트 앞에 1을 갖는 노드를 삽입
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 1;
	newNode->link = head;
	head = newNode;

	displayList1(head);
	printf("\n");
	displayList2(head);
}