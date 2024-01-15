#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_VERTICES 50

typedef struct GraphType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES] = { 0 };

// 그래프 초기화 
void graph_init(GraphType* g)
{
    int r, c;
    g->n = 0;
    for (r = 0; r < MAX_VERTICES; r++)
        for (c = 0; c < MAX_VERTICES; c++)
            g->adj_mat[r][c] = 0;
}

void insert_vertex(GraphType* g, int v)
{
    g->n++;
}

void insert_edge(GraphType* g, int start, int end)
{
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

void read_graph(GraphType* g, char* filename)
{
    int number, u, v;
    GraphType* node;
    FILE* fp;
    fp = fopen(filename, "rt");
    if (fp == NULL)
    {
        printf("file open error!\n");
        return;
    }

    fscanf(fp, "%d", &number);
    g->n = number;

    while (fscanf(fp, "%d %d", &u, &v) != EOF)
        insert_edge(g, u, v);

    fclose(fp);
}

// 이 함수에 간선을 출력하기위한 코드를 삽입하는 것이 HW6_2_1의 요구이다
void dfs_mat(GraphType* g, int v)
{
    int w;
    visited[v] = 1;
    for (w = 0; w <= g->n; w++)
        if ((g->adj_mat[v][w] == 1) && (visited[w] == 0)) { // u가 인접한 정점이고 u가 아직 방문되지 않았으면
            printf("<%d %d>\n", v, w);
            dfs_mat(g, w);
        }
}
int main(void)
{
    /*
    4
    0 1
    1 2
    2 3
    3 0
    0 2

    5
    0 1
    0 2
    0 4
    1 2
    2 3
    2 4
    3 4
    */

    GraphType graph;
    int u, v;

    graph_init(&graph);
    read_graph(&graph, "infile.txt");
    //read_graph(&graph, "infile2.txt");

    printf("Enter 정점: ");
    scanf("%d", &v);

    dfs_mat(&graph, v);
}