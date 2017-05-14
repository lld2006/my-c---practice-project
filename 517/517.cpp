#include "../lib/tools.h"
#include <cstdlib> 
//problem solved, but too slow while computing the binomial coefficeint and sqrt(n) 
//of them TODO
int64_t nmod = 1000000007;
//after playing with my brute force function testG for some time, the problem 
//is now clear, it is a sqrt(n)*combination cost. looks OK
int64_t calcG(int64_t n)
{
    double n2 = sqrt(n);
    int64_t sum = 1;
    for(int64_t k = 1; k < n2; ++k){ // this is the situation with k sqrt(n)
        int64_t start = n-(k+1)*n2+1;
        int64_t term = n-k*n2;
        int64_t fs = combination(start+k-1, k, nmod);
        int64_t ft = combination(k+term, k, nmod);
        int64_t fe = combination(term+k-1, k-1,nmod);
        sum = addmod(sum , ft-fs+fe, nmod);
    }
    return sum;
}

void testG(int n){
    double dn2 = sqrt(n);
    int n2 = dn2+1;
    vector<vector<int>> vn;
    vn.resize(n+1);
    for(unsigned int i = 0; i < vn.size(); ++i){
        vn[i].resize(n+1, 0);
    }
    vn[0][0] = 1;
    for(unsigned int i = 0; i< vn.size(); ++i){
        for(unsigned int j = 0; j < vn[i].size(); ++j){
            int ncnt = vn[i][j];
            if(n-i-(j+1)*dn2 < 0){
               continue; 
            }else{
                vn[i][j] = 0;
                vn[i+1][j] += ncnt;
                vn[i][j+1] += ncnt;
            }
        }
    }
    int sum = 0;
    for(unsigned int i = 0; i < vn.size(); ++i){
        for(unsigned int j = 0; j < vn.size(); ++j){
            sum += vn[i][j];
            if(vn[i][j] > 0)
                printf("[%d,%d],%d\n", i, j, vn[i][j]);
        }
    }
    printf("result = %d\n", sum );
}  
int main(int argc, char* argv[])
{
    int nmax  = 10010000;
    int nmax2 = 10000000;
    if(argc == 2){
        int n = atol(argv[1]);
        testG(n);
        printf("%ld\n", calcG(n));
        return 0;
    }
    vector<int> primes;
    sievePrimes(nmax, primes);
    int size = primes.size();
    int64_t sum = 0;
    printf("number of primes %zu\n", primes.size());
    for(unsigned int i = size-1; primes[i]>nmax2; --i){
        sum = addmod(sum ,calcG(primes[i]), nmod);
        printf("%u %ld\n", i, sum);
    }
    printf("%ld\n", sum);
}
