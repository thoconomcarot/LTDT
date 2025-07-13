#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500

//......................Graph.........................//
typedef struct {
    int u, v;
    int w;
} Edge;

typedef struct {
    int n, m;
    Edge edges[MAX_N];
} Graph;

void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
}

void add_edge(Graph *pG, int u, int v, int w) {
    if (u > v) { int tmp = u; u = v; v = tmp; }  // đảm bảo u < v
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->edges[pG->m].w = w;
    pG->m++;
}

//.....................Kruskal...........................//
int parent[MAX_N];

int find_root(int u) {
    while (parent[u] != u)
        u = parent[u];
    return u;
}

// Bubble sort cạnh tăng dần theo trọng số, u, v
void sort_edges(Graph *pG) {
    for (int i = 0; i < pG->m - 1; i++) {
        for (int j = i + 1; j < pG->m; j++) {
            Edge a = pG->edges[i];
            Edge b = pG->edges[j];
            int swap = 0;
            if (a.w > b.w) swap = 1;
            else if (a.w == b.w && a.u > b.u) swap = 1;
            else if (a.w == b.w && a.u == b.u && a.v > b.v) swap = 1;
            if (swap) {
                Edge tmp = pG->edges[i];
                pG->edges[i] = pG->edges[j];
                pG->edges[j] = tmp;
            }
        }
    }
}

int Kruskal(Graph *pG, Graph *pT) {
    init_graph(pT, pG->n);

    sort_edges(pG);  // gọi sort bubble tự viết

    for (int i = 1; i <= pG->n; i++)
        parent[i] = i;

    int total_weight = 0;

    for (int i = 0; i < pG->m; i++) {
        int u = pG->edges[i].u;
        int v = pG->edges[i].v;
        int w = pG->edges[i].w;
        int root_u = find_root(u);
        int root_v = find_root(v);
        if (root_u != root_v) {
            add_edge(pT, u, v, w);
            parent[root_v] = root_u;
            total_weight += w;
        }
    }
    return total_weight;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    Graph G, T;
    init_graph(&G, n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    int total = Kruskal(&G, &T);
    printf("%d\n", total);
    for (int i = 0; i < T.m; i++) {
        printf("%d %d %d\n", T.edges[i].u, T.edges[i].v, T.edges[i].w);
    }

    return 0;
}
