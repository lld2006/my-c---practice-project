#include <cstdio>
#include <vector>
#include <cstdlib>
#include "../lib/tools.h"
i64 mult = 1234567890LL;
vector<int> primes;
vector<int> ftable;
vector<IntPair> pfactors;

//first I thought the largest prime is most important
//but after some experiment, the fact is power and base 
//are both important; so I need to revise the code.

//after a second round experiment, I found that the number 
//that is most important is the largest number that can 
//be expressed at p^m, so the map is removed, and a vector
//is introduced for this purpose
i64 facprimepow(i64 num, i64 px)
{
    i64 tot = 0;
    while(num >= px){
        num /= px;
        tot += num;
    }
    return tot;
}
i64 search_n_pidx(int pfac, const i64 pidx, i64 nstart, i64 nend, i64 plow)
{
    i64 nmid = 0, pmid = 0;
    while(nstart < nend){
        nmid = (nstart + nend)/2;
        pmid = facprimepow(nmid, pfac);
        if(pmid > pidx) {
            nend = nmid-1;
        }else if( pmid < pidx){
            nstart = nmid+1;
        }else{//equal case
            return (nmid/pfac*pfac);
        }
    }
    nmid = (nstart + nend)/2;
    if (facprimepow(nmid, pfac) >= pidx){
        nmid = nmid/pfac*pfac;
    }else{
        nmid = (nmid/pfac+1)*pfac;
    }
    return nmid;
}
//find the minimum number that satisfy the criteria
i64 find_min_facnum(int num)
{
    i64 nmax = 0;
    int npl = pfactors[num].second;;//largest prime factor of num;
    i64 pidx = pfactors[num].first*mult;
    
    //first give a search range
    i64 plow = 0;
    if(npl > 2)
        plow = log((double)(pidx)*(npl-1)+1)/log(npl);
    else
        plow = log(pidx+1)/log(npl);

    i64 nstart = power((i64)npl, plow);
    i64 nend = power((i64)npl, plow+1);
    assert(facprimepow(nstart, npl) <= pidx && facprimepow(nend, npl)>= pidx);
    //now based on the search range, tell me the exact number 
    //that is needed
    i64 n = search_n_pidx(npl, pidx, nstart, nend, plow);
    if(n > nmax) {
        nmax = n;
    }
    //printf("debug %d %d\n", num, pkeep);
    return nmax;    
}
int main()
{
    int limit = 1000;
    i64 n18=1000000000000000000LL;
    primeWithin(primes, limit);
    factor_table_max(limit, ftable);
    pfactors.resize(limit+1, IntPair(0,0));
    
    for(unsigned int i = 0; i < primes.size(); ++i){
        int pk = log(limit)/log(primes[i]);

        i64 pn = primes[i];
        for( int j = 1; j<=pk; ++j){
            if(j==1)
                pfactors[pn]=IntPair(pn,pn);
            i64 iter = pn+1;
            while(iter <= limit && ftable[iter] != iter){
                if(pfactors[iter].first < pn)
                    pfactors[iter] = IntPair(pn, primes[i]);
                ++iter;
            }
            pn *= primes[i];
        }
    }
    i64 sum = 0;
    for(int i = 10; i<=limit; ++i){
        if(i% 10000 == 0)
            printf("%d\n",i);
        i64 single = find_min_facnum(i);
        sum += single;
        sum %= n18;
        printf("%d %lld %lld\n",i, single, sum);
    }
    printf("%lld\n", sum);
}
