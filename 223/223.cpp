#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cassert>
using namespace std;
//c^2-b^2=a^2-1
//so factor a-1 a+1
int limit = 25000000;
int nfac(int& na, int px, const vector<int>& ftable){
    int fa = ftable[na];
    int cnt = 0;
    while(ftable[na] == fa){
        ++cnt;
        na/= fa;
    }
    return cnt;
}
void special_factor(int number, IntPairVec& factors, vector<int>& ftable)
{
    factors.clear();
    int na = number-1, nb=number+1;
    int cnt = 0;
    while(na >1 && nb > 1){
        int fa = ftable[na];
        int fb = ftable[nb];
        int fmin = fa < fb? fa:fb;
        if(fa < fb ){
            cnt = nfac(na, fa, ftable);
        }else if(fa > fb){
            cnt = nfac(nb, fb, ftable);
        }else{
            cnt = nfac(na, fa, ftable);
            cnt += nfac(nb, fb, ftable);
        }
        factors.push_back(IntPair(fmin, cnt));
    }
    if(na > 1){ //lesson forgot to add assertion here na==1 nb ==1
        while(na > 1){
            int fa = ftable[na];
            int cnt = nfac(na, fa, ftable);
            factors.push_back(IntPair(fa, cnt));
        }
    }
    if(nb > 1){
        while(nb > 1){
            int fb = ftable[nb];
            int cnt = nfac(nb, fb, ftable);
            factors.push_back(IntPair(fb, cnt));
        }
    }
}
void find_triangle(IntPairVec& factors, i64 a, int cpos, i64 prod, int& sum )
{   //c-b is prod
    if(prod > a) 
        return ;
    if(cpos == static_cast<int>(factors.size())){
        i64 value = a*a-1;
        i64 p2 = value/prod;
        assert(p2 > prod);
        if(((prod -p2) & 1) ) return ;
        if((p2-prod) < 2*a) return;
        if(p2 + a > limit ) return;
        i64 b = (p2-prod)/2;
        i64 c = (p2 + prod)/2;
        assert(c*c-b*b-a*a+1LL==0);
        //printf("%lld %lld %lld %lld\n", a, b, c, a+b+c);
        
        ++sum;
        return;
    }
    int tp = 1;
    i64 px = factors[cpos].first;
    i64 maxp = factors[cpos].second;
    for(unsigned int i = 0; i <= maxp; ++i){
        i64 p1 = prod * tp;
        find_triangle(factors, a, cpos+1, p1, sum );
        tp *= px;
    }
}
int main()
{
    //limit = 200;
    double df = 2 + sqrt(2.0);
    int amax = limit/df;
    vector<int> ftable;
    factor_table_min(amax+1, ftable);
    int sum = 0;
    sum +=(limit-1)/2;

    IntPairVec factors;
    for( int i = 2; i <=amax;++i){
        if(i % 100000==0)printf("%d\n", i);
        special_factor(i, factors, ftable);
        find_triangle(factors, i, 0, 1LL, sum);
    }
    printf("%d\n", sum);
}
