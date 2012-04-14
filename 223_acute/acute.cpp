#include "../lib/typedef.h"
#include <tr1/unordered_map>
#include <cstdio>
typedef std::tr1::unordered_map<i64,i64> hashmap;
int main()
{
    //code only consider a > 1 b>= a c> b
    //solutions for a=1 will be considered at the end
    int cnt = 0;
    i64 limit = 7322331;
    i64 perimeter = 25000000;
    vector<i64> tria;
    hashmap squares;
    tria.resize(limit+1);
    for(i64 i=0; i <= limit; ++i){
        tria[i]= i;
    }
    i64 seglim,seglim2;
    int nstart = 2;
    i64 segsize = 1000000;//do not put all numbers in hash
    for(i64 seg = 0; seg<25; ++seg){//for each segment
        printf("seg = %lld\n", seg);
        seglim = seg*segsize+segsize;
        seglim2 = seglim*seglim;
        squares.clear();
        //hash all the squares
        for(i64 ic = seg*segsize+1; ic<=seglim; ++ic){
            i64 value = ic * ic+1;
            squares.insert(pair<i64, i64>(value, ic));
        }
        i64 ialimit = seglim/(2+1.414)+1;
        for(int ia = nstart; ia < ialimit; ++ia){
            i64 ia2 = ia*ia;
            if(2*tria[ia]+2> ia2){
                ++nstart;
                continue;  //otherwise no need to continue;
            }
            i64 ibmax = (ia*ia-1)/2+1;
            if(ibmax > seglim) ibmax =seglim;
            for(int ib = tria[ia]; ib < ibmax; ++ib){
                i64 absum = ia2+ib*ib;
                if(absum > seglim2) {//temporarily stop
                    tria[ia] = ib;
                    break;
                }
                hashmap::iterator iter = squares.find(absum);
                if(iter != squares.end() && iter->second+ia+ib<=perimeter)
                    ++cnt;
            }
        }
    }
    printf("%d\n", cnt);
}
