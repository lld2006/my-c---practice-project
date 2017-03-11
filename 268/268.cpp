#include <vector>
#include "../lib/tools.h"
#include <cstdio>
#include <numeric>
using namespace std;
vector<int> vfactor;
i64 limit = 10000000000000000LL;
i64 verify(int nupper, vector<int>& ndiv)
{
    vector<int> flags;
    flags.resize(nupper+1, 0);
    for(unsigned int i = 0; i<ndiv.size(); ++i){
        int xd =ndiv[i];
        for(int xi = xd; xi <= nupper; xi+=xd)
            ++flags[xi];
    }
    int cnt = 0;
    for(unsigned int i = 0; i< flags.size(); ++i){
        if(flags[i] >= 4)
           ++cnt; 
    }
    return cnt;
}
i64 inc_ex_search(int pos, i64 nupper, i64 product, int cnt, vector<int>& primes)
{
    if(product >= nupper) return 0;
    i64 sum = cnt >= 4?nupper/product * vfactor[cnt]:0;
    //if(sum > 0) printf("%lld %lld\n",product, sum);
    //printf("%lld\n", )
    for(unsigned int i = pos; i< primes.size(); ++i){
        i64 prod1 = product * primes[i];
        i64 tsum = inc_ex_search(i+1, nupper, prod1,cnt+1, primes);
        sum -= tsum;
    }
    return sum;
}
int main()
{
    //limit = 100000;
    vector<int> primes;
    primeWithin(primes, 100);
    vfactor.resize(16, 0);
    vfactor[4] = 1;
    for(unsigned int i = 5; i <= 13;++i){
        int value = -1;
        int sign = 1;
        for(unsigned int j = 4; j < i; ++j){
            value += sign * combination(i, j) * vfactor[j];
            sign = -sign;
        }
        if(value < 0) value = -value;
        vfactor[i] = value;
        printf("%d\n", value);
    }
    i64 sum = inc_ex_search(0, limit, 1, 0, primes);
    //printf("%lld, %lld\n", sum, verify(100000, primes));
    printf("%lld\n", sum); 
}
