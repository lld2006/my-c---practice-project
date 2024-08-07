#include "../lib/tools.h"
#include "../lib/rational.h"
#include "../lib/typedef.h"
#include <cstdio>
#include <set>
using namespace std;
int main()
{
    i64 sum = 0;
    set<pair<i64, i64>> pset;
    i64 limit = 100000000;
    limit = 100000;
    int lim2 = 50;//1/100 /2
    assert( limit > 100);
    i64 cnt = limit/2-50;//trivial cases
    printf("trivial %lld\n",cnt);
    i64 root = sqrt(limit/2);
    //first create all numbers within root, created in a vector
    vector<I64Pair> vf; 
    i64 x, y, gcd1; 
    i64 tp, xp, yp, xn, yn, tcnt, tmax;
    for(i64 iden = 2; iden <= root; ++iden){
        i64 inmax = iden/lim2;
        for(i64 inum=1; inum<=inmax; ++inum){
            extended_euclid(inum, iden, x, y, gcd1);
            if(gcd1 != 1) continue;
            i64 a = inum;
            i64 b = iden;
            if(x <= 0) 
                tp = x/b-1;          
            else
                tp = x/b;
            xp = x - tp * b;
            yp = y + tp * a;
            if(yp == 0) {
                xp += b;
                yp -= a;
            }

            assert(xp > 0 && yp < 0);
            yp = -yp;
            //now process xp 
            if(100*a - b <= 0){
                i64 u = limit/(2*b);
                tcnt = (u - xp)/b+1;
                if(u < xp)
                    tcnt = 0;
                else if(tcnt * b + xp == u)
                    ++tcnt;
            }else{
                tmax = 100*a - b;//tmax is the maximum x possible
                if(lim2 % tmax == 0)
                    tmax = lim2/tmax-1;
                else
                    tmax = lim2/tmax;
                i64 u = limit/(2*b);
                if(tmax > u)
                    tmax = u;
                tcnt = (tmax -xp)/b+1;
                if(tmax< xp) tcnt = 0;
                if(tcnt * b + xp == tmax)
                    ++tcnt;
            }
            for(unsigned int i = 0; i < tcnt; ++i){
                i64 c = xp + i * b;
                i64 d = yp + i * a;
                i64 p = a*c+b*d;
                i64 q = 2*b*c;
                assert(q <= limit);
                assert( a < b);
                assert( d < c);
                pset.insert(I64Pair(p,q));
            }
            sum += tcnt;
            //--------------------//
            xn = xp - b;
            yn = -yp + a;
            if(xn == 0|| yn==0){
                xn -= b;
                yn += a;
            }
            assert(xn < 0 && yn > 0);
            //now process xn
            xn = -xn;
            if( 100 * a - b >= 0) continue;
            i64 tmin = 50 /(b- 100*a);//actually it is tmin
            if(xn < tmin){
                tp = (tmin - xn)/b;
                if(tp * b + xn == tmin)
                    xn = tmin;
                else
                    xn += (tp+1)*b;
            }
            i64 u = limit/(2*b);

            tcnt = (u - xn)/b+1;
            if( u < xn) 
                tcnt = 0;
            else if(tcnt*b+xn == limit)
                ++tcnt;
            sum += tcnt;
            for(unsigned int i = 0; i < tcnt; ++i){
                i64 c = xn + i * b;
                i64 d = yn + i * a;
                assert( a < b);
                assert( d < c);
                i64 p = a*c+b*d;
                i64 q = 2*b*c;
                assert(q <= limit);
                pset.insert(I64Pair(p, q));
            }
        }
    }
    printf("test %lld\n", sum+cnt);
    printf("%zu %lld %lld\n", pset.size(), cnt, pset.size()+cnt);
}
