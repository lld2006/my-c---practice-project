#include "../lib/tools.h"
#include <cstdio>
//update 09042016, new method is better than old, 
//use a vector to memorize all the sum to avoid repetitive 
//sum calc, still has potential to improve. see discussion of 
//this problem at projectEuler
int main()
{
    int target = 1000000;
    int nx = 1000000/21;
    vector<int> primes;
    primeWithin(primes, target);
    vector<int> fvec;
    fvec.resize(target+1, 0);
    for(unsigned int i = 0; i < primes.size(); ++i){
        fvec[primes[i]] = 1;
    }
#if 0
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
#else
    vector<i64> vSum;
    vSum.reserve(primes.size()+1);
    int sum = 0;
    for(unsigned int i = 0; i < primes.size(); ++i){
        sum += primes[i];
        vSum.push_back(sum);
    }
    int maxcnt = 21;
    int maxsum = 0;
    for(unsigned int i = 0; i < vSum.size(); ++i){
        if(primes[i] > nx) break;
        for(unsigned int j = i+maxcnt+1; j < vSum.size(); ++j){
            int  val = vSum[j] - vSum[i];
            if(val > target) break;
            if(fvec[val] == 1){
                maxcnt = j - i ;
                maxsum = val;
                nx = target/maxcnt;
            }
        }
    }
#endif
    printf("%d %d\n", maxsum, maxcnt);
}
