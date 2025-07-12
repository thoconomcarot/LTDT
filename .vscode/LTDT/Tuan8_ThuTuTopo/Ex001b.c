//Viết chương trình đọc vào một đồ thị có hướng không chu trình G, in các đỉnh của G ra màn hình theo thứ tự topo. 
//Nếu có nhiều thứ tự topo, in một thứ tự bất kỳ.
#include <stdio.h>
#define MAX_N 100
typedef int ElementType;
int mark[MAX_N];

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

//-------------------------DFS--------------------------
void DFS(Graph *pG, int u, List *pL) {
    mark[u] = 1;
    for (int v = 1; v <= pG->n; v++){
        //kiểm tra u có kề v không 
        if (pG->A[u][v] == 1 && mark[v] == 0)
            DFS(pG, v, pL);
            
    }
    push_back(pL, u);  //sau khi duyệt thì thêm vào list
}
        

//-------------------------topo-----------------------
void topo_sort(Graph *pG, List *pL) {
    init_list(pL);
    for (int i = 1; i <= pG->n; i++)
        mark[i] = 0;

    for (int u = 1; u <= pG->n; u++) {
        if (mark[u] == 0) {
            DFS(pG, u, pL);
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

    // In ngược danh sách kết quả
    for (int i = size(&L) - 1; i >= 0; i--) {
        printf("%d ", element_at(&L, i));
    }

	
	return 0;
}
