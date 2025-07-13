//biểu diễn hàm add_edge trong đồ thị vô hướng
#include <stdio.h>
#define max_m 500
typedef struct{
    int u,v;
}Edge;

typedef struct{
    int n,m;
    Edge edges[max_m];
}Graph;

//Ham khoi tao
void init_graph(Graph *pG, int n){
    pG->n = n; //Gán số đỉnh = n
    pG->m = 0; //Gán số cung = 0
}

//Them cung uv vào do thi do pG tro den
void add_edge (Graph *pG, int u, int v){
    int e;
    //Kiểm tra u v có trong đồ thị vô hướng
    for (e = 0; e < pG->m; e++){
        if ((pG->edges[e].u == v && pG->edges[e].v == u) || (pG->edges[e].u == u && pG->edges[e].v == v)){
            return;
        }
    }
    //dua cung (u,v) vao edges
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    //Tang so cung len 1
    pG->m++;
}

int main (){
    Graph G;
    int e;
    init_graph(&G, 4);
    //In ra so dinh va so cung
    printf ("n = %d, m = %d\n", G.n, G.m);

    add_edge(&G, 1, 1);
    add_edge(&G, 1, 3);
    add_edge(&G, 5, 2);
    add_edge(&G, 2, 4);
    add_edge(&G, 3, 3);
    add_edge(&G, 5, 4);
    add_edge(&G, 3, 3);
    add_edge(&G, 2, 5);
    //in cac cung 
    for (e = 0; e < G.m; e++){
        printf ("%d %d\n", G.edges[e].u, G.edges[e].v);
    }
    return 0;
}