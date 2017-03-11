//this should be a simple dynamic programming problem
#include <cstdio>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cassert>
i64 nmod = 1000000000;

i64 single_expe_dist(int src, int dest, int length, vector<i64>& vp)
{
    assert(src != dest);
    i64 t;
    if(src < dest) {
        t = vp[dest] - vp[src];
        t *= (vp[dest] + vp[src] - 2);
    }else{
        t = (vp[src] - vp[dest]);
        t *= (2*length- vp[src] - vp[dest]);
    }
    t %= nmod;
    return  t;
}

i64 expected_steps(i64 a, i64 b, i64 c, i64 len, i64 n)
{
    vector<vector<i64>> ve;
    vector<i64> vp = {a, b, c};
    ve.resize(3); 
    for(unsigned int i = 0; i<3; ++i){
        ve[i].resize(3, 0);
    }
    for( int src = 0; src < 3; ++src){
        for(int dest = 0; dest < 3; ++dest){
            if(src == dest) continue;
            ve[src][dest] = single_expe_dist(src, dest, len, vp);
        }
    }
    vector<vector<i64>> vdist(ve);
    vector<vector<i64>> vdt(vdist);
    //ve stored a single transition from src to dest
    //also initialized the first round motion
    for(int k = 2; k<=n; ++k){
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 3; ++j){
                if(i == j) continue;
                int k = 3-i-j;
                assert(k!=i && k!=j && k >=0);
                vdt[i][j] = vdist[i][k]+vdist[k][j]+ve[i][j] + ve[k][i] + ve[j][k];
                vdt[i][j] %= nmod;
            }
        }
        vdt.swap(vdist);
    }   
    //       overall    b to a
    return (vdist[0][2]+ve[1][0])%nmod;
}

int main()
{
    //i64 n, a, b,c, k;
    //n=3; k = 20; a = 4; b = 9; c = 17;
    i64 sum = 0;
    for(i64 n = 1; n<= 10000;++n){
        i64 k = powermodule(10LL, n, nmod);
        i64 a = powermodule(3LL,n,nmod);
        i64 b = powermodule(6LL,n,nmod);
        i64 c = powermodule(9LL,n,nmod);
        sum += expected_steps(a, b,c,k, n);
        sum %= nmod;
        //printf("%lld %lld\n", n, sum);
    }
    printf("%lld\n", sum);
}
