//Viết hàm add_edge lưu trữ đa đồ thị vô hướng và chứa khuyên
void add_edge(Graph *pG, int u, int v){
    pG->A[u][v] += 1;
    pG->m++;
    if (u != v){
        pG->A[v][u] += 1;
    }
}