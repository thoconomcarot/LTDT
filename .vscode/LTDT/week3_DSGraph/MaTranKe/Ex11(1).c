//In các đỉnh kề của các đỉnh trong đồ thị vô hướng có đa cung và khuyên
#include <stdio.h>
#define max_n 100
typedef struct{
    int n,m;
    int A[max_n][max_n];
}Graph;

void init_graph(Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= n; u++){
        for (int v = 1; v <= n; v++){
            pG->A[u][v] = 0;
        }
    }
}

void add_edge(Graph *pG, int u, int v){
    pG->A[u][v]+=1;
    if (u != v){
        pG->A[v][u]+=1;
    }
    pG->m++;
}

void neighbours (Graph *pG, int u){
    int v;
    for (v = 1; v <= pG->n; v++){
        if (pG->A[u][v] != 0){
            printf ("%d ", v);
        }
    }
    printf ("\n");
}

int main (){
    Graph G;
    int n,m,u,v;
    scanf ("%d %d", &n, &m);
    init_graph(&G, n);
    for (int e = 0; e < m; e++){
        scanf ("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    
    // printf ("Ma tran ke:\n");
    // for (int u = 1; u <= G.n; u++){
    //     for (int v = 1; v <= G.n; v++){
    //         printf ("%d ", G.A[u][v]);
    //     }
    //     printf ("\n");
    // }
    
    for (int v = 1; v <= G.n; v++){
        printf ("neighbours(%d) = ", v);
        neighbours(&G, v);
    }
    return 0;
}