//TODO someone used less than 0.5 second to solve it!
//it is 60 times faster than my code
//notice that 2017 is a prime, so this problem can be restated as how many
//primes p have the following property: (p^(m+1)-1)/(p-1) mod 2017 == 0
//let us first assume p-1 does not divide 2017, then, the problem is
//p^(m+1)=1 mod 2017, First let me see how many numbers needs to be counted
//this function is now revised for number that can be expressed as prime^power only
//2017*n relys on n but not 2017.
//for p^2=1 mod 2017 i = 2016, need to find all primes like
//        4034k+4033 p < nmax
//for p^3=1 mod 2017 i = 294 and 1722 need to find all numbers like
//        (4034k+2311 or 4034k+3739) p^2 < nmax
//for p^4=1 mod 2017 i = 229, need to find numbers like
//        (4034k+229) with p^3 < nmax
#include "../lib/tools.h"
#include <cstdio>
#include <algorithm>
int main()
{
    i64 nmax = 100000000000LL;
    int nmod = 2017;
    i64 nmod2 = 2*nmod;
    i64 total = 0;
    vector<vector<i64>> vn; 
    vn.resize(3);
    for(i64 i = nmod2-1; i<nmax; i += nmod2){
        if(strong_pseudo_test(i)){
            assert((i-1)%nmod != 0);
            assert((i+1)%nmod == 0);
            i64 nx1 = nmax/i;
            i64 pos = nx1*(nx1+1)/2*i;
            i64 nx2 = nmax/(i*i);
            i64 neg = nx2*(nx2+1)/2*(i*i);
            //printf("i=%lld %lld %lld %lld %lld\n", i, nx1, pos, nx2, neg);
            vn[0].push_back(i);
            total += pos - neg;
        }
    }
    printf("r1 %lld\n", total);
    for(i64 i = 294+nmod; i*i<nmax; i += nmod2){
        i64 vx = i * i;
        if(strong_pseudo_test(i)){
            i64 nx1 = nmax / (vx);
            i64 pos = nx1*(nx1+1)/2*(vx);
            vn[1].push_back(vx);
            vx *=i;
            i64 nx2 = nmax/vx;
            i64 neg = nx2*(nx2+1)/2*(vx);
            assert((i-1)%nmod != 0);
            assert((i*i*i-1)/(i-1)%nmod ==0);
            //printf("i=%lld %lld %lld %lld %lld\n", i, nx1, pos, nx2, neg);
            total += pos - neg;
        }
    }
    printf("r21 %lld\n", total);
    for(i64 i = 1722+nmod; i*i<nmax; i += nmod2){
        i64 vx = i * i;
        if(strong_pseudo_test(i)){
            i64 nx1 = nmax / (vx);
            i64 pos = nx1*(nx1+1)/2*vx;
            vn[1].push_back(vx);
            vx *= i;
            i64 nx2 = nmax / (vx);
            i64 neg = nx2*(nx2+1)/2*vx;
            assert((i-1)%nmod != 0);
            assert((i*i*i-1)/(i-1)%nmod ==0);
            //printf("i=%lld %lld %lld %lld %lld\n", i, nx1, pos, nx2, neg);
            total += pos - neg;
        }
    }
    printf("r22 %lld\n", total);
    for(i64 i = 229; i*i*i<nmax; i += nmod2){
        i64 vx = i*i*i;
        if(strong_pseudo_test(i)){
            assert((i-1)%nmod != 0);
            //printf("3 %lld\n", i);
            i64 nx1 = nmax / (vx);
            i64 pos = nx1*(nx1+1)/2*(vx);
            vn[2].push_back(vx);
            vx *=i;
            i64 nx2 = nmax/vx;
            i64 neg = nx2*(nx2+1)/2*(vx);
            assert((i*i*i*i-1)/(i-1)%nmod ==0);
            //printf("i=%lld %lld %lld %lld %lld\n", i, nx1, pos, nx2, neg);
            total += pos - neg;
        }
    }
    printf("r3 %lld\n", total);
    //1 2 
    sort(vn[1].begin(), vn[1].end());
    printf("sort %lld\n", vn[1][0]);
    for(unsigned int i = 0; i < vn[1].size(); ++i){
        i64 v2 = vn[1][i];
        for(unsigned int j = 0; j < vn[0].size(); ++j){
            i64 v1 = vn[0][j];
            i64 v = v1 * v2;
            if(v > nmax) break;
            i64 nx = nmax/v;
            i64 val = (nx+1)*nx/2*v;
            total -= val;
            //printf("10 %lld %lld %lld\n", v1, v2, val );
        }
    }
    printf("r12 %lld\n", total);
    //1 3
    for(unsigned int i = 0; i < vn[2].size(); ++i){
        i64 v2 = vn[2][i];
        for(unsigned int j = 0; j < vn[0].size(); ++j){
            i64 v1 = vn[0][j];
            i64 v = v1 * v2;
            if(v > nmax) break;
            i64 nx = nmax/v;
            total -= (nx+1)*nx/2*v;
        }
    }
    printf("r13 %lld\n", total);
    //2 3
    for(unsigned int i = 0; i < vn[2].size(); ++i){
        i64 v2 = vn[2][i];
        for(unsigned int j = 0; j < vn[1].size(); ++j){
            i64 v1 = vn[1][j];
            i64 v = v1 * v2;
            if(v > nmax) break;
            i64 nx = nmax/v;
            total -= (nx+1)*nx/2*v;
        }
    }
    printf("r23 %lld\n", total);
    //1 1 
    i64 root = sqrt(nmax);
    for(unsigned int i = 0; i < vn[0].size(); ++i){
        i64 v1 = vn[0][i];
        if(v1 > root) break;
        for(unsigned int j = i+1; j < vn[0].size(); ++j){
            i64 v2 = vn[0][j];
            i64 v = v1 * v2;
            if(v > nmax) break;
            i64 nx = nmax /v;
            total -= nx*(nx+1)/2*v;
            //printf("11 %lld %lld %lld\n", v1, v2, nx*(nx+1)/2*v );
        }
    }
    printf("%lld\n", total);
}
