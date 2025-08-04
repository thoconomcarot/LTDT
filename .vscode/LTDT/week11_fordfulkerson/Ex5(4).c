#include <stdio.h>
#define MAX_N 100
#define NO_EDGE 0
#define oo 999999

//---------------------GRAPH--------------------------
typedef struct{
    int C[MAX_N][MAX_N];  //khả năng thông qua của cung
    int F[MAX_N][MAX_N];  //luồng qua cung
    int n;
}Graph;

void init_flow (Graph *pG){
    for (int u = 0; u < pG->n; u++){
        for (int v = 0; v < pG->n; v++){
            pG->F[u][v] = 0;
        }
    }
}

//---------------------LABEL--------------------------
typedef struct{
    int dir;    //+1:+     -1:-    0:chưa có nhãn
    int p;      //đỉnh trước
    int sigma;  //lượng tăng luồng khi qua đỉnh này 
}Label;

Label labels[MAX_N]; //Nhãn các đỉnh

int min (int a, int b){
    return (a < b) ? a : b;
}

//---------------------Queue--------------------------
typedef struct{
    int data[MAX_N];
    int front, rear;
}Queue;

void init_queue (Queue *pQ){
    pQ->front = 0;
    pQ->rear = -1;
}

void enqueue (Queue *pQ, int u){
    pQ->rear++;
    pQ->data[pQ->rear] = u;
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

int front (Queue *pQ){
    return pQ->data[pQ->front];
}

//---------------------FORD-FULKERSON--------------------------
int FordFulkerson (Graph *pG, int s, int t){
    //khởi tạo luồng = 0, gán F[u][v] = 0
    init_flow(pG);
    int max_flow = 0; //tổng luồng cực đại tìm được từ s->t

    //lặp
    Queue Q;
    do {
        //B1 - xóa nhãn các đỉnh và gắn nhãn cho s
        for (int i = 0; i <= pG->n; i++){
            labels[i].dir = 0;
        }
        //Xóa tất cả các nhãn, gán nhãn s: (+,s,oo)
        labels[s].dir = +1;
        labels[s].p = -1;
        labels[s].sigma = oo;

        //Khởi tạo Q rỗng, đưa s vào Q
        init_queue(&Q);
        enqueue(&Q, s);

        int found = 0; //đánh dấu đã tìm được đường chưa?

        //B2 - lặp gán nhãn cho các đỉnh để tìm đường tăng luồng
        while (!empty(&Q)){
            //Lấy 1 đỉnh trong Q ra, gọi nó là u
            int u = front(&Q);
            dequeue(&Q);

            //Xét gán nhãn cho các đỉnh kề với u: cung thuận
            for (int v = 1; v <= pG->n; v++){
                //ktra v có nhãn chưa và cung từ u->v có còn tăng luồng được nữa không
                if (pG->C[u][v] != NO_EDGE && labels[v].dir == 0 && pG->F[u][v] < pG->C[u][v]){
                    labels[v].dir = +1; //cung thuận 
                    labels[v].p = u;
                    labels[v].sigma = min(labels[u].sigma, pG->C[u][v] - pG->F[u][v]);
                    enqueue(&Q, v);
                }            
            }
            //xét gán nhãn cho các đỉnh đi đến u: cung nghịch
            for (int v = 1; v <= pG->n; v++){
                //ktra v có nhãn chưa và có tồn tại v->u đang có luồng không => thu hồi luồng từ u về v
                if (pG->C[v][u] != NO_EDGE && labels[v].dir == 0 && pG->F[v][u] > 0){
                    labels[v].dir = -1; //gán nhãn thu hồi luồng
                    labels[v].p = u;
                    labels[v].sigma = min(labels[u].sigma, pG->F[v][u]);
                    enqueue(&Q, v);
                }
            }
            //nếu t được gán nhãn => Tìm được đường tăng luồng, thoát vòng lặp
            if (labels[t].dir != 0){
                found = 1;
                break;
            }
        }

        //if (tìm được đường tăng luồng){
        if (found == 1){
            //Bước 3 - Tăng luồng
            int sigma = labels[t].sigma;
            //3.1 - cập nhật các luồng trên cung
            int u = t;
            while (u != s){
                int p = labels[u].p;
                if (labels[u].dir > 0){
                    pG->F[p][u] += sigma; //đi xuôi thì tăng luồng
                }
                else{
                    pG->F[u][p] -= sigma; //đi ngược thì giảm luồng
                }
                u = p; //truy ngược u về s
            }
            //3.2 - tăng giá trị luồng
            max_flow += sigma;
        }
        else{
            break; //thoát vòng lặp
        }
    } while(1);

    return max_flow;
}

int main (){
    Graph G;
    int n, m, u, v, c;
    scanf ("%d %d", &n, &m);
    G.n = n;
    init_flow(&G);

    for (int e = 0; e < m; e++){
        scanf ("%d%d%d", &u, &v, &c);
        G.C[u][v] = c;
    }

    int max_flow = FordFulkerson(&G, 1, n);
    printf ("Max flow: %d\n", max_flow);
    printf ("S: ");
    for (int i = 1; i <= n; i++){
        if (labels[i].dir != 0){
            printf ("%d ", i);
        }
    }
    printf ("\n");
    printf ("T: ");
    for (int i = 1; i <= n; i++){
        if (labels[i].dir == 0){
            printf ("%d ", i);
        }
    }

    return 0;
}