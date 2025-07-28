#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
// danh sách cung
int parent[MAX_N];

typedef struct
{
    int u, v;
    int w;
} Edge;
typedef struct
{
    int n, m;
    Edge edges[MAX_N];
} Graph;

void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
}
//int min(int u, int v)
//{
//    return u < v ? u : v;
//}
//
//int max(int u, int v)
//{
//    return u > v ? u : v;
//}
//// d? bài là u < v

void add_edge(Graph *pG, int u, int v, int w){	
	if (u > v){
		int temp = u;
		u = v;
		v = temp;
	}
    // dua cung (u,v) vào edges
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->edges[pG->m].w = w;
    pG->m++;
}


// Tìm g?c c?a d?nh u (l?p)
int findRoot(int u)
{
    while (parent[u] != u)
        u = parent[u];
    return u;
}

int cmpfunc(const void *a, const void *b){
	Edge* e1 = (Edge*)a;
	Edge* e2 = (Edge*)b;
    return e1->w - e2->w;
}


//.......................Kruskal...................
int Kruskal(Graph *pG, Graph *pT)
{
    // 1. S?p x?p các cung c?a G theo th? t? tr?ng s? tang d?n
    qsort(pG->edges, pG->m, sizeof(Edge), cmpfunc);

    // 2. Kh?i t?o pT không ch?a cung nào, kh?i t?o b? qu?n lý các BPLT
    init_graph(pT, pG->n);
    for (int u = 1; u <= pG->n; u++)
        parent[u] = u; // M?i d?nh u là m?t b? ph?n liên thông

    int sum_w = 0; // T?ng tr?ng s? các cung c?a cây

    // 3. Duy?t qua các cung c?a G (dã s?p x?p)
    for (int e = 0; e < pG->m; e++)
    {
        int u = pG->edges[e].u;
        int v = pG->edges[e].v;
        int w = pG->edges[e].w;
        int root_u = findRoot(u); // Tìm BPLT c?a u
        int root_v = findRoot(v); // Tìm BPLT c?a v
        if (root_u != root_v)
        { // u và v ? 2 BPLT khác nhau
            // Thêm cung (u, v; w) vào cây pT
            add_edge(pT, u, v, w);
            // G?p 2 BPLT root_u và root_v l?i
            parent[root_v] = root_u;
            sum_w += w;
        }
    }
    return sum_w;
}

// S? d?ng thu?t toán Kruskal
int main()
{
    Graph G, T;
    int n, m, u, v, w, e;

    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    for (e = 0; e < m; e++)
    {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    int sum_w = Kruskal(&G, &T); // G?i hàm Kruskal
    printf("%d\n", sum_w);

    for (e = 0; e < T.m; e++)
        printf("%d %d %d\n", T.edges[e].u, T.edges[e].v, T.edges[e].w);

    return 0;
}