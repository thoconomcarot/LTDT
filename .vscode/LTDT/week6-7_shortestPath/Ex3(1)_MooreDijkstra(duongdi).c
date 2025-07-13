//Viết chương trình đọc một đơn đồ thị có hướng, có trọng số không âm từ bàn phím, 
//tìm đường đi ngắn nhất từ đỉnh s đến đỉnh t (s và t cũng được đọc từ bàn phím).
//Lần ngược theo p[u] để có được đường đi ngắn nhất.

#include <stdio.h>
#define MAX_N 100
#define NO_EDGE -1
#define oo 99999
int mark[MAX_N];
int pi[MAX_N], p[MAX_N];
int path[MAX_N];


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

void add_edge (Graph *pG, int u, int v, int w){
    pG->W[u][v] = w;
    pG->m++;
}

void Moore_Dijkstra (Graph *pG, int s){
    int u;
    for (u = 1; u <= pG->n; u++){
        pi[u] = oo;
        mark[u]= 0;
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
                if (pi[u] + pG->W[u][v] < pi[v]){
                    pi[v] = pi[u] + pG->W[u][v];
                    p[v] = u;
                }
            }
        }
    }
    if (pi[u] == oo){
        printf ("-1");
    }
}

void print_path (int s, int t){
    int k = 0;
    int current = t;
    if (pi[t] == oo){
        printf ("-1");
    }
    else{
        while (current != -1){
            path[k++] = current;
            current = p[current];
        }

        for (int u = k - 1; u >= 0; u--){
            printf("%d", path[u]);
            if (u != 0){
                printf (" -> ");
            }
        }

        //printf ("%d\n", pi[n]);
    }
}

int main (){
    Graph G;
    int n,m,u,v,w;
    int s,t;
    scanf ("%d%d", &n, &m);
    init_graph(&G, n);

    for (int e = 0; e < m; e++){
        scanf ("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    scanf ("%d%d", &s, &t);
    Moore_Dijkstra(&G, s);
    print_path(s, t);

    // if (pi[n] == oo){
    //     printf("-1\n");
    // }
        
    // else{
    //     k = 0;
    //     current = n;
    //     while (current != -1){
    //         path[k++] = current;
    //         current = p[current];
    //     }

    //     printf ("%d\n", pi[n]);
    // }
        
    return 0;
}
