#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;
typedef struct TreeNode {
	element key;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* new_node(int item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, int key)
{
	// Ʈ���� �����̸� ���ο� ��带 ��ȯ�Ѵ�. 
	if (node == NULL) return new_node(key);

	// �׷��� ������ ��ȯ������ Ʈ���� ��������. 
	if (key < node->key)
		node->left = insert_node(node->left, key);
	else if (key > node->key)
		node->right = insert_node(node->right, key);

	// ����� ��Ʈ �����͸� ��ȯ�Ѵ�. 
	return node;
}
TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;

	// �� ���� �ܸ� ��带 ã���� ������
	while (current->left != NULL)
		current = current->left;

	return current;
}
// ���� Ž�� Ʈ���� Ű�� �־����� Ű�� ����� ��带 �����ϰ� 
// ���ο� ��Ʈ ��带 ��ȯ�Ѵ�. 
TreeNode* delete_node(TreeNode* root, int key)
{
	if (root == NULL) return root;

	// ���� Ű�� ��Ʈ���� ������ ���� ���� Ʈ���� �ִ� ����
	if (key < root->key)
		root->left = delete_node(root->left, key);
	// ���� Ű�� ��Ʈ���� ũ�� ������ ���� Ʈ���� �ִ� ����
	else if (key > root->key)
		root->right = delete_node(root->right, key);
	// Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
	else {
		// ù ��°�� �� ��° ���
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
		// �� ��° ���
		TreeNode* temp = min_value_node(root->right);

		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->key = temp->key;
		// �߿� ��ȸ�� �İ� ��带 �����Ѵ�. 
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

// ��ȯ���� Ž�� �Լ�
TreeNode* search(TreeNode* node, int key)
{
	if (node == NULL) return NULL;
	if (key == node->key) return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

void print_tree(TreeNode* root)
{
	if (root != NULL) {
		printf("%d ", root->key); //��� �湮
		print_tree(root->left); //���� ����Ʈ�� ��ȸ
		print_tree(root->right); //������ ����Ʈ�� ��ȸ
	}
}

int get_height(TreeNode* node)
{
	int height = 0;

	if (node != NULL)
		height = 1 + max(get_height(node->left), 
			get_height(node->right));

	return height;
}

int get_node_count(TreeNode* node)
{
	int count = 0;

	if (node != NULL)
		count = 1 + get_node_count(node->left) +
		get_node_count(node->right);

	return count;
}

int get_maximum(TreeNode* node)
{
	TreeNode* current = node;

	while (current->right != NULL)
		current = current->right;

	return current->key;
}

int get_minimum(TreeNode* node)
{
	TreeNode* current = node;

	while (current->left != NULL)
		current = current->left;

	return current->key;
}

void alert()
{
	printf("Enter i<nsert>, d<elete>, s<earch>, p<rint>, h<eight>, c<ount>, m<ax>, n<min>, q<uit>: ");
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
			printf("������ key�� �Է�: ");
			scanf("%d", &e);
			root = insert_node(root, e);
			while (getchar() != '\n');
			break;
		case 'd':
			printf("������ key�� �Է�: ");
			scanf("%d", &e);
			root = delete_node(root, e);
			while (getchar() != '\n');
			break;		
		case 's':
			printf("Ž���� key�� �Է�: ");
			scanf("%d", &e);
			tmp = search(root, e);
			if (tmp != NULL)
				printf("����\n");
			else
				printf("����\n");
			while (getchar() != '\n');
			break;
		case 'p':
			print_tree(root);
			printf("\n");
			break;
		case 'h':
			printf("Ʈ���� ���̴� %d\n", get_height(root));
			break;
		case 'c':
			printf("����� ������ %d\n", get_node_count(root));
			break;		
		case 'm':
			printf("���� ū ���� %d\n", get_maximum(root));
			break;
		case 'n':
			printf("���� ���� ���� %d\n", get_minimum(root));
			break;
		}
	} while (answer != 'q');

	return 0;
}