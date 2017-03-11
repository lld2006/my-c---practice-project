#include "../lib/tools.h"
#include <cstdio>

i64 nmod = 1234567890LL;
int main()
{
    
    vector<i64> vn2;
    i64 nmax = 123456787654321;
    vn2.push_back(nmax % nmod);
    i64 n = nmax;
    int count = 0;
    while(n){
        n/=2;        
        vn2.push_back(n % nmod);
        vn2[count] -= vn2[count+1];
        ++count;
    }
    i64 sum = 0;
    for(int i = 0; i<(int)vn2.size(); ++i){
        for(int j = i; j<(int)vn2.size();++j){
            for(int k=j; k<(int)vn2.size();++k){
                i64 mult = 6;
                if(i==j && j==k)
                    mult = 1;
                else if(i==j||j==k||i==k){
                    mult = 3;
                }
                if((i^j^k)==0){
                    mult = multmod(mult, vn2[i], nmod);
                    mult = multmod(mult, vn2[j], nmod);
                    mult = multmod(mult, vn2[k], nmod);
                    printf("%d %d %d %lld %lld %lld %lld\n", i, j, k, vn2[i], vn2[j], vn2[k], mult);
                    sum = addmod(sum ,mult, nmod);
                }
            }
        }
    }
    i64 nx = nmax%nmod;
    i64 x0 = multmod(nx, nx, nmod);
    x0 = multmod(x0, nx, nmod);
    sum = addmod(x0, -sum, nmod);
    if(sum < 0) sum += nmod;
    printf("%lld\n", sum);
}
