//DUYỆT TOÀN BỘ ĐỒ THỊ
//in các đỉnh theo thứ tự duyệt khi duyệt đồ thị theo chiều rộng bắt đầu từ đỉnh 1. (đơn có hướng)
    //không liên thông, sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó
    //cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.

#include <stdio.h>
#define max 100
typedef int ElementType; //dễ đổi sang kdl khác như float, char mà không cần thay đổi từng cái một nếu dùng int
int mark[max];

typedef struct{
    ElementType data[max];
    int front, rear;
}Queue;

typedef struct{
    int A[max][max];
    int n,m;
}Graph;

void init_queue (Queue *pQ){
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

void add_edge (Graph *pG, int u, int v){
    pG->A[u][v] = 1;
    pG->m++;
}

void BFS(Graph *pG, int s){   //s là đỉnh bắt đầu duyệt
    Queue Q;
    init_queue(&Q);   //khởi tạo hàng đợi
    enqueue(&Q, s);   //thêm ptu s là đỉnh bắt đầu vào cuối hàng đợi
    while (!empty(&Q)){   //lặp cho đến khi queue rỗng  (!empty là chưa rỗng)
        int u = front (&Q);   //lấy phần tử đầu tiên ra
        dequeue(&Q);  //sau khi đã đọc u thì xóa nó
        if (mark[u] != 0){
            continue;
        }
        printf ("%d\n", u);
        mark[u] = 1;  //đánh dấu đỉnh u đã được duyệt

        for (int v = 1; v <= pG->n; v++){
            if (pG->A[u][v] > 0){  //ktra có cung nối từ u->v không  (>0 nghĩa là có cạnh)  (ktra đỉnh kề của u)
                enqueue(&Q,v);  //nếu có cung từ u->v thì thêm v vào hàng đợi, cb duyệt v
            }
        }
    }
}

int main (){
    Graph G;
    int n,m,u,v;
    scanf ("%d%d", &n, &m);
    init_graph(&G,n);
    
    for (int e = 0; e < m; e++){
        scanf("%d%d", &u, &v);
        add_edge(&G,u,v);
    }

    //đánh dấu i chưa duyệt
    for (int i = 1; i <= n; i++){
        mark[i] = 0;  
    }

    for (int i = 1; i <= n; i++){
        if (mark[i] == 0){
            BFS(&G, i);
        }
    }
    return 0;
}