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

int degree(Graph *pG, int u){
    int deg = 0;
    for (int e = 0; e < pG->m; e++){
        if (pG->edges[e].u == u){
            deg++;
        }
        if (pG->edges[e].v == u){
            deg++;
        }
    }
    return deg;
}

int main(){
    Graph G;
    int n, m;
    int u,v;
    freopen("dt.txt", "r", stdin);
    scanf ("%d %d", &n, &m);
    init_graph(&G, n);
    for (int e = 0; e < m; e++){
        scanf ("%d %d", &u, &v);
        add_edge(&G, u, v);
    }
    for (int u = 1; u <=n; u++){
        printf ("deg(%d) = %d\n", u, degree(&G, u));
    }
    return 0;
}