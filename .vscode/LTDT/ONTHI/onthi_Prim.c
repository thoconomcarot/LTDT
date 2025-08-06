//SỬ DỤNG MA TRẬN KỀ
#include <stdio.h>
#define MAX_N 100
#define NO_EDGE 0
#define oo 999999

//GRAPH
typedef struct{
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

void add_edge(Graph *pG, int u, int v, int W){
    pG->W[u][v] = W;
}

//PRIM
int mark[MAX_N];
int pi[MAX_N];
int p[MAX_N];

int prim (Graph *pG, Graph *pT, int s){
    //khởi tạo
    int u;
    for (u = 1; u <= pG->n; u++){
        pi[u] = oo;
        p[u] = -1;
        mark[u] = 0;
    }

    pi[s] = 0; //xđ đây là đỉnh bắt đầu

    //lặp để mở rộng cây khung
    for (int i = 1; i <= pG->n; i++){
        int min_dis = oo; //khoảng cách chưa có
        for (int x = 1; x <= pG->n; x++){ 
            //duyệt các đỉnh x chưa được đưa vào cây khung
            if (mark[x] == 0 && pi[x] < min_dis){
                min_dis = pi[x]; //cập nhật = pi[x] mới
                u = x; // đỉnh x sẽ được vào cây khung
            }
        }
        mark[u] = 1;
        
        //mở rộng cây khung từ đỉnh kề của u 
        for (int v = 1; v <= pG->n; v++){
            //có tồn tại cạnh u->v?
            if (pG->W[u][v] != NO_EDGE && mark[v] == 0){
                if (pG->W[u][v] < pi[v]){
                    pi[v] = pG->W[u][v];
                    p[v] = u;
                }
            }
        }
    }
    //dựng cây pT dựa trên p[u] và u 
    init_graph (pT, pG->n);
    int sum_w = 0;
    for (int u = 1; u <= pG->n; u++){
        //xét các đỉnh có cha
        if (p[u] != -1){
            int w = pG->W[p[u]][u];
            add_edge(pT, p[u], u, w);
            sum_w += w;
        }
    }
    return sum_w;
}

int main (){
    Graph G, T;
    int n,m,u,v,w;
    scanf ("%d%d", &n, &m);
    init_graph(&G, n);

    for (int e = 0; e < m; e++){
        scanf ("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    int result = prim(&G, &T, 1);
    printf ("%d\n", result);

    //in thông tin pi và p
    for (u = 1; u <= T.n; u++){
        for (v = 1; v <= T.n; v++){
            if (T.W[u][v] != NO_EDGE){
                printf ("%d %d %d\n", u, v, T.W[u][v]);
            }
        }
    }
    return 0;
}

