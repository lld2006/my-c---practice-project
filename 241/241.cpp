#include <vector>
#include <cstdio>
#include "../lib/tools.h"
using namespace std;
i64 nmax = 1000000000000000000LL;
i64 total = 0;
/* 
int main()
{
    int limit = 40000000LL;
    vector<int> vn;
    vn.resize(limit+1, 1); 
    for(unsigned int nx = 2; nx <vn.size(); ++nx){
        for(unsigned int nt = nx; nt < vn.size(); nt+=nx){
            vn[nt] += nx;
        }
    }
    for(unsigned int i = 1; i< vn.size(); ++i){
        if(vn[i] % i ==0 ) continue;
        if((2*vn[i]) %i==0)
        printf("%d %d\n", i, vn[i]);
    }
}
*/
//this problem means that sigma = (1+p+p^2+p^n) (1+q+q^2+q^n)
//to make it k + 1/2 form, we definitely need 2, then for each 
//odd factors, if it is p^2n form, then there is no contribution 
//to cancel 2, if it is odd, it has 2^k for factor of twos,
//when the number of two in denominator is 0, give up, if it is one
//and the rest cancelled, it is a solution, otherwise, continue search
/*
i64 search_quotient(int cpos, i64 prod, i64 sigma, int n20, int n2, const vector<int>& primes)
{
    if(n2 <= 0) return 0;
    assert(prod <= nmax);
    //printf("%lld %lld %d\n", prod, sigma, n20);
    if(n2==1){//check if this is the number
        if(sigma%prod == 0){
            printf("%lld\n", prod << n20);
            total += prod <<  n20;
            return (prod << n20);
        }else
            return 0LL;
    }
    if(cpos == primes.size())
        return 0;
    i64 px = primes[cpos];
    double value = (prod<<n20) * px;
    if(value > nmax) return 0LL;

    i64 tp = 1;
    i64 sum = 0;
    double dtp = prod << n20;
    for(unsigned int i = 0; 1 ;++i){
        if( dtp > nmax) break;
        i64 p1 = prod * tp;
        i64 p2 = tp * px;
        i64 sigma1 = p2 - 1;
        sigma1 /= (px-1);
        int cnt = 0;
        while((sigma1 & 1) == 0) {
            ++cnt;
            sigma1 >>= 1;
        }
        sum += search_quotient(cpos+1, p1, sigma*sigma1, n20, n2 - cnt, primes  );
        tp = p2;
        dtp *= px;
    }
    return sum;
}
*/
//24
//4680
//26208
//17428320
//4320
//8910720
//91963648
//197064960
//20427264
//8583644160
//57629644800
//206166804480
//17116004505600
//75462255348480000
//57575890944
//10200236032
//21857648640
//15338300494970880
//sigma is (p^(n+1)-1)/(p-1)
//
struct powerfactor
{
    int d_prime; //p^n-1
    int d_power;
    vector<IntPair> d_facPairs;
    powerfactor(int px, int pn)
    {
        d_prime = px;
        d_power = pn;
    }
};
bool factor_prime_power(struct powerfactor& pf, const vector<int>& primes, vector<vector<IntPair>>& vfac)
{
    double value = pow(pf.d_prime, pf.d_power)-1;
    value /= (pf.d_prime-1);
    if(value > nmax) return false;
    i64 pn = power((i64)pf.d_prime, (i64)pf.d_power)-1;
    pn /= (pf.d_prime - 1);
    vector<IntPair>& results = pf.d_facPairs;
    for(unsigned int i = 0; i < primes.size(); ++i){
        int px = primes[i];
        if(px > 500) break;
        int cnt = 0;
        while(pn % px == 0){
            pn /= px;
            ++cnt;
        }
        results.push_back(IntPair(px, cnt));
        int v1 = (pf.d_power << 8) + cnt;//use 255 as masker
        vfac[px].push_back(IntPair(pf.d_prime, v1));
    }
    return true;
}
int main()
{
    i64 sum = 0;
    int limit = 100000;
    vector<int> primes;
    primeWithin(primes, 100000);
    vector<vector<IntPair>> vfac;
    vector<vector<powerfactor>> vpf; // factor results of each sigma
    vpf.resize(500);
    vfac.resize(limit);
    sum = 0;
    //nmax = 1000000000LL;
    for(unsigned int i = 0; i < primes.size(); ++i){
        i64 px = primes[i];
        if(px > 500) break;
        for(unsigned int pn = 1; pn; ++pn){
            vpf[px].push_back(powerfactor(px, pn));
            bool flag = factor_prime_power(vpf[px].back(), primes, vfac);
            if(!flag){
                vpf[px].pop_back();
                break;
            }
        }
    }
    for(unsigned int i = 1; i < 100; ++i){
        vector<int> vp;
        vp.resize(500, 0);
        vp[2] = i;
        vector<int>& vf = vpf[2][i];
        for(unsigned int j = 0; j < vf.size(); ++j)
            sum += searchq();
    }
    printf("%lld\n", sum);
}
