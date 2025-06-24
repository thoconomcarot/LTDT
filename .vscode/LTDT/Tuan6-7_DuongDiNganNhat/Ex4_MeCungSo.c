#include <stdio.h>
#define MAX_N 1000
#define NO_EDGE -1
#define oo 99999
 
int n,m;
int A[100][100];
int mark[MAX_N];
int pi[MAX_N];  
int p[MAX_N];

int dr[] = {-1, 1, 0, 0};  //row
int dc[] = {0, 0, -1, 1};  //column

//Kiểm tra ô đó có nằm trong mê cung hong
int inside (int r, int c){
	return r >= 0 && r < n && c >= 0 && c < m;
}

//Moore-Dijkstra
void MooreDijkstra (int s){
    int N = n * m; //tổng đỉnh trong ma trận
	//khoi tao cac dinh co pi = oo va p = 0
	for (int i = 0; i < N; i++){
		pi[i] = oo;
		mark[i] = 0;
		p[i] = -1; 
	}

	
	//khoi tao chi phí ban đầu 
	pi[s] = 0;
	
    //lặp n-1 lần
	for (int it = 0; it < N; it++){
		//tim u chua danh dau va co pi[u] nho nhat
		int u = -1;
		int min_pi = oo;
		for (int i = 0; i < N; i++){
			if ( !mark[i] && pi[i] < min_pi){
				min_pi = pi[i];
				u = i;
			}
		}
		if (u < 0){
			break;
		}

		mark[u] = 1;
		//Đổi đỉnh u thành ô (i,j)
		int ur = u/m; 
		int uc = u%m;
		
        for (int k = 0; k < 4; k++){
			int vr = ur + dr[k], vc = uc + dc[k];
			if (!inside(vr, vc)){
				continue;
			} 
			int v = vr*m + vc;
			int w = A[vr][vc];
			if (!mark[v] && pi[u] + w < pi[v]){
				pi[v] = pi[u] + w;
				p[v] = u;
			}
		}
	}
}

int main (){
	scanf ("%d%d", &n, &m);
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			scanf ("%d", &A[i][j]);
		}
	}

	MooreDijkstra(0);
	int t = (n-1)*m + (m-1);
	printf ("%d ", pi[t]);
	return 0;
}

