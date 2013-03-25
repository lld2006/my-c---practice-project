//inclusion-exclusion principle
#include <cstdio>
#include <cassert>
#include "../lib/typedef.h"

//x-y == 3 9 but not 2
vector<int> primes;
i64 xysum = 6008819575;
i64 inc_ex(int pos, i64 product){
    i64 sum = 0;
    if(pos == primes.size()){//exceeding the array bound)
        return 0;
    }
    if(pos == -1){
        sum += xysum/product;
        sum -= xysum/product/2;
        sum -= inc_ex(0, product);
        assert(sum >= 0);
        return sum;
    }
    for(unsigned int i = pos; i < primes.size(); ++i){
        sum += xysum/(product*primes[i]);
        sum -= xysum/(product*primes[i])/2;
        sum -= inc_ex(i+1, product*primes[i]);
    }
    assert(sum >= 0);
    return sum;
}
int main(){
    //primes.push_back(53);
    //primes.push_back(89);
    primes.push_back(5);
    primes.push_back(11);
    primes.push_back(17);
    primes.push_back(23);
    primes.push_back(29);
    primes.push_back(41);
    primes.push_back(47);
    i64 total = inc_ex(-1, 3);
    printf("%lld\n", total*2);
}
