#include <stdio.h>
#define MAX_N 100
#define NO_EDGE 0
#define oo 999999

//GRAPH
typedef struct{
    int C[MAX_N][MAX_N];  //kha nang qua luong
    int F[MAX_N][MAX_N];  //luong qua cung
    int n;
}Graph;

int out_flow[MAX_N];
int in_flow[MAX_N];

void init_flow (Graph *pG){
    for (int u = 1; u <= pG->n; u++){
        for (int v = 1; v <= pG->n; v++){
            pG->F[u][v] = 0;
        }
    }
}

//QUEUE
typedef struct{
    int front, rear;
    int data[MAX_N];
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

int front (Queue *pQ){
    return pQ->data[pQ->front];
}

int empty (Queue *pQ){
    if (pQ->front > pQ->rear){
        return 1;
    }
    return 0;
}

//LABELS
typedef struct{
    int dir; //+1:+     -1:-    0:chua co nhan
    int p; //parent
    int sigma;  //luong tang luong
}Label;
Label labels[MAX_N];

int min (int a, int b){
    return (a < b) ? a : b;
}

//FORD_FULKERSON
int FordFulkerson (Graph *pG, int s, int t){
    
    //khởi tạo luồng = 0, gán F[u][v] = 0
    init_flow(pG);
    
    //tổng luồng cực đại tìm được từ s->t
    int max_flow = 0;
    
    Queue Q;
    
    //lặp - sai do...while
    do{
        //B1 - xóa nhãn các đỉnh và gắn nhãn cho s
        for (int u = 1; u <= pG->n; u++){
            labels[u].dir = 0;
        }

        //Xóa tất cả các nhãn, gán nhãn s: (+,s,oo)
        labels[s].dir = +1;
        labels[s].p = -1;
        labels[s].sigma = oo;

        //Khởi tạo Q rỗng, đưa s vào Q
        init_queue(&Q);
        enqueue(&Q, s);
        
        //đánh dấu đã tìm được đường chưa?
        int found = 0;
        
        //B2 - lặp gán nhãn cho các đỉnh để tìm đường tăng luồng
        while (!empty(&Q)){
            //Lấy 1 đỉnh trong Q ra, gọi nó là u
            int u = front(&Q);
            dequeue(&Q);

            //Xét gán nhãn cho các đỉnh kề với u: cung thuận
            for (int v = 1; v <= pG->n; v++){
                //ktra v có nhãn chưa và cung từ u->v có còn tăng luồng được nữa không
                if (pG->C[u][v] != NO_EDGE && labels[v].dir == 0 && pG->C[u][v] > pG->F[u][v]){
                    labels[v].dir = +1;
                    labels[v].p = u;
                    labels[v].sigma = min(labels[v].sigma, pG->C[u][v] - pG->F[u][v]);
                    enqueue(&Q, v);
                }
            }
            //xét gán nhãn cho các đỉnh đi đến u: cung nghịch
            for (int v = 1; v <= pG->n; v++){
                 //ktra v có nhãn chưa và có tồn tại v->u đang có luồng không => thu hồi luồng từ u về v
                if (pG->C[v][u] != NO_EDGE && labels[v].dir == 0 && pG->F[v][u] > 0){
                    labels[v].dir = -1;
                    labels[v].p = u;
                    labels[v].sigma = min(labels[v].sigma, pG->F[v][u]);
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
                if (labels[u].dir != 0){
                    pG->F[p][u] += sigma;
                }
                else{
                    pG->F[u][p] -= sigma;
                }
                u = p;
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
    int n, m, u, v, c, f;
    scanf ("%d %d", &n, &m);
    G.n = n;
    init_flow(&G);

    //Khởi tạo
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            G.C[i][j] = 0;
            G.F[i][j] = 0;
        }
        in_flow[i] = out_flow[i] = 0;
    }

    for (int e = 0; e < m; e++){
        scanf ("%d%d%d%d", &u, &v, &c, &f);
        //Kiểm tra điều kiện 1: 0 <= f <= c
        if (f < 0 || f > c){
            printf ("NO\n");
            return 0;
        }

        G.C[u][v] = c;
        G.F[u][v] = f;

        out_flow[u] += f;
        in_flow[v] +=f;
    }

    //Kiểm tra dk2: Tổng luồng đi ra khỏi đỉnh s = Tổng luồng đi vào đỉnh t
    int s = 1, t = G.n;
    if (out_flow[s] != in_flow[t]){
        printf ("NO\n");
        return 0;
    }

    //Ktra dk3: Tổng luồng đi vào đỉnh u = Tổng luồng đi ra khỏi u (u khác s và u khác t)
    for (int u = 1; u <= n; u++) {
        if (u == s || u == t){
            continue;
        } 
        if (in_flow[u] != out_flow[u]) {
            printf("NO\n");
            return 0;
        }
    }

    // Nếu qua tất cả kiểm tra
    printf("YES\n");
    return 0;
}
   
    
    
    
