//Viết chương trình đọc vào một đơn đồ thị có hướng và kiểm tra xem nó có chứa chu trình hay không.
//Nhắc lại: Chu trình là một đường đi có đỉnh đầu trùng với đỉnh cuối.

#include <stdio.h>
#define max 100
#define WHITE 0
#define GRAY 1
#define BLACK 2
int mark[max];
int color[max];
int has_circle;

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
	pG->m++;
}

int adjacent(Graph *pG, int u, int v){

	return pG->A[u][v] > 0;
		
}

void DFS(Graph *pG, int u){
	//To mau dang duyet cho u
	color[u] = GRAY;
	
	for (int v = 1; v <= pG->n; v++){
		if (adjacent(pG, u, v)){
			if (color[v] == WHITE){
				DFS(pG, v);
			}
			else if (color[v] == GRAY){
				has_circle = 1;
			}
		}
	}
	color[u] = BLACK;
}

int main (){
	Graph G;
	int n,m,u,v;
	scanf ("%d%d", &n, &m);
	init_graph (&G, n);
	
	for (int e = 0; e < m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	for (u = 1; u <= G.n; u++){
		color[u] = WHITE;
	}
	
	has_circle = 0;
	
	for (u = 1; u <= n; u++){
		if (color[u] == WHITE){
			DFS(&G, u);
		}
	}
	
	if (has_circle){
		printf ("CIRCLED");
	}
	else{
		printf ("NO CIRCLE");
	}
	
	return 0;
}