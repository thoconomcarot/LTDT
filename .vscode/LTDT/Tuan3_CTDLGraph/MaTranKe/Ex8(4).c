//Viết hàm add_edge lưu trữ đa đồ thị có hướng và chứa khuyên
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