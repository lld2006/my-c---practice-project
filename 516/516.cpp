#include "../lib/tools.h"
#include <algorithm>
i64 nmax = 1000000000000LL;
i64 nroot = sqrt(nmax);
vector<i64> vreal;

//at least a product
//spent too much time on find_all, overflow killed me
void find_all_real_numbers(const vector<i64>& primes, i64 nc, i64 prod)
{
    for(unsigned int i = nc+1; i < primes.size(); ++i){
        i64 p1 = prod * primes[i];
        if(p1 > nmax) break;
        assert(p1 > 0 && p1<= nmax);
        vreal.push_back(p1);
        if(nmax/p1 >= primes[i+1]) 
            find_all_real_numbers(primes, i, p1);
    }
    return;
}
void generateAllCombinations(vector<i64>& vcands, vector<i64>& vpsum)
{
    i64 nmod = 1LL<<32;
    vector<i64> v3 = {2,3,5};
    vector<vector<i64>> vpower;
    vpower.resize(3);
    //performance saver
    for(unsigned int i = 0; i < v3.size(); ++i){
        i64 nx = v3[i];
        i64 prod = 1;
        for(unsigned int j = 0; j < 50; ++j){
            vpower[i].push_back(prod);
            prod *= nx;
            if(prod > 5*nmax) break;
        }
    }
    //create all candidates
    vector<int> vIndex;
    vcands.clear();
    vIndex.resize(3, 0);
    for(unsigned int i = 0; i < 50; ++i){
        i64 v2 = vpower[0][i];
        if(v2 > nmax) break;
        for(unsigned int j = 0; j < 50; ++j){
            i64 v3 = vpower[1][j];
            v3 *= v2;
            if(v3 > nmax) break;
            for(unsigned int k =0; k < 50; ++k){
                i64 v5=vpower[2][k];
                v5*=v3;
                if(v5 == 1) continue;
                if(v5 <= nmax){
                    assert(v5 > 1);
                    vcands.push_back(v5);
                }
                else
                    break;
            }
        }
    }
    //cands are used for leading factor 2^a 3^b 5^c purpose
    sort(vcands.begin(), vcands.end());
    printf("number of candidates are %lu\n", vcands.size());

    vector<i64> vprimes;
    vprimes.clear();
    vprimes.push_back(1);
    for(unsigned int i =0; i <vcands.size(); ++i){ 
        i64 value = vcands[i] + 1; 
        if(value < 6 || value > nmax)
            continue;

        if(!(value & 1)) continue;
        if(strong_pseudo_test(value)){
            assert(isPrime(value));
            vprimes.push_back(value);
        }else{
            assert(!isPrime(value));
        }
    }
    //I found I made a mistake here, prime products is also acceptable
    //printf("number of primes are %lu\n", vprimes.size());
    vreal = vprimes;
    for(unsigned int i = 1; vprimes[i]<nroot; ++i){
        find_all_real_numbers(vprimes, i, vprimes[i]);
    }
    i64 sum = 0;


    sort(vreal.begin(), vreal.end());
    vpsum.clear();
    for(unsigned int i = 0; i < vreal.size(); ++i){
        assert(vreal[i]> 0);
        sum += vreal[i];
        sum %= nmod;
        vpsum.push_back(sum);
    }
}
int main()
{
    //nmax = 1000;
    nroot = sqrt(nmax);
    i64 nmod = 1LL<<32;
    vector<i64> vcands, vpsum;
    generateAllCombinations(vcands, vpsum);
    i64 sum = vpsum.back();
    printf("%lld %lld %lld\n", 1LL, sum, sum);
    printf("real size %lu\n", vreal.size());
    //for(unsigned int i = 0; i< vreal.size(); ++i){
    //    printf("pp %lld\n", vreal[i]);
    //}
    for(unsigned int i = 0; i < vcands.size(); ++i){
        i64 value = nmax/(vcands[i]);
        assert(value >= 1);
        auto iter = lower_bound(vreal.begin(), vreal.end(), value);
        int dist = iter -vreal.begin();
        if(*iter >value) --dist;
        assert(dist >= 0);
        assert(vreal[dist] <= value && vreal[dist+1] > value);
        i64 x = vpsum[dist];
        i64 y = vcands[i] % nmod;
        //printf("x y %lld %lld\n", x, y);
        assert(x < (1LL<<32) && x>=0);
        assert(y < (1LL<<32) && y>=0);
        i64 val = vpsum[dist]*(vcands[i]%nmod);
        //val = x * y;
        val %= nmod;
        sum += val;
        sum %= nmod;
        //printf("%lld %lld %lld\n",vcands[i], vpsum[dist]*vcands[i], sum);
    }
    if(sum < 0) sum += 1LL<<32;
    printf("%lld\n", sum);
}
