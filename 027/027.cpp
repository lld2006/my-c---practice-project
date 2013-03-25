#include "../lib/tools.h"
#include <cstdio>
int main(int argc, const char *argv[])
{
    vector<int> primes;
    primeWithin(primes, 1000000);
    vector<int> flags;
    flags.resize(1000000+1, 0);
    for(unsigned int i = 0; i < primes.size(); ++i){
        int px = primes[i];
        flags[px] = 1;
    }
    int nmax = 0;
    int prod = 0;
    int ai, bi;
    for( int b = -999; b< 1000; ++b){
        int vb = abs(b);
        if(!flags[vb]) continue;
        for( int a = - 999; a < 1000; ++a){
            int n;
            for(n = 1; ;++n){
                int tval = n*n+a*n+b;
                int val = abs(tval);
                if(!flags[val])
                    break;
            }
            if(n > nmax){
                nmax = n;
                prod = a*b;
                ai =a ;
                bi =b ;
            }
        }
    }
    printf("a=%d b=%d %d\n",ai,bi, prod);
    return 0;
}
