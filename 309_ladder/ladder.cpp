#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <tuple>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <set>
using namespace std;
typedef tuple<int, int, int> triplet;
bool operator< (const triplet& t1, const triplet& t2)
{
    if(get<0>(t1) < get<0>(t2))
        return true;
    else if(get<0>(t1) == get<0>(t2)){
        if(get<1>(t1) < get<1>(t2))
            return true;
        else if(get<1>(t1) == get<1>(t2)){
            if(get<2>(t1) < get<2>(t2))
                return true;
            else
                return false;
        }else
            return false;
    }else
        return false;
}
int main()
{
    int limit = 1000000;
    vector<triplet> vtr;
    for( int m = 1; m < 1000; ++m)
        for( int n=m+1; n< 1000; n+=2){
            if(gcd(m, n) > 1) continue;
            int a = n*n - m*m;
            int b = 2*m*n;
            int c = n*n+m*m;
            assert(a >0 && b > 0 && c > 0);
            if(c >= limit)
               break; 
            vtr.push_back(triplet(a, b, c));
            vtr.push_back(triplet(b, a, c));
        }
    int size = vtr.size();
    for( int i = 0; i< size; ++i){
        int c = get<2>(vtr[i]);
        int b = get<1>(vtr[i]);
        int a = get<0>(vtr[i]);
        assert(a > 0 && b >0 && c> 0);
        int cnum = limit/c;
        if(cnum * c == limit)
            --cnum;
        for( int j = 2; j<=cnum; ++j)
            vtr.push_back(triplet(a*j, b*j, c*j));
    }
    printf("%zu\n",vtr.size() );
    sort(vtr.begin(), vtr.end());
    vector<int> vpos;
    vpos.resize(limit, 0);
    
    for(unsigned int i = 0; i< vtr.size(); ++i){
        ++vpos[get<0>(vtr[i])];
        //printf("%d %d %d\n", get<0>(vtr[i]),get<1>(vtr[i]), get<2>(vtr[i]) );
    }


    i64 total = 0;
    set<triplet> tset;
    for(unsigned int i = 0; i< vpos.size(); ++i)
        total += vpos[i];

    assert(total == vtr.size());

    total = 0;
    int cpos =0;
    for(unsigned int i = 0; i < vpos.size(); ++i) {
        if(vpos[i] == 0) continue;
        if(vpos[i] == 1) {
            ++cpos;
            continue;
        }
        for( int j = cpos; j < cpos + vpos[i]; ++j){
            for( int k = j+1; k < cpos + vpos[i]; ++k){
                assert(j < vtr.size());
                assert(k < vtr.size());
                i64 x = get<1>(vtr[j]);
                i64 y = get<1>(vtr[k]);
                i64 a = get<2>(vtr[j]);
                i64 b = get<2>(vtr[k]);
                assert(a > 0 && b>0);
                assert(get<1>(vtr[j]) != get<1>(vtr[k]));
                i64 g = gcd(x*y, x+y);
                i64 scale = (x+y)/g;

                a *= scale;
                if(a >= limit) 
                    continue;
                b*= scale;
                if(b >= limit)
                    continue;
                tset.insert(triplet(a, b, x*y*scale/(x+y)));
                assert(a > 0 && b >0);
                if(a< 200 && b < 200)
                    printf("%lld %lld %lld\n", a, b, x*y*scale/(x+y));
                ++total;
            }
        }
        cpos += vpos[i];
    }
    printf("%zu\n", tset.size());
}
