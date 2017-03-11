// no code for this problem, the idea is simple. 
// first notice that all qualified numbers must take the form
// n = p1*p2 *...*pn, so it is square free. also, p must be odd.
// then call q1=p1*p2*...*p_{n-1} and the corresponding totient function for 
// this number q2. then write the cosillience number in form of q1 and q2.
// try to find integer solutions, and check if the solution is prime.
// recursive method is used since 3 primes or more are possible. 
// performance is poor, need to learn and find better method.
// my run is about 80s.
//
// the reason that we can not have a p^2 is that on the denominator it is p-1, can not be divisible by p, so never a unit fraction.
// another observation is also correct. it can not be even. if it is even, for example 2p, then phi= p-1, even n-1 odd, can not be unit fraction. 
#include <cstdio>
#include <vector>
#include "../lib/tools.h"
using namespace std;
i64 nmax = 200000000000LL;
i64 lim2 = 0;
i64 sum = 0;
vector<bool> flags;
void search_coresilience(int clevel, int maxlevel, int cindex, i64 prod, i64 totient, const vector<int>& primes)
{
    if(clevel==maxlevel-1){
        i64 kmax = prod/(prod-totient);
        for(unsigned int k = 2; k<=kmax; k+=2){
            i64 num = k * totient + 1;
            i64 den = prod - k * (prod - totient);
            if(num % den == 0){
                i64 value = num/den;
                if(value <= primes[cindex])
                    continue;
                i64 v1 = value * prod;
                if(v1 > nmax) return;
                if((value < lim2 && flags[value] )||(value >=nmax && strong_pseudo_test(value))){
                    sum += v1;
                    printf("%lld\n", v1);
                }
            }
        }
        return;
    }
    
    for(unsigned int i = cindex+1; i < primes.size();  ++i){
        i64 px = primes[i];
        if((prod * power(px, (i64)maxlevel-clevel)) >nmax) break;
        i64 p1 = prod *px;
        i64 t1 = totient * (px-1);
        search_coresilience(clevel+1, maxlevel, i, p1, t1, primes);
    }
}
bool isPrime245(i64 num, const vector<bool>& flags)
{
    if(num < static_cast<int>(flags.size()))
        return flags[num];
    return strong_pseudo_test(num);
}
//find factors less than sqrt(i)
i64 recursive_check_factor(int nth, int cpos, i64 prod, vector<I64Pair>& vfac, const vector<bool>& flags )
{
    i64 n = (i64)nth*(nth-1)+1;
    if(prod * prod > n)
        return 0;
    if(cpos == static_cast<int>(vfac.size())){
        i64 n1 = prod;
        i64 n2 = n/prod;
        i64 n12 = (n1+nth) *(n2+nth);
        if(n12>nmax) return 0;
        if(isPrime245(n1+nth, flags) && isPrime245(n2+nth, flags)){
            return n12; 
        } else
            return 0;
    }

    i64 sum = 0;
    i64 px = vfac[cpos].first;
    i64 npmax = vfac[cpos].second;
    i64 tp = 1;
    for(unsigned int i = 0; i <= npmax; ++i){
        sum += recursive_check_factor(nth, cpos+1, prod*tp, vfac, flags);
        tp *= px;
    }
    return sum;
}
//(p-n)(q-n) = n^2 -n+1
//since (p-n)(q-n) = pq -pn-qn + n^2
//p>n q>n, then pq = pn + qn - n^2 +n^2-n + 1> 2 n^2 = 2e12
i64 semi_prime_count(i64 limit, vector<bool>& flags)
{
    vector<i64> vn;
    i64 sum = 0;
    int nmax = sqrt(limit/2)+1;
    vn.resize(nmax+1);
    vector<vector<I64Pair>> vfac;
    vfac.resize(nmax+1);
    for(i64 i = 0; i < static_cast<int>(vn.size()); ++i){
        vn[i] = i*(i-1)+1;
    }
    //special treat ment for prime 3
    for(unsigned int i = 2; i < vn.size(); i+=3){
        int np = 0;
        while(vn[i] % 3 == 0){
            vn[i]/=3;
            ++np;
        }
        vfac[i].push_back(I64Pair(3, np));
    }
    for(unsigned int i = 3; i<vn.size(); ++i){
        assert(vn[i] > 0);
        if(vn[i]==1) continue;
        i64 px = vn[i];
        for(unsigned int j = i; j < vn.size(); j += px){
            int np = 0;
            while(vn[j] %px == 0){
                ++np;
                vn[j]/=px;
            }
            vfac[j].push_back(I64Pair(px, np));
        }
        for(unsigned int j = px+1 - i; j < vn.size(); j+=px){
            int np = 0;
            while(vn[j] %px == 0){
                ++np;
                vn[j] /= px;
            }
            vfac[j].push_back(I64Pair(px, np));
        }
    }
    for(unsigned int i = 2; i < vfac.size(); ++i ){
        sum += recursive_check_factor(i, 0, 1LL, vfac[i], flags);
    }
    return sum;
}
int main()
{
    struct timer mytimer;
    lim2 = 20000000;
    vector<int> primes;
    primeWithin(primes, lim2);
    flags.resize(lim2, false);
    for(unsigned int i = 0; i < primes.size(); ++i){
        int px = primes[i];
        flags[px] = true;
    }
    printf("time %.3f\n", mytimer.getTime());
    sum = semi_prime_count(nmax, flags);
    printf("time %.3f\n", mytimer.getTime());
    printf("test sum %lld\n", sum);
    //sum = 286828184937440LL;
    for(unsigned int level = 3; level <= 10; ++level){
        //printf("level %d %lld\n", level, sum);
        //             clevel, maxlevel, prime index, prod, totient, vec
        search_coresilience(0, level, 0, 1LL, 1LL, primes);
    }
    printf("%lld\n", sum);
}
