#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdlib>
#include <cassert>
#include <algorithm>
using namespace std;
i64 limit = 1000000000000000LL;
i64 l10 = 1;
vector<int> primes;
vector<int> pindex;
i64 sum = 0;
i64 totient(int n)
{
    assert(n < 1000);
    if(n == 1)
        return 1;
    int prod = 1;
    int total = 1;
    for(unsigned int i = 0; i < primes.size(); ++i){
        prod = 1;
        bool first = true;
        while((n % primes[i] )== 0){
            n/= primes[i];
            if(first){
                prod *= (primes[i]-1);
                first = false;
            }else
                prod *= primes[i];
        }
        total *= prod;
        if(n == 1)
            break;
    }
    return total;
}
void calc_div(unsigned int level, int prod, I64PairVec vpairs, vector<int>& vd)
{
    if(level == vpairs.size()){
        vd.push_back(prod);
        return;
    }
    int px = vpairs[level].first;
    int pw = vpairs[level].second;
    int tp = 1;
    int prod1 = prod;
    for( int j = 0; j <= pw; ++j){
        calc_div(level+1, prod1, vpairs, vd);
        tp *= px;
        prod1 = prod * tp;
    }
    return;
}
void find_all_divisors(int n, vector<int>& vd)
{
    if(n == 1){
        vd.push_back(1);
        return;
    }
        
    I64PairVec vpairs;
    factor(n, vpairs, primes);
    calc_div(0, 1, vpairs, vd);
    sort(vd.begin(), vd.end());
}
i64 f(int m, int n, int d)
{
    assert( d <= n);
    int t = m *n/d;
    long double prod = 1;
    for( int i = 2; i <= t; ++i)
        prod *= i;
    
    long double p2 = 1;
    for( int i = 2; i <= n/d; ++i)
        p2 *= i;

    for( int i = 0; i< m; ++i)
        prod /= p2;
    if(prod > limit*m*n)
        return l10;
    else
        return round(prod);

}
bool calc_f_m_n(int m, int n, i64& sum)
{
    sum = 0;
    vector<int> vd;
    find_all_divisors(n, vd);
    for(unsigned int j = 0; j < vd.size(); ++j){
        i64 tot = totient(vd[j]);
        i64 result = f(m, n, vd[j]);
        if(result > limit*m*n/tot)
            return false;
        sum += result * tot;
        if(sum > limit*m*n)
            return false;
        if(result > limit*m*n)
            return false;
    }
    sum /=(m*n);
    return true;
}
int main()
{
    l10 = 1000*limit;
    primeWithin(primes, 1000);
    //calculated prime indices
    pindex.resize(1000, 0);
    int cnt = 0;
    for(unsigned int j = 0; j < primes.size(); ++j){
        int px = primes[j];
        pindex[px] = cnt++;
    } 

    //int t = totient(168);
    //printf("%d\n", t);
    //vector<int> vt;
    //find_all_divisors(168, vt);
    //for(unsigned int j = 0; j < vt.size(); ++j){
    //    printf("%d\n", vt[j]);
    //}
    //exit(1);
    i64 total = 0;
    bool mflag, nflag;
    for(i64 m = 2; ;++m){ //color
        mflag = false;
        for(i64 n = 1; ; ++n){// dup
             i64 sum = 0;
             nflag = calc_f_m_n(m, n, sum);
             if(nflag){
                 printf("%lld %lld %lld\n", m, n, sum);
                 mflag = true;
                 total += sum;
             }else
                 break;
        }
        if(!mflag)
            break;
    }
    printf("%lld\n", total);
}
