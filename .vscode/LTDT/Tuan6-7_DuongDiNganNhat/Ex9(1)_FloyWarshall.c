//Viết chương trình đọc vào một đơn đồ thị có hướng, có trọng số, Không có chu trình âm
//Áp dụng thuật toán Floyd - Warshall để tìm đường đi ngắn nhất giữa các cặp đỉnh.

#include <stdio.h>
#define MAX_N 105
#define INF 100000000
#define NO_EDGE -1


int pi[MAX_N][MAX_N]; //đường đi ngắn nhất u -> v
int next[MAX_N][MAX_N];   //đỉnh kế tiếp đỉnh u trên đường đi ngắn nhất từ u -> v
int path[MAX_N];

typedef struct{
    int n,m;
    int W[MAX_N][MAX_N];
}Graph;

//khởi tạo ma trận k/c
void init_graph (Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= n; u++){
        for (int v = 1; v <= n; v++){
            pG->W[u][v] = NO_EDGE;
        }
    }
}

void add_edge (Graph *pG, int u, int v, int w){
    pG->W[u][v] = w;
    pG->m++;
}

void FloydWarshall (Graph *pG){
    // trong đoạn đường từ i -> j thì có 1 đỉnh trung gian ở giữa là k
    int u, v, k;
    for (u = 1; u <= pG->n; u++){
        for (v = 1; v <= pG->n; v++){
            pi[u][v] = INF;
            next[u][v] = -1;
        }
    } 

    for (u = 1; u <= pG->n; u++){
        pi[u][u] = 0;
        next[u][u] = u;
    }

    for (u = 1; u <= pG->n; u++){
        for (v = 1; v <= pG->n; v++){
            if (pG->W[u][v] != NO_EDGE){
                pi[u][v] = pG->W[u][v]; //đi trực tiếp từ u -> v
                next[u][v] = v;
            }
        }
    }

    for (k = 1; k <= pG->n; k++){
        for (u = 1; u <= pG->n; u++){
            for (v = 1; v <= pG->n; v++){
                if (pi[u][k] + pi[k][v] < pi[u][v]){
                    pi[u][v] = pi[u][k] + pi[k][v];
                    next[u][v] = next[u][k];
                }
            }
        }
    }
}

void print(Graph *pG) {
    for (int u = 1; u <= pG->n; u++) {
        for (int v = 1; v <= pG->n; v++) {
            printf("%d -> %d: ", u, v);
            if (next[u][v] == -1){
                 printf("NO PATH\n");
            }
            else{
                printf("%d\n", pi[u][v]);
            }
        }
    }
}

int main (){
    int n,m,u,v,w;
    Graph G;
    scanf ("%d%d", &n, &m);
    init_graph(&G, n);
    G.m = m;

    for (int e = 0; e < m; e++) {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    FloydWarshall(&G);
    print(&G);

    return 0;
}





