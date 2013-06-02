#include <cstdio>
#include <cmath>
#include <cassert>
#include "../lib/typedef.h"
#include "../lib/tools.h"

// current best method with the following parmeterization(PE).
// c with 60 x-y=3n, non primitive, scale by 3
// otherwise primitive
// a = x^2 + 2*xy   b = y^2 + 2*xy   c = x^2 + y^2 + xy
int main()
{
    int limit = 1053779;
    //limit = 10000000;
    double r32 = 2/sqrt(3.0);
    i64 total = 0;
    r32 *= limit;
    int zmax = r32;
    int z3 = 3* r32;
    for(i64 x = 1; x<= z3 ; ++x){
        int ymax = z3/x;
        for(i64 y=x+1; y <= ymax; ++y){
            int nxy = x*y;
            if((x-y)%3 !=0){
                if(x< zmax && nxy <=zmax){ 
                    if(gcd(x, y) != 1) continue;
                    total += r32/(nxy);
                }
            }else{
                if(gcd(x, y) != 1) continue;
                i64 n0 = 3*r32/(nxy);
                total += n0;
            }
        }
    }
    printf("zmax %d z3 %d answer=%lld\n",zmax, z3, total);
}

