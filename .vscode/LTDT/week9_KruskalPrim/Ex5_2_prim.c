
#include <stdio.h>
#define MAX_N 100
#define NO_EDGE 0
#define oo 999999

typedef struct
{
    int n, m;
    int W[MAX_N][MAX_N];
} Graph;

// ham khoi tao
void init_graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= pG->n; u++)
        for (int v = 1; v <= pG->n; v++)
            pG->W[u][v] = NO_EDGE;
}

// them cung vao do thi
void add_edge(Graph *pG, int u, int v, int W)
{
    pG->W[u][v] = W;
    // pG->A[v][u] = 1;
    // pG->m++;
}

int mark[MAX_N];
int pi[MAX_N]; // chiều dài từ đỉnh s đến u
int p[MAX_N];  // đỉnh trước của u

int Prim(Graph *pG, Graph *pT, int s)
{
    int u, v, it;
    for (u = 1; u <= pG->n; u++)
    {
        pi[u] = oo;
        p[u] = -1;
        mark[u] = 0;
    }

    pi[s] = 0;
    // p[s] = -1;

    // lap n-1
    for (it = 1; it < pG->n; it++)
    {
        int min_dist = oo;
        for (int x = 1; x <= pG->n; x++)
            if (mark[x] == 0 && pi[x] < min_dist)
            {
                min_dist = pi[x];
                u = x;
            }
        mark[u] = 1; // danh dau da duyet

        for (v = 1; v <= pG->n; v++)
            if (pG->W[u][v] != NO_EDGE && mark[v] == 0)
                if (pi[u] + pG->W[u][v] < pi[v])
                {
                    pi[v] = pG->W[u][v];
                    p[v] = u; // gắn cha cho v
                }
    }

    // dựng cây dựa vào p[u]: thêm các cung (p[u], u) vào cây T
    init_graph(pT, pG->n);
    int sum_w = 0; // tổng trọng số của cây T
    for (u = 1; u <= pG->n; u++)
    { // có n đỉnh thì có n-1 cung
        if (p[u] != -1)
        {
            int w = pG->W[p[u]][u];
            add_edge(pT, p[u], u, w);
            sum_w += w;
        }
    }
    return sum_w;
}

int main()
{
    Graph G, T;
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (int e = 0; e < m; e++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    int result = Prim(&G, &T, 1); // Chỉ gọi 1 lần
    printf("%d\n", result);

    // In thông tin pi và p
    for (int u = 1; u <= T.n; u++)
    {
        for (int v = 1; v <= T.n; v++)
        {
            if (T.W[u][v] != NO_EDGE)
            {
                printf("%d %d %d\n", u, v, T.W[u][v]);
            }
        }
    }

    return 0;
}
