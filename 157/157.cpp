#include "../lib/tools.h"
#include <algorithm>
#include <cstdio>
//special function for this problem, not for general purpose
//be careful about difference between limit and pwr.
//be careful about for loop start and end point.
int limit = 9;
vector<int> primes;

i64 get_factor_value(i64 num)
{
    int product = 1;
    for(unsigned int i = 0; i < primes.size(); ++i){
        if(primes[i] > num) break;
        if( num % primes[i] == 0){
            int pi = 0;
            do{
                num /= primes[i];
                ++pi;
            } while(num % primes[i]==0);
            product *= (pi+1);
        }
    }
    if(num > 1) 
        product *= 2;//primes greater than sqrt 1e9
    return product;
}

void getAllFactors(int pwr, vector<i64>& vfac)
{
    for(int i = 0; i<= pwr; ++i){
        i64 a1 = power(2, i);
        for( int j = 0; j<= pwr; ++j){
            i64 a2 = power(5, j);
            i64 value = a1 * a2;
            vfac.push_back(value);
        }
    }
}
i64 diop10(int pwr)
{
    vector<i64> vfac; 
    getAllFactors(pwr, vfac);
    i64 sum = 0;
    i64 xb = power(10, pwr);
    for(unsigned int i = 0; i < vfac.size();++i){
        sum += get_factor_value(xb/vfac[i]+xb);
    }
    for( int i = 1; i <= pwr; ++i)
        for( int j = 1; j <= pwr; ++j){
            i64 v1 = (i64) power(2, i);
            i64 v2 = (i64) power(5, j);
            sum += get_factor_value(xb/v1+xb/v2);
        }
    return sum;
            
}
int main()
{
    i64 sum = 0;
    primeWithin(primes, 44722);
    for(int i = 1; i <= limit; ++i)  {
        int value = diop10(i);
        sum += value;
        printf("%d %d\n", i, value);
    }
    printf("%lld\n", sum);
}
