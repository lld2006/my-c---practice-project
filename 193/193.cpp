#include <cstdio>
#include <cmath>
#include <vector>
#include <cassert>
#include <ctime>
#include "../lib/typedef.h"
#include "../lib/tools.h"
using namespace std;
//a key point to accelerate is that the primes needed is to the sqrt of mobius range
void create_primes_and_mobius2(int limit, vector<int>& primes, vector<int>& mobius)
{
    double time=clock();
    primeWithin(primes, limit);
    printf("Time = %.3f seconds\n\n", (clock()-time)/CLOCKS_PER_SEC);
    mobius.clear(); mobius.resize(limit+1, 1);
    for(unsigned int i  = 0; i < primes.size(); ++i){
        i64 px = primes[i];
        for(i64 j = px; j <=limit; j+=px){
            mobius[j] = -mobius[j];
        }
    }

    for(unsigned int i  = 0; i < primes.size(); ++i){
        i64 px = primes[i];
        i64 p2 = px * px;
        if(p2 > limit) break;
        for(i64 j = p2; j <=limit; j+=p2){
            mobius[j] = 0;
        }
    }
    printf("Time = %.3f seconds\n\n", (clock()-time)/CLOCKS_PER_SEC);
}
void create_primes_and_mobius(int limit, vector<int>& primes, vector<int>& mobius)
{
    int root = sqrt(limit);
    primeWithin(primes, root);
    mobius.clear(); mobius.resize(limit+1, 1);
    vector<bool> flags; flags.resize(limit+1, true);
    for(unsigned int i  = 0; i < primes.size(); ++i){
        i64 px = primes[i];
        mobius[px] = -mobius[px];
        for(i64 j = px*2; j <=limit; j+=px){
            mobius[j] = -mobius[j];
            flags[j] = 0;
        }
    }
    for(unsigned int i = primes.back()+2; i< flags.size(); i+=2){
        if(flags[i]) mobius[i] = - mobius[i];
    }

    for(unsigned int i  = 0; i < primes.size(); ++i){
        i64 px = primes[i];
        i64 p2 = px * px;
        if(p2 > limit) break;
        for(i64 j = p2; j <=limit; j+=p2){
            mobius[j] = 0;
        }
    }
    
}
int main()
{
    i64 limit = 1LL<<50;
    vector<int> primes, p2;
    vector<int> mobius, m2;
    i64 root = 1LL<<25;
    //create_primes_and_mobius(root, primes, mobius);
    create_primes_and_mobius2(root, p2, mobius);
    i64 sum = limit;
    for(i64 i = 2; i<=root; ++i){
        //assert(mobius[i] == m2[i]);
        if(mobius[i]){
            sum += mobius[i] * (limit/(i*i));
        }
    }
    printf("%lld\n", sum);
}
