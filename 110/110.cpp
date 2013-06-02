#include <cstdio>
#include "../lib/tools.h"
i64 min_prod;
int ndiv = 8000000;
    vector<int> primes;
    vector<int> vpow={20,5,4,3,3, 3, 2,2,2,2,1,1,1 };
void find_minimum_prod(int cpos, i64 cprod, i64 powprod)
{
    assert(cprod >= 1LL);
    if(powprod > ndiv){
        if(cprod < min_prod)
            min_prod = cprod;
        return;
    }
    if(cpos == 13)
        return;
    
    for( int i=1; i<=vpow[cpos]; ++i){
        i64 cp1 = cprod*power(primes[cpos], i);
        if(cp1 > min_prod) return;
        i64 p1 = powprod*(2*i+1);
        find_minimum_prod(cpos+1, cp1, p1);
    }
}
int main()
{
    i64 bound = 65718056921877360;
    min_prod=bound;
    primeWithin(primes, 41);
    find_minimum_prod(0, 1LL, 1LL); 
    printf("%lld\n", min_prod);
}
