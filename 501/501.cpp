#include "../lib/typedef.h"
#include "../lib/tools.h"
#include "./primecount.hpp"
#include <cmath>
#include <cassert>
#include <map>
#include <vector>
using namespace std;
// pi table up to sqrt(n)
vector<int> vpi;
i64 gn = 0;
void init_pi_table(i64 n)
{
    vector<int> primes;
    i64 root = pow(n, 2.0/3);
    vpi.clear();
    vpi.resize(root+1, 0);
    primeWithin(primes, root);
    int pf = primes.size();
    int np = 1;
    for( int pi = 0; pi < pf-1; ++pi){
        for( int j = primes[pi]; j < primes[pi+1]; ++j)
            vpi[j] = np;
        ++np;
    }
    for(unsigned int j = primes.back(); j < vpi.size(); ++j)
        vpi[j] = np;
}
i64 pi(i64 n)
{
    if(n <= gn) 
        return vpi[n];
    else
        return primecount::pi(n);
    printf("pi %lld\n", n);
    i64 root = sqrt(n);
    assert(root * root <= n && (root+1)*(root+1) > n);
    vector<i64> values;
    for(i64 i = 1; i <= root; ++i){
        values.push_back(n/i);
    }
    i64 v0 = values.back();
    //printf("v0 is %lld\n", v0);
    for(i64 i = v0 -1; i > 0; --i)
        values.push_back(i);
    map<i64, i64> primen;
    for(unsigned int i = 0; i < values.size(); ++i){
        primen.insert(pair<i64, i64>(values[i], values[i] - 1));
    }
    //printf("map size is %lu\n", primen.size());
    // p *p may exceed max int32
    for(i64 p = 2; p < root + 1; ++p){
        if(primen[p] > primen[p-1]){
            i64 sp = primen[p-1];
            i64 p2 = p * p;
            for(unsigned int k = 0; k < values.size(); ++k){
                i64 v = values[k];
                if(v < p2) break;
                primen[v] -= primen[v/p] - sp;
            }
        }
    }
    return primen[n];
}
int main()
{
    i64 n = 1000000000000LL;
    gn = pow(n, 2.0/3);
    init_pi_table(n);
    i64 n2 = sqrt(n/2);
    vector<int> primes;
    primeWithin(primes, n2);
    //this is p^7 part
    i64 total = pi(pow(n, 1.0/7.0));
    printf("=== %lld\n", total);
    //now handle the p1^3 p2 part
    i64 n3 = pow(n, 1.0/3.0);
    for(unsigned int i = 0; i < primes.size(); ++i){
        if(primes[i] > n3) break;
        i64 px = n/((i64)primes[i]*primes[i]*primes[i]);
        total += pi(px);
        if(px >= primes[i]) --total;
    }
    printf("=== %lld\n", total);
    // now handle the p1 p2 p3 part
    for(unsigned int i = 0; i < primes.size(); ++i){
        if(primes[i] > n3) break;
        i64 nx = n/(primes[i]);
        i64 nx2 = sqrt(nx);
        printf("%d %lld\n", primes[i], total);
        for(unsigned int j = i +1; j< primes.size(); ++j){
            if(primes[j] >= nx2) break;
            i64 n2 = nx/primes[j];
            total += pi(n2) - (j+1);
        }
    }
    printf("=== %lld\n", total);
}

