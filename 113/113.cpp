#include "../lib/typedef.h"
#include <cstdio>
#include <cassert>
#include <numeric>
void find_non_bouncy_numbers(int ndig, vector<i64>& vn)
{
    vector<i64> vnnew;
    vnnew.resize(ndig, 0LL);
    for( int i = 0; i < ndig; ++i ){
        for( int j = i; j <ndig; ++j){
            vnnew[j] += vn[i];
        }
    }
    vn.swap(vnnew);
    return;
}
int main()
{
    int maxdig = 100;
    vector<i64> vn;
    vn.resize(9,1);

    i64 total = 9;
    for( int i = 2; i<= maxdig; ++i){
        find_non_bouncy_numbers(9, vn);
        total += accumulate(vn.begin(), vn.end(), 0LL);
    }
    vn.clear(); 
    vn.resize(10, 1);
    total += 10;
    for( int i = 2; i<= maxdig; ++i){
        find_non_bouncy_numbers(10, vn);
        total += accumulate(vn.begin(), vn.end(), 0LL);
    }
    printf("%lld\n", total-10*maxdig);
}
