#include <cstdio>
#include <vector>
#include <numeric>
#include <cassert>
#include "../lib/typedef.h"
using namespace std;

int get(int num, int base)
{
    int cnt = 0;
    while(num % base ==0){
        num/=base;
        ++cnt;
    }
    return cnt;
}

int main()
{
    int target = 200000;
    vector<int> v2;
    vector<int> v5;
    v2.resize(target+1,0);
    v5.resize(target+1,0);
    for( int i = 2; i<=target; ++i){
        v2[i] = v2[i-1] + get(i, 2);
        v5[i] = v5[i-1] + get(i, 5);
    }
    int vala = 200000/3+1;
    i64 cnt = 0;
    for(int ia = vala; ia <= target;++ia ){
        //if(!(ia & 16383))printf("%d\n", ia);
        int t5 = v5[target]-v5[ia];
        int t2 = v2[target]-v2[ia];
        if(t5 < 12 || t2 < 12) continue;
        int bstart = target-ia < ia? target-ia:ia;
        int ta = target -ia;
        int ib, ic;
        int b1 = bstart==ia?bstart+1:bstart;
        for(ib = b1; true; --ib){
            ic = ta - ib;
            if(ic >= ib) break;
            int nx5 = t5-v5[ib]-v5[ic] ;
            if(nx5 < 12) continue;
            int nx2 = t2-v2[ib]-v2[ic]; 
            if(nx2 < 12) continue;
            //assert(ia+ib+ic==target);
            //assert(nx2 >=0 && nx5 >=0);
                cnt += 6;
        }
        int nx5 = t5-v5[ib]-v5[ic] ;
        int nx2 = t2-v2[ib]-v2[ic]; 
        if(ic == ib && nx5 >= 12 && nx2 >= 12){
            cnt+= 3;
        }
        nx5 = t5-v5[bstart]-v5[target-ia-bstart] ;
        nx2 = t2-v2[bstart]-v2[target-ia-bstart]; 
        if(nx5>=12 && nx2>=12){
            if(bstart==ia)
            cnt += 3;
        }
         
    }
    printf("%lld\n", cnt);
}
