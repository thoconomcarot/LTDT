//Peter rất thích chơi đá. //Viết chương trình đọc vào một đồ thị có hướng không chu trình G. 
//Áp dụng thuật toán sắp xếp topo theo phương pháp duyệt theo chiều rộng để sắp xếp các đỉnh của G. 
//In các đỉnh ra màn hình theo thứ tự topo.
#include <stdio.h>
#define MAX_N 100
typedef int ElementType;

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
	int d[MAX_N]; //degree cua u
	//tinh deg vao cua u
    for (int u = 1; u <= pG->n; u++){
        d[u] = 0;
        for (int x = 1; x <= pG->n; x++){
            if (pG->A[x][u] != 0)
                d[u]++;
        }
    }

	//in_degree(pG);
	
	Queue Q;
	init_queue(&Q);
	
	for (int u = 1; u <= pG->n; u++){
		if (d[u] == 0){
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
				d[v]--;
				if (d[v] == 0){
					enqueue(&Q, v);
				}
			}
		}
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
	
	topo_sort(&G, &L);
	for (int i = 0; i < size(&L); i++){
		printf("%d\n", element_at(&L, i));
	}
	
	return 0;
}
