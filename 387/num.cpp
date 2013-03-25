#include "../lib/tools.h"
#include <cstdio>
#include <cassert>
i64 nsum(i64 n)
{
    i64 ret = 0;
    while(n){
       int res = n%10;
       ret += res;
       n /= 10;
    }
    return ret;
}
int main()
{
    int limit = 10000000;
    int nl = 13;
    vector<int> primes;
    primeWithin(primes, limit);
    vector<vector<i64> > vh;
    vh.resize(nl);
    for(unsigned int i = 1; i<=9; ++i)
        vh[0].push_back(i);
    for(unsigned int level = 1; level< nl; ++level){
        for(unsigned int ni = 0; ni< vh[level-1].size(); ++ni){
            i64 num = vh[level-1][ni];
            i64 sum = nsum(num);
            for(unsigned int i = 0; i<=9; ++i){
               i64 nx = num * 10+i; 
               if(nx % (sum+i) == 0)
                   vh[level].push_back(nx);
            }
        }
    }
    i64 result = 0;
    for(unsigned int i = 1; i < vh.size(); ++i){
        for(unsigned int j = 0; j < vh[i].size(); ++j){
            i64 num = vh[i][j];
            i64 sum = nsum(num);
            assert(num % sum == 0);
            i64 n1 = num/sum;
            if(!isPrime(n1, primes))
                continue;
            for(unsigned int k = 1; k<=9; k+=2){
                if(k == 5) continue;
                i64 nx= num*10+k;
                if(isPrime(nx, primes)){
                    //printf("%lld\n", nx);
                    result += nx;
                }
            }
        }
    }
    printf("%lld\n", result);
}
