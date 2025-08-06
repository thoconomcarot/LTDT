#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct {
    int u, v;
    int cost; // s * d
} Edge;

typedef struct {
    int n, m;
    Edge edges[MAX_N];
} Graph;

int parent[MAX_N];

// Khởi tạo đồ thị
void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
}

// Thêm cạnh với chi phí
void add_edge(Graph *pG, int u, int v, int s, int d) {
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->edges[pG->m].cost = s * d;
    pG->m++;
}

// Tìm gốc của đỉnh u
int findRoot(int u) {
    while (u != parent[u])
        u = parent[u];
    return u;
}

// Sắp xếp tăng dần theo cost
int cmp(const void *a, const void *b) {
    return ((Edge *)a)->cost - ((Edge *)b)->cost;
}

// Kruskal: trả về tổng chi phí nhỏ nhất
int kruskal(Graph *pG) {
    qsort(pG->edges, pG->m, sizeof(Edge), cmp);
    for (int i = 1; i <= pG->n; i++)
        parent[i] = i;

    int total_cost = 0;
    int count = 0;

    for (int i = 0; i < pG->m && count < pG->n - 1; i++) {
        int u = pG->edges[i].u;
        int v = pG->edges[i].v;
        int cost = pG->edges[i].cost;
        int root_u = findRoot(u);
        int root_v = findRoot(v);

        if (root_u != root_v) {
            parent[root_v] = root_u;
            total_cost += cost;
            count++;
        }
    }

    return total_cost;
}

int main() {
    Graph G;
    int n, m;
    scanf("%d %d", &n, &m);
    init_graph(&G, n);

    for (int i = 0; i < m; i++) {
        int u, v, s, d;
        scanf("%d%d%d%d", &u, &v, &s, &d);
        add_edge(&G, u, v, s, d);
    }

    int result = kruskal(&G);
    printf("%d\n", result);
    return 0;
}