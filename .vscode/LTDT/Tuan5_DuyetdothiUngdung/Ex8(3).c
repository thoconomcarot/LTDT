//Viết chương trình đọc một đồ thị vô hướng từ bàn phím và đếm số đỉnh của bộ phận liên thông của đỉnh s. 
//Đỉnh s được đọc từ bàn phím.
#include <stdio.h>
#define max 100
    int dem;

typedef int ElementType;
int mark[max];
typedef struct{
    int n,m;
    int A[max][max];
}Graph;

typedef struct{
    ElementType data[max];
    int front,rear;
}Queue;

//khoi tao hang doi
void init_queue (Queue *pQ){
    pQ->front = 0;
    pQ->rear = -1;
}

//dua ptu vao cuoi
void enqueue (Queue *pQ, int u){
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

void add_edge(Graph *pG, int u, int v){
    pG->A[u][v] = 1;
    pG->A[v][u] = 1;
    pG->m++;
}

void BFS(Graph *pG, int s){
    Queue Q;
    //khởi tạo Q rỗng

    init_queue (&Q);
    enqueue (&Q,s);   //đưa s vào Q, duyệt từ s
    //vòng lặp chính để duyệt
    while (!empty(&Q)){
        int u = front (&Q);
        dequeue(&Q);
        if (mark[u] != 0){
            continue;  //u đã duyệt thì bỏ qua
        }
        //printf ("%d\n", u);
        mark[u] = 1;  //đánh dấu đã duyệt
        dem +=1;
        
        //xét các đỉnh kề của u, đưa vào Q
        for (int v = 1; v <= pG->n; v++){
            if (pG->A[u][v] > 0){
                enqueue (&Q,v);
            }
        }
    }
}

// //kiểm tra đồ thị có liên thông không
// int connected (Graph *pG){
//     //khởi tạo all đỉnh đều chưa duyệt
//     for (int i = 1; i <= pG->n; i++){
//         mark[i] = 0;
//     }

//     //Duyệt đồ thị từ đỉnh bất kỳ
//     BFS(pG, 1);

//     //ktra xem còn đỉnh nào chưa duyệt
//     for (int i = 1; i <= pG->n; i++){
//         if (mark[i] == 0){ //vẫn còn đỉnh chưa duyệt
//             return 0;  //đồ thị không liên thông, thoát
//         }
//     }
//     return 1; //tất cả đỉnh đã duyệt => liên thông
// }

int main (){
    Graph G;
    int n, m, u, v,s;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
	
    for (int e = 0; e < m; e++) {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    for (int i = 1; i <= n; i++){
        mark[i] = 0;
    }

    scanf ("%d", &s);
    dem = 0;
    BFS(&G, s);
    // for (int i = 1; i <= n; i++){
    //     if (mark[i] == 0){
    //         dem = 0;
    //         BFS(&G, i);
    //     }
    // }

    printf ("%d", dem);
    return 0;
}
