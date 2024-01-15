#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode {	// 이중연결 노드 타입
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

// 이중 연결 리스트를 초기화
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

// 이중 연결 리스트의 노드를 출력
void print_dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}
// 새로운 데이터를 노드 before의 오른쪽에 삽입한다.
void dinsert(DListNode* before, element data)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = data;
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}
// 노드 removed를 삭제한다.
void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}
//역순으로 순회하면서 저장된 데이터 값을 출력
void print_reverse_dlist(DListNode* head)
{
	DListNode* p;
	for (p = head->llink; p != head; p = p->llink)
		printf("<-| |%d| |-> ", p->data);
	printf("\n");
}
//data를 갖는 노드를 찾아서 반환
DListNode* search(DListNode* head, element data)
{
	DListNode* p;
	if (head == NULL) {
		printf("리스트가 비어 검색을 못함\n");
		return NULL;
	}

	for (p = head->rlink; p != head; p = p->rlink) {
		if (p->data == data) {
			printf("%d를 찾음\n", data);
			return p;
		}
	}

	printf("%d를 찾을 수 없음\n", data);
	return NULL;
}

// 이중 연결 리스트 테스트 프로그램
int main(void)
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);
	printf("추가 단계\n");

	//맨 앞에 노드 삽입
	//30->20->10->
	dinsert(head, 10);
	print_dlist(head);
	dinsert(head, 20);
	print_dlist(head);
	dinsert(head, 30);
	print_dlist(head);

	//맨 뒤에 노드를 삽입하려면?
	//30->20->10->99
	dinsert(head->llink, 99);
	print_dlist(head);

	printf("\n삭제 단계\n");
	//맨 앞의 노드를 삭제
	//20->10->99
	ddelete(head, head->rlink);
	print_dlist(head);

	//맨 뒤의 노드를 삭제하려면?
	//20->10
	ddelete(head, head->llink);
	print_dlist(head);

	printf("\n추가 함수\n");
	printf("역순으로 출력\n");
	print_reverse_dlist(head);

	search(head, 20);
	
	free(head);
	return 0;
}