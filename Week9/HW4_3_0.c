#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 100

typedef struct {
	int id;
	char name[MAX_STRING];
	char tel[MAX_STRING];
	char dept[MAX_STRING];
} element;

typedef struct TreeNode {
	element data;
	struct TreeNode* left, * right;
} TreeNode;

int compare(element a, element b)
{
	return a.id - b.id;
}

TreeNode* new_node(element item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, element key)
{
	if (node == NULL) return new_node(key);
 
	if (compare(key, node->data) < 0)
		node->left = insert_node(node->left, key);
	else if (compare(key, node->data) > 0)
		node->right = insert_node(node->right, key);

	return node;
}
TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

TreeNode* delete_node(TreeNode* root, element key)
{
	if (root == NULL) return root;

	if (compare(key, root->data) < 0)
		root->left = delete_node(root->left, key);
	else if (compare(key, root->data) > 0)
		root->right = delete_node(root->right, key);
	else {
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		TreeNode* temp = min_value_node(root->right);

		root->data = temp->data;
		root->right = delete_node(root->right, temp->data);
	}
	return root;
}

// 순환적인 탐색 함수
TreeNode* search(TreeNode* node, element key)
{
	TreeNode* p = node;

	while (p != NULL) {
		if (compare(key, p->data) == 0)
			return p;
		else if (compare(key, p->data) < 0)
			p = p->left;
		else if (compare(key, p->data) > 0)
			p = p->right;
	}
	return p;
}

void print_tree(TreeNode* root)
{
	if (root != NULL) {
		print_tree(root->left);
		printf("-----------------------------------\n");
		printf("학번: %d\n", root->data.id);
		printf("이름: %s\n", root->data.name);
		printf("전화번호: %s\n", root->data.tel);
		printf("학과: %s\n", root->data.dept);
		print_tree(root->right);
	}
}

int get_student_count(TreeNode* node)
{
	int count = 0;

	if (node != NULL)
		count = 1 + get_student_count(node->left) +
		get_student_count(node->right);

	return count;
}

void alert()
{
	printf("Enter i<nsert>, d<elete>, s<earch>, p<rint>, c<ount>, q<uit>: ");
}

int main(void)
{
	TreeNode* root = NULL;
	TreeNode* tmp;
	char answer;
	element e;

	do {
		alert();
		answer = getchar();
		getchar();

		switch (answer) {
		case 'i':
			printf("학번 입력: ");
			scanf("%d", &e.id);
			printf("이름 입력: ");
			scanf("%s", e.name);
			printf("전화번호 입력: ");
			scanf("%s", e.tel);
			printf("학과 입력: ");
			scanf("%s", e.dept);

			root = insert_node(root, e);
			while (getchar() != '\n');
			break;
		case 'd':
			printf("삭제할 학번 입력: ");
			scanf("%d", &e.id);
			root = delete_node(root, e);
			while (getchar() != '\n');
			break;
		case 's':
			printf("탐색할 학번 입력: ");
			scanf("%d", &e.id);
			tmp = search(root, e);
			if (tmp == NULL) 
				printf("id가 %d인 학생은 없읍니다.\n", e.id);
			else {
				printf("학번: %d\n", tmp->data.id);
				printf("이름: %s\n", tmp->data.name);
				printf("전화번호: %s\n", tmp->data.tel);
				printf("학과: %s\n", tmp->data.dept);
			}
			while (getchar() != '\n');
			break;
		case 'p':
			printf("학생 정보 학번 순 출력\n");
			print_tree(root);
			printf("\n");
			break;
		case 'c':
			printf("현재 저장된 학생의 총 수는 %d\n", get_student_count(root));
			break;
		}
	} while (answer != 'q');

	return 0;
}