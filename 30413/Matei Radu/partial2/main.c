#include <stdio.h>
#include <stdlib.h>

int no_paths(int i, int j, int M, int N){
    if(i>N || j>M){
        return 0;
    }
    if(i==N && j==M){
        return 0;
    }
    if(M-i == 1 && N-j == 1){
        return 3;
    }
    if(M-i == 0 && N-j == 1){
        return 1;
    }
    if(M-i == 1 && N-j == 0){
        return 1;
    }
    return no_paths(i+1,j+1,M,N) + no_paths(i,j+1,M,N) + no_paths(i+1,j,M,N);
}

int main()
{
    int N,M;
    printf("Input N:");
    scanf("%d", &N);
    printf("Input M:");
    scanf("%d", &M);
    int paths = no_paths(1,1,M,N);
    printf("paths: %d", paths);
    return 0;
}
