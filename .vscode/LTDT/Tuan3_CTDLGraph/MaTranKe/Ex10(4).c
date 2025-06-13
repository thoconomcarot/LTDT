//Tính bậc ra của đỉnh vào trong đồ thị có hướng chứa đa cung và khuyên
int outdegree(Graph *pG, int u){
    int outdeg = 0;
    for (int v = 1; v <= pG->n; v++){
        outdeg += pG->A[u][v];
    }
    return outdeg;
}