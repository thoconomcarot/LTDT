#include <stdio.h>
#define max_m 500
typedef struct{
    int u,v;
}Edge;
typedef struct{
    int n,m;
    Edge edges[max_m];
}Graph;

//hàm khởi tạo
void init_graph (Graph *pG, int n){
    pG->n = n;  //gán n là số đỉnh
    pG->m = 0;  //gán m là số cung
}

void add_edge(Graph *pG, int u, int v){
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->m++;
}

//kiểm tra u có kề với v không trong đồ thị có hướng
int adjacent (Graph *pG, int u, int v){
    for (int e = 0; e < pG-> m; e++){
        if (pG->edges[e].u == u && pG->edges[e].v == v) {
            return 1;
        }
    }
    return 0;
}

int main (){
    Graph G;
    init_graph(&G, 3);
    add_edge(&G, 1, 3);
    add_edge(&G, 2, 3);
    add_edge(&G, 2, 2);
    printf ("n = %d, m = %d\n", G.n, G.m);
    // for (int e = 0; e < G.m; e++){
    //     printf ("%d %d\n", G.edges[e].u, G.edges[e].v);
    // }
    for (int u = 1; u <= G.n; u++){
        for (int v = 1; v <= G.n; v++){
            if (adjacent(&G, u, v)){
                printf ("%d ke voi %d\n", u, v);
            }
            else{ 
                printf ("%d khong ke voi %d\n", u, v);
            }
        }
    }
    return 0;
}