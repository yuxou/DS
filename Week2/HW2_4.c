#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define MAX_STRING 100
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

//���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}

//���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}

//��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}

//���� �Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

//���� �Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

//��ũ �Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf("���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}

int palindrome(char str[])
{
	StackType s;
	int len = strlen(str);

	init_stack(&s);

	//str�� ���ڵ��� ���ÿ� ����
	for (int i = 0; i < len; i++)
		push(&s, str[i]);

	//���ÿ��� �ϳ��� ���鼭 str�� ���ڵ�� ��
	for (int i = 0; i < len; i++) {
		if (pop(&s) != str[i])
			return FALSE;
	}

	return TRUE; //palindrome��
}

int main(void)
{
	char word[MAX_STRING];

	printf("Enter a word to check palindrome: ");
	scanf("%s", word);

	if (palindrome(word))
		printf("palindrome�Դϴ�.\n");
	else
		printf("palindrome�� �ƴմϴ�.\n");
}