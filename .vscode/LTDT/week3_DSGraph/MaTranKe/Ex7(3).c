//Viết hàm init và add_edge lưu trữ đa đồ thị có hướng có chứa khuyên
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