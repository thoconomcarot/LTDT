//Cô giáo Trang chuẩn bị kẹo để phát cho các bé mà cô đang giữ. 
//Hãy viết chương trình giúp cô tính xem mỗi em cần được chia ít nhất bao nhiêu kẹo và 
//tổng số kẹo ít nhất mà cô phải chuẩn bị là bao nhiêu.

#include <stdio.h>
#define MAX_N 100
typedef int ElementType;
int rank[MAX_N];

//-------------------------List--------------------------
typedef struct{
	ElementType data[MAX_N];
	int size;
}List;

//lam rong ds
void init_list (List *pL){
	pL->size = 0;
}

//thêm vào cuối ds
void push_back (List *pL, int x){
	pL->data[pL->size] = x;
	pL->size++;
}
//luu so ptu trong ds
int size (List *pL){
	return pL->size;
}

//trả về giá trị tại ptu vị trí i
int element_at(List *pL, int i) {
    if (i >= 0 && i < pL->size) {
        return pL->data[i];
    } 
    else {
        return -1;  // hoặc một giá trị báo lỗi
    }
}

//copy các ptu của S2 vào S1
void copy_list (List *pS1, List *pS2){
    pS1->size = pS2->size;
    for (int i = 0; i < pS2->size; i++) {
        pS1->data[i] = pS2->data[i]; // sao chép từng phần tử
    }
}

//-----------------------Graph-------------------------
typedef struct{
	int n,m;
	int A[MAX_N][MAX_N];
}Graph;

void init_graph (Graph *pG, int n){
	pG->n = n;
	pG->m = 0;
	for (int u = 1; u <= pG->n; u++){
		for (int v = 1; v <= pG->n; v++){
			pG->A[u][v] = 0;
		}
	}
}

void add_edge (Graph *pG, int u, int v){
	pG->A[u][v] = 1;
	pG->m++;
}

//----------------------------Rank-----------------------
void topo_rank (Graph *pG){
    int deg[MAX_N];
    List S1;  //ds lưu các đỉnh đang xđ hạng (gốc cũ)
    List S2;  //ds lưu các đỉnh sắp xem xét hạng (d[u] == 0, gốc mới)
    //khởi tạo
    init_list(&S1);
    init_list(&S2);

    //tính bậc cho all đỉnh
    for (int u = 1; u <= pG->n; u++){
        deg[u] = 0;
        for (int x = 1; x <= pG->n; x++){
            if (pG->A[x][u] != 0){
                deg[u]++;
            }
        }
    }

    //đưa các đỉnh u có d[u] == 0 vào S1
    for (int u = 1; u <= pG->n; u++){
        if (deg[u] == 0){
            push_back(&S1, u);
        }
    }

    int k = 0;

    while (S1.size > 0){
        init_list(&S2);
        for (int i = 0; i < S1.size; i++){
            int u = S1.data[i];
            rank[u] = k;
            for (int v = 1; v <= pG->n; v++){
                if (pG->A[u][v] != 0){
                    deg[v]--;
                    if (deg[v] == 0){
                        push_back(&S2, v);
                    }
                }
            }
        }
        k++;
        copy_list(&S1, &S2); //sao chép s2 vào s1
    }
}

int main (){
    int n,m,u,v;
    Graph G;
    scanf ("%d%d", &n, &m);
    init_graph(&G, n);

    for (int e = 0; e < m; e++){
        scanf ("%d%d", &u, &v);
        add_edge(&G,v,u);
    }

    topo_rank(&G);
    int sum = 0;
    for (int u = 1; u <= n; u++){
        printf ("%d\n", rank[u]+1);
        sum += rank[u] + 1;
    }

    printf ("%d", sum);
    return 0;
}