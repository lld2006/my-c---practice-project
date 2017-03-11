#include <cstdio>
#include <cassert>
#include <vector>
#include "../lib/typedef.h"
#include "../lib/tools.h"
using namespace std;
i64 nmod = 104060401LL;
//comments, here the code is not correct the correct formula
//for p^n is (n+1)^k+(n-1)^k-2*n^k, k is the list size.

i64 gfun(const IntPairVec& vpairs, i64 nlist)
{
    i64 prod = 1;
    for(unsigned int i = 0; i < vpairs.size(); ++i){
        int np = vpairs[i].second;
        i64 v1 = powermodule(np, nlist, nmod);
        i64 v2 = powermodule(np-1, nlist, nmod);
        v1 -= v2;
        if(v1 < 0) v1 += nmod;
        assert(v1 >= 0);
        prod *= v1;
        prod %= nmod;
    }
    return prod;
}

int main()
{
    i64 mg = 1000000;
    i64 ml = 1000000000000LL; 
    i64 nlist = 1000000000000000000LL;
    mg = 10;
    ml = 100;
    nlist = 1;
    i64 limit = ml/mg;
    vector<int> ftable;
    factor_table_min(limit, ftable);
    vector<i64> vn, vsum;
    vn.resize(limit+1, 0);
    vn[1] = 1;
    for(int ng = 2; ng <vn.size(); ++ng){
        IntPairVec vpairs; 
        factor_using_table(ng, vpairs, ftable );
        vn[ng] = gfun(vpairs, nlist);
    }
    i64 sum = 0;
    for(int ng = 2; ng < vn.size(); ++ng){
        sum += vn[ng];
        sum %= nmod;
        vn[ng] = sum;
    }

    sum = 0;
    for(int ng = 1; ng <= limit; ++ng){
       i64 nmax = ml/ng; 
       i64 nmin = ml/(ng+1) + 1;
       i64 dn = nmax - nmin +1;
       i64 tp = (dn % nmod) * vn[ng];
       tp %= nmod;
       sum += tp;
       sum %= nmod;
    }
    printf("%lld\n", sum);
}
