#include <cstdio>
#include <vector>
#include <cassert>
#include <map>
#include "../lib/typedef.h"
using namespace std;

int total_level = 10;
int lsize = 32;
vector<unsigned int> combinations;

void search23(vector<unsigned int>& vcb, int shift, unsigned int mask){
    if(shift > lsize) 
        return;
    else if(shift == lsize){
        vcb.push_back(mask);
        return;
    } else{
        unsigned int tp = 1 <<(shift +2);
        unsigned int n1;
        n1 = (shift+2 == lsize) ? mask :mask + tp;
        search23(vcb, shift+2, n1);
        tp = 1 << (shift +3);
        n1 = (shift+3 == lsize) ? mask :mask + tp;
        search23(vcb, shift+3, n1);
    }
    return;
}

int main(){
    combinations.reserve(4000);
    search23(combinations, 0, 0);
    printf("%d\n", static_cast<int>(combinations.size()));
    IntPairVec pairvec;   
    pairvec.reserve(4000);
    for(unsigned int i = 0; i < combinations.size(); ++i){
        for(unsigned int j = 0; j < combinations.size(); ++j)
            if(!(combinations[i] & combinations[j]))
                pairvec.push_back(make_pair(i, j));
    }
    vector<i64> stat(combinations.size(),1);
    vector<i64> newstat(combinations.size(),0);
    for(int level = 1; level < total_level; ++level){
        newstat.clear();
        newstat.resize(combinations.size(), 0);
        for(unsigned int i = 0; i < pairvec.size(); ++i){
            int pf = pairvec[i].first;
            int ps = pairvec[i].second;
            newstat[pf] += stat[ps];
        }
        stat = newstat;
    }
    i64 sum = 0;
    for(unsigned int i =0 ; i< stat.size(); ++i)
        sum += stat[i];
    printf("%lld\n", sum);
}
