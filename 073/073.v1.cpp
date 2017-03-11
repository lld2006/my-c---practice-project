#include "../lib/typedef.h"
#include <cstdio>
//this is a stupid method, daniel's material is very useful
//1/3 n/d ....1/2
//n*3-d=1 //3-2=1
//so (n-1)*3 = d- 2 // ====n = 1+ k d = 2 + 3*k=====
//now I understood this algorithm!
int main()
{
    int nlimit = 12000;
    int ka = (nlimit - 2)/3;
    int a=1, b=3, c=ka+1, d=3*ka+2;
    int k=0;
    i64 cnt = 1;

    while(( c <= nlimit) ){
        k = (nlimit + b) / d;
        int a1 = a, b1 = b;  
        a = c; b = d;
        c = k*c-a1;
        d = k*d-b1;
        if(c == 1) break;
        ++cnt;
    }
    printf("%lld\n", cnt);
}
