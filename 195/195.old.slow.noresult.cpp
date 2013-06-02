#include <cstdio>
#include <cmath>
#include <cassert>
#include <tr1/unordered_set>
#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <cstdlib>
#include <set>
//typedef std::tr1::unordered_set<i64> hashset;
//lesson my method is still slow, need to find better method
class pairless
{
    public:
    bool operator() (const I64Pair& p1, const I64Pair& p2)
    {
        return (p1.first < p2.first || (p1.first ==p2.first && p1.second < p2.second));
    }
};
typedef set<I64Pair, pairless> hashset;
int main()
{
    hashset hset;
    hset.clear();
    i64 rlim = 1053779;
    //rlim = 10000;
    double prod_lim = 2*rlim/(sqrt(3.0));
    i64 sum = 0;
    for(i64 u = 2; u <= 3*(prod_lim+1); ++u){
        //the maximum is in the middle so search for r 
        // will start from just one end. The other end give the same result
        for( i64 v = 1; v < u; ++v){
            i64 prod = (u-v)*v;
            if((u-v)*v > prod_lim*3) break;
            i64 guv = gcd(u, v);
            assert(guv > 0);
            if(guv != 1) continue;
            i64 a = u*u - v*v;
            i64 b = 2*u*v-v*v;
            i64 c = u*u+v*v-u*v;
            assert(a > 0 && b > 0 && c > 0);
            if( a == b) continue;
            i64 gab = gcd (a, b);
            i64 gabc = (gab ==1) ? 1 : gcd(gab, c);
            if(gabc > 1){
                a /= gabc;
                b /= gabc;
                c /= gabc;
                assert(gabc == 3);
            }
            if(a*b*sqrt(3.0)/2/(a+b+c) <= rlim){
                //assert( a*a + b*b -a*b == c*c);
                //assert( a < (1LL<<32));
                //assert( b < (1LL<<32));
                //i64 hvalue = (a<<32)+b;
                //assert(hvalue > 0);
                i64 cnt = (prod_lim*gabc)/prod;
                if(cnt == 0) continue;
                if( a > b)
                    swap(a, b);
                hashset::iterator iter;
                iter = hset.find(I64Pair(a, b));
                if(iter != hset.end())
                    continue;
                else
                    hset.insert(I64Pair(a,b));
                assert(cnt > 0);
                //printf("a=%lld b=%lld c=%lld cnt=%lld\n", a, b, c,cnt);
                sum += cnt;
            }
        }
    }
    printf("%lld\n", sum);
}
