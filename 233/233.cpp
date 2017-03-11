#include <cstdio>
#include <cassert>
#include <algorithm>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <set>
i64 vsum = 0;
i64 vupper= 100000000000LL;
//using sieve method to get all numbers that has no 4n+1 prime factors
void generate_p3(int limit, const vector<int>& p1, vector<int>& v3)
{
    vector<int> sift;
    sift.resize(limit+1, 1);
    for(unsigned int i = 0; i < sift.size(); i+=2)
        sift[i] = 0;
    for(unsigned int i = 0; i <p1.size(); ++i)
        for(unsigned int j = 0; j < sift.size(); j+=p1[i])
            sift[j] = 0;
    v3.clear();
    v3.reserve(limit);
    for(unsigned int i = 0; i<sift.size(); ++i)
        if(sift[i] != 0)
            v3.push_back(i);

}
int main()
{
    //vupper = 10000000000LL;
    int limit = 4733727;
    int p3limit = 278453;
    vector<int> primes;
    primeWithin(primes, limit);
    vector<int> p1, p3;
    p1.reserve(primes.size()); // put primes into 4n+1 type and 4n+3 type array
    p3.reserve(primes.size());
    for(unsigned int i = 1; i < primes.size(); ++i){
        if(primes[i]%4 == 1)
            p1.push_back(primes[i]);
        else 
            p3.push_back(primes[i]);
    }
    vector<int> v3;
    generate_p3(p3limit, p1, v3);
    i64 vp3 = 1, vp2=1, vp1=1, cnt = 0;
    //3 5 7 is not the only option!!!!!!
    for(unsigned int i3 = 0; i3 < p1.size(); ++i3){
        if(p1[i3] >= 675) break;
        vp3 = (i64)p1[i3] *(i64)p1[i3]*p1[i3]; //p^3
        for(unsigned int i2 = 0; i2 < p1.size(); ++i2){
            if(i2 == i3)continue;
            vp2 = vp3* (i64)p1[i2]*p1[i2]; //q^2
            if(vp2 > vupper) break;
            for(unsigned int i1 = 0; i1 <p1.size(); ++i1){
                if(i1==i2 ||i1==i3) continue;
                vp1 = vp2* p1[i1]; //r
                if(vp1 > vupper) break;
                for(unsigned int k = 0; k < v3.size(); ++k){
                    assert(v3[0]==1);
                    assert((vp1 & 1) == 1);
                    i64 prod = (i64) v3[k] * vp1;
                    if(prod > vupper) break;
                    while(prod <= vupper){
                        vsum += prod;
                        assert(vsum > 0);
                        prod *= 2;
                        ++cnt;
                    }
                }
            }
        }
    }
    vector<i64> pwr;
    pwr.push_back(10); //21*5 option
    pwr.push_back(2);
    pwr.push_back(7); //15 *7 option
    pwr.push_back(3);
    for(unsigned int ij = 0; ij < 2; ++ij){
        for(unsigned int i1 = 0; i1<p1.size();++i1){
            i64 vp1 = power((i64)p1[i1], (i64)pwr[2*ij]);
            assert(vp1 > 0);
            if(vp1 > vupper) break;
            for(unsigned int i2 = 0; i2 <p1.size(); ++i2){
                if(i2 == i1) continue;
                i64 p2 = p1[i2];
                vp2 = vp1 * power(p2, (i64)pwr[2*ij+1]);
                assert(vp2 > 0);
                if(vp2 > vupper)
                    break;
                for(unsigned int ik = 0; ik < v3.size(); ++ik){
                    assert(v3[ik]<v3[ik+1]);
                    vp3 = vp2 * (i64)v3[ik];
                    if(vp3 > vupper) break;
                    while(vp3 <= vupper){
                        vsum += vp3;
                        vp3 *=2;
                        ++cnt;
                    }
                }
            }
        }
    }
    printf("%lld %lld\n", vsum, cnt);
}
