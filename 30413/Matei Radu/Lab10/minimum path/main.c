#include <stdio.h>
#include <stdlib.h>

#define N_MAX 100
#define M_MAX 100

int dir[2][2] = {{0,-1},{-1,0}};

int cost_min(int x, int y, int n, int m, int c_map[N_MAX][M_MAX])
{
    int min = 1000000000;
    int n_x,n_y;
    for(int d = 0; d < 2; d++)
    {
        n_x = x + dir[d][0];
        n_y = y + dir[d][1];
        if(c_map[n_x][n_y] < min)
            min = c_map[n_x][n_y];
    }

    return min;
}

int build_matrix(int map[N_MAX][M_MAX],int m, int n){
    int c_map[N_MAX][M_MAX];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
           c_map[i][j] =0;
        }
    }
    c_map[0][0] = map[0][0];
    for (int i = 1; i < n; i++) {
        c_map[i][0] = c_map[i - 1][0] + map[i][0];
    }
    for (int j = 1; j < m; j++) {
        c_map[0][j] = c_map[0][j - 1] + map[0][j];
    }

     for(int i = 1; i < n; i++){
        for(int j = 1; j < m; j++)
        {
            c_map[i][j] = cost_min(i, j, n, m, c_map) + map[i][j];
        }
      }
      return c_map[n-1][m-1];
}

int main()
{
    int m,n;
    int map[N_MAX][M_MAX];
    FILE *rp ;
    rp = fopen("map.in", "r");
    fscanf(rp,"%d %d",&m,&n);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            fscanf(rp,"%d",&map[i][j]);
        }
    }

    printf("%d",build_matrix(map,m, n));

    return 0;
}
