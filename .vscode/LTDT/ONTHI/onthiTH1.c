//tìm (đếm-count) số đỉnh của bộ phận liên thông chứa đỉnh 1 và đánh giá độ lớn của BPLT

#include <stdio.h>
#define MAX_N 100
int A[MAX_N][MAX_N]; // ma trận kề
int mark[MAX_N];  // mảng đánh dấu

int count = 0;
void DFS(int u, int n) {
    mark[u] = 1; //đánh dấu dã duyệt u
    count++; //đếm số đỉnh trong BPLT
    for (int v = 1; v <= n; v++) { //lặp qua các đỉnh kể của u 
        if (A[u][v] && mark[v] == 0) { //nếu có cung u->v mà chưa duyệt thì gọi DFS duyệt
            DFS(v, n); 
        }
    }
}

int main() {
    int n;
    scanf("%d", &n); 
 
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &A[i][j]);

    DFS(1, n); // bắt đầu từ đỉnh 1

    printf("So dinh trong BPLT chua dinh 1: %d\n", count);

    // Đánh giá độ lớn
    if (count == n)
        printf("BPLT chua dinh 1 la toan bo do thi.\n");
    else if (count > n / 2)
        printf("BPLT la lon.\n");
    else if (count > 1)
        printf("BPLT la vua.\n");
    else
        printf("BPLT la nho.\n");

    return 0;
}

//in ra những cung có trọng số không nhỏ hơn 5 
//theo thứ tự ngược lại với thứ tự nhập (dscung)
#include <stdio.h>
#define MAX_M 1000  // số cung tối đa

typedef struct {
    int u, v, w; // đỉnh đầu, đỉnh cuối, trọng số
} Edge;

typedef struct {
    int m;
    Edge edges[MAX_M];
} Graph;

void print_heavy_edges(Graph *pG) {
    for (int e = pG->m - 1; e >= 0; e--) {
        if (pG->edges[e].w >= 5) {
            printf("%d %d %d\n", pG->edges[e].u, pG->edges[e].v, pG->edges[e].w);
        }
    }
}

int main() {
    Graph G;
    int m; // số cung
    Edge edges[MAX_M];

    scanf("%d", &m); // nhập số cung

    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    print_heavy_edges(&G);

    return 0;
}

//in tất cả khuyên của đồ thị vô hướng, không lưu đa cung, có thể lưu được khuyên
//theo trình tự chỉ số đỉnh tăng dần, nếu kh khuyên thì in NO
void loop(Graph *pG){
    int check = 0;
    for (int u = 1; u <= pG->n; u++) {
        if (pG->A[u][u] > 0) { //có khuyên
            printf("(%d,%d)\n", u, u);
            check = 1;
        }
    }
    if (check == 0) {
        printf("NO\n");
    }
}

//đọc một đồ thị VÔ HƯỚNG  và in bậc lớn nhất và các đỉnh có bậc đó theo thứ tự tăng dần
void max_degree(Graph *pG) {
    int deg[MAX_N]; // mảng lưu bậc của các đỉnh, giả sử MAX_N = 100
    int max_deg = 0;

    // Tính bậc cho từng đỉnh
    for (int u = 1; u <= pG->n; u++) {
        deg[u] = 0;
        for (int v = 1; v <= pG->n; v++) {
            deg[u] += pG->A[u][v];
        }

        // Lưu lại bậc lớn nhất
        if (deg[u] > max_deg) {
            max_deg = deg[u];
        }
    }

    // In ra kết quả
    printf("Max degree: %d\n", max_deg);
    for (int u = 1; u <= pG->n; u++) {
        if (deg[u] == max_deg) {
            printf("%d ", u);
        }
    }
    printf("\n");
}

//vô hướng -> in các đỉnh kề của 1 theo thứ tự từ nhỏ đến lớn (ma trận kề)
#include <stdio.h>
#define MAX_N 100

typedef struct {
    int A[MAX_N][MAX_N];
    int n;
} Graph;

void neighbour(Graph *pG, int u) {
    for (int v = 1; v <= pG->n; v++) {
        if (pG->A[u][v] > 0) { // Có cạnh giữa u và v
            printf("%d ", v);
        }
    }
    printf("\n");
}

//hoặc là code
int adjacent (Graph *pG, int u, int v){
    return pG->A[u][v] > 0;
}
int main (){
    Graph G;

    for (int u = 1; u <= G.n; u++){
        if (adjacent(&G,1,u)){
            printf ("%d\n", u);
        }
    }
}



//count_edge đồ thị có hướng chứa đa cung và có khuyên (ma trận kề)
int count_edge(Graph *pG) {
    int count = 0;
    for (int u = 1; u <= pG->n; u++) {
        for (int v = 1; v <= pG->n; v++) {
            if (pG->A[u][v] > 0) {
                count += pG->A[u][v];
            }
        }
    }
    return count;
}

//in ra số cung thuộc thành phần liên thông cho trước
#include <stdio.h>

#define MAX_N 1000
#define MAX_M 5000

typedef struct {
    int u, v;
} Edge;

typedef struct {
    int n, m;
    Edge edges[MAX_M];
} Graph;

int mark[MAX_N];  // mảng đánh dấu đỉnh đã duyệt

void DFS(Graph *G, int u) {
    mark[u] = 1;
    for (int i = 0; i < G->m; i++) {
        if (G->edges[i].u == u && mark[G->edges[i].v] == 0) {
            DFS(G, G->edges[i].v);
        }
        if (G->edges[i].v == u && mark[G->edges[i].u] == 0) {
            DFS(G, G->edges[i].u);
        }
    }
}

int main() {
    Graph G;
    int x;
    scanf("%d%d%d", &G.n, &G.m, &x);
    for (int i = 0; i < G.m; i++) {
        scanf("%d%d", &G.edges[i].u, &G.edges[i].v);
    }

    // B1: tìm tập các đỉnh thuộc thành phần liên thông chứa x
    DFS(&G, x);

    // B2: đếm số cạnh có cả 2 đầu thuộc thành phần liên thông
    int count = 0;
    for (int i = 0; i < G.m; i++) {
        int u = G.edges[i].u;
        int v = G.edges[i].v;
        if (mark[u] && mark[v]) {
            count++;
        }
    }

    printf("%d\n", count);
    return 0;
}

//in ra đỉnh kề đồ thị có hướng, có thể đa cung, có thể có khuyên. (ma trận kề)
void print_neighbors(Graph *pG, int u) {
    for (int v = 1; v <= pG->n; v++) {
        for (int k = 1; k <= pG->A[u][v]; k++) {
            printf("%d ", v);
        }
    }
}


