#include <vector>
#include "../lib/typedef.h"
#include <cstdio>
#include <cassert>
vector<i64> tentative;
vector<i64> succeed;
int dim = 10;
int index30(int dim, int i, int j, int k){
    return i*dim*dim+j*dim+k;
}
i64 pandig(){
    i64 sum = 0;
    for(int number = 2; number <= 40; ++number){
        vector<i64> vsc(succeed);
        succeed.clear();
        succeed.resize(10,0);
        succeed[1] = vsc[0];
        succeed[8] = vsc[9];
        //for the new level
        for(int i = 1; i <= 8; ++i){
            succeed[i-1]+=vsc[i];
            succeed[i+1]+=vsc[i];
        }
    vector<i64> vcp(tentative);
    tentative.clear();
    tentative.resize(dim*dim*dim, 0);
    for(int i = 0; i < 10; ++i)
        for(int j =0; j < 10; ++j)
            for(int k=j; k<10; ++k){
                if(vcp[index30(dim,i,j,k)] ==0) continue;
                if(i == 0){
                    assert(j == 0);
                    assert(k > i);
                    tentative[index30(dim, i+1,j,k)] += vcp[index30(dim,i,j,k)];
                }
                else if(i==9){
                    assert(k == 9);
                    assert(j <= 9);
                    if(i-1 <j)
                        tentative[index30(dim, i-1,i-1,k)] += vcp[index30(dim,i,j,k)];
                    else
                        tentative[index30(dim, i-1,j,k)] += vcp[index30(dim,i,j,k)];
                } else{
                    if( i- 1 < j )
                        tentative[index30(dim, i-1, i-1, k)] += vcp[index30(dim,i,j,k)];
                    else
                        tentative[index30(dim, i-1, j, k)] += vcp[index30(dim,i,j,k)];
                    if(i + 1 > k)
                        tentative[index30(dim, i+1, j, i+1)] += vcp[index30(dim,i,j,k)];
                    else
                        tentative[index30(dim, i+1, j, k)] += vcp[index30(dim,i,j,k)];
                }
            }
        for(int i = 0; i<=9; ++i){
            assert(tentative[index30(dim, i, 0, 9)] ==0 ||(i==0||i==9));
            succeed[i] += tentative[index30(dim, i, 0, 9)];
            tentative[index30(dim, i, 0, 9)] = 0;
        }
        for(int i = 0; i<=9; ++i)
            sum += succeed[i];
    }
    return sum;
}
//tentative [i, j, k] i is the current number j is min, k is max
int main(){
    i64 sum = 0;
    tentative.clear();
    tentative.resize(dim*dim*dim, 0);
    succeed.resize(dim, 0);
    for(int i = 1; i <= 9; ++i)
        tentative[index30(dim,i,i,i)] = 1;
    sum = pandig();
    printf("%lld\n", sum);
}
