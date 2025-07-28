#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
// danh sách cung
//.................Graph.......................
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

void add_edge(Graph *pG, int u, int v, int w){
    if (u > v){
		int temp = u;
		u = v;
		v = temp;
	}
    // đưa cung (u,v) vào edges
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->edges[pG->m].w = w;
    pG->m++;
}

//......................findroot..................
int parent[MAX_N];

// Tìm gốc của đỉnh u (lặp)
int findRoot(int u)
{
    while (parent[u] != u)
        u = parent[u];
    return u;
}

int cmpfunc(const void *a, const void *b){
    return ((Edge*)a)->w - ((Edge*)b)->w;
}

//......................Kruskal...................
int Kruskal(Graph *pG, Graph *pT){

    //Sx cung của G theo thứ tự trọng số tăng dần
    qsort(pG->edges, pG->m, sizeof(Edge), cmpfunc);

    //Khởi tạo pT không chứa cung nào, khởi tạo bộ quản lý các BPLT
    init_graph(pT, pG->n);
    for (int u = 1; u <= pG->n; u++)
        parent[u] = u; // Mỗi đỉnh u là một bộ phận liên thông

    int sum_w = 0; // Tổng trọng số các cung của cây

    //Duyệt qua các cung của G (đã sắp xếp)
    for (int e = 0; e < pG->m; e++)
    {
        int u = pG->edges[e].u;
        int v = pG->edges[e].v;
        int w = pG->edges[e].w;
        int root_u = findRoot(u); // Tìm BPLT của u
        int root_v = findRoot(v); // Tìm BPLT của v
        if (root_u != root_v)
        { // u và v ở 2 BPLT khác nhau
            // Thêm cung (u, v; w) vào cây pT
            add_edge(pT, u, v, w);
            // Gộp 2 BPLT root_u và root_v lại
            parent[root_v] = root_u;
            sum_w += w;
        }
    }
    return sum_w;
}

// Sử dụng thuật toán Kruskal
int main(){
    Graph G, T;
    int n, m, u, v, w, e;
    int sum_all= 0;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    
    for (e = 1; e <= m; e++){
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
        //sum_all += w;
    }

    int sum_w = Kruskal(&G, &T); // Gọi hàm Kruskal
    printf("%d\n",sum_w);

    return 0;
}