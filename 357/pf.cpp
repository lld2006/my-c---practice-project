#include "../lib/tools.h"
#include <cstdio>
#include <cassert>
//first only numbers of 4n+2 can be of this type. 4n+3 must be a prime
//second, n+1 must be a prime. so only primes of 4n+3 are candidates
//
int main(){
    i64 limit = 100000000;
    vector<int> primes;
    primeWithin(primes, limit);
    vector<int> flags;
    vector<int> flag2;
    flag2.resize(limit/4, 0); //4*i+2
    for(unsigned int i = 1; i< primes.size();++i){
        int p = primes[i];
        if(p %4==3)
            flag2[(p-3)/4]=1;
    }
        
    flags.resize(limit , 0);
    for(unsigned int i = 0; i < primes.size(); ++i){
        //if(primes[i] >= limit/2) break;
        flags[primes[i]] = 1;
    }

    for(int i = 9; i <=limit/2-1; i+=2){
        if((i -1) % 100000 ==0)
            printf("%d\n", i);
        if(flags[i]==1)continue;
        i64 value1 = 2; 
        i64 value2 = i-value1;
        assert(value2 > 0);
        bool exceed = false;
        while( value1 < i){
            i64 mult = value1*value2;
            if(value1*value2 > limit){
                exceed = true;
                break;
            }
            //assert((mult-2) %4 ==0);
            //mult -= 2;
            //mult = mult >> 2;
            mult = (mult-2)/4;
            flag2[mult] = 0;
            value1 += 4;
            value2 -= 4;
        }
        if(exceed == true){
            i64 res = i%4;
            if( res == 3)
                value1 = i - 1;
            else
                value1 = i - 3;
            value2 = i - value1;
            exceed = false;
            while(value1 > 0){
                assert(value2 > 0);
                i64 mult = value1*value2;
                if(value1*value2 > limit){
                    exceed = true;
                    break;
                }
                //assert((mult-2) %4 ==0);
                mult = (mult-2)/4;
                //mult -= 2;
                //mult = mult >>2;
                flag2[mult] = 0;
                value1 -= 4;
                value2 += 4;
            }
            assert(exceed == true);
        }
    }
    i64 sum = 0;
    for(unsigned int i = 0; i < flag2.size(); ++i){
        if(flag2[i]){
            assert(flags[4*i+3]==1);
            sum += (4*i+2);
            printf("%lld %d\n", sum, 4*i+2);
        }
    }
    printf("%lld\n", sum);
}
