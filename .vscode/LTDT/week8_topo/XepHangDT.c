#include <stdio.h>
#define MAX_N 100
int rank[MAX_N];

//.....................List............................
typedef struct{
    int size;
    int data[MAX_N];
}List;

//khoi tao list rong
void init_list (List *pL){
    pL->size = 0;
}

//thêm ptu x vào cuối ds
void push_back (List *pL, int x){
    pL->data[pL->size] = x;
    pL->size++;
}

//số ptu hiện có
int size (List *pL){
    return pL->size;
}

//lấy gtri ptu tai chi so i
int element_at (List *pL, int i){
    if (i >= 0 && i < pL->size){
        return pL->data[i];
    }
    else{
        return -1;
    }
}

//hàm copy các ptu từ pL2 vào pL1
void copy_list (List *pL1, List *pL2){
    pL1->size = pL2->size;
    for (int i = 0; i < pL2->size; i++){
        pL1->data[i] = pL2->data[i];
    }
}

//.................Graph................
typedef struct{
    int n,m;
    int A[MAX_N][MAX_N];
}Graph;

void init_graph (Graph *pG, int n){
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= n; u++){
        for (int v = 1; v <= n; v++){
            pG->A[u][v] = 0;
        }
    }
}

void add_edge (Graph *pG, int u, int v){
    pG->A[u][v] = 1;
    pG->m++;
}

//..................Rank.......................
void topo_rank (Graph *pG, List *pL){
    //khởi tạo
    int deg[MAX_N];
    List S1, S2;  
    //s1 chứa đỉnh hiện tại có indeg = 0
    //s2 chứa mới có indeg = 0 sau khi đã xử lý các đỉnh trong s1
    init_list(&S1);
    init_list(&S2);

    //tính bậc cho tất cả đỉnh (đây là cách tính bậc vào in_deg) = cách đếm số cạnh đi vào u
    for (int u = 1; u <= pG->n; u++){
        deg[u] = 0;
        for (int x = 1; x <= pG->n; x++){
            if (pG->A[x][u] != 0){  //nếu tồn tại cạnh đi từ x -> u thì tăng bậc lên 1
                deg[u]++;
            }
        }
    }

    //thêm các đỉnh u có deg[u] == 0 vào S1
    for (int u = 1; u <= pG->n; u++){
        if (deg[u] == 0){
            push_back(&S1, u);
        }
    }

    int k = 0;
    while (S1.size > 0){
        init_list(&S2); 
        //init lần 2 là vì trong mỗi lần lặp, S2 phải làm mới để chứa các đỉnh thuộc tầng kế tiếp, thay thế S1 ở vòng sau.
        for (int i = 0; i < S1.size; i++){
            int u = element_at(&S1, i);
            rank[u] = k; 

            //cứ tính hạng 1 đỉnh thì sẽ xóa bỏ đỉnh đó
            for (int v = 1; v <= pG->n; v++){
                if (pG->A[u][v] != 0){
                    deg[v]--;  //xóa canh u->v bằng cách giảm bậc
                    if (deg[v] == 0){
                        push_back(&S2,v); //nếu hiện tại v có bậc = 0 thì thêm vào s2
                    }
                }
            }
        }
    k++;
    copy_list (&S1, &S2);
    }
}

int main (){
    int n,m,u,v;
    Graph G;
    List L;
    scanf ("%d%d", &n, &m);
    init_graph(&G, n);
    
    for (int e = 0; e < m; e++){
        scanf ("%d%d", &u, &v);
        add_edge(&G,u,v);
    }

    topo_rank(&G, &L);
    for (int u = 1; u <= n; u++){
        printf ("%d\n", rank[u]);
    }
    return 0;
}

