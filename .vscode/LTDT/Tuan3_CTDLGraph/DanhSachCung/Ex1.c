#include <stdio.h>
#define max_m 500
typedef struct{
    int u,v;
}Edge;

typedef struct{
    int n,m;
    Edge edges[max_m];
}Graph;

//Ham khoi tao
void init_graph(Graph *pG, int n){
    pG->n = n; //Gán số đỉnh = n
    pG->m = 0; //Gán số cung = 0
}
int main (){
    Graph G;
    int e;
    init_graph(&G, 4);
    //In ra so dinh va so cung
    printf ("n = %d, m = %d\n", G.n, G.m);
    return 0;
}