#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define TRUE 1
#define FALSE 0
#define MAX_TREE_SIZE 20

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode n1 = { 15, NULL, NULL };
TreeNode n2 = { 4, NULL, &n1 };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 15, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;

TreeNode m1 = { 15, NULL, NULL };
TreeNode m2 = { 4, NULL, &m1 };
TreeNode m3 = { 16, NULL, NULL };
TreeNode m7 = { 28, NULL, NULL }; 
TreeNode m4 = { 25, NULL, &m7 }; 
TreeNode m5 = { 15, &m3, &m4 };
TreeNode m6 = { 15, &m2, &m5 };
TreeNode* root2 = &m6;

//��ܸ������ ���� ����ϴ� �Լ�
int get_nonleaf_count(TreeNode* t)
{
	if (t != NULL) {
		if ((t->left != NULL) || (t->right != NULL))
			return get_nonleaf_count(t->left) + get_nonleaf_count(t->right) + 1;
		else
			return 0;
	}
	
	return 0;
}
//�ڽ��� �ϳ��� ����� ���� ��ȯ
int get_oneleaf_count(TreeNode* node)
{
	if (node != NULL) {
		if ((node->left != NULL) && (node->right == NULL))
			return get_oneleaf_count(node->left) + 1;
		else if ((node->left == NULL) && (node->right != NULL))
			return get_oneleaf_count(node->right) + 1;
		else
			return get_oneleaf_count(node->left) + get_oneleaf_count(node->right);
	}
	
	return 0;
}
//�ڽ��� ���� ����� ���� ��ȯ
int get_twoleaf_count(TreeNode* node)
{
	if (node != NULL) {
		if ((node->left != NULL) && (node->right != NULL))
			return get_twoleaf_count(node->left) + get_twoleaf_count(node->right) + 1;
		else
			return get_twoleaf_count(node->left) + get_twoleaf_count(node->right);
	}

	return 0;
}
//��尪�� �� �ִ밪�� ��ȯ
int get_max(TreeNode* node)
{
	TreeNode* current = node;

	while (current->right != NULL)
		current = current->right;

	return current->data;
}
//��尪�� �� �ּҰ��� ��ȯ
int get_min(TreeNode* node)
{
	TreeNode* current = node;

	while (current->left != NULL)
		current = current->left;

	return current->data;
}
//���� Ʈ���� ������ ���� 1�� ����
void node_increase(TreeNode* node)
{
	if (node != NULL) {
		node->data += 1;

		if (node->left != NULL)
			node_increase(node->left);
		if (node->right != NULL)
			node_increase(node->right);
	}
}
//���� ��ȸ
void preorder(TreeNode* root)
{
	if (root != NULL) {
		printf("%d ", root->data); //��� �湮
		preorder(root->left); //���� ����Ʈ�� ��ȸ
		preorder(root->right); //������ ����Ʈ�� ��ȸ
	}
}
//�� ���� ���� Ʈ���� ���� ����, �����Ǵ� ������ ���� �����͸� ���� ������ 1, �ƴϸ� 0
int equal(TreeNode* t1, TreeNode* t2)
{
	if (t1 == NULL && t2 == NULL)
		return TRUE;
	else if (t1 != NULL && t2 != NULL && (t1->data == t2->data) && equal(t1->left, t2->left) && equal(t1->right, t2->right))
		return TRUE;
	else
		return FALSE;

}
//�־��� ���� Ʈ���� ������ ���ο� Ʈ�� ��ȯ
TreeNode* copy(TreeNode* t)
{
	if (t != NULL) {
		TreeNode* new = (TreeNode*)malloc(sizeof(TreeNode));

		new->data = t->data;
		new->left = copy(t->left);
		new->right = copy(t->right);

		return new;
	}
	
	return NULL;
}

int main(void)
{
	TreeNode* result[MAX_TREE_SIZE];
	TreeNode* clone;
	int i, num;

	printf("��)\n");
	printf("Ʈ�� root �� ��ܸ������ ������ %d.\n", get_nonleaf_count(root));
	printf("Ʈ�� root2 �� ��ܸ������ ������ %d.\n", get_nonleaf_count(root2));

	printf("Ʈ�� root �� �ڽ��� �ϳ��� �ִ� ����� ������ %d.\n", get_oneleaf_count(root));
	printf("Ʈ�� root2 �� �ڽ��� �ϳ��� �ִ� ����� ������ %d.\n", get_oneleaf_count(root2));
	
	printf("Ʈ�� root �� �ڽ��� ���� �ִ� ����� ������ %d.\n", get_twoleaf_count(root));
	printf("Ʈ�� root2 �� �ڽ��� ���� �ִ� ����� ������ %d.\n", get_twoleaf_count(root2));
	
	printf("Ʈ�� root ���� ���� ū ���� %d.\n", get_max(root));
	printf("Ʈ�� root2 ���� ���� ū ���� %d.\n", get_max(root2));
	
	printf("Ʈ�� root ���� ���� ���� ���� %d.\n", get_min(root));
	printf("Ʈ�� root2 ���� ���� ���� ���� %d.\n", get_min(root2));
	
	printf("\n��)\n");
	preorder(root);
	node_increase(root);
	printf("\n");
	preorder(root);
	printf("\n");
	printf("%s\n", equal(root, root) ? "����" : "�ٸ���");
	printf("%s\n", equal(root2, root2) ? "����" : "�ٸ���");
	printf("%s\n", equal(root, root2) ? "����" : "�ٸ���");
	
	printf("\n��)\n");
	clone = copy(root);
	preorder(root);
	printf("\n");
	preorder(clone);
	printf("\n");
}