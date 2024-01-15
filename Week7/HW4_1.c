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

//비단말노드의 개수 계산하는 함수
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
//자식이 하나인 노드의 개수 반환
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
//자식이 둘인 노드의 개수 반환
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
//노드값들 중 최대값을 반환
int get_max(TreeNode* node)
{
	TreeNode* current = node;

	while (current->right != NULL)
		current = current->right;

	return current->data;
}
//노드값들 중 최소값을 반환
int get_min(TreeNode* node)
{
	TreeNode* current = node;

	while (current->left != NULL)
		current = current->left;

	return current->data;
}
//이진 트리의 노드들의 값을 1씩 증가
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
//전위 순회
void preorder(TreeNode* root)
{
	if (root != NULL) {
		printf("%d ", root->data); //노드 방문
		preorder(root->left); //왼쪽 서브트리 순회
		preorder(root->right); //오른쪽 서브트리 순회
	}
}
//두 개의 이진 트리가 같은 구조, 대응되는 노드들이 같은 데이터를 갖고 있으면 1, 아니면 0
int equal(TreeNode* t1, TreeNode* t2)
{
	if (t1 == NULL && t2 == NULL)
		return TRUE;
	else if (t1 != NULL && t2 != NULL && (t1->data == t2->data) && equal(t1->left, t2->left) && equal(t1->right, t2->right))
		return TRUE;
	else
		return FALSE;

}
//주어진 이진 트리를 복제한 새로운 트리 반환
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

	printf("가)\n");
	printf("트리 root 중 비단말노드의 개수는 %d.\n", get_nonleaf_count(root));
	printf("트리 root2 중 비단말노드의 개수는 %d.\n", get_nonleaf_count(root2));

	printf("트리 root 중 자식이 하나만 있는 노드의 개수는 %d.\n", get_oneleaf_count(root));
	printf("트리 root2 중 자식이 하나만 있는 노드의 개수는 %d.\n", get_oneleaf_count(root2));
	
	printf("트리 root 중 자식이 둘이 있는 노드의 개수는 %d.\n", get_twoleaf_count(root));
	printf("트리 root2 중 자식이 둘이 있는 노드의 개수는 %d.\n", get_twoleaf_count(root2));
	
	printf("트리 root 에서 가장 큰 수는 %d.\n", get_max(root));
	printf("트리 root2 에서 가장 큰 수는 %d.\n", get_max(root2));
	
	printf("트리 root 에서 가장 작은 수는 %d.\n", get_min(root));
	printf("트리 root2 에서 가장 작은 수는 %d.\n", get_min(root2));
	
	printf("\n나)\n");
	preorder(root);
	node_increase(root);
	printf("\n");
	preorder(root);
	printf("\n");
	printf("%s\n", equal(root, root) ? "같다" : "다르다");
	printf("%s\n", equal(root2, root2) ? "같다" : "다르다");
	printf("%s\n", equal(root, root2) ? "같다" : "다르다");
	
	printf("\n다)\n");
	clone = copy(root);
	preorder(root);
	printf("\n");
	preorder(clone);
	printf("\n");
}