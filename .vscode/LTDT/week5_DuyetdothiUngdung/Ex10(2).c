//Viết chương trình đọc vào một đơn đồ thị có hướng và kiểm tra xem nó có chứa chu trình hay không. 
//Nếu đồ thị có chu trình, in ra các đỉnh có trong chu trình.
//Trong ví dụ đầu tiên, ta tìm thấy chu trình 1 -> 3 -> 2 -> 1, vì thế chương trình phải in ra: 1 3 2 1

#include <stdio.h>
#define max 100
int mark[max];

//GRAPH////////
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

//ktra u có kề v
int adjacent(Graph *pG, int u, int v){
	return pG->A[u][v] > 0;
		
}

//DUYET//////
#define WHITE 0
#define GRAY 1
#define BLACK 2

int color[max];
int parent[max];
int circle_start, circle_end;
int has_circle;

void DFS(Graph *pG, int u, int p){
	//To mau dang duyet cho u
	color[u] = GRAY;
	parent[u] = p;
	
	for (int v = 1; v <= pG->n; v++){
		if (adjacent(pG, u, v)){
			if (color[v] == WHITE){   //v chưa duyệt
                DFS(pG, v, u);  //gọi đệ quy duyệt
			}
			else if (color[v] == GRAY){  //v đang duyệt
				has_circle = 1;
                circle_start = u;
				circle_end = v;
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
	
	for (u = 1; u <= G.n; u++){
		if (color[u] == WHITE){
			DFS(&G, u, -1);
		}
	}
	
	//Kiểm tra has_circle
	if (has_circle){
		int A[100], i = 0;
        A[0] = circle_start;
        int u = circle_start;

        do {
            u = parent[u];
			i++;
            A[i] = u;
        } while (u != v);
        
        for (int j = i; j >= 0; j--)
            printf("%d ", A[j]);

        printf("%d\n", A[i]);
    } 
	else{
		printf("-1\n");
	}
	
	return 0;
}