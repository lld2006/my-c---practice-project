// no code for this problem, the idea is simple. 
// first notice that all qualified numbers must take the form
// n = p1*p2 *...*pn, so it is square free. also, p must be odd.
// then call q1=p1*p2*...*p_{n-1} and the corresponding totient function for 
// this number q2. then write the cosillience number in form of q1 and q2.
// try to find integer solutions, and check if the solution is prime.
// recursive method is used since 3 primes or more are possible. 
// performance is poor, need to learn and find better method.
// my run is about 80s.
//
// the reason that we can not have a p^2 is that on the denominator it is p-1, can not be divisible by p, so never a unit fraction.
// another observation is also correct. it can not be even. if it is even, for example 2p, then phi= p-1, even n-1 odd, can not be unit fraction. 
#include <cstdio>
#include <vector>
#include "../lib/tools.h"
using namespace std;
i64 nmax = 200000000000LL;
i64 lim2 = 0;
i64 sum = 0;
vector<bool> flags;
void search_coresilience(int clevel, int maxlevel, int cindex, i64 prod, i64 totient, const vector<int>& primes)
{
    if(clevel==maxlevel-1){
        //if(clevel==3 && prod == 21845) 
        //    printf("why\n");
        //process for the last level
        i64 kmax = prod/(prod-totient);
        for(unsigned int k = 2; k<=kmax; k+=2){
            i64 num = k * totient + 1;
            i64 den = prod - k * (prod - totient);
            if(num % den == 0){
                i64 value = num/den;
                if(value <= primes[cindex])
                    continue;
                i64 v1 = value * prod;
                if(v1 > nmax) return;
                if((value < lim2 && flags[value] )||(value >=nmax && strong_pseudo_test(value))){
                    sum += v1;
                    printf("%lld %lld\n", v1,sum);
                }
            }
        }
        return;
    }
    
    for(unsigned int i = cindex+1; i < primes.size();  ++i){
        i64 px = primes[i];
        if(prod * power(px, (i64)maxlevel-clevel) >nmax) break;
        i64 p1 = prod *px;
        i64 t1 = totient * (px-1);
        search_coresilience(clevel+1, maxlevel, i, p1, t1, primes);
    }
}
int main()
{
    lim2 = 200000000;
    vector<int> primes;
    primeWithin(primes, lim2);
    flags.resize(lim2, false);
    for(unsigned int i = 0; i < primes.size(); ++i){
        int px = primes[i];
        flags[px] = true;
    }
    i64 root = pow(nmax, 1.0/2.0);
    for(unsigned int i = 0 ; i < primes.size(); ++i){
        i64 px = primes[i];
        if(px > root)break;
        if(i% 1000 == 0) 
            printf("%d\n", i);
        i64 jmax = px * px +1; 
        if(jmax > primes.back()) jmax = primes.back();
        i64 j1 = nmax/px;
        if(jmax > j1) jmax = j1;
        for(unsigned int j = i+1; primes[j] <= jmax && j < primes.size(); ++j){
            i64 py = primes[j];
            i64 prod = px * py - 1;
            if(prod < nmax && prod %(px + py - 1) == 0){
                sum += px * py;
            }
        }
    }
    //sum = 286828184937440LL;
    for(unsigned int level = 3; level <= 10; ++level){
        printf("level %d %lld\n", level, sum);
        //             clevel, maxlevel, prime index, prod, totient, vec
        search_coresilience(0, level, 0, 1LL, 1LL, primes);
    }
    printf("%lld\n", sum);
}
