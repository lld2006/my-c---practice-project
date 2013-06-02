#include <cstdio>
#include <algorithm>
#include "../lib/tools.h"

//this method is correct! let us check where I made mistake on 169
int main(){
    int limit = 1000000;
    vector<int> primes;
    primeWithin(primes, limit);
    int np3 = 2; //1 2 is special, considered first;
    for(int nring = 2; nring; ++nring){
        //i==1 first i==2 last
        for(int i = 1; i<=2; ++i){// each ring just consider two
            //both share this, must be true
            if(!binary_search(primes.begin(), primes.end(), 6*nring -1))
                    break;
            if(i == 1){
                if(!binary_search(primes.begin(), primes.end(), 6*nring +1))
                    continue;
                if(!binary_search(primes.begin(), primes.end(), 12*nring+5))
                    continue;
            }else{//last
                if(!binary_search(primes.begin(), primes.end(), (nring+1)*6-1))
                    continue; 
                if(!binary_search(primes.begin(), primes.end(), (nring)*12-7))
                    continue;
            }
            ++np3;
            long long int value;
            if(i==1)
                value = 3LL*nring*(nring - 1LL)+2LL;
            else
                value = 3LL*nring*(nring+1LL)+1;
            printf("%lld %d\n", value, np3);
            if(np3 == 2000){
                break;
            }
        }
        if(np3==2000) break;
    }
}
