#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { 	// ��� Ÿ��
	element number;
	struct ListNode* link;
} ListNode;

//6)�ݺ��� �̿��Ͽ� ��帮��Ʈ ���
	//1 -> 10 -> 20 -> 30 -> 44 ->
void displayList1(ListNode* head)
{
	ListNode* temp = head;

	while (temp != NULL) {
		printf("%d -> ", temp->number);
		temp = temp->link;
	}
}

//7) ��ȯ�� �̿��Ͽ� ��帮��Ʈ ���
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

	//1) ListNode Ÿ���� ��带 ������ �� newNode�� ����Ű�� �ϰ�,
	//10�� NULL�� �־� ��尪�� ä��� �̸� head�� ����Ű�� �Ѵ�.
	//�� head --> 10, NULL
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 10;
	newNode->link = NULL;
	head = newNode;

	//2) ���� ������� newNode�� ����Ű�� ��带 ������ ��,
	//20�� NULL�� �־� ��尪�� ä��� �Ʒ�ó�� �ǰ� �Ѵ�.
	//�� ��帮��Ʈ ���� ���ο� ��� ���� 
	//head --> 10, --> 20, NULL
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 20;
	newNode->link = NULL;
	head->link = newNode; //newNode ����

	//3) �ٽ� newNode�� ����Ű�� ��� ���� �� , 30�� NULL ����
	//�� ��帮��Ʈ ���� ���ο� ��� ����
	//head --> 10, --> 20, --> 30, NULL
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 30;
	newNode->link = NULL;
	head->link->link = newNode; //newNode ����

	//4) head --> 10, --> 20, --> 30, --> 44, NULL
	//��帮��Ʈ ���� ���ο� ��带 ������ ��, temp �����͸� ����Ͽ� head�� ����Ű�� ��帮��Ʈ�� �������� ����Ű�� �� ��
	//temp�� ����Ͽ� �� ���(44, NULL)�� ���� ����
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 44;
	newNode->link = NULL;
	
	temp = head;
	while (temp->link != NULL)
		temp = temp->link;
	temp->link = newNode;

	//5) head --> 1, --> 10, --> 20, --> 30, --> 44, NULL
	//��帮��Ʈ �տ� 1�� ���� ��带 ����
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 1;
	newNode->link = head;
	head = newNode;

	displayList1(head);
	printf("\n");
	displayList2(head);
}