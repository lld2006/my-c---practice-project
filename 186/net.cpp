#include <vector>
#include <cstdio>
#include <cassert>
#include "../lib/typedef.h"
using namespace std;
//this problem is a practice problem for the disjoint set concept introduced int CLRS
//without the concept of disjoint set, it is very complicated and lengthy. 
//with the help of disjoint set, it is easy and clear with pleasure to write the code
vector<int> vrand;
int nmod = 1000000;
int nprimer = 524287;
int generate_number(int nth){
    i64 value = 0;
    if(nth <= 55){
        value =  100003 - 200003LL*nth + 300007LL*nth*nth*nth;
        value %= nmod;
        vrand[nth-1] = value;
    }else{
        int i1 = (nth-1)%55;
        int i2 = (nth-25)%55;
        value = vrand[i1] + vrand[i2];
        value %= nmod;
        vrand[i1] = value;
    }
    return value;
}


int main(){
    vector<DisJointSet> vall;
    vall.resize(nmod);       
    vrand.resize(55, 0);    //used to calculate next random number
    bool cond_not_met = true;
    i64 call_count = 0;
    int ig = 1;
    while(cond_not_met){
        int i1 = generate_number(ig++);
        int i2 = generate_number(ig++);

        if(i1 == i2) continue;

        ++call_count;

        if(vall[i1].parent() == 0)
            vall[i1].makeset(i1);
        if(vall[i2].parent() == 0)
            vall[i2].makeset(i2);
        vall[i1].union_set(vall[i2]);

        //check if we need to break
        if(vall[nprimer].parent()!=0 && vall[nprimer].set_size() >= 990000)
            break;
    }
    printf("%lld\n", call_count);
}
