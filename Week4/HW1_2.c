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

void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
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

	while (current != NULL) {
		if (current->data == key) {
			if (pre == NULL) //ù��° ��� ����
				head = delete_first(head);
			else //�߰� �Ǵ� �� ��� ����
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

int main(void)
{
	ListNode* list1 = NULL, * list2 = NULL, * list3 = NULL;

	//list1 = 30->20->10-> �����, 10, 20, 30�� ������ ��� ����
	list1 = insert_first(list1, 10);
	list1 = insert_first(list1, 20);
	list1 = insert_first(list1, 30);
	
	//list1 ���
	printf("list1 = ");
	print_list(list1);

	//list1 �� �� ��� ����, list1 = 20->10->
	list1 = delete_first(list1);
	
	//list1 ���
	printf("list1 = ");
	print_list(list1);

	//list2 = 11->22->33->44-> �����, 44, 33, 22, 11�� ������ ��� ����
	list2 = insert_first(list2, 44);
	list2 = insert_first(list2, 33);
	list2 = insert_first(list2, 22);
	list2 = insert_first(list2, 11);
	
	//list2 ���
	printf("list2 = ");
	print_list(list2);

	//list2 �� �� ��� ����, list2 = 11->22->33->
	list2 = delete(list2, list2->link->link);
	
	//list2 ���
	printf("list2 = ");
	print_list(list2);

	//list2�� �������� �ٲ� ����Ʈ�� list3, list3 = 33->22->11->
	//list2�� ù��° ������ ����
	while (list2 != NULL) {
		list3 = insert_first(list3, list2->data);
		list2 = list2->link;
	}
	
	//list3 ���
	printf("list3 = ");
	print_list(list3);

	//list1 = 20->10->33->22->11->, ��, list1�� list3�� ���ļ� list1�� ����Ű��
	ListNode* current = list1;
	while (current->link != NULL) {
		current = current->link;
	}
	current->link = list3;

	//list1 ���
	printf("list1 = ");
	print_list(list1);

	//���� �߰��� �Լ��� �׽�Ʈ
	printf("list1�� 20�� ������ 1, ������ 0, �����? %d\n", is_in_list(list1, 20));
	
	printf("list1�� �����ϴ� ����� ����? %d\n", get_length(list1));
	
	printf("list1�� ��� ������ ���� ���� ����? %d\n", get_total(list1));

	printf("list1�� 2��°�� �ִ� ����? (0���� ����) %d\n", get_entry(list1, 2));

	//list1�� key 33�� ������ ��, list1 ���
	list1 = delete_by_key(list1, 33);
	//list1 ���
	printf("33�� ������ ��, list1 = ");
	print_list(list1);

	//pos ��ġ�� value ���� ��� �߰�
	element value = 99;
	list1 = insert_pos(list1, 2, value);
	//list1 ���
	printf("2��°�� 99�� �߰��� �� (0���� ����), list1 = " );
	print_list(list1);

	//pos ��ġ�� ��� ����, pos = 3;
	list1 = delete_pos(list1, 3);
	//list1 ���
	printf("3��°�� ��� ������ �� (0���� ����), list1 = ");
	print_list(list1);
}