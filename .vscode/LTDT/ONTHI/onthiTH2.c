#include <stdio.h>
#define MAX_N 100

//------------------------------------Danh sách cung--------------------------------
typedef struct{
    int u,v;
}Edge;

typedef struct{
    int n,m;
    Edge edges[MAX_N];
}Graph1;

//Tính bậc vào của đỉnh (đồ thị có hướng)
int in_deg(Graph1 *pG, int u) {
    int deg = 0;
    for (int e = 0; e < pG->m; e++) {
        if (pG->edges[e].v == u) {
            deg++;
        }
    }
    return deg;
}

//tính bậc ra của đỉnh (đồ thị có hướng)
int out_deg(Graph1 *pG, int u) {
    int deg = 0;
    for (int e = 0; e < pG->m; e++) {
        if (pG->edges[e].u == u) {
            deg++;
        }
    }
    return deg;
}


//tính tổng bậc của đồ thị vô hướng 
int deg (Graph1 *pG, int u){
    int deg = 0;
    for (int e = 0; e < pG->m; e++){
        if (pG->edges[e].u == u || pG->edges[e].v == u){
            deg++;
        }
    }
    return deg;
}

//add_edge; đa cung vô hướng, có khuyên (dscung)
void add_edge(Graph1 *pG, int u, int v) {
    if (pG->m >= MAX_N) {
        return;
    }
    pG->edges[pG->m].u = u;
    pG->edges[pG->m].v = v;
    pG->m++;
}

//có hướng: in đỉnh kề theo thứ tự từ nhỏ đến lớn (phải code hàm adj -> neighbour)
//danh sách cung có hướng(ktra có cung từ u-> v không)
int adjacent (Graph1 *pG, int u, int v){
    for (int e = 0; e < pG->m; e++){
        if (pG->edges[e].u = u && pG->edges[e].v == v){
            return 1; //tìm thấy cung u->v
        }
    }
    return 0;
}

//ds cung vô hướng
int adjacent (Graph1 *pG, int u, int v){
    for (int e = 0; e < pG->m; e++){
        if ((pG->edges[e].u == u && pG->edges[e].v == v)|| (pG->edges[e].u == v && pG->edges[e].v == u)){
            return 1;
        }
    }
    return 0;
}

//in ra các đỉnh kề (đã theo thứ tự tăng dần do v: 1->n)
void neighbour (Graph *pG, int u){
    for (int v = 1; v <= pG->n; v++){
        if(adjacent(pG, u, v) != 0){
            printf ("%d ",v);
        }
    }
    printf ("\n");
}

//-------------------------------------Ma trận kề-----------------------------------------
typedef struct{
    int n,m;
    int A[MAX_N][MAX_N];
}Graph;

// Thêm cạnh giữa u và v (có thể là khuyên, đa cung): có hướng
void add_edge(Graph *pG, int u, int v){
    if (u == v){  //co khuyen
        pG->A[u][v]++; 
    }
    else if (pG->A[u][v] == 1){ //da cung 13 31
        pG->A[u][v]++;
    }
    else{
        pG->A[u][v] = 1;
    }
    pG->m++;
}

//đa đồ thị vô hướng có chứa khuyên
void add_edge(Graph *pG, int u, int v){
    pG->A[u][v]++;  //trường hợp đa cung
    pG->m++;
    if (u != v){
        pG->A[v][u]++;
    }
}


int adjacent (Graph *pG, int u, int v){
    if (pG->A[u][v] != 0){
        return 1;
    }
    return 0;
}

//in ra các đỉnh kề (đã theo thứ tự tăng dần do v: 1->n)
void neighbour (Graph *pG, int u){
    for (int v = 1; v <= pG->n; v++){
        if(adjacent(pG, u, v) != 0){
            printf ("%d ",v);
        }
    }
    printf ("\n");
}
//in không cần hàm adj vô hướng
void neighbours (Graph *pG, int u){
    int v;
    for (v = 1; v <= pG->n; v++){
        if (pG->A[u][v] != 0){  //có hướng: pG->A[u][v] > 0
            printf ("%d ", v); 
        }
    }
    printf ("\n");
}

//tính bậc ra của đt có hướng
int out_deg(Graph *pG, int u) {
    int deg = 0;
    for (int v = 1; v <= pG->n; v++) {
        if (pG->A[u][v] != 0)
            deg++;
    }
    return deg;
}

//tính bậc vào của đt có hướng
int in_deg(Graph *pG, int u) {
    int deg = 0;
    for (int v = 1; v <= pG->n; v++) {
        if (pG->A[v][u] != 0)
            deg++;
    }
    return deg;
}

//Tính tổng bậc trong dt có hướng chứa đa cung và khuyên
int degree(Graph *pG, int u){
    int deg = 0;
    for (int v = 1; v <= pG->n; v++){
        deg += pG->A[u][v] + pG->A[v][u];
    }
    return deg;
}

//Tính in_deg đồ thị có hướng chứa đa cung và khuyên
int indegree(Graph *pG, int u){
    int indeg = 0;
    for (int v = 1; v <= pG->n; v++){
        indeg += pG->A[v][u]; //outdeg += pG->A[u][v]
    }
    return indeg;
}

//tính bậc của dt vô hướng
int deg(Graph *pG, int u) {
    int deg = 0;
    for (int v = 1; v <= pG->n; v++) {
        if (pG->A[u][v] != 0) {
            if (u == v)
                deg += 2; // khuyên
            else
                deg++;
        }
    }
    return deg;
}

