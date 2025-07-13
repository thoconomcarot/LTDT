//Cho một dự án gồm n công việc. Mỗi công việc u có một thời gian hoàn thành d[u] và 
//một danh sách các công việc phải hoàn thành trước khi thực hiện u. 
//Hãy tính thời gian sớm nhất và thời gian trễ nhất để bắt đầu các công việc.

#include <stdio.h>
#define MAX_N 100
#define oo 999999
#define max(a,b) ((a > b) ? a : b)
#define min(a,b) ((a < b) ? a : b)
typedef int ElementType;
int d[MAX_N];   //thời gian mỗi cv

//---------------------Queue-----------------------
typedef struct{
	ElementType data[MAX_N];
	int front, rear;
}Queue;

void init_queue (Queue *pQ){
	pQ->front = 0;
	pQ->rear = -1;
}

int front (Queue *pQ){
	return pQ->data[pQ->front];
} 

void enqueue (Queue *pQ, ElementType x){
	pQ->rear++;
	pQ->data[pQ->rear] = x;
}

void dequeue (Queue *pQ){
	pQ->front++;
}

int empty_queue (Queue *pQ){
	if (pQ->front > pQ->rear){
		return 1;
	}
	return 0;
}

//-------------------------List--------------------------
typedef struct{
	ElementType data[MAX_N];
	int size;
}List;

//lam rong ds
void init_list (List *pL){
	pL->size = 0;
}

void push_back (List *pL, int x){
	pL->data[pL->size] = x;
	pL->size++;
}
//luu so ptu trong ds
int size (List *pL){
	return pL->size;
}

int element_at(List *pL, int i) {
    if (i >= 0 && i < pL->size) {
        return pL->data[i];
    } else {
        return -1;  // hoặc một giá trị báo lỗi
    }
}

//-----------------------Graph-------------------------
typedef struct{
	int n,m;
	int A[MAX_N][MAX_N];
}Graph;

void init_graph (Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	for (int u = 1; u <= pG->n; u++){
		for (int v = 1; v <= pG->n; v++){
			pG->A[u][v] = 0;
		}
	}
}

void add_edge (Graph *pG, int u, int v){
	pG->A[u][v] = 1;
	pG->m++;
}

void topo_sort (Graph *pG, List *pL){
	int indeg[MAX_N] = {0}; //degree cua u
	//tinh deg vao cua u
    for (int u = 1; u <= pG->n; u++){
        for (int v = 1; v <= pG->n; v++){
            if (pG->A[u][v] != 0)
                indeg[v]++;
        }
    }

	//in_degree(pG);
	
	Queue Q;
	init_queue(&Q);
	
	for (int u = 1; u <= pG->n; u++){
		if (indeg[u] == 0){
			enqueue(&Q, u);
		}
	}
	
	init_list(pL);
	
	//lap den khi Q rong => stop
	while (!empty_queue(&Q)){
		int u = front(&Q);
		dequeue(&Q);
		push_back(pL, u);
		
		//xoa dinh u => giam bac cua cac dinh ke v cua u
		for (int v = 1; v <= pG->n; v++){
			if(pG->A[u][v] != 0){
				indeg[v]--;
				if (indeg[v] == 0){
					enqueue(&Q, v);
				}
			}
		}
	}
}



void read_list (Graph *pG, int n){
    int x;
    //đọc ds công việc
    for (int u = 1; u <= n; u++){
        scanf ("%d", &d[u]);
        do{
            scanf ("%d", &x);
            if (x > 0){
                add_edge(pG, x, u);
            }
        }while (x > 0);
    }
}

void add_vert(Graph *pG, int n, int alpha, int beta){
    int u, v, x;

    //thêm cung nối alpha với đỉnh có indeg = 0
    int alpha = n+1;
    d[alpha] = 0;
    for (int u = 1; u <= n; u++){
        int indeg = 0;
        for (x = 1; x <= n; x++){
            if (pG->A[x][u] > 0){
                indeg++;
            }
        }
        if (indeg == 0){
            add_edge (pG, alpha, u);
        }
    }

    //thêm cung nối đỉnh có outdeg = 0 vào beta
    int beta = n+2;
    for (u = 1; u <= n; u++){
        int outdeg = 0;
        for (v = 1; v <= n; v++){
            if (pG->A[u][v] > 0){
                outdeg++;
            }
        }
        if (outdeg == 0){
            add_edge (pG, u, beta);
        }
    }
}

void time_earliest(Graph *pG, List *pL){
    int n;
    int alpha = n+1, beta = n+2;
    //tính t[u]
    int t[MAX_N];
    t[alpha] = 0;
    for (int j = 2; j <= n; j++){
        int u = element_at(pL,j);
        t[u] = -oo;
        for (int x = 1; x <= pL->size; x++){
            if (pG->A[x][u] > 0){
                t[u] = max(t[u], t[x] + d[x]);
            }
        }
    }
}

void time_latest (Graph *pG, List *pL){
    int n;
    int alpha = n+1, beta = n+2;
    //tính T[u]
    int T[MAX_N];
    T[beta] = T[beta - 1];
    for (int j = pL->size - 1; j >= 1; j--){
        int u = element_at(pL, j);
        T[u] = +oo;
        for (int v = 1; v <= pG->n; v++){
            if (pG->A[u][v] > 0){
                T[u] = min(T[u], T[v] - d[v]);
            }
        }
    }
}
int main (){
	Graph G;
	List L;
	int n,u,v, x;
	scanf ("%d%d", &n);
	init_graph (&G, n+2);
    int alpha = n+1, beta = n+2;
    d[alpha] = 0;

    //xếp thứ tự đỉnh theo tôpo
    topo_sort(&G, &L);


    for (int j = 2; j <= L.size; j++){
        printf ("%d ", t[u]);
    }
    printf ("\n");

    for (int j = L.size - 1; j >= 1; j++){
        printf ("%d ", T[u]);
    }
    printf ("\n");

	return 0;
}
