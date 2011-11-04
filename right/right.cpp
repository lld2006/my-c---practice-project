#include <cstdio>
#include <cassert>
#include <numeric>
#include "../lib/primelist.h"

int main()
{
    int max = 50;
    int count = 3* max *max;
    for(int m = 1; m<=max; ++m)
        for(int n = 1; n <=max; ++n){
            int gc = gcd(m, n);
            int rc = m *m+n * n;
            assert(rc % gc == 0); 
            
            //if(rc % gc ) continue;  //must divide right hand side
            //
            // need to first reduce the m n by gcd(m, n) and 
            // gcd must divide (m^2+n^2)
            //start from (m, n) the perpendicular equation 
            //is mx + ny = m^2+n^2  
            //in x direction (n , -m) 
            //in y direction (-n, m )
            int gm = m/ gc;
            int gn = n/ gc;
            int sx = min<int>((max - m)/ gn, n/gm);
            int sy = min<int>(m/gn, (max-n)/gm);
            count += (sx+sy);
        }
    printf("%d\n", count);
}
