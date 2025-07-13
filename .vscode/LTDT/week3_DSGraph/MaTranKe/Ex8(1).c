//Viết hàm add_edge lưu trữ đơn đồ thị vô hướng
void add_edge(Graph *pG, int u, int v){
    pG->A[u][v]++;
    pG->A[v][u]++;
    pG->m++;
}