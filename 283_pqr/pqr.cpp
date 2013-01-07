#include <cstdio>
#include <cmath>
#include <cassert>
#include "../lib/typedef.h"
//first this is a brute force method, I hate it.
//but still there is a subtle bug somewhere, let me debug.
int main()
{
    int limit0 = 100;
    i64 limit = 12*limit0*limit0;
    i64 root = sqrt(limit);
    i64 r, peri=0;
    for( i64 p = 1; p <= root; ++p){
            //printf("%lld %lld\n",p, peri);
        i64 qmax = limit/p;
        for(i64 q = p; q<=qmax; ++q){
            i64 pq= p*q;
            i64 kmax = pq;
            double root = sqrt(pq);
            kmax = round(root/2);
            if(kmax *kmax *4 - pq > 0) --kmax;
            if(kmax > limit0) kmax = limit0;
            if(kmax  >=  pq) kmax = pq-1;
            bool debug = false;
            for(i64 k = kmax; k> 0; --k){
                i64 k2 = k*k*4;
                i64 a = k2*(p+q);
                i64 b = pq-k2;
                if(b <= 0) {
                    debug = true; 
                    printf("%lld %lld %lld\n", b, p, q);
                    continue;};
                assert( a > 0 && b > 0);
                if(a % b == 0){
                    r = a/b;
                    if(r >= q ) peri +=(p+q+r);
                    if(debug) 
                        printf("debug %lld %lld %lld\n", p,q,r);
                }
            }
        }
    }
    printf("%lld\n", peri*2);
}
