#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
using namespace std;
int main()
{
    vector<int> primes;
    int limit = 40000000;
    primes.resize(limit);
    vector<int> chain;
    chain.resize(limit);
    chain[1] = 1;
    i64 sum = 0;
    for(unsigned int i = 0; i< primes.size(); ++i){
        primes[i] = i;
    }
    for(unsigned int i =2; i < primes.size(); ++i){
        if(primes[i]==i){ //it is a prime.
            int px = primes[i];
            for(unsigned int j = px;  j < primes.size(); j+=px){
                primes[j] /= px;
                primes[j] *= (px-1);
            }
        }
        chain[i] = chain[primes[i]] + 1;
        if(chain[i] == 25 && primes[i]==i-1) 
            sum += i;
    }
    printf("%lld\n", sum);
}
