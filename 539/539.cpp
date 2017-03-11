#include <vector>
#include <algorithm>
#include "../lib/tools.h"
using namespace std;
//number of count with k.....
i64 calc_base4(const vector<int>& v4)
{
    i64 val = 1;
    i64 p4 = 1;
    for(unsigned int i = 0; i < v4.size(); ++i){
        val += v4[i] * p4;
        p4 *= 4LL;
    }
    return val;
}
int main(int argc, char* argv[])
{
    i64 nmax = 1000000000000000000LL;
    int nx = atol(argv[1]);
    if(nx > 0) nmax = nx;
    i64 nmod = 987654321LL;
    vector<int> v4;
    i64 nt = nmax;
    while(nt){
       int r = nt % 4;
       nt /= 4;
       v4.push_back(r);
    }
    //number on 4^0 4^1.... 4^n, total is n+1 number
    //plans
    //1) add all full set sumAlpha -4 -4 ....
    //2) add partial full set, sumalpha_prime -4 -4 ....
    //                    need to loop all below pnpn-1...p1p0
    //3) add partial set alpha(n)* p_{n-1}p_{n-2} .....p_0
    //                   beta(n-1)
    vector<int> alpha, beta;
    alpha.resize(4);
    beta.resize(4);
    alpha[0] = 0; alpha[1] = 1;  alpha[2] = 2;  alpha[3] = 2;
    beta[0] = -2; beta[1]  = -2; beta[2]  = 0;  beta[3]  = 0;
    i64 sumAlpha = 5; //a1+a2+a3
    vector<i64> results;
    results.resize(100, 0);
    int n4 = v4.size();
    //part 1
    for(int i = 0; i < n4-1; ++i){
        int nalpha = i;
        i64 multiplier = powermodule(4LL, nalpha, nmod);
        i64 val = multmod(sumAlpha, multiplier, nmod);
        results[i] = addmod(val, results[i], nmod);
        for( int j = 0; j < nalpha; ++j){
            i64 tp = multmod(3LL, multiplier, nmod);
           results[j] = addmod(-tp, results[j], nmod);
        }
    }
    //part 2, 3 can be combined in a "while loop", but
    //be careful np = n4 -1 should be handled a little bit differently
    //not careful enough
    //let me handle np = n4 -1 first;

    int np = n4 - 1;
    while(np >= 0){
        if(np == n4 -1){
            assert(v4.back()>= 1);
            i64 partSum = 0;
            for( int i = 1; i<v4.back(); ++i)
                partSum += alpha[i];
            i64 multiplier = powermodule(4LL, np, nmod);
            partSum = multmod(partSum, multiplier, nmod);
            results[np] = addmod(results[np], partSum, nmod);

            for( int j = 0; j < np; ++j){
                i64 prod = multmod((i64)(v4.back() -1), multiplier, nmod);
                results[j] = addmod(results[j], -prod, nmod);
            }
        }else if(v4.back() >=1){
            i64 partSum = 0;
            i64 multiplier = powermodule(4LL, np, nmod);
            for( int i = 0; i<v4.back(); ++i)
                partSum += beta[i];
            partSum = multmod(partSum, multiplier, nmod);
            results[np] = addmod(results[np], partSum, nmod);

            for( int j = 0; j < np; ++j){
                i64 prod = multmod((i64)(v4.back()), multiplier, nmod);
                results[j] = addmod(results[j], -prod, nmod);
            }
        }
        //part 3 k
        i64 kval = v4.back();
        if(np == n4 - 1) 
            kval = alpha[kval];
        else
            kval = beta[kval];
        v4.pop_back();
        i64 number = calc_base4(v4);
        results[np] += multmod(kval, number, nmod);
        --np;
    }
    i64 nf = 0;
    i64 prod = 1;
    for(unsigned int i = 0; i<results.size(); ++i){
        i64 nt = multmod(prod, results[i], nmod);
        nf = addmod(nt, nf, nmod);
        prod = multmod(prod, 4LL, nmod);
    }
    if(nf < 0) nf += nmod;
    printf("%lld %lld\n",nmax, nf);
}
