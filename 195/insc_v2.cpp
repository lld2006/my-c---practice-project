#include <cstdio>
#include <cmath>
#include <cassert>
#include "../lib/typedef.h"
#include "../lib/tools.h"
// current best method with the following parmeterization(PE).
// c with 60 x-y=3n, non primitive, scale by 3
// other wise primitive
// a = x2 + 2*xy   b = y2 + 2*xy   c = x2 + y2 + xy
// maybe we can put in one loop to save some gcd
int main()
{
    int limit = 1053779;
    double r32 = 2/sqrt(3.0);
    //first consider case 1 1 1;
    i64 total = 0;
    //bool found = true;
    int zmax = limit* r32;
    int z3 = 3*limit* r32;
    for(i64 x = 1; x< zmax; ++x){
        for(i64 y= x+1; y <= zmax/x; ++y){
            if(gcd(x, y) != 1) continue;
            if((x-y) %3 == 0) continue; 
            i64 n0 = limit*r32/(x*y);
            total += n0;
        }
    }
    for(i64 x = 1; x<= z3 ; ++x){
        for(i64 y=x+1; y <= z3/x; ++y){
            if(gcd(x, y) != 1) continue;
            if((x-y) %3 != 0) continue; 
            i64 n0 = 3*limit*r32/(x*y);
            total += n0;
        }
    }
    printf("%lld\n", total);
}
