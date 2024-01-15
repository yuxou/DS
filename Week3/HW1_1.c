#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 5	// 리스트의 최대크기

typedef int element;			// 항목의 정의
typedef struct {
	element array[MAX_LIST_SIZE];	  // 배열 정의
	int size;		  // 현재 리스트에 저장된 항목들의 개수
} ArrayListType;

// 오류 처리 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 리스트 초기화 함수
void init(ArrayListType* L)
{
	L->size = 0;
}

// 리스트가 비어 있으면 1을 반환
// 그렇지 않으면 0을 반환
int is_empty(ArrayListType* L)
{
	return L->size == 0;
}

// 리스트가 가득 차 있으면 1을 반환
// 그렇지 많으면 1을 반환
int is_full(ArrayListType* L)
{
	return L->size == MAX_LIST_SIZE;
}

element get_entry(ArrayListType* L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("위치 오류");
	return L->array[pos];
}

// 리스트 출력
void print_list(ArrayListType* L)
{
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d -> ", L->array[i]);
	printf("리스트 끝\n");
}

void insert_last(ArrayListType* L, element item)
{
	if (L->size >= MAX_LIST_SIZE) 
		printf("리스트 오버플로우\n");

	L->array[L->size++] = item;
}

void insert(ArrayListType* L, int pos, element item)
{
	if (is_full(L))
		printf("리스트 오버플로우\n");

	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		for (int i = (L->size - 1); i >= pos; i--)
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;
		L->size++;
	} 
}

element delete(ArrayListType* L, int pos)
{
	element item;

	if (pos < 0 || pos >= L->size)
		error("위치 오류");
	item = L->array[pos];
	for (int i = pos; i < (L->size - 1); i++)
		L->array[i] = L->array[i + 1];
	L->size--;
	return item;
}

//리스트를 비운다
void clear(ArrayListType* L)
{
	for (int i = 0; i < L->size; i++)
		L->array[i] = 0;
	init(L);
}

//item을 리스트의 첫번째 항목에 추가한다
void insert_first(ArrayListType* L, element item)
{
	if (is_full(L))
		printf("리스트 오버플로우\n");
	else {
		for (int i = (L->size - 1); i >= 0; i--)
			L->array[i + 1] = L->array[i];

		L->array[0] = item;
		L->size++;
	}
}

//리스트의 항목 수를 반환한다
int get_length(ArrayListType* L)
{
	return L->size;
}

//POS번째 항목을 item으로 바꾼다
void replace(ArrayListType* L, int pos, element item)
{
	if (!is_empty(L) && pos >= 0 && pos <= L->size)
		L->array[pos] = item;
}

//item이 리스트에 있으면 1 아니면 0을 반환
int is_in_list(ArrayListType* L, element item)
{
	for (int i = 0; i < L->size; i++) 
		if (L->array[i] == item)
			return 1;
	return 0;
}

//리스트에서 key값을 검색하여 그를 삭제한다. 여러 개의 key값이 있으면 첫 번째 key를 삭제, 없으면 "없음"
delete_by_key(ArrayListType* L, element key)
{
	int i;

	for (i = 0; i < L->size; i++) 
		if (L->array[i] == key) {
			delete(L, i);
			break;
		}

	if (i == L->size)
		printf("삭제하려는 key값 %d은 리스트에 없습니다.\n", key);
}

int main(void)
{
	ArrayListType list1;

	init(&list1);
	insert(&list1, 0, 20);
	insert(&list1, 0, 10); print_list(&list1);
	clear(&list1); print_list(&list1);

	insert_last(&list1, 90); print_list(&list1);

	insert(&list1, 0, 30);
	insert(&list1, 0, 20);
	insert(&list1, 0, 10); print_list(&list1);

	delete(&list1, 2); print_list(&list1);

	printf("\n--이 이후는 HW1_1에서 추가한 함수들 테스트--\n");
	insert_first(&list1, 9); print_list(&list1);
	insert_last(&list1, 99); print_list(&list1);

	//현재 리스트가 꽉 찬(크기 5개) 상태이므로 한 항목을 더 추가하면 "리스트 오버플로우"를 출력한다.
	insert_first(&list1, 1); print_list(&list1);

	printf("길이는 %d\n", get_length(&list1));
	printf("세 번째 데이터는 %d\n", get_entry(&list1, 2));

	replace(&list1, 3, 40); print_list(&list1);
	printf("20은 리스트에 %s\n", is_in_list(&list1, 20) ? "있습니다" : "없습니다");
	printf("22는 리스트에 %s\n", is_in_list(&list1, 22) ? "있습니다" : "없습니다");

	delete_by_key(&list1, 20); print_list(&list1);
	delete_by_key(&list1, 22); print_list(&list1);
}