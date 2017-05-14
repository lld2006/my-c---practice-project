#include <cstdio>
#include <cstdlib>
int main(int argc, char* argv[])
{
    int N = 1000;
    if(argc == 2) {
        N = atol(argv[1]);
    }
    int p, q, r;
    bool A[N+1][N+1][N+1];

    for(int i = 0; i<= N; ++i)
        for(int j =0; j<=N; ++j)
            for(int k=0; k<=N; ++k)
                A[i][j][k] = false;
    A[0][0][0] = true;

    for( int i = 0; i <= N; ++i){
        for(int j = 0; j<=N; ++j){
            for(int k = 0; k<= N; ++k){
                if(A[i][j][k] == true) continue;
                for(int multiple = 2; multiple<=N; ++multiple){
                       p=multiple * i; 
                       q=multiple * j;
                       r=multiple * k;
                       if(p>N || q>N || r>N) break;
                       A[p][q][r] = true;
                }
            }
        }
    }
    
    int cnt = 0;
    for(int i = 0; i<= N; ++i)
        for(int j =0; j<=N; ++j)
            for(int k=0; k<=N; ++k)
                if(!A[i][j][k])
                    ++cnt;
    printf("%d\n", cnt);
}
