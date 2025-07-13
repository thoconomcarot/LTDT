//DỰNG CÂY DUYỆT ĐỒ THỊ khi duyệt đồ thị theo chiều sâu bắt đầu từ đỉnh 1. (có hướng đơn)
//Nếu vẫn còn đỉnh chưa duyệt sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó
//cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.
#include <stdio.h>
#define max 100
int mark[max];
int parent[max];
typedef int ElementType;

typedef struct{
    ElementType data[max];
    int top;
}Stack;

typedef struct{
    int n,m;
    int A[max][max];
}Graph;

void init_stack (Stack *pS){
    pS->top = -1;
}

void push (Stack *pS, ElementType u){
    pS->top++;
    pS->data[pS->top] = u;
}

ElementType peek (Stack *pS){
    return pS->data[pS->top];
}

void pop(Stack *pS){
    pS->top--;
}

int empty(Stack *pS){
    return pS->top == -1;
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
    pG->m++;
}

void DFS (Graph *pG, int u, int p){
    Stack S;
    init_stack(&S);
    push(&S, u);
    mark[u] = 1;
    parent[u] = p;
    while(!empty(&S)){
        int u = peek(&S);
        pop(&S);
        
        if (mark[u] == 0){
            continue;
        }

        for (int v = 1; v <= pG->n; v++){
            if (pG->A[u][v] > 0 && mark[v] == 0){
                push(&S, v);
                DFS(pG, v, u);
                // parent[v] = u;
                // mark[v] = 1;
            }
        }
    }
}

int main (){
    Graph G;
    int n,m,u,v;
    scanf("%d%d", &n, &m);
    init_graph(&G,n);

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
            DFS(&G, i, -1);
        }
    }

    for (u = 1; u <= n; u++){
        printf ("%d %d\n", u, parent[u]);
    }
    return 0;
}