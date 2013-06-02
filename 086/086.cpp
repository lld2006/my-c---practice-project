#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/typedef.h"
#include "../lib/tools.h"
using namespace std;
int count(int a, int b, int nmax)
{
    int total = 0;
    if(a > b) swap(a, b);
    // a < b
    if(a & 1){ // a odd b even
        int dmax = nmax/b;
        //split from odd side, odd side small
        assert((b & 1 )== 0);
        //multiple of a odd
        int start = a/2;
        int nd = (dmax + 1)/2;
        int diff = a;
        total += nd * start + nd*(nd-1)/2*diff;

        //multiple of a even
        start = a;
        nd = dmax/2;
        diff = a;
        total += nd * start + nd*(nd-1)/2*diff;


        //forget that it is possible that b > nmax, 
        //but split still OK.
        
        // split from the even side
        dmax = nmax/a;
        diff = a - b/2;
        start = diff + 1;
        if(start <= 0 ) 
            return total;
        nd = dmax;
        total += nd*start +diff*nd*(nd-1)/2;

    }else{ // b odd a even
        int dmax = nmax/b;
        //consider even a
        int start = a/2;
        int nd = dmax;
        int diff = a/2;
        total += nd*start +diff*nd*(nd-1)/2;
        
        //consider odd multiple of b
        dmax = nmax/a;
        if(2*a-b <0) return total;
        start = a - (b+1)/2 + 1;
        diff = 2*a-b;
        nd = (dmax+1)/2;
        total += nd*start +diff*nd*(nd-1)/2;

        nd = dmax/2;
        start = 2*a-b+1;
        diff = 2*a-b;
        total += nd*start +diff*nd*(nd-1)/2;
        
    }
    return total;
}

int paircount(int nmax, vector<IntPair>& vp)
{
    int total = 0;
    for(unsigned int i = 0; i< vp.size(); ++i){
        int value = count(vp[i].first, vp[i].second, nmax);
        total += value;
        assert(value >= 0);
        //if(value)
        //printf("%d %d %d\n", vp[i].first, vp[i].second, value);
    }
    return total;
}
int binary_search_n( vector<IntPair>& vp)
{
    int low = 10;
    int high= 4000;
    int target = 1000000;
    while(low < high){
        int mid = (low+high)/2;
        int cmid = paircount(mid, vp);
        if(cmid > target){
            high = mid;
        }else{
            low = mid+1;
        }
    }
    return low;

}
int main()
{
    vector<IntPair> vp;
    int limit = 5000;
    for( int m = 1; m < 100; ++m ){
        for(int n = m+1; n < 100; n+=2){
            if(gcd(m, n) != 1) continue;
            int a = n*n -m*m;
            int b = 2*m*n;
            if(a > limit || b > limit)
                continue;
            if(a < b)
                vp.push_back(IntPair(a, b));
            else
                vp.push_back(IntPair(b, a));
        }
    }
    //printf("%d \n", paircount(100, vp) );
    printf("%d \n", binary_search_n(vp) );
}
