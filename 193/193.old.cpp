#include <cstdio>
#include <cmath>
#include "../lib/tools.h"
vector<int> primes;
i64 limit = 1LL<<25;
i64 limit2 = limit*limit;
//return how many numbers are square number
i64 squaresInlevel(int level, int max_level, i64 product, int prime_pos){
    if(level == max_level) {
        return  limit2/(product*product);
    }
    i64 num = 0;
    for(unsigned int i = prime_pos; i < primes.size(); ++i){
        int max_prime = limit/product;
        if(primes[i] > max_prime)
            break;
        i64 p1 = product * primes[i];
        if(product > limit) 
            break;
        else{
            num += squaresInlevel(level+1, max_level, p1, i+1);
        }
    }
    return num;
}
int main(){
    i64 total = limit2;
    primeWithin(primes, limit + 200);
    for(int level = 1; level <= 8; ++level){
        i64 part = squaresInlevel(0, level, 1, 0);
        total += level %2? -part: part;
    }
    printf("%lld\n", total);
}
