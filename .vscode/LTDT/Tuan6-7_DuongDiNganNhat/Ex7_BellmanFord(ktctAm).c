//Viết chương trình đọc vào một đơn đồ thị có hướng, có trọng số, 
//áp dụng thuật toán Bellman – Ford kiểm tra xem nó có chứa chu trình âm hay không 
//khi ta tìm đường đi ngắn nhất từ đỉnh s đến các đỉnh còn lại.
#include <stdio.h>
#define MAX_N 1000
#define NO_EDGE -1
#define oo 99999

int pi[MAX_N];  //dinh u(pi/p) 
int p[MAX_N];

//Biểu diễn đồ thị bằng phương pháp danh sách cung
typedef struct{
    int u,v;
    int w;
}Edge;

//GRAPH//
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

//Bellman_Ford
void BellmanFord (Graph *pG, int s){
    int u, v, w;
	//khoi tao cac dinh co pi = oo va p = 0
	for (u = 1; u <=pG->n; u++){
		pi[u] = oo;
	}
	
	//khoi tao dinh bat dau
	pi[s] = 0;
	p[s] = -1; //truoc dinh s khong co cha 
	
    //lặp n-1 lần
	for (int it = 1; it < pG->n; it++){
		for (int k = 0; k < pG->m; k++){
            //duyệt qua các cung và cập nhật nếu thỏa
            u = pG->edges[k].u;
            v = pG->edges[k].v;
            w = pG->edges[k].w;
            if (pi[u] == oo){ //chưa có đường đi đến u, bỏ qua cung u v
                continue;
            }

            if (pi[u] + w < pi[v]){
                pi[v] = pi[u] + w;
                p[v] = u;
            }
		}
	}
    //Cách 2
    // for (int k = 0; k < pG->m; k++){
    //     u = pG->edges[k].u;
    //     v = pG->edges[k].v;
    //     w = pG->edges[k].w;
    //     if (pi[u] == oo){
    //         continue;
    //     }
    //     if (pi[u] + w < pi[v]){
    //         return 1;
    //     }
    // }
    // return 0;
    
}

int main (){
	Graph G;
	int n,m,u,v,w,s;
	scanf ("%d%d", &n, &m);
    init_graph(&G, n);
	
	for (int e = 0; e < m; e++){
		scanf ("%d%d%d",&u, &v, &w);
			add_edge (&G, u, v, w);
	}

	scanf ("%d", &s);
    BellmanFord(&G, s);

    //
    int negative_cycle = 0;
    for (int k = 0; k < G.m; k++){
        u = G.edges[k].u;
        v = G.edges[k].v;
        w = G.edges[k].w;
        if (pi[u] == oo){
            continue;
        }
        if (pi[u] + w < pi[v]){
            negative_cycle = 1;
            break;
        }
    }
    // if (BellmanFord(&G, s) == 1){
    //     printf ("YES\n");
    // }
    // else{
    //     printf ("NO");
    // }

    if (negative_cycle){
        printf ("YES");
    }
    else{
        printf ("NO");
    }

	return 0;
}

