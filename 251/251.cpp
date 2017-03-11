#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdio>
#include <cassert>
#include <cmath>
//try linguo's method
void xgcd(const i64 p, const i64 q, i64& gcd, i64& pcoeff, i64& qcoeff)
{ int a[3]; a[0] = 1; a[1] = 0; a[2] = p; 
   int b[3]; b[0] = 0; b[1] = -1; b[2] = q; 
   while (a[2] != 0){ 
       int k = b[2]/a[2]; 
       b[0] -= k * a[0]; 
       b[1] -= k*a[1]; 
       b[2] -= k*a[2]; 
       if (b[2] == 0){ 
           b[0] = a[0]; a[0] = 0; b[1] = a[1]; a[1] = 0; b[2] = a[2]; a[2] = 0; 
       } else { 
           int k = a[2]/b[2]; a[0] -= k*b[0]; a[1] -= k*b[1]; a[2] -= k*b[2]; 
       } 
   } 
   gcd = b[2]; pcoeff = b[0]; qcoeff = b[1]; 
} 
int main()
{
// since 8pq = sr^2 + 3
// so r must be odd and s be odd, otherwise right side can not be even
    i64 limit = 110000000;
    //limit = 1000;
    i64 qmax = sqrt((limit+1)/5);
    i64 rmax = sqrt((limit+1)*8/15);
    i64 s, p, gcd, t;
    i64 sum = 0;
    for(i64 r = 1; r <= rmax; r+=2){
        i64 r2 = r * r;
        for(i64 q= 1; q<=qmax; ++q){
            //now we need to use extended Euclidean algo to solve 8q * p - s * r^2 = 1;
            //if not available, try next q and r pair. q is coprime to r
            //notice r is odd, so 8q is coprime to r^2.
            i64 q8 = q<<3;
            //here s is negated
            //extended_euclid(q8, r2, p, s, gcd);
            xgcd(q8, r2, gcd, p, s);
            assert(gcd > 0);
            if(gcd > 1) continue;
            if(p <= 0){
                t = 1 -p / r2 ;
                p += t * r2;
                s += t * q8;
            }
            assert( p > 0 && s > 0 && p <= r2);
            p *= 3;
            s *= 3;
            //after mulitplication by 3, we can not gurrantee 
            //that the result is lowest positive solution. subtract
            //the coefficient.
            t = s / q8;
            s -= t*q8;
            p -= t * r2;
            //now p and s are the lowest positive solution
            //to the equation 8pq = s r^2 + 3;
            i64 abc = p * (3 * q + r) + s * q * q;
            if(abc > limit+1) continue; 
            i64 kcoeff = (3*q + r) * r2 + 8*q*q*q;
            sum += (limit+1-abc)/kcoeff + 1;
        }
    }
    printf("%lld\n", sum);
}
