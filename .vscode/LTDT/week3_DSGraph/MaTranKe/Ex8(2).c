//Viết hàm add_edge lưu trữ đơn đồ thị có hướng
void add_edge(Graph *pG, int u, int v){
        pG->A[u][v]++;
    pG->m++;
}