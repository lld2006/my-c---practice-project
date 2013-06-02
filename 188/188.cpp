#include "../lib/tools.h"
#include <cstdio>
//pp is power of p
i64 hexmod(int base, int pow, i64 nmod)
{
    if(nmod == 1){
        return 0;
    }
    i64 nmod1 = nmod;
    if(nmod %2 == 0)
        nmod/=2;
    if(nmod % 5 == 0)
        nmod= nmod/5*4;
    int ret = hexmod(base, pow-1, nmod);
    ret %= nmod;
    return powermodule(base, ret, nmod1);
}
int main()
{
    int a5 = hexmod(1777, 1855, 100000000);
    printf("%d \n",  a5);
}
