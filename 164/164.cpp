#include <cstdio>
#include <numeric>
#include <vector>
#include <cassert>
#include "../lib/typedef.h"
using namespace std;
void init_vec(vector<vector<i64>>& vvn)
{
    vvn.clear();
    vvn.resize(10);
    for(unsigned int i = 0; i< vvn.size(); ++i){
        vvn[i].resize(999, 0);
    }
}
int sumdigit(int num){
    int sum = 0;
    while(num){
        int res = num % 10;
        sum += res;
        num /= 10;
    }
    return sum;
}
i64 cnt(vector<vector<i64>>& vvn)
{
    i64 sum = 0;
    for(unsigned int i =0 ; i<vvn.size(); ++i){
        sum = accumulate(vvn[i].begin(), vvn[i].end(), sum);
    }
    return sum;
}
int main()
{
    vector<vector<i64>> vvn;
    init_vec(vvn);
    for(unsigned int i = 100; i<=999; ++i){
        int val = sumdigit(i);
        if(val <= 9)
            ++vvn[val][i]; 
    }
    for(unsigned int nd=4; nd<= 20; ++nd ){
        vector<vector<i64>> newv;
        init_vec(newv);
        for(int i = 0; i <= 9; ++i){
            int val = i;
            for(unsigned int j = 0; j < vvn[0].size(); ++j){
                if(!vvn[i][j])continue;
                int nf = j/100;
                int res = j % 100;
                for( int k = 0; k<= 9; ++k){
                    int newval = val + k -nf;
                    if(newval > 9) continue;
                    int dest = res*10+k;
                    newv[newval][dest] += vvn[i][j];
                    //if(vvn[i][j]) printf("init %d dest %d %d %lld %lld\n",j,dest, i, vvn[i][j], newv[newval-nf][dest]);
                }
            }
        }
        printf("%d %lld %lld\n", nd, cnt(vvn), cnt(newv));
        vvn.swap(newv);
    }
    printf("%lld\n", cnt(vvn));
}
