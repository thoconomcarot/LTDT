//In các cung từ ma trận kề với đầu vào là số đỉnh của đồ thị có hướng
#include <stdio.h>
#define Max_n 100
typedef struct{
    int n;
    int A[Max_n][Max_n];
}Graph;

void init_graph (Graph *pG, int n){
    pG->n = n;
    for (int u = 1; u <= n; u++){
        for (int v = 1; v <= n; v++){
            pG->A[u][v] = 0;
        }
    }
}
int main (){
    Graph G;
    int n,u,v;
    scanf ("%d", &n);  //nhập số đỉnh của đồ thị
    init_graph(&G, n);

    for (u = 1; u <= G.n; u++){
        for (v = 1; v <= G.n; v++){
            scanf ("%d", &G.A[u][v]);
        }
    }

    for (u = 1; u <= G.n; u++){
        for (v = 1; v <= G.n; v++){  //A[u][v] khác A[v][u]
            for (int i = 1; i <= G.A[u][v]; i++){
                printf ("%d %d\n", u, v);
            }
        }
    }
    return 0;
}