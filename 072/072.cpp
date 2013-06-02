#include "../lib/tools.h"
#include <cstdio>
#include <vector>
#include <numeric>
using namespace std;
int relprime(int num, I64PairVec& ifac)
{
    if(ifac.empty()|| (ifac.size()==1 && ifac[0].first==num)){
        return num-1;
    }
    int size = ifac.size();
    //total number of reducible
    int totalfac = 0;
    int sign = 1;
    //i number of factors
    for(int i =1; i <= size; ++i){
        IntVec comb;
        comb.resize(i);
        for(int j = 0; j < i; ++j)
            comb[j] = j;
        bool flag = true;
        while(flag){
            int facnum = 1;
            for(int ix = 0; ix < i; ++ ix)
            {
                assert(ix < comb.size());
                assert(comb[ix]<size);
                facnum *= ifac[comb[ix]].first;
            }
            totalfac += sign*(num/facnum-1);
            flag = next_combination(comb, size, i);
        }
        sign *= -1;
    }
    return num - totalfac - 1;
}
int main()
{
    int target = 1000000;
    //target = 8;
    int root = sqrt(target);
    vector<int> primes;
    primeWithin(primes, target);
    //primeWithin(primes2, root);
    vector<int> vtot;
    vtot.resize(target+1);
    for(unsigned int i = 0; i < vtot.size(); ++i){
        vtot[i] = i;
    }
    for(unsigned int i = 0; i < primes.size(); ++i){
        unsigned int px = primes[i];
        for(unsigned int j = px; j < vtot.size(); j +=px){
            vtot[j] /= px;
            vtot[j] *= (px-1);
        }
    }
    i64 total = accumulate(vtot.begin(), vtot.end(), 0LL) - 1;
    //i64 total = 0;
    //I64PairVec ifac;
    //for(unsigned int i = 2; i<vtot.size(); ++i){
    //    total += vtot[i];
    //}
    printf("%lld\n", total);
}
