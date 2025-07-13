//DUYỆT TOÀN BỘ ĐỒ THỊ
//in các đỉnh theo thứ tự duyệt khi duyệt đồ thị theo chiều rộng bắt đầu từ đỉnh 1. (đơn vô hướng)
    //không liên thông, sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó
    //cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.
#include <stdio.h>
#define max 100
typedef int ElementType;
int mark[max];
typedef struct{
    ElementType data[max];
    int front, rear;
}Queue;

typedef struct{
    int n,m;
    int A[max][max];
}Graph;

void init_queue (Queue *pQ){
    pQ->front = 0;
    pQ->rear = -1;
}

void enqueue(Queue *pQ, int u){
    pQ->rear++;
    pQ->data[pQ->rear] = u;
}

void dequeue (Queue *pQ){
    pQ->front++;
}

ElementType front (Queue *pQ){
    return pQ->data[pQ->front];
}

int empty(Queue *pQ){
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

void add_egde (Graph *pG, int u, int v){
    pG->A[u][v] = 1;
    pG->A[v][u] = 1;
    pG->m++;
}


void BFS(Graph *pG, int s){
    Queue Q;
    init_queue(&Q);
    enqueue(&Q,s);
    while(!empty(&Q)){
        int u = front(&Q);
        dequeue(&Q);
        if (mark[u] != 0){
            continue;  //bỏ qua
        }
        printf ("%d\n", u);
        mark[u] = 1;

        for (int v = 1; v <= pG->n; v++){
            if (pG->A[u][v] > 0){
                enqueue(&Q, v);
            }
        }
    }
}

int main (){
    Graph G;
    int n, m, u, v;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (int e = 0; e < m; e++){
        scanf ("%d%d", &u, &v);
        add_egde(&G, u, v);
    }

    for (int i = 1; i <= n; i++){
        mark[i] = 0;
    }

    for (int i = 1; i <= n; i++){
        if (mark[i] == 0){
            BFS(&G,i);
        }
    }
    return 0;
    
}