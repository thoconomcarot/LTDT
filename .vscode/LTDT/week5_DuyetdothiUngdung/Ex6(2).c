//Dựng (các) cây DUYỆT ĐỒ THỊ khi duyệt đồ thị theo chiều rộng bắt đầu từ đỉnh 1. (đồ thị có hướng đơn)
//Nếu vẫn còn đỉnh chưa duyệt sau khi duyệt xong lần 1. tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó
//cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.
#include <stdio.h>
#define max 100
typedef int ElementType;
int mark[max];
int parent[max];
typedef struct{
    ElementType data[max];
    int front, rear;
}Queue;

typedef struct{
    int A[max][max];
    int n,m;
}Graph;

void init_queue(Queue *pQ){
    pQ->front = 0;
    pQ->rear = -1;
}

void enqueue (Queue *pQ, ElementType u){
    pQ->rear++;
    pQ->data[pQ->rear] = u;
}

ElementType front (Queue *pQ){
    return pQ->data[pQ->front];
}

void dequeue (Queue *pQ){
    pQ->front++;
}

int empty (Queue *pQ){
    if (pQ->front > pQ->rear){
        return 1;
    }
    return 0;
}

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

void BFS (Graph *pG, int s){
    Queue Q;
    init_queue(&Q);
    enqueue(&Q,s);
    //parent[s] = -1;
    mark[s] = 1;
    while(!empty(&Q)){
        int u = front(&Q);
        dequeue(&Q);
        for (int v = 1; v <= pG->n; v++){
            if (pG->A[u][v] > 0 && mark[v] == 0){   
                enqueue(&Q, v);
                parent[v] = u;
                mark[v] = 1;
            }
        }
    }
}

int main (){
    Graph G;
    int n,m,u,v;
    scanf ("%d%d", &n, &m);
    init_graph(&G, n);

    for (int e = 0; e < m; e++){
        scanf ("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    for (int i = 1; i <= n; i++){
        mark[i] = 0;   
		parent[i] = -1;     
    }

    for (int i = 1; i <= n; i++){
        if (mark[i] == 0){
            BFS(&G, i);
        }
    }

    for (u = 1; u <= n; u++){
        printf ("%d %d\n",u, parent[u]);
    }

    return 0;
}