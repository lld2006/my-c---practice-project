#include <cstdio>
#include <cassert>
#include <cstdlib>
#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <numeric>
using namespace std;

int main(){
    
    //unsigned int limit  = 50000000;
    unsigned int limit = 100;
    //vector<int> primes;
    //primeWithin(primes, 1.42*limit);
    vector<u64> numbers;
    set<u64> nset;
    flags.resize(limit-1, 1);
    numbers.resize(limit-1, 0);

    for(u64 i = 2; i <=limit; ++i){
        numbers[i-2] = 2LL*i*i-1;
    }
    //int pos = 0;
    for(unsigned int i = 0; i<numbers.size(); ++i){
        if(flags[i] == 0)continue;
        u64 prime = numbers[i];
        //if( prime > 1.45 * limit) break;
        for(unsigned int j = i+1; j < numbers.size();++j){
            if(numbers[j]%prime ==0) 
                flags[j] = 0;
        }
    }
    int count = accumulate(flags.begin(), flags.end(), 0);
    for(unsigned int i = 0; i < numbers.size(); ++i)
        if(flags[i] == 1  && isPrime(2*(i+2)*(i+2)-1)==0) printf("catch %d %lld\n", i, numbers[i]);
    printf("%d\n", count);
}
