#include <cstdio>
#include <cassert>
#include <cstdlib>
#include "../lib/typedef.h"
vector<vector<IntPair>> vnum;
int numbers(int n, int order)
{
    switch(order){
        case 3:
            return n*(n+1)/2;
        case 4:
            return n*n;
        case 5:
            return n*(3*n-1)/2;
        case 6:
            return n*(2*n-1);
        case 7:
            return n*(5*n-3)/2;
        case 8:
            return n*(3*n-2);
        default:
            assert(0);//should never come here
            return 0;
    }
}
void search_cir_6(vector<int>& flags, int value, int nc, int value0, int sum)
{
    if(nc == 6){
        if(value % 100 == value0/100){
            printf("%d\n", sum);
            exit(0);
        }
        return;
    }
    int index = value%100;
    if(value < 10) return;
    vector<IntPair>& vi = vnum[index];
    for(unsigned int i = 0; i < vi.size(); ++i){
        int value1 = vi[i].first;
        int order = vi[i].second;
        if(flags[order]) continue;
        flags[order] = 1;
        search_cir_6(flags, value1, nc+1, value0, sum+value1);
        flags[order] = 0;
    }
}
int main()
{
    vnum.resize(100);
    for(unsigned int order = 3; order<= 8; ++order){
        for(unsigned int i = 1; i; ++i){
            int value = numbers(i, order);
            if(value < 1000) 
                continue;
            if(value >= 10000) break;
            int q = value / 100;
            vnum[q].push_back(IntPair(value, order));
        }
    }
    //let us start from 8 since octagonal numbers increase faster
    //than others
    vector<int> flags;
    flags.resize(9, 0);
    for(unsigned int i = 15; i; ++i){
        int value = numbers(i, 8);
        if(value < 1000 ) continue;
        if(value >= 10000) break;
        flags[8] = 1;
        search_cir_6(flags, value, 1, value, value);
    }
}
