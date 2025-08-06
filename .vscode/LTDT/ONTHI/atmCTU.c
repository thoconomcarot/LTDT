#include <stdio.h>

#define MAX_N 100
#define MAX_M 500
#define INFINITY 999999

typedef struct {
    int u, v, w;
} Edge;

typedef struct {
    Edge edges[MAX_M];
    int n, m;
} Graph;

void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
}

void add_edge(Graph *pG, int u, int v, int w){
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->edges[pG->m].w = w;
    pG->m++;
}

//Cần phải điền
#include <stdlib.h>
int parent[MAX_N];
//FINDROOT
int findroot(int u){
    while (parent[u] != u){
        u = parent[u];
    }
    return u;
}

//CMPFUNCT
int cmpfunc(const void *a, const void *b){
    Edge *e1 = (Edge*)a;
    Edge *e2 = (Edge*)b;
    return e1->w - e2->w;
}

//KRUSKAL
int Kruskal (Graph *pG, Graph *pT){
    //1. sắp xếp các cung theo thứ tự trọng số tăng dần
    qsort (pG->edges, pG->m, sizeof(Edge), cmpfunc);

    //2. Khởi tạo pT không chứa cung nào, khởi tạo bộ quản lý các BPLT
    init_graph (pT, pG->n);
    for (int u = 1; u <= pG->n; u++){
        //mỗi đỉnh u là một BPLT
        parent[u] = u;
    }

    int sum_w = 0;
    
    //3. duyệt qua các cung của G 
    for (int e = 0; e < pG->m; e++){
        int u = pG->edges[e].u;
        int v = pG->edges[e].v;
        int w = pG->edges[e].w;
        int root_u = findroot(u);
        int root_v = findroot(v);
        //ktra nếu u và nằm ở 2 BPLT khác nhau
        if (root_u != root_v){
            //thêm cung u v vào cây
            add_edge(pT,u,v,w);
            //gán cha v bằng u
            parent[root_v] = root_u;
            sum_w += w;
        }
    }
    return sum_w;
} 

int main() {
    Graph G, T;
    int n,m,u,v, w, t;
    scanf ("%d%d", &n, &m);
    init_graph(&G,n);
    
    for (int e = 0; e < m; e++){
        scanf ("%d%d%d%d", &u, &v, &w, &t);
        add_edge(&G,u,v,w+t);
    }
    
    int sum_w = Kruskal(&G, &T);
    int atm_cost = (n-1)*1;
    printf ("%d\n", sum_w + atm_cost);
    
    return 0;
}