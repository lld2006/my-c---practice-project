#include <cstdio>
#include <cstdlib>
#include <set>
#include "../lib/tools.h"
//first looks like only a*10 has no solution, otherwise, we can always find a solution
//second, I still prefer to find the multiplicative order for all the numbers. 
//after I find the multiplication order, I found that the (remainder mod 1e9 )mod order
//is much less than I expected!
//baby step giant step helps?
#define MYDEBUG 0
#ifndef MYDEBUG
    i64 nmod = 1000000000LL;
    IntPairVec p2, p5, p10;
    int find_multiplicative_order0(i64 nbase, i64 pmod, const vector<IntPair>&  vpairs)
    {
        i64 totient,result = 1;
        if(pmod == 1953125)
            totient = 1562500LL;
        else if(pmod==1000000000)
            totient = 400000000LL;
        else
            assert(0);

        for(unsigned int i = 0; i < vpairs.size(); ++i){
            int qi = vpairs[i].first; //base
            int powi= vpairs[i].second;// power
            int yi = totient / power(qi, powi);
            int xi = powermodule((i64)nbase, (i64)yi, pmod);
            if(xi == 1) continue; //has nothing to do with this prime factor
            i64 t = xi; 
            int cnt = 0;
            do{
                t = powermodule((i64)t , qi, pmod); //t^(q^n) == (t^q)^(q^(n-1)) !!!!!!
                ++cnt;
                assert(cnt <= powi);
            }while(t != 1);
            assert(t ==1);
            result *= power(qi, cnt);
        }
        return result;
    }
int multOrder(i64 n)
{
    if(n % 5 == 0){// 5x //p2
        i64 nx = 512; //nmod = 2^9
        int px = 1;
        while(n!=1){
            n *= n;
            n %= nx;
            px*=2;
            assert(px <= 256);
        }
        return px;
    }else if(n % 2 == 0){//2x
       return find_multiplicative_order0(n, power(5LL, 9LL), p5); 
    }else{//neither 2x nor 5x
       return find_multiplicative_order0(n, 1000000000LL, p10); 
    }
}
int main()
{
#ifdef MYDEBUG
    p2.push_back(IntPair(2, 3));

    p5.push_back(IntPair(2, 2));
    p5.push_back(IntPair(5, 3));

    p10.push_back(IntPair(5, 3));
    p10.push_back(IntPair(2, 5));
#else  
    p2.push_back(IntPair(2, 8));

    p5.push_back(IntPair(2, 2));
    p5.push_back(IntPair(5, 8));

    p10.push_back(IntPair(5, 8));
    p10.push_back(IntPair(2, 10));
#endif  
    for(i64 i = 4; i<= 1000000; ++i){
        if(i %10 == 0)continue;
        int order = multOrder(i);
        set<i64> remainder; 
        i64 prod = 1LL;
        for(int j = 1; j; ++j){
            prod = multmod(prod, i, nmod);
            i64 rem = prod % order;
            if(remainder.insert(rem).second ==false)
                break;
        }
        printf("%lld %d %zu\n", i, order, remainder.size());
    }
}
#else
    //int main()
    //{
    //    i64 prod = 1, prod0= 1;
    //    i64 nmod = 10000;
    //    for(unsigned int i = 2; i<= 1000; ++i){
    //        if(i % 2 == 0 || i % 5 == 0) {
    //            continue;
    //            prod0 = powermodule(i, 10, nmod);;
    //            prod = prod0;
    //        }
    //        int count = 0;
    //        while(prod != prod0 || count==0) {
    //            prod = prod * i;
    //            prod %= nmod;
    //            ++count;
    //        }
    //        printf("%d %d\n", i, count);
    //    }
    //    return 0;
    //}
    //debug code
    int main(int argc, char* argv[])
    {
        i64 n=8;
        i64 nmod = 1000000000LL;
        if(argc >= 2)
            n = atol(argv[1]);
        if(argc >=3)
            nmod = atol(argv[2]);
        i64 prod = 1;
        i64 count = 0;
        for(unsigned int j = 1; j < 1000000; ++j){
            //n = powermodule(n, 4, 1000000000LL);
            ++count;
            prod *= n;
            prod %= nmod;
            printf("%d %lld\n", j, prod%50000000);
        }
    }
#endif
