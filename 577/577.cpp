#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
using namespace std;
int main()
{
    i64 nmax = 12345;
    vector<i64> v1, v2, vf;
    v1.resize(nmax-2, 0);
    v2.resize((nmax)/3, 0);
    vf.resize(nmax-2, 0);
    //initialize
    for(i64 i = 0; i < v1.size(); ++i)
        v1[i] = (i+1)*(i+2)/2;
    for(i64 j = 0; j< v2.size(); ++j)
        v2[j] = j+1;
    
    for(i64 j = 0; j<v2.size(); ++j){
        i64 ifinal = nmax -3-3*j;
        for(i64 i = 0; i <= ifinal; ++i){
            i64 value = v2[j] * v1[i];
            vf[i+3*j] += value;
        }
    }
    i64 sum = 0;
    for(int i = 0; i < vf.size(); ++i)
        sum += vf[i];
    printf("%lld\n", sum);
}
