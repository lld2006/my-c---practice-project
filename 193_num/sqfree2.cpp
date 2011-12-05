#include <numeric>
#include <vector>
#include <cstdio>
#include "../lib/tools.h"
using namespace std;
int main(){
    vector<int> primes;
    primes.resize(11,0);
    primes[0]=2; 
    primes[1]=3; 
    primes[2]=5; 
    primes[3]=7; 
    primes[4]=11; 
    primes[5]=13; 
    primes[6]=17; 
    primes[7]=19; 
    primes[8]=23; 
    primes[9]=29; 
    primes[10]=31; 
    vector<int> flags;
    flags.resize(1024, 1);
    for(int num = 4; num < 1024; ++num){
        for(unsigned int i = 0; i< primes.size(); ++i){
            if(num % (primes[i]*primes[i])==0)
                flags[num-1] = 0;
        }
    }
    int sum = accumulate(flags.begin(), flags.end(), 0);
    printf("%d\n", sum);
}
