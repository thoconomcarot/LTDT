//ỨNG DỤNG CỦA LIÊN THÔNG
//Có n hòn đảo và m cây cầu. Mỗi cây cầu bắt qua 2 hòn đảo. 
//Một hôm chúa đảo tự hỏi là với các cây cầu hiện tại thì đứng ở một hòn đảo bất kỳ 
//có thể nào đi đến được tất cả các hòn đảo khác mà không cần dùng đến thuyền hay không.
//Hãy giúp chúa đảo viết chương trình kiểm tra.

#include <stdio.h>
#define max 100
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
    //kh?i t?o Q r?ng
    init_queue (&Q);
    enqueue (&Q,s);   //dua s vào Q, duy?t t? s
    //vòng l?p chính d? duy?t
    while (!empty(&Q)){
        int u = front (&Q);
        dequeue(&Q);
        if (mark[u] != 0){
            continue;  //u dã duy?t thì b? qua
        }
        //printf ("%d\n", u);
        mark[u] = 1;  //dánh d?u dã duy?t
        
        //xét các d?nh k? c?a u, dua vào Q
        for (int v = 1; v <= pG->n; v++){
            if (pG->A[u][v] > 0){
                enqueue (&Q,v);
            }
        }
    }
}

//ki?m tra d? th? có liên thông không
int connected (Graph *pG){
    for (int i = 1; i <= pG->n; i++){
        mark[i] = 0;
    }

    BFS(pG, 1);

    for (int i = 1; i <= pG->n; i++){
        if (mark[i] == 0){ //v?n còn d?nh chua duy?t
            return 0;  //d? th? không liên thông, thoát
        }
    }
    return 1; //t?t c? d?nh dã duy?t => liên thông
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

    for (int i = 1; i <= n; i++){
        mark[i] = 0;
    }


    for (int i = 1; i <= n; i++){
        if (mark[i] == 0){
            BFS(&G, i);
        }
	}
	
	if (connected(&G) != 0){
		printf ("YES");
	}
	else{
		printf ("NO");
	}
	
    
    return 0;
}
