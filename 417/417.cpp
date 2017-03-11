#include "../lib/tools.h"
#include <cstdio>
#include <cstdlib>
int simplify(int num)
{
    while((num & 1 ) == 0) num >>= 1;
    while(num % 5 == 0) num /= 5;
    return num;
}

int main()
{
    int target = 100000000;
    vector<int> primes;
    vector<int> vfac;
    factor_table_min(target, vfac);
    for(unsigned int i= 2; i<vfac.size(); ++i){
        if(vfac[i] == static_cast<int>(i)) primes.push_back(i) ;
    }
    vector<int> vn, vorder;
    vn.resize(target+1, 1);
    vorder.resize(target+1, 0);
    //value could be 1, but these numbers has no contribution
    //to the result
    for(unsigned int i = 4; i <= vn.size(); ++i){
        if(i %2 == 0 || i%5 ==0 ) {
            vn[i] = 0;
            int value = simplify(i);
            ++vn[value];
        }
    }
    for(unsigned int i = 1; i < primes.size(); ++i){
        i64 prod = primes[i];
        if(prod == 5) continue;
        for(int j = 1; j ; ++j){
            int order = find_multiplicative_order(10LL, primes[i], j, vfac);
            vorder[prod] = order;
            prod *= primes[i];
            if(prod > target) break;
        }
    }
    i64 sum = 0;
    IntPairVec vpairs;
    for(unsigned int i = 3; i < vn.size(); i+=2){
        if(vn[i] == 0) continue;
        factor_using_table(i, vpairs, vfac);
        int lcm = 1;
        for(unsigned int i = 0; i < vpairs.size(); ++i ){
            i64 value = power(vpairs[i].first, vpairs[i].second);
            int t  = vorder[value];
            int g = gcd(lcm , t);
            lcm = t * lcm/g;
        }
        sum += (i64)lcm * vn[i];
    }
    printf("%lld\n", sum);
}
