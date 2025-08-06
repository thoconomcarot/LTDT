#include <stdio.h>
#define MAX_N 100
int r[MAX_N];

//LIST
typedef struct{
    int data[MAX_N];
    int size;
}List;

void init_list (List *pL){
    pL->size = 0;
}

void push_back (List *pL, int x){
    pL->data[pL->size] = x;
    pL->size++;
}

int size (List *pL){
    return pL->size;
}

int element_at (List *pL, int x){
    if (x >= 0 && x < pL->size){
        return pL->data[x];
    }
    return -1;
}

void copy_list (List *pL1, List *pL2){
    pL1->size = pL2->size;
    for (int i = 0; i < pL2->size; i++){
        pL1->data[i] = pL2->data[i];
    }
}

//GRAPH
typedef struct{
    int n,m;
    int A[MAX_N][MAX_N];
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

//TOPO
void topo_rank (Graph *pG){
    //tính bậc vào cho tất cả đỉnh
    int in_deg[MAX_N];
    for (int u = 1; u <= pG->n; u++){
        in_deg[u] = 0;
        for (int v = 1; v <= pG->n; v++){
            if (pG->A[v][u] != 0){
                in_deg[u]++;
            }
        }
    }
    
    //khởi tạo dsL1 và L2
    List L1, L2;
    init_list(&L1);
    init_list(&L2);

    //các đỉnh có bậc vào bằng 0 vào ds L1
    for (int u = 1; u <= pG->n; u++){
        if (in_deg[u] == 0){
            push_back(&L1, u);
        }
    }

    //hạng tính từ 0
    int k = 0;

    while (L1.size > 0){
        init_list(&L2);
        for (int i = 0; i < L1.size; i++){
            int u = element_at(&L1, i);
            r[u] = k; //xep hang cho u

            for (int v = 1; v <= pG->n; v++){
                if (pG->A[u][v] != 0)
                    in_deg[v]--;
                    if (in_deg[v] == 0)
                        push_back(&L2, v); 
            }
        }
        k++;
        copy_list(&L1, &L2);
    }
}
    

int main (){
	Graph G;
	List L;
	int n,m,u,v;
	scanf ("%d%d", &n, &m);
	init_graph (&G, n);
	
	for (int e = 0; e < m; e++){
		scanf ("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	
	topo_rank(&G);
    for (int u = 1; u <= n; u++){
        printf ("r[%d] = %d\n", u, r[u]);
    }
	return 0;
}