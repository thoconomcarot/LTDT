#include <stdio.h>
#define max 100
#define NO_COLOR 0
#define BLUE 1
#define RED 2
int mark[max];
int color[max];
int conflict;

typedef struct{
	int n,m;
	int A[max][max];
}Graph;

void init_graph (Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	for (int u = 1; u <= n; u++){
		for (int v = 1; v <= n; v++){
			pG->A[u][v] = 0;
		}
	}
}

void add_edge (Graph *pG, int u, int v){
	pG->A[u][v] = 1;
	pG->A[v][u] = 1;
	pG->m++;
}

int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0;	
}

void DFS (Graph *pG, int u, int c){
	color[u] = c;
	
	for (int v = 1; v <= pG->n; v++){
		if (adjacent(pG, u, v)){
			if (color[v] == NO_COLOR){
				DFS(pG, v, 3-c);
			}
			else if (color[v] == color[u]){
				conflict = 1;
			}
		}
	}
}

int main (){
	Graph G; 
	int n,m,u,v;
	scanf ("%d%d", &n, &m);
	init_graph (&G, n);
	
	for (int e = 0; e < m; e++){
		scanf ("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for (int u = 1; u <= G.n; u++){
		color[u] = NO_COLOR;
	}
	
	conflict = 0;
	for (u = 1; u <= n; u++){
		if (color[u] == NO_COLOR){
			DFS(&G, u, BLUE);
		}
	}
	
	if (conflict){
		printf ("NO");
	}
	else{
		printf ("YES");
	}
	
}