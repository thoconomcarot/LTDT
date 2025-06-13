//Tính bậc của đỉnh trong đồ thị có hướng chứa đa cung và khuyên
int degree(Graph *pG, int u){
    int deg = 0;
    for (int v = 1; v <= pG->n; v++){
        deg += pG->A[u][v] + pG->A[v][u];
    }
    return deg;
}