#include "../lib/tools.h"
#include <cmath>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <numeric>
using namespace std;
int digsum(i64 num){
    int sum = 0;
    while(num){
        sum += num % 10;
        num/=10;
    }
    return sum;
}
int main()
{
    vector<i64> vn;
    vn.resize(200, 1);
    set<i64> nset;
    int ndig = 2;
    i64 prod = 100;
    while(nset.size()< 30){
        for( int i = 2; i<= ndig * 9; ++i){
            while(vn[i] < prod){
                vn[i] *= i;
                if(digsum(vn[i]) == i){
                    if(vn[i] < 10) continue;
                    printf("insert %d %lld\n", i, vn[i]);
                    nset.insert(vn[i]);
                }
            }
        }
        prod *= 10;
        ++ndig;
    }
    int cnt = 1;
    for(auto iter = nset.begin(); iter !=nset.end(); ++iter, ++cnt){
            printf("%d %lld\n", cnt, *iter);
    }
}
