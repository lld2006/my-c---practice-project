#include <cstdio>
#include "../lib/tools.h"
#include <vector>
#include <cassert>
#include <algorithm>
//lesson, be careful about the start index 0/1
//lesson, do not forget the equal case
//assume something need to verify, for example, the array is sorted, 
//then after some transformation, check if it is still valid
//TODO need to remove equal compare, since right now it is impossible

int compare(int size, vector<int> top, vector<int> bottom){
    int sum = 0;
    unsigned int vsize = top.size();
    assert(top.size() == bottom.size());
    vector<int> realbottom;
    realbottom.resize(vsize, 0);
    do{
        //find the real combination
        for(unsigned int i = 0; i < vsize; ++i){
            realbottom[vsize-1-i] = size - 1 - bottom[i];
        }
        do{
            vector<int> sunion;
            set_union(top.begin(), top.end(), 
                    realbottom.begin(), realbottom.end(),
                    back_inserter(sunion));
            if(sunion.size()!= 2*vsize)
                continue;
            bool alwaysequal = true;
            bool initialized = false;
            bool greater = true;
            bool needCompare = false; 
            for(unsigned int i = 0; i<vsize; ++i){
                if(top[i]== realbottom[i]) 
                    continue;
                alwaysequal = false;
                if(!initialized){
                    greater = top[i] > realbottom[i];
                    initialized = true;
                    continue;
                }
                if((top[i] > realbottom[i]) != greater){
                    needCompare = true;
                    break;
                }
            }
            if(alwaysequal)
                continue;
            if(needCompare)
                ++sum;
            
        }while(next_combination(top, size, vsize));
    }while(next_combination(bottom, size, vsize));
    return sum;
}
int main(){
    unsigned int setsize = 12;
    int sum = 0;
    for(unsigned int i = 1;  i <= setsize/2; ++i){
        vector<int> bottom;
        vector<int> top;
        bottom.resize(i, 0);
        top.resize(i, 0);
        for(unsigned int j = 0; j < i; ++j){
            bottom[j]= j;
            top[j] = j;
        }
        sum += compare(setsize, top, bottom);
    }
    assert(sum %2 == 0);
    printf("%d\n", sum/2);
}
