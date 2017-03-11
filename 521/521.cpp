//TODO too slow!!!!!
#include "../lib/tools.h"
#include <vector>
#include <map>
using namespace std;
i64 nmod = 1000000000LL;
int main()
{
    i64 nmax = 1000000000000LL;
    //nmax = 100;
    i64 root = sqrt(nmax);
    assert(root * root <= nmax && (root +1) * (root + 1) > nmax);
    vector<i64> V;
    map<i64, i64> S;
    map<i64, i64> N;
    for(int i = 1; i < root+1; ++i)
        V.push_back(nmax/i);
    int val = V.back();
    for(int i = val -1; i>=1; --i)
        V.push_back(i);
    for(i64 i = 0; i < (i64)V.size(); ++i){
        i64 t = 0;
        i64 v = V[i];
        if( v & 1)
            t = multmod(v, (v+1)/2, nmod);
        else
            t = multmod(v/2, v+1, nmod);
        S.insert(I64Pair(v, t-1));
        N.insert(I64Pair(v, v-1));
    }
    i64 sum = 0;
    i64 count = 0;
    for(i64 p =2; p<root+1; ++p){
        //i64 s0 = S[nmax];
        ++count;
        if(count% 100 == 0)
            printf("%lld\n", count);
        i64 n0 = N[nmax];
        if(N[p] > N[p-1]){
            i64 sp = S[p-1];
            i64 np = N[p-1];
            i64 p2 = p * p;
            for(int k = 0; k < (int)V.size(); ++k){
                if ( p2 > V[k])
                    break;
                i64 svk = S[V[k]];
                svk -= multmod(p ,  (S[V[k]/p] - sp), nmod);
                svk %= nmod;
                S[V[k]] = svk;
                N[V[k]] -= (N[V[k]/p] - np);
            }
        }
        //i64 ds = s0 - S[nmax];
        i64 dn = n0 - N[nmax];
        sum += multmod(dn, p, nmod);
        //printf("%lld %lld %lld\n", dn, p, sum);
        sum %= nmod;
    }
    sum += S[nmax];
    sum %= nmod;
    printf("%lld %lld %lld\n", S[nmax], N[nmax], sum);
}
