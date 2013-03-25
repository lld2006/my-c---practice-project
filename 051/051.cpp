#include "../lib/tools.h"
#include <vector>
#include <cstdio>
using namespace std;
bool get_same_digits(int num, int& newnum, int& inc)
{
    int nx = num;
    vector<int> vpos;
    vpos.clear();
    vector<int> vdigits;
    vdigits.resize(10, 0);
    while(num){
        int res = num % 10;
        ++vdigits[res];
        num /= 10;
    }
    unsigned int i;
    for( i = 0; i < vdigits.size(); ++i)
        if(vdigits[i]==3) break;
    if(vdigits[i]!=3) 
        return false;
    num = nx;
    int np = 0;
    while(num){
        unsigned int res = num % 10;
        if(res == i)
            vpos.push_back(np);
        ++np;
        num /= 10;
    }
    inc = 0;
    for(unsigned int j = 0; j < vpos.size(); ++j){
        inc += power(10, vpos[j]);
    }
    newnum = nx - inc * i;
    return true;
}
int main()
{
    int target = 1000000;
    vector<int> primes, fvec;
    primeWithin(primes, target );
    fvec.resize(target+1, 0);
    for(unsigned int i = 0; i < primes.size(); ++i){
        fvec[primes[i]] = 1;
    }

    for(unsigned int i = 0; i < primes.size(); ++i){
        if(primes[i] < 56000) 
            continue;
        int newnum, inc;
        if(get_same_digits(primes[i], newnum, inc)){
            int cnt = 0;
            int first = -1;
            for(unsigned int j = 1; j < 10; ++j){
                int tv = newnum +j*inc; 
                if(fvec[tv]){
                    ++cnt;
                    if(first < 0)
                        first = j;
                }
            }
            if(cnt == 8){
                printf("%d\n", newnum+first*inc);
                return 0;
            }
        }
    }
}
