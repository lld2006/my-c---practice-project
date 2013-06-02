#include <cstdio>
#include <vector>
#include "../lib/tools.h"
using namespace std;
i64 n0 = 1000000000LL;
bool isFactor(i64 num ){
    if(!strong_pseudo_test(num)){
        return false;
    }
    if(powermodule(10LL, n0, num) != 1)
        return false;
    return true;
}
int main()
{
    int cnt = 0;
    i64 sum = 0;
    vector<int> v210;
    for(unsigned int i=1; i< 210; i+=2){
        if(i% 3 ==0) continue;
        if(i% 5 ==0) continue;
        if(i% 7 ==0) continue;
        v210.push_back(i);
    }
    int n1 = n0/210+1;
    for( int i = 0; i<= n1 ; ++i){
        i64 ni = 210LL*i;
        for(unsigned int j = 0; j < v210.size(); ++j){
            i64 num = ni + v210[j];
            if(isFactor(num)){
                if(num > n0) continue;
                ++cnt;
                sum += num;
                printf("%d %lld\n", cnt, num);
            }
        }
    }
    printf("%lld\n", sum);
}
