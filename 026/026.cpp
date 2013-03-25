#include <cstdio>
#include "../lib/tools.h"
int cycle0(int num)
{
    vector<int> flags;
    flags.resize(num, 0);
    int nc = 1;
    while(nc < num){
        nc *= 10;
    }
    int period = 0;
    while(true){
        int res = nc%num;
        if(flags[res]==1){
            return period;
        }else{
            flags[res] = 1;
        }
        nc = res * 10;
        ++period;
    }
    return 0;
}
i64 cycle(i64 num)
{
    while((num & 1) == 0)
        num >>= 1;
    while(num% 5 == 0)
        num /= 5;
    if(num==3 || num==9)
        return 1;
    i64 m = 1;
    int prod = 10;
    
    while(prod != 1){
        ++m;
        prod *= 10;
        prod %= num;
    }
    return m;
}
int main()
{
    int target = 100000;
    vector<int> primes;
    primeWithin(primes, target);
    vector<int> vnum;
    vnum.resize(target, 0);
    
    for(unsigned int i = 0; i < primes.size(); ++i){
        int px = primes[i];
        if(px ==2 || px ==5)continue;
        for(unsigned int j = px; j < vnum.size(); j+=px)
            vnum[j] = 1;
    }
    int nmax = 0;
    int nx = 0;
    for(unsigned i = 3; i < vnum.size(); ++i){
        if(vnum[i] == 0) continue;
        int nt = cycle(i);
        if(nt > nmax){
            nmax = nt;
            nx = i;
        }
    }
    printf("%d number=%d\n", nmax, nx);
}
