#include <stdio.h>
int main (){
    int n,m;
    scanf ("%d %d", &m, &n);
    int a[m][n];
    int c = 0;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            scanf ("%d", &a[i][j]);
            if(a[i][j] > 0){
                c++;
            }
        }
    }
    printf ("%d", c);
    return 0;
}