#include <stdio.h>
#include <stdlib.h>
#define MAX_N 500

//......................Graph.........................
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

//.....................Kruskal...........................
int parent[MAX_N];

//tim goc cua dinh u 
int find_root (int u){
	while (parent[u] != u){
		u = parent[u];
	}
	return u;
}

void sort_edges(Graph *pG) {
    for (int i = 0; i < pG->m - 1; i++) {
        for (int j = i + 1; j < pG->m; j++) {
            Edge a = pG->edges[i];
            Edge b = pG->edges[j];
            int swap = 0;
            if (a.w > b.w) swap = 1;
            else if (a.w == b.w && a.u > b.u) swap = 1;
            else if (a.w == b.w && a.u == b.u && a.v > b.v) swap = 1;
            if (swap) {
                Edge tmp = pG->edges[i];
                pG->edges[i] = pG->edges[j];
                pG->edges[j] = tmp;
            }
        }
    }
}

int Kruskal (Graph *pG, Graph *pT){
	int m;

	//sap xep cac cung theo thu tu trong so tang dan
	sort_edges(pG);

	//khoi tao pT, khoi tao bo quan ly BPLT
	init_graph(pT, pG->n);
	for (int u = 1; u <= pG->n; u++){
		parent[u] = u; //moi dinh u la BPLT nen u la goc
	}
	
	int total_w = 0; //tong trong so cung cua cay
	//duyet qua cac cung cua G
	for (int e = 0; e < pG->m; e++){
		int u = pG->edges[e].u;
		int v = pG->edges[e].v;
		int w = pG->edges[e].w;
		int root_u = find_root(u);
		int root_v = find_root(v);
		if (root_u != root_v){
			add_edge(pT, u, v, w); //them cung u,v va trong so vao cay pT
			parent[root_v] = root_u; //hop nhat 2 BPLT
			total_w += w;
		}
	}
	return total_w;
}

int main (){
	int n,m,u,v,w;
	scanf ("%d%d", &n, &m);
	Graph G, T;
	init_graph(&G, n);
	
	for (int e = 0; e < m; e++){
		scanf ("%d%d%d", &u, &v, &w);
		add_edge(&G, u, v, w);
	}
	
	int total_w = Kruskal(&G, &T);
	printf ("%d\n", total_w);
	
	for (int e = 0; e < T.m; e++){
		printf ("%d %d %d\n", T.edges[e]. u, T.edges[e].v, T.edges[e].w);
	}
	return 0;
}















