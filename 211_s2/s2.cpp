#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdio>
#include <cmath>

//  primeIndex :: next prime must be equal to or greater than current prime index
//  product    :: number up till now, each time, a prime will be multiplied on it,
//                    this number must be less than the limit.
//  npow       :: current prime raised to "npow", when prime changed, np need to be set to 0
//  sum        :: sum till now, each time prime is changed, the contribution from
//                the previous prime number will be added to sum
//  np         :: number of primes used, if only one, no need to check, since the 
//                value will be prime^2+1 can not be a perfect square
//  this recursive function is better than checking each individual since we do not need
//  to factor each number, all numbers are based on its prime factor
int limit = 64000000;
vector<int> primes;
i64 searchSigma2(const int primeIndex, const int npow, const i64 product, 
                 const i64 sum, const int np){
    i64 sret = 0; 
    for(unsigned int i = primeIndex; i<primes.size(); ++i){
        i64 newproduct = product * primes[i];
        if(newproduct >= limit) break;
        if(newproduct ==9799)
            printf("------------------------------------------------\n");
        i64 newsum = sum;
        if(i != primeIndex){
            //check whether current number is a square
            newsum *= (power(primes[primeIndex], 2*npow+2)-1LL)/
                ((i64)primes[primeIndex]*(i64)primes[primeIndex]-1LL);
            i64 tsum = newsum * ((i64)primes[i]*(i64)primes[i]+1LL);
            if(isPerfectSquare(tsum)){
                sret += newproduct;
                printf("%lld\n", newproduct);
            }
            sret += searchSigma2(i, 1, newproduct, newsum, np+1);
        }else{
            //still using the same number
            i64 tsum = sum * (power(primes[primeIndex], 2*npow+4)-1LL)/
                ((i64)primes[primeIndex]*(i64)primes[primeIndex]-1LL);
            if(true||np != 0)
                if(isPerfectSquare(tsum)){
                    sret += newproduct;
                    printf("%lld\n", newproduct);
                }
            sret += searchSigma2(i, npow+1, newproduct, sum, np);
        }
    }
    return sret;
}
int main(){
    primeWithin(primes, limit+100);
    i64 sum = 1+searchSigma2(0, 0, 1, 1, 0);
    printf("%lld\n", sum);
}
