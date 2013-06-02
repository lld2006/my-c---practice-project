#include <set>
#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;
int gcd(int ia, int ib){
    if (ia >= ib) return gcd ( ib, ia);
    // ia < ib;
    while (ia){
        int res = ib % ia;
        ib = ia;
        ia = res;
    }
    return ib;
}
int main()
{
    int limit =  1500000;
    set<int> flags;
    vector<int> fvec;
    fvec.resize( limit + 1, 0);
    for(int a=2; a<= 866; ++a)//866
        for(int b =1; b< a; ++b){
            int ia  = a*a - b*b;
            int ib = 2*a*b;
            int ic = a*a +b*b;
            int len = ia + ib + ic;
            //if( ia > ib ) continue;
            if(len > limit) continue;
            if(gcd(ia, ib) > 1) continue;
            flags.insert(len);
            ++fvec[len];
        }
    for(set<int>::reverse_iterator iter=flags.rbegin(); iter != flags.rend(); ++iter){
        const int ni = *iter;
        assert(fvec[ni] > 0);
        int num = 2 * ni;
        while(num < limit){
            fvec[num] += fvec[ni];
            num += ni;
        }
    }
    int num = count( fvec.begin(), fvec.end(), 1);
    printf("%d\n", num);
}
