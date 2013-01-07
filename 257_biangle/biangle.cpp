#include <cstdio>
#include <cmath>
#include <cstdlib>
#include "../lib/typedef.h"
#include "../lib/tools.h"
int plimit = 100000000;
//special version for this problem only
void find_factors(int n, const vector<int>& ftable, vector<IntPair>& vpairs, int mult)
{
    vpairs.clear();
    int pwr = 0;
    int curr_fac = ftable[n];
    while(curr_fac>1){
        ++pwr;
        n /= ftable[n];
        while(curr_fac == ftable[n]){
            ++pwr;
            n /= ftable[n];
        }
        vpairs.push_back(IntPair(curr_fac, pwr*mult));
        curr_fac = ftable[n];
        pwr = 0;
    }
}
i64 find_divisor(const IntPairVec& vpairs, i64 dmin, i64 dmax, int cpos, i64 prod, i64 a)
{
    if(cpos == static_cast<int>(vpairs.size())) {
        i64 peri = 3*a+prod+2*a*a/prod;
        if(prod >= dmin && prod <= dmax){
            //printf("a  %lld %lld %lld %lld\n", a, a+prod, a+a*a*2/prod, 3*a+prod+2*a*a/prod);
            if(peri <= plimit)
                return 1;
            else
                return 0;
        }else
            return 0;
    }
    i64 tp = 1;
    i64 total = 0;
    for( int pow = 0; pow <= vpairs[cpos].second; ++pow){
        i64 p1 = prod * tp;
        tp *= vpairs[cpos].first;
        total += find_divisor(vpairs, dmin, dmax, cpos+1, p1, a);
    }
    return total;
}
i64 find_divisor2(const IntPairVec& vpairs, i64 dmin, i64 dmax, const int cpos, const i64 prod, i64 delta)
{
    if(cpos == static_cast<int>(vpairs.size())) {
        i64 a = prod - 2* delta;
        if(a < dmin || a > dmax) return 0;
        i64 peri = 2*a + delta;
        i64 c = a*(2*a+delta);
        assert(c % (a+ 2* delta) == 0);
        c /= (a+2*delta);
        if(peri + c <= plimit){
            //printf("b %lld %lld %lld %lld\n",a, a+delta, c, 2*a+delta+c);
            return 1;
        }else 
            return 0;
    }
    i64 tp = 1;
    i64 total = 0;
    for( int pow = 0; pow <= vpairs[cpos].second; ++pow){
        i64 p1 = prod * tp;
        tp *= vpairs[cpos].first;
        total += find_divisor2(vpairs, dmin, dmax, cpos+1, p1, delta);
    }
    return total;
}
int main()
{
    i64 cnt = plimit/3;
    
    //real coding part
    //delta is b-a;
    //
    vector<int> ftable;
    //providing the factor for all numbers
    factor_table_max(plimit, ftable);
    vector<IntPair> vpairs;
    for( i64 a = 1; a<=plimit/3; ++a){
        if(a % 1000000 == 0)
            printf("%lld %lld\n", a, cnt);
        find_factors(a, ftable, vpairs, 2);
        if(vpairs.empty()){
            vpairs.push_back(IntPair(2,1));
        }else if( vpairs.back().first == 2){
            vpairs.back().second++;
        }else
            vpairs.push_back(IntPair(2,1));
        int deltamin=a+1;//can be equal
        int deltamax=a*sqrt(2.0);
        cnt += find_divisor(vpairs, deltamin, deltamax, 0, 1, a);
    }
    for(i64 delta = 1; delta <= plimit/2 ; ++delta){
        if(delta % 1000000 == 0)
            printf("%lld %lld\n", delta, cnt);
        find_factors(delta, ftable, vpairs, 2);
        int nsize = vpairs.size();
        if(vpairs.empty()||vpairs.back().first > 3){//no 2 3
            vpairs.push_back(IntPair(3,1));
            vpairs.push_back(IntPair(2,1));
        }else if(vpairs.back().first == 3){ //only 3
            vpairs.back().second++;
            vpairs.push_back(IntPair(2,1));
        }else{
            if(vpairs.size()==1){
                assert(vpairs[0].first == 2);
                vpairs[0].second++;
                vpairs.push_back(IntPair(3,1));
                swap(vpairs[0], vpairs[1]);
            }else{
                assert(nsize >= 2);
                if(vpairs[nsize-2].first == 3){
                    vpairs[nsize-2].second++;
                    vpairs[nsize-1].second++;
                }else{
                    vpairs[nsize-1].second++;
                    vpairs.push_back(IntPair(3,1));
                    swap(vpairs[nsize], vpairs[nsize-1]);
                }
            }
        }//end of creating 6 delta^2
        i64 amin = delta * (sqrt(3.0)+1)+1;
        i64 amax = plimit/3;
        cnt += find_divisor2(vpairs,amin, amax, 0, 1, delta );
    }
    printf("%lld\n", cnt);
    exit(1);
    //brute force method
    int amax = plimit/3;
    for(int a = 1; a<= amax; ++a){
        int bmax = (plimit-a)/2;
        for(int b = a; b<= bmax; ++b){
            int cstart = (a==b)? b+1:b;
            int cmax = plimit+1-a-b < a+b? plimit+1-a-b:a+b;
            for(int c = cstart; c< cmax;++c){
                i64 num = (i64)a*(a+b+c);
                i64 den = (i64)b*c;
                if(num == den || num == 2*den){
                    printf("%d %d %d %lld\n",a, b, c, num/den);
                    ++cnt;
                }
            }
        }
    }
    printf("%lld\n", cnt);
}
