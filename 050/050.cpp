#include "../lib/tools.h"
#include <cstdio>
int main()
{
    int target = 1000000;
    vector<int> primes;
    primeWithin(primes, target);
    vector<int> fvec;
    fvec.resize(target+1, 0);
    for(unsigned int i = 0; i < primes.size(); ++i){
        fvec[primes[i]] = 1;
    }
    int maxsum = 0;
    int maxcnt = 0;
    for(unsigned int i = 0; i < primes.size(); ++i){
        int sum =0;
        for(unsigned int j = i; j < primes.size(); ++j){
            sum += primes[j];
            if(j - i +1 < maxcnt) continue;
            if(sum > target)
                break;
            if(fvec[sum] == 1){
                maxcnt = j-i+1;
                maxsum =sum;
            }
        }
    }
    printf("%d %d\n", maxsum, maxcnt);
}
