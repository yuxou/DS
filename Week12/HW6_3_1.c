//Kruskal 알고리즘
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "minheap.h"
#include "unionfind.h"

#define MAX_VERTICES 100
#define INF 9999

typedef struct GraphType {
	int n;					// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
		for (int j = 0; j < MAX_VERTICES; j++)
			g->adj_mat[i][j] = INF;
}

void insert_edge(GraphType* g, int start, int end, int key)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}

	g->adj_mat[start][end] = key;
	g->adj_mat[end][start] = key;
}

void read_graph(GraphType* g, char* filename)
{
	int number, u, v, key;
	FILE* fp;

	fp = fopen(filename, "rt");
	if (fp == NULL)
	{
		printf("file open error!\n");
		return;
	}

	fscanf(fp, "%d\n", &number);
	g->n = number;

	while (fscanf(fp, "%d %d %d\n", &u, &v, &key) != EOF)
		insert_edge(g, u, v, key);

	fclose(fp);
}

void write_graph(GraphType* g, char* filename)
{
	int i, j;
	FILE* fp;

	if (filename == NULL) fp = stdout;
	else {
		fp = fopen(filename, "wt");
		if (fp == NULL)
		{
			printf("file open error!\n");
			return;
		}
	}

	fprintf(fp, "%d\n", g->n);

	for (i = 0; i < g->n; i++) {
		for (j = 0; j < g->n; j++) {
			if (g->adj_mat[i][j] != INF)
				fprintf(fp, "%d %d %d\n", i, j, g->adj_mat[i][j]);
		}
	}

	if (filename != NULL) fclose(fp);
}

// 인접 행렬이나 인접 리스트에서 간선들을 읽어서 최소 히프에 삽입 
// 현재는 예제 그래프의 간선들을 삽입한다.
void insert_all_edges(HeapType* h, GraphType* g)
{
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			if (i < j && g->adj_mat[i][j] != INF) {
				element e;
				e.u = i; 
				e.v = j;
				e.key = g->adj_mat[i][j];
				insert_min_heap(h, e);
			}
		}
	}
}

// kruskal의 최소 비용 신장 트리 프로그램
void kruskal(GraphType* g, GraphType* t)
{
	int edge_accepted = 0;
	HeapType h;
	int uset, vset;
	element e;

	init(&h);
	insert_all_edges(&h, g);
	set_init(g->n);

	while (edge_accepted < (g->n - 1)) {
		e = delete_min_heap(&h);
		uset = set_find(e.u);
		vset = set_find(e.v);

		if (uset != vset) {
			printf("<%d, %d> %d\n", e.u, e.v, e.key);
			edge_accepted++;
			t->adj_mat[e.u][e.v] = e.key;
			set_union(uset, vset);
		}
	}
}

int main()
{
	/*
	input1
	4
	0 1 20
	1 2 30
	2 3 40
	3 0 50
	0 2 10

	output
	4
	0 1 20
	0 2 10
	2 3 40
	*/
	GraphType g, t;		// 입력 그래프, 결과 트리

	graph_init(&g);
	read_graph(&g, "input1.txt");
	//read_graph(&g, "input2.txt");

	graph_init(&t);
	t.n = g.n;

	printf("선택된 간선<순서대로>:\n");
	kruskal(&g, &t);

	printf("\n파일로 출력:\n");
	write_graph(&t, "output.txt");
	write_graph(&t, NULL);	// to stdout
}
