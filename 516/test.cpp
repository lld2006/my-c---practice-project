#include "../lib/tools.h"
int main()
{
    int nmax = 1000;
    vector<int> vn;
    vn.resize(nmax+1, 0);
    vector<int> primes;
    primeWithin(primes, nmax);
    int sum = 1;
    for(unsigned int i = 2; i<= nmax; ++i ){
        int vt = totient(i, primes);
        int n = vt;
        int fac = 1;
        while(n%2 ==0) n/=2;
        while(n%3 ==0) n/=3;
        while(n%5 ==0) n/=5;
        if(n==1) {
            sum +=i;
            n = i;
            while(n%2 ==0) n/=2;
            while(n%3 ==0) n/=3;
            while(n%5 ==0) n/=5;
            int j = i/n;
            vn[j]+=i;
            if(j == 1)
                printf("pp %d\n", i);
        }
    }
    int s2 = 1;
    for(unsigned int i=1; i<=nmax; ++i){
        s2 += vn[i];
        if(vn[i]> 0)
            printf("%d %d %d\n", i, vn[i], s2);
    }
    printf("%d %d\n", sum, s2);
}
