#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 3
typedef struct {
	char name[20];
	char gender;
} element;

typedef struct { // 큐 타입
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 공백 상태 검출 함수
void init(QueueType* q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

// 삭제 함수
element peek(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
// ===== 원형큐 코드 끝 ======

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

	printf("미팅 주선 프로그램입니다.\n");

	while (answer != 'q') {
		printf("i<nsert, 고객입력>, c<heck, 대기자 체크>, q<uit>: ");
		scanf(" %c", &answer);

		switch (answer) {
		case 'i':
			printf("이름을 입력: ");
			scanf("%s", newPerson.name);

			printf("성별을 입력<m or f>: ");
			scanf(" %c", &newPerson.gender);

			if (newPerson.gender == 'm') {
				enqueue(&manQ, newPerson);

				if (is_empty(&womanQ))
					printf("아직 대상자가 없습니다. 기다려 주십시오.\n");
				else if (is_empty(&womanQ) && is_full(&manQ))
					printf("아직 대상자가 없습니다. 대기자가 꽉 찼으니 다음 기회를 이용하세요.\n");
				else {
					printf("커플이 탄생했습니다! %s와 %s\n", dequeue(&manQ).name, dequeue(&womanQ).name);
				}
			}
			else if (newPerson.gender == 'f') {
				enqueue(&womanQ, newPerson);

				if (is_empty(&manQ))
					printf("아직 대상자가 없습니다. 기다려 주십시오.\n");
				else if (is_empty(&manQ) && is_full(&womanQ))
					printf("아직 대상자가 없습니다. 대기자가 꽉 찼으니 다음 기회를 이용하세요.\n");
				else {
					printf("커플이 탄생했습니다! %c와 %c\n", dequeue(&manQ).name, dequeue(&womanQ).name);
				}
			}
			break;

		case 'c':
			printf("남성 대기자 %d명: ", get_count(&manQ));
			print_queue(&manQ);

			printf("여성 대기자 %d명: ", get_count(&womanQ));
			print_queue(&womanQ);
			break;

		case 'q':
			break;
		}
	}
	return 0;
}