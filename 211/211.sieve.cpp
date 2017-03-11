#include <cstdio>
#include <vector>
#include <cmath>
#include "../lib/typedef.h"
using namespace std;
int main()
{
    int limit = 64000000;
    vector<i64> v2;
    v2.resize(limit, 1);
    for(i64 n = 2; n< limit; ++n){
        for(i64 m = n; m <limit; m+=n){
            v2[m] += n*n;
        }
    }
    i64 sum = 1;
    for(i64 n = 2; n < limit; ++n){
        i64 root = sqrt(v2[n]); 
        if(root*root == v2[n]) 
            sum += n;
    }
    printf("%lld\n", sum);
}
