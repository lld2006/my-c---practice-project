#include "../lib/tools.h"
#include <cstdio>
#include <numeric>
int main(){
    vector<vector<int> > dp;
    dp.resize(27);
    for(int i = 2; i<=26; ++i){
        dp[i].resize(i,1); //0 is number of no greater the rest has 
        //exactly 1 greater happens at position i
        //initialize to 1 because 
    }
    for(int i = 3; i<=26; ++i){
        vector<int>& dp0 = dp[i-1];
        vector<int>& dp1 = dp[i];
        for(unsigned int j = 1; j<dp0.size();++j){
            dp1[j]+= dp0[j];
            dp1[j+1]+=dp0[j];
        }
    }
    for(unsigned int i = 3; i< dp.size(); ++i){
        vector<int>& dpi = dp[i];
        i64 sum = accumulate(dpi.begin()+1, dpi.end(), 0);
        sum *= combination((i64)26, (i64) i);
        printf("%d %lld\n", i, sum);
    }
}
