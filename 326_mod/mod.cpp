#include <vector>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include "../lib/typedef.h"
#include "../lib/tools.h"
i64 range = 1000000000000LL;
i64 nmod = 1000000;
bool operator< (const I64Pair& p1, const I64Pair& p2)
{
    if(p1.first < p2.first)
        return true;
    else if(p1.first == p2.first)
        return p1.second < p2.second;

    return false;
}
int f(int n0)
{
    int res = n0%6;
    int n = n0/6;
    switch(res){
        case 0:
            return 3*n;
        case 1:
            return 4*n+1;
        case 2:
            return 3*n+1;
        case 3:
            return n;
        case 4:
            return 6*n+3;
        case 5:
            return n;
        default:
            assert(0);
            return -1;
    }
}
int main()
{
    I64PairVec vn; 
    vn.resize(12*nmod + 1, I64Pair(0,0));
    vn.push_back(I64Pair(0,0));// 0 is actually not used
    for(unsigned int i = 1; i <= vn.size(); ++i){
        vn[i] = I64Pair(f(i), i);
    }
    i64 sum = 0;
    // no need to create a new vector, overwrite
    // if the sum from i to j % nmod == 0, then they should be equal in vn
    for(unsigned int i = 1; i < vn.size(); ++i){
        sum += vn[i].first;
            sum %= nmod;
        vn[i].first = sum;
    }
    sort(vn.begin(), vn.end());
    //the period is 6*nmod;
    //now first check how many nmod exist in 
    i64 total = 0;
    i64 mod6 = nmod*6;
    unsigned int i = 0;
    while( i < vn.size() ){// the second half is only for end-head situation
    //for(unsigned int i = 1; i<vn.size(); ++i){
        if(vn[i].second >= range){
            ++i;
            continue;
        }
            
        //i64 ne = (range  - i)/mod6;
        //if(ne > 0)
        //    total += (ne+1)*ne/2;//whole piece always mod nmod == 0;

        i64 current = vn[i].first;
        i64 last = i;
        //find all same sum
        while(last !=static_cast<i64>(vn.size()) && vn[last].first == current){
            ++last;
        }

        for(unsigned int j = i; j < last; ++j){
            i64 p1 = vn[j].second;
            if( p1 >= range-1) continue;
            if(p1 >= mod6) break;
            for(unsigned int k = j + 1; k < last; ++k){
                i64 p2 = vn[k].second;
                if(p2 > range) continue;
                assert(p2 - p1 > 0);
                if(p2 - p1 > mod6) continue;// has already been considered
                i64 ne = (range  - p2)/mod6+1;
                //i64 old = total;
                if(ne > 0)
                    total += (ne+1)*ne/2;
                //if(old != total){
                //    printf("%lld %lld\n", p1+1,p2);
                //}
            }
        }
        i = last;
    }
    printf("%lld\n", total);
}
