#include <cstdio>
#include <cassert>
#include "../lib/typedef.h"
#include "../lib/tools.h"
//=======================================================
//this problem is kind of labor,  I drew a diagram
//to figure out which part needs to be computed in oder to 
//avoid the 0 contribution to the sum mod prime
//the second thing is that wilson's theorem helps a great deal
//to reduce the computation cost
//BUT STILL NEED TO FIGURE OUT THE BUG!!!!!
i64 nmod = 999999937LL;
i64 n = 10000000000000LL;
i64 m = 1000000000000LL;
i64 p = 10000;
int main()
{
    //n= 100; m = 10; p = 4;
    i64 p1k = 1;
    i64 p1kinv = 0;
    for(i64 k = 2; k <= p; ++k){
        p1k *=k;
        p1k%=nmod;
    }
    i64 nr = n % nmod; //630000
    i64 mr = m % nmod; //63000 
    assert(mr < nr);
    vector<i64> v1, v2;
    v1.resize(15000, 0);
    v2.resize(15000, 0);
    vector<i64> vnum;
    vector<i64> vden;
    vnum.resize(nr-p, 1);
    vden.resize(nr-p, 0); // k= p to nr - 1, cannot have k = nr
    i64 prod = 1;
    for(i64 kk=0; kk<p; ++kk )
        prod = product_mod(prod, n-kk, nmod);

    for(i64 kk = 0; kk<(i64)vnum.size(); ++kk){
        vnum[kk] = prod;
        prod = product_mod(prod, n-p-kk, nmod);
    }
    prod = 1;
    vden[0] = 1;
    i64 x, y, gcd;
    for(i64 kk = 1; kk <= (i64)vden.size(); ++kk){
        prod = product_mod(prod, kk, nmod);
        extended_euclid(prod, nmod, x, y, gcd);
        vden[kk] = x; //actuallly it has been inversed!!!
    }
    assert(product_mod(2LL, vden[2], nmod)== 1);
    assert(product_mod(6LL, vden[3], nmod)== 1);
    
    prod = 1;
    v1[0] = 1;
    for( i64 i = 1, t = n/nmod; t > 0; --t, ++i){
        prod = product_mod(prod, t, nmod);
        v1[i] = prod;
    }
    prod = 1;
    v2[0] = 1;
    for(i64 t = 1; t <= n/nmod; ++t){
        prod = product_mod(prod, t, nmod);
        extended_euclid(prod, nmod, x, y, gcd);
        v2[t] = x;//inversed!!!!
    }
    extended_euclid(p1k,nmod, p1kinv, y, gcd);//calculate p1kinv
    
    i64 kpart =0;
    i64 kpart2 = 0;
    for(i64 kk = 0; kk < (i64)vden.size(); ++kk ){
        i64 t = product_mod(vden[kk], vnum[kk], nmod );
        kpart += kk & 1 ? -t:t;
        kpart %= nmod;
        //printf("kk=%lld, num=%lld den=%lld t=%lld kpart=%lld sum=%lld\n", kk,vnum[kk], vden[kk], t, kpart, product_mod( p1kinv, kpart, nmod));
        if(kk==mr-p-1) kpart2 = kpart;
    }
    i64 jpart = 0;
    i64 jt = 1;
    i64 t = 0;
    i64 sign = -1;
    i64 nseg = (m/nmod); //k = 0...nseg *nmod+(0, 630000)
    for(int j = 0; j < nseg; ++j){
        t = product_mod(v1[j], v2[j], nmod);    
        jt = product_mod(jt, t, nmod);
        sign = -sign;
        jpart += jt*sign;
        jpart %= nmod;
    }
    i64 sum = product_mod(jpart, kpart, nmod) + sign * product_mod(kpart2, jt, nmod);
    sum = product_mod(sum , p1kinv, nmod);
    printf("jpart=%lld kpart=%lld  kpart2=%lld jt=%lld %lld\n",jpart, kpart, kpart2, jt, sum);
}
