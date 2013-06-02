#include <cstdio>
#include <vector>
#include "../lib/tools.h"
using namespace std;
int get25(int num){
    int prod = 1;
    while(num%5 ==0){
        num/=5;
        prod *= 5;
    }
    while(num%2 ==0){
        num/=2;
        prod *= 2;
    }
    return prod;
}
int main()
{
    vector<int> primes;
    primeWithin(primes, 100000);
    i64 sum = 5;
    for(unsigned int i = 1; i < primes.size(); ++i){
        int px = primes[i];
        int n25 = get25(px-1);
        if(powermodule(10LL, n25, px) != 1){
            sum += px;
        }
    }
    printf("%lld\n", sum);
}
