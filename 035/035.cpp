#include <cstdio>
#include "../lib/tools.h"

int check_cyclic_primes(int num, vector<bool>& flags, int nmod)
{
    int px = num;
    int cnt = 0;
    while(cnt==0||num != px){
        px *= 10;
        int nd = px/nmod;
        px = (px + nd)%nmod;
        if(px < num || flags[px]==0)
            return 0; 
        ++cnt;
    }
    return cnt;
}

int main()
{
    int target = 1000000;
    vector<bool> flags;
    flags.resize(target + 1, true);
    flags[2] = 1;
    int root = round(sqrt(target));
    for( int i = 2; i <= root; ++i){
        if(!flags[i]) continue;
        for( int j = 2*i; j< flags.size(); j+=i){
            flags[j] = false;
        }
    }
    int nmod = 1;
    int tot = 0;
    for(unsigned int i = 2; i < flags.size(); ++i){
        if(!flags[i]) continue;
        if(i > nmod) nmod *= 10;
        tot += check_cyclic_primes(i, flags, nmod);
    }
    printf("%d\n", tot);
}
