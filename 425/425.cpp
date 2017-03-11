#include <cstdio>
#include <bitset>
#include "../lib/tools.h"
const int bitsize = 10000001;
vector<int> find_odd_neighbors(vector<int> vnum, int nmax, bitset<bitsize>& pbits, bitset<bitsize>& fbits)
{
    vector<int> vr;
    for(unsigned int i=0; i < vnum.size(); ++i){
        int number = vnum[i];
        int prod = 1;
        while(prod <= nmax){
            int digit =((number/prod) % 10);
            int n1 = number - digit * prod;
            int p1 = prod/10;
            for(unsigned int i = 0; i < 10; ++i){
                if(n1 >= nmax) break; //faster, no need to continue;
                if(n1 < p1){
                    n1 += prod;
                    continue; //avoid zeros
                }
                if(n1 != number && n1<nmax && pbits.test(n1) && !fbits.test(n1) ){
                    fbits.set(n1);
                    vr.push_back(n1);
                }
                n1 += prod;
            }
            prod *= 10;
        }//all numbers with same number of digits
        for(unsigned int i = 1; i< 10; ++i){
            int n1 = number + prod * i;
            if(n1 > nmax) break; //faster, no need to continue;
            if(n1 < nmax && pbits.test(n1))
                vr.push_back(n1);
        }
        prod /= 10;
    }
    return vr;
}
bool is_relative_2(vector<int> vnum, int nmax, vector<int>& flags, vector<int>& primes, bitset<bitsize>& pbits, bitset<bitsize>& fbits)
{
    vector<int> vn=find_odd_neighbors(vnum, nmax, pbits, fbits);
    if(vn.empty()) return false;
    for(unsigned int i = 0; i < vn.size(); ++i){
        int ni = vn[i];
        if(flags[ni]) return true;
    }
    bool found = is_relative_2(vn, nmax, flags, primes, pbits, fbits);
    return found;
}
int main()
{
    vector<int> primes;
    int limit = 10000000;
    //limit = 10000;
    primeWithin(primes, limit);
    bitset<bitsize> pbits;
    for(unsigned int i = 0; i < primes.size(); ++i){
        pbits.set(primes[i]);
    }
    i64 sum = 0;
    vector<int> flags;
    flags.resize(limit+1, 0);
    flags[3] = 1;
    flags[5] = 1;
    flags[7] = 1;
    for(unsigned int j = 4; j < primes.size(); ++j){
        if( j % 10000 == 0) printf("%d\n", primes[j]);
        int px = primes[j];
        bitset<bitsize> fbits;
        vector<int> vn={px};
        if(is_relative_2(vn, px, flags, primes, pbits, fbits)){
            flags[px] = 1;
        }
    }
    for(unsigned int i = 1; i< primes.size(); ++i){
        int px = primes[i];
        if(!flags[px]){
            sum += px;
            printf("%d\n", px);
        }
    }
    printf("%lld\n", sum);
}
