//#include "../lib/primelist.h"
#include <cstdio>
#include <cmath>
#include <vector>
#include <set>
#include <cassert>
#include "../lib/tools.h"
using namespace std;

int main(){
    unsigned int limit = 50000000;
    vector<int> primes;
    set<int> strip;
    primeWithin(primes, 7071);
    int s4, s3 ;
    int lim4 = pow((double)limit, 0.25);
    for(unsigned int i4 = 0; i4 !=primes.size(); ++i4){
        if(primes[i4] > lim4) break;
        s4 = primes[i4]*primes[i4]*primes[i4]*primes[i4];
        int lim3 = pow((double) (limit - s4), (double) 1 /3.0);
        for(unsigned int i3 = 0; i3 != primes.size(); ++i3){
            if(primes[i3] > lim3) break;
            s3 = primes[i3]*primes[i3]*primes[i3];
            int lim2 = sqrt(limit - s4 - s3);
            for(unsigned int i2 = 0; i2 != primes.size(); ++i2){
                if(primes[i2] > lim2) break;
                unsigned int sum = primes[i2] * primes[i2] + s3 + s4;
                assert(sum <= limit);
                //printf("%u %u %u\n", primes[i2], primes[i3], primes[i4]);
                strip.insert(sum);
            }
        }
    }
    printf("num = %zu\n", strip.size());
}

    //square  <= 7071
    //3th power <= 367
    //4th power <= 83
