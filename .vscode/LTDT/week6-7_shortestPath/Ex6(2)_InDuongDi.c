//Viết chương trình đọc một đơn đồ thị có hướng, 
//có trọng số (có thể âm) từ bàn phím và in ra đường đi ngắn nhất từ đỉnh s đến đỉnh t (u1 -> u2 -> u3 ->....un)
//(s và t cũng được đọc từ bàn phím).
#include <stdio.h>
#define MAX_N 1000
#define oo 999999
#define NO_EDGE -1

int pi[MAX_N];
int p[MAX_N];
int path[MAX_N];  //lưu các đỉnh trên đường đi

typedef struct{
    int u,v;
    int w;
}Edge;

typedef struct{
    int n,m;
    Edge edges[MAX_N];
}Graph;

void init_graph (Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
}

void add_edge (Graph *pG, int u, int v, int w){
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->edges[pG->m].w = w;
    pG->m++;
}

void BellmanFord (Graph *pG, int s){
    int u, v, w;
    for (int u = 1; u <= pG->n; u++){
        pi[u] = oo;
    }
    pi[s] = 0;
    p[s] = -1;

    for (int it = 1; it < pG->n; it++){
        for (int k = 0; k < pG->m; k++){
            u = pG->edges[k].u;
            v = pG->edges[k].v;
            w = pG->edges[k].w;
            
            if (pi[u] == oo){
                continue;
            }

            if (pi[u] + w < pi[v]){
                pi[v] = pi[u] + w;
                p[v] = u;
            }
        }
    }
}

void print_path (int s, int t){
    int k = 0;  //số đỉnh của đường đi
    int current = t;
    if (pi[t] == oo){
        printf ("-1");
    }
    else{
        //lần ngược theo p để lấy đường đi
        while (current != -1){
            path[k] = current;
            k++;
            current = p[current];
        }

        //In ra màn hình theo chiều ngược lại
        printf("%d", path[k-1]);
    
        for (int u = k-2; u >= 0; u--){
            printf(" -> %d", path[u]);
        }

        //printf ("%d\n", pi[t]);
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

    int s, t;
    scanf ("%d%d", &s, &t);
    BellmanFord(&G, s);
    print_path(s,t);
}
