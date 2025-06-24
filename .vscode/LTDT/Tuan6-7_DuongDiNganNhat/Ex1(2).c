//Viết chương trình đọc một đơn đồ thị vô hướng, có trọng số không âm từ bàn phím. 
//Cài đặt thuật toán Moore – Dijkstra để tìm (các) đường đi ngắn nhất từ đỉnh 1 đến các đỉnh còn lại. 
//In các thông tin pi[u] và p[u] của các đỉnh ra màn hình.
#include <stdio.h>
#define MAX_N 100
#define NO_EDGE -1
#define oo 999999
int mark[MAX_N];
int pi[MAX_N], p[MAX_N];

//GRAPH
typedef struct {
    int n,m;
    int W[MAX_N][MAX_N];
}Graph;

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
    pG->W[v][u] = w;
    pG->m++;
}

void Moore_Dijkstra (Graph *pG, int s){
    int u;
    for (u = 1; u <= pG->n; u++){
        pi[u] = oo;
        mark[u] = 0;
    }

    pi[s] = 0;
    p[s] = -1;

    for (int it = 1; it <= pG->n; it++){
        int min_pi = oo;
        for (int i = 1; i <= pG->n; i++){
            if (mark[i] == 0 && pi[i] < min_pi){
                min_pi = pi[i];
                u = i;
            }
        }
        
        mark[u] = 1;

        for (int v = 1; v <= pG->n; v++){
            if (pG->W[u][v] != NO_EDGE && mark[v] == 0){
                if(pi[u] + pG->W[u][v] < pi[v]){
                    pi[v] = pi[u] + pG->W[u][v];
                    p[v] = u;
                }
            }
        }
    }
}

int main (){
    Graph G;
    int n,m,u,v,w;
    scanf ("%d%d", &n, &m);
    init_graph(&G, n);

    for (int e = 0; e < m; e++){
        scanf ("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    Moore_Dijkstra(&G, 1);
    for (u = 1; u <= G.n; u++){
        printf ("pi[%d] = %d, p[%d] = %d\n", u, pi[u], u, p[u]);
    }
    return 0;
}
