//SỬ DỤNG DANH SÁCH CUNG
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
int parent[MAX_N];

//GRAPH
typedef struct{
    int u,v;
    int w;
}Edge;

typedef struct{
    int n,m; 
    Edge edges[MAX_N];
}Graph;

void init_graph (Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
}

void add_edge (Graph *pG, int u, int v, int w){
    if (u > v){
        int temp = u;
        u = v;
        v = temp; 
    }
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->edges[pG->m].w = w;
    pG->m++;
}

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

int main (){
    Graph G, T;
    int n,m,u,v,w;
    scanf ("%d%d", &n, &m);
    init_graph(&G, n);

    for (int e = 0; e < m; e++){
        scanf ("%d%d%d", &u, &v, &w);
        add_edge(&G,u,v,w);
    }

    int sum_w = Kruskal(&G, &T);
    printf ("%d\n", sum_w);

    for (int e = 0; e < T.m; e++){
        printf ("%d %d %d\n", T.edges[e].u, T.edges[e].v, T.edges[e].w);
    }
    return 0;
}
