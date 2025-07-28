#include <stdio.h>
#define MAX_N 100
#define oo 999999
#define NO_EDGE 0

int mark[MAX_N];
int pi[MAX_N];
int p[MAX_N];

//-------------------Graph-------------------
typedef struct{
    int n,m;
    int W[MAX_N][MAX_N];
}Graph;

void init_graph (Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= n; u++){
        for (int v = 1; v <= n; v++){
            pG->W[u][v] = 0;
        }
    }
}

void add_edge (Graph *pG, int u, int v, int w){
    pG->W[u][v] = w;
}

int prim(Graph *pG, Graph *pT, int s){
    int u,v;
    //khởi tạo
    for (int u = 1; u <= pG->n; u++){
        pi[u] = oo;
        p[u] = -1;
        mark[u] = 0;   //chưa đỉnh nào được đánh dấu => S = rỗng
    }

    pi[s] = 0;

    //lặp n-1 lần
    for (int i = 1; i <= pG->n; i++){
        int min_dist = oo;
        for (int x = 1; x <= pG->n; x++){
            if (mark[x] == 0 && pi[x] < min_dist){
                min_dist = pi[x];
                u = x;
            }
        }
        mark[u] = 1;

        for (v = 1; v <= pG->n; v++){
            if (pG->W[u][v] != NO_EDGE){
                if (mark[v] == 0 && pi[v] > pG->W[u][v]){
                    pi[v] = pG->W[u][v];
                    p[v] = u;
                }
            }
        }

    }

    //dựng cây (dựa vào các p[u] tìm được ở trên)
    init_graph(pT, pG->n);
    int sum_w = 0;

    for (u = 1; u <= pG->n; u++){
        if (p[u] != -1){
            int w = pG->W[u][v];
            add_edge(pT, p[u], v, w);
            sum_w +=w;
        }
    }
    return sum_w;
}



