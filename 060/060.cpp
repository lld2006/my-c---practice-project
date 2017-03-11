#include "../lib/tools.h"
#include <cstdio>
#define OLD 0

bool isPrimeJoint(int p1, int p2, vector<int>& primes){
#if OLD
    if(p1%3==1 && p2%3==2) return false;
    if(p1%3==2 && p2%3==1) return false;
#endif
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
            assert(index < (int)i);
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
#if OLD
    flags.resize(nsize*nsize, false);
    //oh, I see what I mean here, 2 and 5 are impossible, so
    //the list should be 3 7 11...
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
#else
    vector<int> prime1, prime2;
    prime1.push_back(3);
    prime2.push_back(3);
    for(unsigned int i = 3; i < primes.size(); ++i){
        if(primes[i] % 3 == 1)
            prime1.push_back(primes[i]);
        else{
            assert(primes[i] % 3 == 2);
            prime2.push_back(primes[i]);
        }
    }
    vector<int> v5;
    v5.resize(5, 0);
    nsize = prime1.size();
    flags.resize(nsize*nsize, false);
    for(unsigned int i = 0; i < prime1.size(); ++i){
        for(unsigned int j = i; j < prime1.size(); ++j){
            if(isPrimeJoint(prime1[i], prime1[j], prime1) && isPrimeJoint(prime1[j], prime1[i], prime1)) 
                flags[index0(nsize, i, j )] = true;
        }
    }
    search_5primes(v5, 0, prime1, flags );
    v5.clear();
    flags.clear();
    nsize = prime2.size();
    flags.resize(nsize*nsize, false);
    v5.resize(5, 0);
    for(unsigned int i = 0; i < prime2.size(); ++i){
        for(unsigned int j = i; j < prime2.size(); ++j){
            if(isPrimeJoint(prime2[i], prime2[j], prime2) && isPrimeJoint(prime2[j], prime2[i], prime2)) 
                flags[index0(nsize, i, j )] = true;
        }
    }
    search_5primes(v5, 0, prime2, flags );
    //use two vectors to save space and avoid some check
#endif
}
