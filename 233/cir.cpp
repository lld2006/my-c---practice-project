#include <cstdio>
#include <cassert>
#include <algorithm>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <set>
i64 vsum = 0;
i64 vupper= 100000000000LL;
//a stupid mistake in original generate_p3
//void generate_p3(int limit, const vector<int>& p3, vector<int>& v3){
//    v3 = p3;
//    unsigned int nsize = p3.size();
//    for(unsigned int i = 0; i <nsize; ++i){//do some push back
//        int prime = p3[i];
//        i64 prod = (i64)prime*prime;
//        while(prod <= limit){
//           v3.push_back(prod);
//           prod *= prime; 
//           assert(prod > 0);
//        }
//    }//nth power inserted into the vector
//    sort(v3.begin(), v3.end());
//    nsize = v3.size();
//    for(unsigned int i =0; i < nsize; ++i)
//        for(unsigned int j = i + 1; j< nsize; ++j){
//            i64 prod = (i64)v3[i] * (i64)v3[j];
//            assert(prod > 0);
//            if(prod  > limit) break;
//            v3.push_back(prod);
//        }
//    v3.push_back(1);
//    sort(v3.begin(), v3.end());
//    v3.erase(unique(v3.begin(), v3.end()), v3.end());
//}
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
    p1.reserve(primes.size());
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
    //357is not the only option!!!!!!
    for(unsigned int i3 = 0; i3 < p1.size(); ++i3){
        if(p1[i3] >= 675) break;
        vp3 = (i64)p1[i3] *(i64)p1[i3]*(i64)p1[i3];
        //printf("vp3 %lld cnt %lld\n", vp3, cnt);
        //assert(p1[i3] < 675);
        for(unsigned int i2 = 0; i2 < p1.size(); ++i2){
            if(i2 == i3)continue;
            vp2 = vp3* (i64)p1[i2]*(i64)p1[i2];
            if(vp2 > vupper) break;
            for(unsigned int i1 = 0; i1 <p1.size(); ++i1){
                if(i1==i2 ||i1==i3) continue;
                //if(p1[i1]<= 20 && p1[i2]<=20 &&p1[i3]<=20)
                //    printf("%d %d %d\n",p1[i3], p1[i2], p1[i1]);
                vp1 = vp2* (i64)p1[i1];
                if(vp1 > vupper) break;
                for(unsigned int k = 0; k < v3.size(); ++k){
                    assert(v3[0]==1);
                    assert((vp1 & 1) == 1);
                    i64 prod = (i64) v3[k] * vp1;
                    assert(gcd((i64)v3[k], vp1)==1);
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
    printf("%lld %lld\n", vsum, cnt);
    vector<i64> pwr;
    pwr.push_back(10);
    pwr.push_back(2);
    pwr.push_back(7);
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
                        //printf("%d %d %lld %lld %d %lld %lld\n", p1[i1], p1[i2], pwr[2*ij],pwr[2*ij+1], v3[ik], vp3, cnt);
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
