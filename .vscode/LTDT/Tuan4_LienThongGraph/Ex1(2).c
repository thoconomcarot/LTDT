//in ra các đỉnh theo thứ tự duyệt khi duyệt đồ thị theo chiều rộng bắt đầu từ đỉnh 1 (Đồ thị có hướng)
#include <stdio.h>
#define max 100
typedef int ElementType;
int mark[max];
typedef struct{
    int front, rear;
    ElementType data[max];
}Queue;

typedef struct{
    int n,m;
    int A[max][max];
}Graph;

//khởi tạo hàng đợi
void init_queue (Queue *pQ){
    pQ->front = 0;
    pQ->rear = -1;
}

//kiểm tra rỗng
int empty(Queue *pQ){
    return pQ->front > pQ->rear;
    //return pQ->front > pQ->rear;
}

//trả về phần tử đầu hàng đợi
ElementType front (Queue *pQ){
    return pQ->data[pQ->front];
}

//thêm vào cuối hàng đợi
void enqueue (Queue *pQ, int u){
    pQ->rear++;
    pQ->data[pQ->rear] = u;
}

//xóa hàng đợi
void dequeue (Queue *pQ){
    pQ->front++;
}

//Khởi tạo đồ thị
void init_graph (Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= n; u++){
        for (int v = 1; v <= n; v++){
            pG->A[u][v] = 0;
        }
    }
}

void add_edge(Graph *pG, int u, int v){
    pG->A[u][v] = 1;
    pG->m++;   
}

void BFS(Graph *pG, int s){
    Queue Q;
    init_queue (&Q);
    enqueue (&Q,s);
    while (!empty(&Q)){
        int u = front (&Q);
        dequeue(&Q);
        if (mark[u] != 0){
            continue;
        }
        printf ("%d\n", u);
        mark[u] = 1;
        
        for (int v = 1; v <= pG->n; v++){
            if (pG->A[u][v] > 0){
                enqueue (&Q,v);
            }
        }
    }
}

int main (){
    Graph G;
    int n, m, u, v;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
	
    for (int e = 0; e < m; e++) {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }
    BFS(&G, 1);
    
    return 0;
}



