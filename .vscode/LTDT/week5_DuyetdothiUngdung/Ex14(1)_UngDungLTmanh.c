#include <stdio.h>
#define max_n 100
#define min(a,b)  ((a < b) ? (a) : (b))  //định nghĩa hàm macro để sd bởi vi trong C kh có thư viện algorithm
typedef int ElementType;
int mark[max_n];
int num[max_n];  //lưu chỉ số đỉnh v trong quá trình duyệt
int min_num[max_n];  //lưu chỉ số nhỏ nhất của nút có thể đi đến được v(qt duyệt v theo chiều sâu)
int k; //chỉ số đỉnh (tăng dần trong quá trình duyệt)
int cnt_scc;

//GRAPH//
typedef struct{
    int n,m;
    int A[max_n][max_n];
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

int adjacent (Graph *pG, int u, int v){
    if (pG->A[u][v] > 0){
        return 1;
    }
    return 0;
}

//STACK//
typedef struct{
    int top_idx;
    ElementType data[max_n];
}Stack;

Stack S; //lưu theo thứ tự được duyệt
int on_stack[max_n];  // v có đang ở trong stack hay không ?


void init_stack (Stack *pS){
    pS->top_idx = -1;
}

void push (Stack *pS, ElementType u){
    pS->top_idx++;
    pS->data[pS->top_idx] = u;
}

int empty (Stack *pS){
    return pS->top_idx == -1;
}

int top (Stack *pS){
    return pS->data[pS->top_idx];
}

void pop (Stack *pS){
    pS->top_idx--;
}

void SCC (Graph *pG, int u){
    num[u] = min_num[u] = k;
    k++;
    push(&S, u);
    on_stack[u] = 1;

    //xét các đỉnh kề của u
    for (int v = 1; v <= pG->n; v++){
        if (adjacent(pG,u,v)){
            if (num[v] < 0){
                SCC(pG,v);
                min_num[u] = min(min_num[u], min_num[v]);
            }
            else if (on_stack[v]){
                min_num[u] = min(min_num[u], num[v]);
            }
        }
    }

    //ktra u có phải là đỉnh khớp/đỉnh cắt
    if (num[u] == min_num[u]){
        int w;
        cnt_scc++;
        do {  //lấy ll các đỉnh trong S ra cho đến khi gặp u
            w = top(&S);
            pop(&S);
            on_stack[w] = 0; 
        } while (w != u);
    }
}

int main (){
    Graph G;
    int n,m,u,v,p;
    scanf ("%d%d", &n, &m);
    init_graph(&G, n);
    init_stack(&S);
    cnt_scc = 0;
    k = 1;

    for (int e = 0; e < m; e++){
        scanf ("%d%d%d", &u, &v, &p);
        if (p == 1){
            add_edge(&G, u, v);
        } 
        else{
            add_edge(&G,u,v);
            add_edge(&G,v,u);
        }
    }

    //khởi tạo mảng num = -1 (chưa duyệt)
    for (int u = 1; u <= G.n; u++){
        num[u] = -1;
    }

    for (int u = 1; u <= G.n; u++){
        if (num[u] == -1){
            SCC(&G, u);
        }
    }

    if (cnt_scc == 1){
        printf ("OKIE\n");
    }
    else{
        printf ("NO\n");
    }

    // for (u = 1; u <= G.n; u++){
    //     printf("%d %d\n", num[u], min_num[u]);
    // }

    return 0;
}





