#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdio>
int main()
{
    i64 fac=3063060;
    i64 limit = 64000000;
    vector<int> vn;
    vn.resize(limit/fac+1, 0);
    for(i64 ia = 1; ia < 8001; ++ia){
        if(ia % 10 ==0)
            printf("%lld\n",ia);
        i64 ibmax = limit/2/ia;
        for(i64 ib = ia+1; ib<=ibmax; ib+=2){
            i64 la = ib*ib-ia*ia;
            i64 lb = 2*ia*ib;
            if(gcd(la, lb) != 1)
                continue;
            i64 ga = gcd(la, fac);
            ga = la/ga;
            for(i64 i = ga; i< vn.size(); i+=ga){
                ++vn[i];
            }
            i64 gb = gcd(lb, fac);
            gb=lb/gb;
            for(i64 i=gb; i < vn.size(); i+=gb){
                ++vn[i];
            }
        } 
    }
    int nmax = 0;
    for( int i = 0; i < static_cast<int>(vn.size()); ++i)
        if(vn[i]>nmax){
            nmax = vn[i];
            printf("%d %d\n", i, nmax);
        }

}
