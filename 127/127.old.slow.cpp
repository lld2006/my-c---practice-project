#include <cstdio>
#include "../lib/typedef.h"
#include "../lib/tools.h"

vector<int> primes;
vector<i64> rad;
i64 rad_n(int n){
    if(rad[n] != -1) 
        return rad[n];
    I64PairVec ifac1; 
    factor(n, ifac1, primes);
    i64 prod = 1;
    for(unsigned int i = 0; i< ifac1.size(); ++i)
        prod *= ifac1[i].first;
    rad[n] = prod;
    return prod;
}
bool checkrad(int ia, int j){
    int k = ia+j;
    if(gcd(ia, j)!= 1) return false;
    i64 prod = 1;
    prod = rad_n(ia)* rad_n(j)*rad_n(k);
    if(prod < k) {
        printf("%d %d %d %lld\n", ia,j,k, prod);
        return true;
    }
    return false;
}
int main(){
    int limit = 120000;
    limit = 1000;
    i64 sum = 0;
    rad.resize(limit+1, -1);
    primeWithin(primes, 350);
    int shiftj;
    for(int i = 1; i< limit; ++i){
        if(i%2 == 0) 
            shiftj = 2;
        else
            shiftj = 1;
        for(int j = i+1; j < limit - i;j+= shiftj){
            if(checkrad(i, j))
                sum += (i+j);
        }
    }
    printf("%lld\n", sum);
}
