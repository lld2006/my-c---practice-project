#include <cstdio>
#include <cmath>
#include "../lib/tools.h"
vector<int> primes;
i64 limit = 1LL<<25;
//i64 limit = 10; 

i64 limit2 = limit*limit;
//return how many numbers are square number
i64 squares(int level, int max_level, i64 product, int prime_pos){
    if(level >  max_level) {
        return  0;
    }
    i64 num = 0;
    int max_prime = limit/product;
    for(unsigned int i = prime_pos; i < primes.size(); ++i){
        if(primes[i] > max_prime) break;
        i64 p1 = product * primes[i];
        num += limit2/(p1*p1);
        num -= squares(level+1, max_level, p1, i+1);
    }
    return num;
}
int main(){
    i64 total = limit2;
    primeWithin(primes, limit + 200);
    total -= squares(0, 8, 1, 0);
    printf("%lld\n", total);
}
