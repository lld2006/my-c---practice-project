#include "../lib/tools.h"
#include <cstdlib>
int64_t nmod = 1000000007L;
int nmax = 600;
vector<int64_t> vfact;
int64_t fm(int64_t n, int64_t k, int64_t p)
{
    int mmax = min(nmax/2, 3*(int)p);
    int64_t t;
    int64_t num = 1L;
    int64_t den = 1L;
    num = multmod(num, vfact[3*p], nmod);//(3*p)!
    t = powermodule(2L, 3*n, nmod); //4^n*2^n
    num = multmod(t, num, nmod);
    t = powermodule(3L, k, nmod); // 3^k
    num = multmod(t, num, nmod);

    t = vfact[n]; //n!
    den = multmod(den, t, nmod);
    t = vfact[k]; //k!
    den = multmod(den, t, nmod);

    int64_t den1, num1;
    int64_t sum = 0;
    for(int64_t m = 0; m<=mmax; ++m){
        if(3*p -m -n-k < 0 || (4*p-m-n-2*k<0))
            break;
        t = powermodule(6L, m, nmod); //6^m
        num1 = multmod(num, t, nmod);
        t = vfact[12*p-2*m-3*n-4*k]; //(12p-2m-3n-4k)!
        num1 = multmod(t, num1, nmod);

        t = vfact[m]; //m!
        den1 = multmod(den, t, nmod);
        t = vfact[3*p-m-n-k];//(3p-m-n-k)!)
        den1 = multmod(den1, t, nmod);
        t = powermodule(6L, (4*p-m-n-2*k), nmod);//6^(4p-m-n-2k)
        den1 = multmod(den1, t, nmod);
        t = vfact[4*p-m-n-2*k];//(4p-m-n-2k)!
        den1 = multmod(den1, t, nmod);

        long long int x, y, g;
        if(den1 < 0) den1 += nmod;
        extended_euclid(den1, nmod, x,y,g);
        num1 = multmod(num1, (int64_t)x, nmod);
        if(m & 1)num1 = -num1;
        sum += num1;
    }
    return sum%nmod;
}
int main(int argc, char* argv[])
{
    int p= 1;
    if(argc == 2){
        p = atol(argv[1]);
    }
    nmax = p * 12;
    vfact.resize(nmax+1, 1);
    int64_t prod = 1LL;
    for(int64_t i= 2; i<(int)vfact.size(); ++i){
        prod = multmod(prod, i, nmod);
        vfact[i] = prod;
    }
    int kmax = min(2*p, nmax/4);
    int nnmax = min(nmax/3, 3*p);
    int64_t sum = 0;
    for(int n = 0; n<=nnmax; ++n){
        for(int k = 0; k <=kmax; ++k ){
            int64_t val = fm(n, k, p);
            sum = addmod(sum, val, nmod);
        }
    }
    if(sum < 0) sum += nmod;
    printf("%ld\n", sum);
}
