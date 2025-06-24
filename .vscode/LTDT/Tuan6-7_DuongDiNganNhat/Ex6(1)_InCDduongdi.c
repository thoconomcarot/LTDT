//Viết chương trình đọc một đơn đồ thị có hướng, 
//có trọng số (có thể âm) từ bàn phím và in ra chiều dài đường đi ngắn nhất từ đỉnh s đến đỉnh t 
//(s và t cũng được đọc từ bàn phím).

#include <stdio.h>
#define MAX_N 1000
#define oo 999999

int pi[MAX_N];
int p[MAX_N];
int path[MAX_N];

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

        // for (int u = k - 1; u >= 0; u--){
        //     printf("%d", path[u]);
        //     // if (u != 0){
        //     //     printf (" -> ");
        //     // }
        // }

        printf ("%d\n", pi[t]);
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
    
    // cách 2
    // if (pi[t] < oo){
    //     printf ("%d\n", pi[t]);
    // }
    // else{
    //     printf ("-1");
    // }
    print_path(s,t);
}
