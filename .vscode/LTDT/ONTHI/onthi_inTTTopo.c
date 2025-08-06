//sài hàng đợi (5 hàm cơ bản)
//sd dsach (init, push_back, size, element_at)
//sd ma trận kề(init, add)

#include <stdio.h>
#define MAX_N 100

//QUEUE
typedef struct{
    int front, rear;
    int data[MAX_N];
}Queue;

void init_queue (Queue *pQ){
    pQ->front = 0;
    pQ->rear = -1;
}

void enqueue (Queue *pQ, int x){
    pQ->rear++;
    pQ->data[pQ->rear] = x;
}

void dequeue (Queue *pQ){
    pQ->front++;
}

int front (Queue *pQ){
    return pQ->data[pQ->front];
}

int empty (Queue *pQ){
    if (pQ->front > pQ->rear){
        return 1;
    }
    return 0;
}

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
void topo_sort (Graph *pG, List *pL){
    //tính bậc vào của mỗi đỉnh
    int in_deg[MAX_N];
    for (int u = 1; u <= pG->n; u++){
        in_deg[u] = 0;
        for (int v = 1; v <= pG->n; v++){
            if (pG->A[v][u] != 0){  //có cung đi từ v -> u
                in_deg[u]++;
            }
        }
    }

    //khởi tạo hàng đợi =>lưu các đỉnh có in_deg = 0
    Queue Q;
    init_queue(&Q);

    //Nếu bậc u = 0 thì thêm vào queue
    for (int u = 1; u <= pG->n; u++){
        if (in_deg[u] == 0){
            enqueue(&Q, u);
        }
    }

    //khởi tạo danh sách lưu kết quả sau khi sắp xếp topo
    init_list(pL);

    while (!empty(&Q)){
        int u = front(&Q); //lấy u trong hàng đợi ra
        dequeue(&Q);
        push_back(pL, u); //thêm u vào ds

        //xóa đỉnh u, giảm bậc của các đỉnh kể v của u
        for (int v = 1; v <= pG->n; v++){
            if (pG->A[u][v] != 0){ //có cung từ u -> v
                in_deg[v]--; //giảm đi bậc vào của v vì đã xử lý u ở trên
                if (in_deg[v] == 0){  // không còn cung đến v nữa
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
    init_graph(&G, n);

    for (int e = 0; e < m; e++){
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    topo_sort(&G, &L);
    for (int i = 0; i < size(&L); i++){
        printf ("%d ", element_at(&L, i));
    }
    return 0;
}


