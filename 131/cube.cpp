#include "../lib/tools.h"
#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
    int limit=1000000;
    vector<int> primes;
    primeWithin(primes, limit);
    int count = 0;
    for(int i = 1; i; ++i){
        int value = i*i*3+3*i+1;
        bool found =binary_search(primes.begin(), primes.end(), value);
        if(found) ++count;
        if(value > limit ) break;
    }
    printf("%d\n", count);
}
