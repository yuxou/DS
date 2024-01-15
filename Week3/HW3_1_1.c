#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ===== ����ť �ڵ� ���� ======
#define MAX_QUEUE_SIZE 3
typedef struct {
	char name[20];
	char gender;
} element;

typedef struct { // ť Ÿ��
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ���� ���� ���� �Լ�
void init(QueueType* q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// ���� �Լ�
element peek(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ===== ����ť �ڵ� �� ======

void print_queue(QueueType* q)
{
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%s ", q->data[i].name);

			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

int get_count(QueueType* q)
{
	return (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

int main(void)
{
	QueueType manQ;
	QueueType womanQ;
	element newPerson;

	char answer = 'a';

	init(&manQ);
	init(&womanQ);

	printf("���� �ּ� ���α׷��Դϴ�.\n");

	while (answer != 'q') {
		printf("i<nsert, ���Է�>, c<heck, ����� üũ>, q<uit>: ");
		scanf(" %c", &answer);

		switch (answer) {
		case 'i':
			printf("�̸��� �Է�: ");
			scanf("%s", newPerson.name);

			printf("������ �Է�<m or f>: ");
			scanf(" %c", &newPerson.gender);

			if (newPerson.gender == 'm') {
				enqueue(&manQ, newPerson);

				if (is_empty(&womanQ))
					printf("���� ����ڰ� �����ϴ�. ��ٷ� �ֽʽÿ�.\n");
				else if (is_empty(&womanQ) && is_full(&manQ))
					printf("���� ����ڰ� �����ϴ�. ����ڰ� �� á���� ���� ��ȸ�� �̿��ϼ���.\n");
				else {
					printf("Ŀ���� ź���߽��ϴ�! %s�� %s\n", dequeue(&manQ).name, dequeue(&womanQ).name);
				}
			}
			else if (newPerson.gender == 'f') {
				enqueue(&womanQ, newPerson);

				if (is_empty(&manQ))
					printf("���� ����ڰ� �����ϴ�. ��ٷ� �ֽʽÿ�.\n");
				else if (is_empty(&manQ) && is_full(&womanQ))
					printf("���� ����ڰ� �����ϴ�. ����ڰ� �� á���� ���� ��ȸ�� �̿��ϼ���.\n");
				else {
					printf("Ŀ���� ź���߽��ϴ�! %c�� %c\n", dequeue(&manQ).name, dequeue(&womanQ).name);
				}
			}
			break;

		case 'c':
			printf("���� ����� %d��: ", get_count(&manQ));
			print_queue(&manQ);

			printf("���� ����� %d��: ", get_count(&womanQ));
			print_queue(&womanQ);
			break;

		case 'q':
			break;
		}
	}
	return 0;
}