//Tính bậc của đỉnh vào trong đồ thị có hướng chứa đa cung và khuyên
int indegree(Graph *pG, int u){
    int indeg = 0;
    for (int v = 1; v <= pG->n; v++){
        indeg += pG->A[v][u];
    }
    return indeg;
}