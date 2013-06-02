//#include "../lib/primelist.h"
#include <cstdio>
#include <cmath>
#include <vector>
#include <set>
#include <cassert>
#include <unordered_set>
#include "../lib/tools.h"
#include "../lib/typedef.h"
using namespace std;

int main(){
    int limit = 50000000;
    vector<int> primes;
    unordered_set<int> strip;
    primeWithin(primes, 7071);
    int sum, sum1, sum2;
    for( int i4 = 0; true; ++i4){
        int sum = power(primes[i4], 4); 
        if(sum >= limit) break;
        for( int i3 = 0; true; ++i3){
            sum1 = sum + power(primes[i3], 3);
            if(sum1 >= limit) break;
            for( int i2 = 0; i2 < primes.size(); ++i2){
                sum2 = sum1 + primes[i2] * primes[i2];
                if(sum2 < limit){
                    strip.insert(sum2);
                    //printf("%d %d %d %d\n", i2,i3, i4, sum2);
                } else
                    break;
            }
        }
    }
    printf("num = %zu \n", strip.size());
}

    //square  <= 7071
    //3th power <= 367
    //4th power <= 83
