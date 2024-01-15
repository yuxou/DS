#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_VERTICES 50

typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}

	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
// ���� ���� ����
void delete_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}

	g->adj_mat[start][end] = 0;
	g->adj_mat[end][start] = 0;
}
//���Ͽ��� �׷��� �б�
void read_graph(GraphType* g, char* filename)
{
	int number, u, v;
	FILE* fp;
	fp = fopen(filename, "rt");
	if (fp == NULL)
	{
		printf("file %s open error!\n", filename);
		return;
	}

	fscanf(fp, "%d", &number);
	g->n = number;

	while (fscanf(fp, "%d %d", &u, &v) != EOF)
		insert_edge(g, u, v);

	fclose(fp);
}
//�׷����� ���Ͽ� ����
void write_graph(GraphType* g, char* filename)
{
	int i, j;
	FILE* fp;

	if (filename == NULL) fp = stdout;
	else {
		fp = fopen(filename, "wt");
		if (fp == NULL)
		{
			printf("file %s open error!\n", filename);
			return;
		}
	}

	fprintf(fp, "%d\n", g->n);

	for (i = 0; i < g->n; i++) {
		for (j = i + 1; j < g->n; j++) {
			if (g->adj_mat[i][j] == 1) 
				fprintf(fp, "%d %d\n", i, j);
		}
	}

	if (filename != NULL) fclose(fp);
}

int main(void)
{
	/*
	input 
	5
	0 1
	0 2
	0 4
	1 2
	2 3
	2 4
	3 4

	output
	5
	0 1
	0 4
	1 2
	1 3
	2 3
	2 4
	3 4
	*/
	GraphType g;
	graph_init(&g);
	read_graph(&g, "input.txt");
	write_graph(&g, NULL);	// to stdout

	insert_edge(&g, 1, 3);
	write_graph(&g, NULL);	// to stdout

	delete_edge(&g, 2, 0);
	write_graph(&g, NULL);	// to stdout

	write_graph(&g, "output.txt");
}