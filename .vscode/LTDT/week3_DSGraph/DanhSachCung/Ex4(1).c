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

//kiểm tra u có kề với v không trong đồ thị vô hướng
int adjacent (Graph *pG, int u, int v){
    for (int e = 0; e < pG-> m; e++){
        if ((pG->edges[e].u == u && pG->edges[e].v == v) || (pG->edges[e].u == v && pG->edges[e].v == u)){
            return 1;
        }
    }
    return 0;
}

int main (){
    Graph G;
    int n,m, u,v;
    scanf ("%d%d", &n, &m);
    init_graph(&G,n);
    
    
    for (int e = 0; e < m; e++){
        scanf("%d%d", &u, &v);
        add_edge(&G,u,v);
    }

    for (int u = 1; u <= G.n; u++){
        if (adjacent(&G, u, v)){ 
                printf ("%d\n", u);
        }
    }
    return 0;
}