//Tính bậc của đỉnh trong đồ thị vô hướng
int degree(Graph *pG, int u){
    int deg = 0;
    for (int v = 1; v <= pG->n; v++){
        deg+=pG->A[u][v];
    }
    return deg + pG->A[u][u];
}