//Viết hàm init và add_edge lưu trữ đa đồ thị vô hướng có chứa khuyên
void init_graph(Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= n; u++){
        for (int v = 1; v <= n; v++){
            pG->A[u][v] = 0;
        }
    }
}

void add_edge(Graph *pG, int u, int v){
    pG->A[u][v] += 1;  //trường hợp đa cung
    pG->m++;
    if (u != v){
        pG->A[v][u] += 1;
    }
}