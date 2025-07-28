#include <stdio.h>
#define MAX_N 100
#define NO_EDGE 0
#define oo 999999

typedef struct {
    int n, m;
    int W[MAX_N][MAX_N];
} Graph;

// Khởi tạo đồ thị
void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= pG->n; u++)
        for (int v = 1; v <= pG->n; v++)
            pG->W[u][v] = NO_EDGE;
}

// Thêm cạnh (vì vô hướng nên thêm cả 2 chiều)
void add_edge(Graph *pG, int u, int v, int w) {
    pG->W[u][v] = w;
    pG->W[v][u] = w;
}

int mark[MAX_N];
int pi[MAX_N]; // chi phí ngắn nhất đến u
int p[MAX_N];  // đỉnh cha của u

int Prim(Graph *pG, Graph *pT, int s) {
    int u, v, it;
    for (u = 1; u <= pG->n; u++) {
        pi[u] = oo;
        p[u] = -1;
        mark[u] = 0;
    }

    pi[s] = 0;

    // Duyệt n lần (chọn n đỉnh)
    for (it = 1; it <= pG->n; it++) {
        int min_dist = oo;
        for (int x = 1; x <= pG->n; x++)
            if (!mark[x] && pi[x] < min_dist) {
                min_dist = pi[x];
                u = x;
            }

        mark[u] = 1; // Đánh dấu đã chọn
        printf("%d\n", u); // 👉 In ra đỉnh được chọn

        for (v = 1; v <= pG->n; v++)
            if (pG->W[u][v] != NO_EDGE && !mark[v])
                if (pG->W[u][v] < pi[v]) {
                    pi[v] = pG->W[u][v];
                    p[v] = u;
                }
    }

    // Xây cây khung nhỏ nhất T (nếu cần dùng)
    init_graph(pT, pG->n);
    int sum_w = 0;
    for (u = 1; u <= pG->n; u++) {
        if (p[u] != -1) {
            int w = pG->W[u][p[u]];
            add_edge(pT, u, p[u], w);
            sum_w += w;
        }
    }
    return sum_w;
}

int main() {
    Graph G, T;
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    Prim(&G, &T, 1); // Prim từ đỉnh 1
    return 0;
}