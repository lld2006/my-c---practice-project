#include "../lib/tools.h"
#include "../lib/rational.h"
#include "../lib/typedef.h"
#include <cstdio>
#include <set>
using namespace std;
struct stree
{
    stree(i64 n1, i64 d1, i64 pn1, i64 pd1):
        num(n1),
        den(d1),
        pnum(pn1),
        pden(pd1)
    {}
    i64 num;
    i64 den;
    i64 pnum;
    i64 pden;
};
int main()
{
    i64 sum = 0;
    set<pair<i64, i64>> pset;
    i64 limit = 100000000;
    int lim2 = 50;//1/100 /2
    assert( limit > 100);
    i64 cnt = limit/2-50;//trivial cases
    printf("%lld\n",cnt);
    i64 root = sqrt(limit/2);
    //first create all numbers within root, created in a vector
    vector<I64Pair> vf; 
    i64 x, y, gcd1; 
    i64 tp, xp, yp, xn, yn, tcnt, tmax;
    printf("before anything %lld\n", sum);
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
            if(tcnt > 0)
                ;
                //printf("positive %lld %lld %lld %lld\n",a, b, tcnt, sum);
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
            if(tcnt > 0)
                ;
                //printf("negative %lld %lld %lld %lld\n",a, b, tcnt, sum);
        }
    }
    printf("%lld\n", sum+cnt);
    printf("%d\n", pset.size()+cnt);
    //for(auto iter = pset.begin(); iter != pset.end(); ++iter)
       // printf("%lld %lld\n", iter->first, iter->second);
    
    //vector<IntPair> vf;
    // 
    //for(int i =3; i <= limit/2; ++i){
    //    farey_sequence(vf, i, true); 
    //    int line_counter = 0;
    //    for(int j = 1; j < vf.size()-1; ++j){
    //        rational r1(vf[j].first, vf[j].second);
    //        rational r2(vf[j+1].first, vf[j+1].second);
    //        rational r = r1+r2;
    //        r = r * rational(1,2);
    //        if(r.pden() > limit) continue;
    //        if(r.pnum()==1 && r.pden() %2 ==0)
    //            continue;
    //        if(2*r.pnum()>= r.pden()) 
    //            break;
    //        if(pset.insert(IntPair(r.pnum(), r.pden())).second){
    //            if(r1.pden() < r2.pden())
    //                printf("%lld %lld %lld %lld %lld %lld\n", r1.pnum(), r1.pden(), r2.pnum(), r2.pden(), r.pnum(), r.pden());
    //            else
    //                printf("%lld %lld %lld %lld %lld %lld\n", r2.pnum(), r2.pden(), r1.pnum(), r1.pden(), r.pnum(), r.pden());
    //            ++line_counter;
    //        }
    //    }
    //    if(line_counter > 0){
    //        //printf("%d %d %zu\n",i, line_counter, pset.size());
    //    }
    //} 
    //for(auto iter = pset.begin(); iter != pset.end();++iter){
    //    printf("%d %d\n", iter->first, iter->second);
    //}
}
