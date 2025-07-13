//DUYỆT TOÀN BỘ ĐỒ THỊ
//in các đỉnh theo thứ tự duyệt khi duyệt đồ thị theo chiều sâu bắt đầu từ đỉnh 1. (đơn có hướng)
//Nếu vẫn còn đỉnh chưa duyệt sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó
//cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.
#include <stdio.h>
#define max_size 100
typedef int ElementType;
int mark[max_size];

typedef struct{
    ElementType data[max_size];
    int top_idx;
}Stack;

typedef struct{
    int n,m;
    int A[max_size][max_size];
}Graph;

void init_stack(Stack *pS){
    pS->top_idx = -1;
}

void push (Stack *pS, ElementType u){
    pS->top_idx++;
    pS->data[pS->top_idx] = u;
}

ElementType top (Stack *pS){
    return pS->data[pS->top_idx];
}

void pop (Stack *pS){
    pS->top_idx--;
}

int empty(Stack *pS){
    return pS->top_idx == -1;
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

void DFS (Graph *pG, int s){
    Stack S;
    init_stack(&S);
    push(&S, s);
    while (!empty(&S)){
        int u = top(&S);
        pop(&S);

        if (mark[u] != 0){
            continue;
        }

        printf ("%d\n", u);
        mark[u] = 1;

        for (int v = pG->n; v >= 1; v--){
            if (pG->A[u][v] > 0 && mark[v] == 0){
                push(&S,v);
            }
        }
    }
}

int main (){
    Graph G;
    int n,m,u,v;
    scanf ("%d%d", &n, &m);
    init_graph(&G,n);

    for (int i = 0; i <= n; i++){
        mark[i] = 0;
    }

    for (int e = 0; e < m; e++){
        scanf("%d%d", &u, &v);
        add_edge(&G,u,v);
    }

    for (int i = 1; i <= n; i++){
        if (mark[i] == 0){
            DFS(&G,i);
        }
    }

    return 0;
}