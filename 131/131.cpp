#include "../lib/tools.h"
#include <cstdio>
#include <algorithm>
using namespace std;
//notice n^3+n^2*p= n^3(1+p/n) = m^3;
//(m/n)^3 can be written in reduced form than p/n = (a^3-b^3)/b^3
// n=b^3 and p = a^3 - b^3
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
