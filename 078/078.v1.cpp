#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/tools.h"
using namespace std;
int main()
{
    int target = 200000;
    vector<i64> vdiv;
    vdiv.resize(target + 1, 1);
    vdiv[0] = 0;
    for( int i = 2; i <= target; ++i){
        for(unsigned int j = i; j < vdiv.size(); j +=i){
            vdiv[j] += i;
        }
    }
    vector<i64> vb;
    vb.resize(target+1, 0);
    vb[1] = vdiv[1] ;
    for(unsigned int i = 2; i < vb.size(); ++i){
        if(i % 10000 ==0)
            printf("%d\n", i);
        i64 sum = vdiv[i];
        for(unsigned int j = 1; j < i; ++j){
            sum += vdiv[j]*vb[i-j];
        }
        sum /= i;
        assert(sum >= vb[i-1]);
        if( sum % 1000000 == 0){
            printf("%d\n", i);
            return 0;
        }
        vb[i] = sum;
    }
}
