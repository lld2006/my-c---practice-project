//first look, it is pretty easy, but after a second thought
//still need careful handling of n^x mod 1e9
#include <cstdio>
#include "../lib/tools.h"
i64 np2 = 1562500LL;
//change number from abcd to abc0;
void process_d(i64& base, vector<i64>& vn, i64 nmod)
{
    base = addmod(base, vn[0], nmod);
    vn[0] = 0;
}
//change number from abc0 to ab00
void process_c(i64& base, vector<i64>& vn, i64 nmod, bool& baselt10)
{
    assert(vn[0] == 0);
    i64 c = vn[1];
    if(c == 0) return;
    if(base<10 && baselt10){//looks like this is useless?
        base += (power(2LL, c) - 1)*(base + 1);
        if(base >= 10) 
            baselt10 = false;
    }else{
        c%=np2;
        base += mult64mod((powermodule(2LL, c, nmod) - 1), (base + 1), nmod);
    }
    vn[1] = 0;
}
//to a000
void process_b(i64& base, vector<i64>& vn, i64 nmod)
{
    assert((vn[0] == 0) && (vn[1] == 0));
    i64 b = vn[2];
    while(b > 0){
        //assert(b < 100000);
        i64 basep = 2 * base + 1;
        i64 t = 2ll* base + 2LL;
        i64 x = powermodule(2LL, base%np2, nmod) - 1;
        i64 y = mult64mod(x, t, nmod);
        y = addmod(basep, y, nmod);
        base = y;
        //printf("base=%lld\n", base);
        assert(base >= 0);
        --b;
    }
    vn[2] = 0;
}
i64 weak_goodstein_sequence(int n, i64& base, i64 nmod)
{
    vector<i64> vn;
    vn.resize(4, 0);
    for(unsigned int i = 0; i < 4; ++i)
        vn[i] = (n & (1<<i)) ? 1: 0;
    bool cIsSmall = true;
    while(true){
        process_d(base, vn, nmod);
        process_c(base, vn, nmod, cIsSmall);
        process_b(base, vn, nmod);
        if(vn[3] > 0){
            vn[3] = 0;
            vn[2] = base;
            vn[1] = base;
            vn[0] = base;
            ++base;
        }else{
            assert((vn[2] == 0) && (vn[1] == 0) && (vn[0] == 0)); 
            return base;
        }
    }
    return 0;
}
int main()
{
    i64 sum = 0;
    for(unsigned int i = 1; i < 16; ++i){
        // number, base, mod
        i64 base = 2;
        i64 val = weak_goodstein_sequence(i, base,1000000000LL) - 2;
        sum += val;
        printf("%d %lld %lld\n", i, val, sum);
    }
    printf("%lld\n", sum%1000000000LL);
}
