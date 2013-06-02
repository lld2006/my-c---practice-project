#include "../lib/rational.h"
#include "../lib/tools.h"
#include <tr1/unordered_set>
#include "../lib/typedef.h"
#include <algorithm>
#include <cstdio>
//the denominator should be less than 35^2 not 25.
//another thing is about the rational += and operator + 
//be careful about overflow;
typedef std::tr1::unordered_set<i64> hashset;
//return the square root
int is_square(int num, int limit){
    for(int i = 1; i <= limit; ++i){
        int i2 = i * i;
        if(num == i2)
            return i;
        else if ( num < i2)
            return 0;
    }
    return 0;
}
int main()
{
   int shift = 20;
   hashset hset;
   hashset::iterator iter;
   i64 mup = (1LL<<(2*shift))-1;
   i64 mdown = (1LL<<shift)-1;
   mup -= mdown;
   vector<rational> vr; 
   for(int di = 2; di <= 35; ++di)
       for(int ni = 1; ni < di; ++ni){
            int common = gcd(ni, di);
            if(common> 1) continue;
            vr.push_back(rational(ni, di));
       }
   sort(vr.begin(), vr.end());

    for(unsigned int i = 0; i < vr.size(); ++i){
        for(unsigned int j = i; j < vr.size(); ++j){
            rational& r1 = vr[i];
            rational& r2 = vr[j];
            const rational xr = r1 + r2;
            //x+y=z
            if(xr.pnum() >= xr.pden()) break;
            if(xr.pden() <= 35){
                rational xr2 = xr + xr;
                i64 value = (xr2.pden()<<shift)+(xr2.pnum());
                assert(((value & mup)>>shift) == xr2.pden());
                assert((value & mdown) == xr2.pnum());
                iter = hset.find(value);
                if(iter == hset.end()){
                    hset.insert(value);
                    //printf("a %lld %lld %lld %lld %lld %lld %lld %lld\n", r1.pnum(), r1.pden(), 
                    //    r2.pnum(), r2.pden(), xr.pnum(), xr.pden(), xr2.pnum(), xr2.pden());
                }
            }
        }
    }
    for(unsigned int i = 0; i < vr.size(); ++i){
        for(unsigned int j = i; j < vr.size(); ++j){
            rational& r1 = vr[i];
            rational& r2 = vr[j];
            //x^2+y^2=z^2
            rational ra(r1.pnum()*r1.pnum(), r1.pden()*r1.pden());
            rational rb(r2.pnum()*r2.pnum(), r2.pden()*r2.pden());
            rational xr2 = ra + rb;;
            rational xr = r1 + r2;
            if(xr2.pnum() >= xr2.pden()) break;
            if(xr2.pden() <= 1225){
                int ns = is_square(xr2.pnum(), 35);
                int nd = is_square(xr2.pden(), 35);
                if( ns && nd ) {
                    assert(ns <= 35 && nd<= 35 && ns < nd);
                    rational xf = xr + rational(ns, nd);
                    i64 value = (xf.pden()<<shift)+xf.pnum();
                    assert(((value & mup)>>shift) == xf.pden());
                    assert((value & mdown) == xf.pnum());
                    iter = hset.find(value);
                    if(iter == hset.end()){
                        hset.insert(value);
                        //printf("b %lld %lld %lld %lld %d %d %lld %lld\n", r1.pnum(), r1.pden(), 
                        //    r2.pnum(), r2.pden(), ns, nd, xf.pnum(), xf.pden());
                    }
                }
            }
        }
    }
    for(unsigned int i = 0; i < vr.size(); ++i){
        for(unsigned int j = i; j < vr.size(); ++j){
            rational& r1 = vr[i];
            rational& r2 = vr[j];
            //x^-2+y^-2=z^-2
            rational ra2(r1.pden()*r1.pden(), r1.pnum()*r1.pnum());
            rational rb2(r2.pden()*r2.pden(), r2.pnum()*r2.pnum());
            rational xr2 = ra2 + rb2;
            if(xr2.pnum() <= 1225 && xr2.pnum() > xr2.pden()){
                int ns = is_square(xr2.pnum(), 35);
                int nd = is_square(xr2.pden(), 35);
                if( ns && nd ) {
                    assert(ns <= 35 && nd<= 35 && ns > nd);
                    rational xr = r1 + r2;
                    rational xf = xr + rational(nd, ns);
                    i64 value = (xf.pden()<<shift)+xf.pnum();
                    assert(((value & mup)>>shift) == xf.pden());
                    assert((value & mdown) == xf.pnum());
                    iter = hset.find(value);
                    if(iter == hset.end()){
                        hset.insert(value);
                        //printf("c %lld %lld %lld %lld %d %d %lld %lld\n", r1.pnum(), r1.pden(), 
                        //    r2.pnum(), r2.pden(), nd, ns, xf.pnum(), xf.pden());
                    }
                }
            }
        }
    }
    for(unsigned int i = 0; i < vr.size(); ++i){
        for(unsigned int j = i; j < vr.size(); ++j){
            rational& r1 = vr[i];
            rational& r2 = vr[j];
            //x^-1+y^-1=z^1
            rational ra1(r1.pden(), r1.pnum());
            rational rb1(r2.pden(), r2.pnum());
            const rational xr2 = ra1 + rb1;;
            if(xr2.pnum() <= 35 && xr2.pnum() > xr2.pden()){
                rational xr = r1 + r2;
                rational xf = xr + rational(xr2.pden(), xr2.pnum());
                i64 value = (xf.pden()<<shift)+xf.pnum();
                assert(((value & mup)>>shift) == xf.pden());
                assert((value & mdown) == xf.pnum());
                iter = hset.find(value);
                if(iter == hset.end()){
                    hset.insert(value);
                    //printf("d %lld %lld %lld %lld %lld %lld %lld %lld\n", r1.pnum(), r1.pden(), 
                    //    r2.pnum(), r2.pden(), xr2.pden(), xr2.pnum(), xf.pnum(), xf.pden());
                }
            }
       }
    }

       rational vsum(0, 1);
       for(iter = hset.begin(); iter!=hset.end(); ++iter){
            i64 value = *iter;
            int inum = value & mdown; 
            int iden = (value & mup) >> shift; 
            assert(iden < 42875);
            vsum += rational(inum, iden);
            //printf("%lld %lld %lld\n", vsum.pnum(), vsum.pden(), vsum.pnum()+vsum.pden());
       }
       printf("%lld %lld %lld\n", vsum.pnum(), vsum.pden(), vsum.pnum()+vsum.pden());
}
