#include "../lib/typedef.h"
#include <cstdio>
#include "../lib/tools.h"
#include <cassert>
//the basic idea of this problem is to find primes in form of (n^2+1)/2
//so this become a quadratic sieve problem. I should learn why the
//prime should be in such a form. 
int main()
{
    int limit = 50000000;
    //limit = 5000;
    vector<int> vflag;
    vflag.resize(limit, 1);
    vector<int> primes;
    primeWithin(primes, 71000000);
    vector<int> sols;
    sols.resize(2, 0);
    for(unsigned int i = 1; i<primes.size(); ++i){
        i64 sol = 0;        
        bool ret = tonelli_shank(primes[i], primes[i]-1, sol);
        if(!ret) continue;
        assert((sol * sol )% primes[i] == primes[i] - 1);
        //sieve out composite
        if(sol % 2 == 0){
            sols[0] = (primes[i]+sol-1) / 2;
            assert(sols[0] > 0 && sols[0] < primes[i] );
            sol = primes[i] - sol;
            sols[1] = (sol-1)/2;
        }else{
            sols[1] = (sol-1)/2;
            assert(sols[1] < primes[i] && sols[1] > 0);
            sol = primes[i] - sol;
            sols[0] = (primes[i]+sol-1) / 2;
        }
        //all quadratic solutions are found now sieve out
        for(unsigned np = 0; np < 2; ++np){
            int index = sols[np];
            for(unsigned int j = index; j < vflag.size(); j += primes[i]){
                i64 number = 2LL*j*j+2LL*j+1LL;
                assert(number > 0);
                //assert(((2LL*j+1)*(2LL*j+1) ) >= primes[i] );
                if(number == primes[i]) continue;
                //assert(((2LL*j+1)*(2LL*j+1) )%primes[i] == primes[i] - 1);
                //assert(!isPrime(2LL*j*j+2LL*j+1));
                assert(number % primes[i] == 0);
                vflag[j] = 0;
            }
        }
    }
    int cnt = 0;
    for(unsigned int k = 1; k< vflag.size(); ++k){
        //if(k % 1000 == 0)
        //    printf("%d %d\n", k, cnt);
        if(vflag[k]){
            //i64 number = 2LL*k*k+2LL*k+1LL;
            //printf("%lld\n", number);
            //assert(k<3291000||isPrime(2LL*k*k+2LL*k+1, primes));
            ++cnt;
        }
    }
    printf("%d\n", cnt);
}
