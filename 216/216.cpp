#include "../lib/tools.h"
#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
//a critical performance gain comes from jacobi
//a second speedup comes from p only p of 8n+1 and 8n+7 are 
//only possible primes that can be a divisor of 2n^2 - 1
double gettime() 
{
  struct timeval t;
  gettimeofday(&t,NULL);
  return t.tv_sec+t.tv_usec/1000000.;
}
int main()
{
    double starttid = gettime();
    int limit = 50000000;
    int limit2 = limit*sqrt(2.0);
    vector<int> primes;
    primeWithin(primes, limit2);
    printf("created regular sieve: %.3f\n",gettime()-starttid);
    vector<char> flags;
    flags.resize(limit+1, true);
    flags[0]=flags[1]=false;
    for(unsigned int i = 1; i<primes.size(); ++i){
        int px = primes[i];
        if(((px & 7) != 1) && ((px & 7) != 7)) continue;
        int residue = (1+px)/2;
        i64 sol = 1;
        bool OK = tonelli_shank(px, residue, sol);
        if(OK){
            //assert((sol * sol*2-1)% px ==0);
            for(unsigned int j = sol; j < flags.size(); j+=px){
                flags[j] = 0;
            }
            for(unsigned int j = px - sol; j < flags.size(); j+=px){
                flags[j] = 0;
            }
            if(2LL*sol*sol-1==px)
                flags[sol]= 1;
            
            if(2LL*(px-sol)*(px-sol)-1==px)
                flags[px-sol] = 1;
        }
    }
    printf("quadratic residue: %.3f\n",gettime()-starttid);
    int cnt = 0;
    for(unsigned int i = 2; i < flags.size(); ++i){
        cnt += flags[i];
    }
    printf("%d\n", cnt);
}
