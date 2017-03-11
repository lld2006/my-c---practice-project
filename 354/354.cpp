#include <cstdio>
#include <set>
#include <vector>
#include <cstdlib>
#include <cassert>
#include "../lib/tools.h"
using namespace std;
//the numbers should take a form of 
//4^n 3^m *(3k+1)^p (3k+2)*2q
int nsolutions(int num, vector<int>& primes)
{
    I64PairVec ifac;
    factor(num, ifac, primes);
    if(ifac[0].second % 2 == 1) return 0;
    int start = 1;
    if(ifac[1].first == 3) start = 2;
    i64 prod = 6;
    for(unsigned int i = start; i<ifac.size(); ++i){
        int px = ifac[i].first;
        int npow=ifac[i].second;
        if(px % 3 == 1) 
            prod *= (npow+1);
        else
            if(npow % 2) 
                return 0;
    }
    return prod;
}
void searchp(i64 cprod, int cpos, i64 qmax, vector<int>& p32, set<i64>& flags) 
{
    assert(cpos < 75000);
    i64 c1 = 0;
    for(unsigned int npos = cpos; npos < p32.size(); ++npos){
        i64 p2 = (i64)p32[npos]*p32[npos];
        long double d1 = (long double)cprod * p2;
        assert(d1 > 0);
        if(d1 > qmax )
            break;
        c1 = cprod * p2;
        while(c1 <= qmax){
            assert(c1 <= qmax);
            flags.insert(c1);
            searchp(c1, npos+1, qmax, p32, flags);
            d1 *= p2;
            assert(d1 > 0);
            if(d1 > qmax) break;
            c1 *= p2;
        }
    }
}
//any order of 4, 3 even 3p+2, 
i64 find_all_cands(i64 qmax, vector<int>& p32, i64 nval = 1)
{
    assert(qmax > 0);
    if(qmax==1) return 1;
    set<i64> flags; 
   
    i64 prod = 1, p1;
    for( int i = 1; i; ++i ) {
        if(prod > qmax) break;
        p1 = 1;
        for(int j = 1; j ; ++j){
            i64 val = p1 * prod;
            if(val > qmax) break;
            assert(val > 0);
            flags.insert(val);
            searchp(val, 0, qmax, p32, flags);
            p1 *= 3LL;//3^j
        }
        prod *= 4LL;//4^i 
    }
    int number = flags.size();
    //for(auto iter = flags.begin(); iter != flags.end(); ++iter){
    //    printf("set %lld, %lld\n", *iter*nval, nval);
    //}
    return number;
}
int debug_3n2(int limit, vector<int>& p32){
    int cnt = 0;
    int val = 0;
    for( int i = 1; i<= limit; ++i){
        val = i;
        while(val % 4 ==0) val /= 4;
        while(val % 3 ==0) val /= 3;
        for(unsigned int j = 0; j < p32.size(); ++j){
            int p2 = (i64) p32[j] * p32[j];
            if(val < p2) break;
            while(val % p2 == 0) val /= p2;
        }
        if(val == 1) ++cnt;
        //if(val == 1)
        //printf("%d\n", i);
    }
    return cnt;
}
int debug_all(int num, vector<int>& p32){
    i64 sum = 0;
    //for(unsigned int i = 1; i; ++i){
    //    p2 = 1;
    //    for(unsigned int j = 1; j; ++j){
    //        i64 val = p1 * p2;
    //        if(val <= num){
    //        }else{
    //            break;
    //        }
    //        p2 *= 3;
    //    } 
    //    p1 *= 4;
    //    if(p1 > num) break;
    //}
    sum += find_all_cands(num, p32);
    return sum;
}
int main()
{
    vector<int> vn;
    vector<int> primes, p31, p32;
    int plimit = 35000000;
    primeWithin(primes, plimit);
    for(unsigned int i = 2; i < primes.size(); ++i){
        if(primes[i] % 3 == 1)
            p31.push_back(primes[i]);
        else
            p32.push_back(primes[i]);
    }
    //find_all_cands(100000, p32);
    //exit(1);

    //for(int i = 1; i<= 150; ++i){
    //    int val = i * 1000;
    //    assert(debug_3n2(val, p32) == debug_all(val, p32));
    //}
    //vn.resize(400000000+1, 0);
    //for(int x = 0; x<=10000;++x){
    //    for(int y=0; y<=10000;++y){
    //        int sum = x*x+3*y*y;
    //        if(x == 0|| y ==0){
    //            vn[sum] += 2;
    //        }else{
    //            vn[sum]+= 4;
    //        }
    //    }
    //}
    //for(unsigned int i = 4; i <= 2500; i+=4){
    //    assert(vn[i]==nsolutions(i, primes));
    //    if(vn[i])
    //        printf("%d %d\n", i, vn[i]);
    //}
    //exit(1);
    //15 5 solution
    long double limit = 25e22/(long double)3;
    i64 sum = 0;
    for(unsigned int i = 0; i < p31.size(); ++i){//15
        long double value = pow((long double)p31[i], 14);
        if(value > limit) break;
        for(unsigned int j = 0; j < p31.size(); ++j){//5
            if(i==j) continue;
            long double v2 = value * pow((long double)p31[j], 4LL);
            if(v2 > limit) break;
            i64 q = limit/v2;
            sum += find_all_cands(q, p32);
        }
    }

    //5 5 3 solutions
    for(unsigned int i = 0; i < p31.size(); ++i){//15
        long double value = pow(p31[i], 2);
        if(value > limit) break;
        for(unsigned int j = 0; j < p31.size(); ++j){//5
            if(i==j) continue;
            long double v2 = value * pow((long double)p31[j], 4LL);
            if(v2 > limit) break;
            for(unsigned int k = j+1; k < p31.size(); ++k){
                if(i==k) continue;
                assert(i != j && j!=k && i!=k);
                long double v3 = v2 * pow((long double)p31[k], 4LL);
                if(v3 > limit) break;
                i64 q = limit/v3;
                sum += find_all_cands(q, p32);
            }
        }
    }
    //3 25 solutions is still possible
    printf("%lld\n", sum);
}
