#include <cstdio>
#include <map>
#include <cassert>
#include <cmath>
#include "../lib/typedef.h"
using namespace std;
double dist(int i, int j )
{
    double val = 10+i+j;
    return sqrt(200*(val));
}
int main()
{
    map<IntPair, double> cfgmap;
    for(unsigned int i = 0; i < 21; ++i){
        IntPair p(1<<i, i);
        cfgmap.insert(make_pair(p, 30+i));
    }

    for(unsigned int level = 1; level < 21; ++level){
        printf("level=%d size=%zu\n", level-1, cfgmap.size());
        map<IntPair, double> newcfgmap;
        for(auto iter = cfgmap.begin(); iter != cfgmap.end(); ++iter){
            int value = iter->first.first;
            int last = iter->first.second;
            double d = iter->second;
            for(unsigned int i= 0; i < 21; ++i){
                if(value & (1<<i)) continue;
                int value1 = value | (1<<i);
                double d1 = d + dist(last, i);
                if(level==20) d1 += (30+i);
                IntPair p(value1, i);
                auto lb = newcfgmap.lower_bound(IntPair(value1, i));
                if(lb->first == p){
                    if(lb->second > d1)
                        lb->second = d1;
                }else{
                    newcfgmap.insert(lb, make_pair(p, d1));
                }
            }
        }
        cfgmap.swap(newcfgmap);
    }
    int value = 1e8;
    for(auto iter = cfgmap.begin(); iter != cfgmap.end(); ++iter){
        int val = round(iter->second*1000);
        if(val < value) value = val;
    }
    printf("minimum is %d\n", value);
}
