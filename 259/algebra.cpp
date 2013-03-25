#include <cstdio>
#include <vector>
#include <cassert>
#include <string>
#include <set>
#include "../lib/rational.h"
#include "../lib/typedef.h"
using namespace std;
//lesson, not efficient, need to know how to make it faster!
string nums("123456789");
set<i64> gset;
//let us store the process result in left;
void search_reachable(string& snum, int level, set<rational>& srat)
{
    i64 num = stoll(snum);
    srat.insert(num);
    
    //to search it means that the string's size >=2
    for(unsigned int i = 1; i < snum.size(); ++i){
        string sleft = snum.substr(0, i);
        string sright =snum.substr(i, snum.size()-i);
        set<rational> setl, setr;
        search_reachable(sleft, level+1, setl);
        search_reachable(sright, level+1, setr);
        for(auto iter1=setl.begin(); iter1 != setl.end(); ++iter1)
            for(auto iter2=setr.begin(); iter2 != setr.end();++iter2){

                rational rt = *iter1 * *iter2;
                srat.insert(rt);
                
                rt = *iter1 + *iter2;
                srat.insert(rt);

                rt = *iter1 - *iter2;
                if(rt.pnum() != 0)
                    srat.insert(rt);

                if(iter2->pnum() != 0){
                    rt = *iter1 / (*iter2);
                    srat.insert(rt);
                }
            }
        if(level == 0){
            auto iter1 = srat.lower_bound(1);
            for(; iter1 != srat.end(); ++iter1){
                if(iter1->pden()==1 && iter1->psign() == 1)
                    gset.insert(iter1->pnum());
            }

        }
    }
}
int main()
{
    set<rational> srat0;
    search_reachable(nums, 0, srat0);
    i64 total = 0;
    for(auto iter1 = gset.begin(); iter1 != gset.end(); ++iter1)
        total += *iter1;
    
    printf("%lld\n", total);
}
