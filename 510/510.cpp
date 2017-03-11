#include "../lib/tools.h"
int main()
{
    i64 total = 0;
    i64 nmax = 1000000000LL;
    nmax = 100;
    for(i64 m = 1; m <=125; ++m){
        i64 m2 = m * m;
        for(i64 n = 2*m; ;++n){
           if(gcd(m, n)> 1) continue;
           i64 n2 = n * n;
           i64 nm2 = (n-m)*(n-m);
           i64 a = nm2* n2;
           if(a > nmax) break;
           i64 b = n2*m2;
           i64 c = nm2 * m2;
           i64 sum = a+b+c;
           i64 cnt = nmax/a;
           total += cnt*(cnt+1)/2*sum;
        }
    }
    printf("%lld\n",total);
}
