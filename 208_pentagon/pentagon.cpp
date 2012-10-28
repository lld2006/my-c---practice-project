#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
using namespace std;
int main()
{
    int steps = 25;
    vector<vector<i64> > vn;
    vn.resize(steps+1);
    for(unsigned int i = 1; i < vn.size(); ++i){
        int lsize = 2*i-1;
        vn[i].resize(lsize, 0);
    }
    vn[1][0] = 1;
    //start from each level is -level
    for(unsigned int level = 2; level < vn.size(); ++level){
        vector<i64>& vp = vn[level-1];
        vector<i64>& vc = vn[level];
        for(unsigned int i = 0; i < vp.size(); ++i){
            vc[i] += vp[i];
            vc[i+2] += vp[i];
        } 
    }
    i64 sum = 0;
    for(unsigned int i = 0; i < vn[steps].size(); ++i){
        printf("%d %lld\n", i, vn[steps][i]);
        if((100-steps+i)%5 ==0){
            sum += vn[steps][i];
        }
    }
    printf("%lld\n", sum);
}   
