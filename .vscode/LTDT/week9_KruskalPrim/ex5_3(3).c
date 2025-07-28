#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
// danh sách cung

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
// int min(int u, int v)
// {
//     return u < v ? u : v;
// }

// int max(int u, int v)
// {
//     return u > v ? u : v;
// }
// đề bài là u < v
void add_edge(Graph *pG, int u, int v, int w)
{
    // đưa cung (u,v) vào edges
    // pG->edges[pG->m].u = min(u, v);
    // pG->edges[pG->m].v = max(u, v);
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->edges[pG->m].w = w;
    pG->m++;
}

int parent[MAX_N];

// Tìm gốc của đỉnh u (lặp)
int findRoot(int u)
{
    while (parent[u] != u)
        u = parent[u];
    return u;
}

int cmpfunc(const void *a, const void *b)
{
    return ((const Edge *)a)->w - ((const Edge *)b)->w;
}

// Thuật toán Kruskal tìm cây khung nhỏ nhất
int Kruskal(Graph *pG)
{
    // 1. Sắp xếp các cung của G theo thứ tự trọng số tăng dần
    qsort(pG->edges, pG->m, sizeof(Edge), cmpfunc);

    // 2. Khởi tạo pT không chứa cung nào, khởi tạo bộ quản lý các BPLT
    for (int u = 1; u <= pG->n; u++)
        parent[u] = u; // Mỗi đỉnh u là một bộ phận liên thông

    int sum_w = 0;  // Tổng trọng số các cung của cây
    int edges_used; // tổng số cunng đã sử dụng

    // 3. Duyệt qua các cung của G (đã sắp xếp)
    for (int e = 0; e < pG->m; e++)
    {
        int u = pG->edges[e].u;
        int v = pG->edges[e].v;
        int w = pG->edges[e].w;

        int root_u = findRoot(u); // Tìm BPLT của u
        int root_v = findRoot(v); // Tìm BPLT của v
        if (root_u != root_v)
        { // u và v ở 2 BPLT khác nhau
            // Gộp 2 BPLT root_u và root_v lại
            parent[root_v] = root_u;
            sum_w += w;
            edges_used++;
            if (edges_used == pG->n - 1)
                break;
        }
    }
    // Nếu không đủ cạnh để tạo MST (đồ thị không liên thông)
    if (edges_used < pG->n - 1)
        return -1;

    return sum_w;
}

// Sử dụng thuật toán Kruskal
int main() {
    Graph G;
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    init_graph(&G, n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    int total_cost = Kruskal(&G);

    if (total_cost == -1) {
        printf("Khong the ket noi tat ca cac sao.\n");
    } else if (total_cost <= k) {
        printf("OK\n");
    } else {
        printf("%d\n", total_cost - k);
    }

    return 0;
}