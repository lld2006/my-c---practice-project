#include "../lib/tools.h"
#include <cstdio>

bool isPrimeJoint(int p1, int p2, vector<int>& primes){
    if(p1%3==1 && p2%3==2) return false;
    if(p1%3==2 && p2%3==1) return false;
    int prod = 1;
    while(prod < p1){
        prod *=10;
        p2 *= 10;
    }
    int px = p2 + p1;
    return strong_pseudo_test(px);
}

void search_5primes(vector<int>& v5, const int cpos, const vector<int>& primes, const vector<int>& flags)
{
    if(cpos == 5){
        int sum = 0;
        for(unsigned int i = 0; i < 5; ++i){
            sum += primes[v5[i]];
        }
        printf("%d\n", sum);
        return;
    }
    if(cpos == 0){
        for(unsigned int i = 2; i < primes.size(); ++i){
            v5[0] = i;
            search_5primes(v5, 1, primes, flags);
        }
        return;
    }
    for(unsigned int i = v5[cpos-1]+1; i<primes.size(); ++i){
        bool isCand = true;
        for( int j = 0; j < cpos; ++j){
            int index = v5[j];
            assert(index < i);
            if(!flags[index0(primes.size(), index, i)]){
                isCand = false;
                break;
            }
        }
        if(!isCand) continue;
        v5[cpos] = i;
        search_5primes(v5, cpos+1, primes, flags);
    }
}
int main()
{
    vector<int> primes;
    vector<int> flags;
    primeWithin(primes, 10000);
    int nsize = primes.size();
    flags.resize(nsize*nsize, false);
    primes[2] = 3;
    for(unsigned int i = 2; i < primes.size(); ++i){
        for(unsigned int j = i; j < primes.size(); ++j){
            if(isPrimeJoint(primes[i], primes[j], primes) && isPrimeJoint(primes[j], primes[i], primes)) 
                flags[index0(nsize, i, j )] = true;
        }
    }
    vector<int> v5;
    v5.resize(5, 0);
    search_5primes(v5, 0, primes, flags );
}
