//in đỉnh kề đồ thị có hướng
#include <stdio.h>
#define max_m 500
typedef struct{
    int u, v;
}Edge;
typedef struct{
    int n,m;
    Edge edges[max_m];
}Graph;
void init_graph(Graph *pG, int n){
    pG->n = n;  //so dinh = n
    pG->m = 0; //so cung = 0
}

void add_edge(Graph *pG, int u, int v){
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->m++;
}

int adjacent (Graph *pG, int u, int v){
    for (int e = 0; e < pG->m; e++){
        if (pG->edges[e].u == u && pG->edges[e].v == v){
            return 1;
        }
    }
    return 0;
}

void neighbours(Graph* pG, int u) {
    for(int v = 1; v <= pG->n; v++){
        if(adjacent(pG,u,v) != 0){
           printf("%d ", v);
       }
    }
    printf ("\n");
}

int main(){
    Graph G;
    int n, m;
    int u,v;
    scanf ("%d %d", &n, &m);
    init_graph(&G, n);
    for (int e = 0; e < m; e++){
        scanf ("%d %d", &u, &v);
        add_edge(&G, u, v);
    }
    
    for (int v = 1; v <= G.n; v++){
        printf("neighbours(%d) = ", v);
        neighbours(&G, v);
    }
    return 0;
}