#include <vector>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include "../lib/tools.h"
#include <cassert>

int limit = 100000;
i64 total = 0;
//still kind of brute force, any better idea?

int calc_cnt(int a, int b, int t)
{
    int nhigh=0, nlow=0;
    int at = a * t;
    int bt = b * t;
    int s = a + b;
    if(bt % s == 0)
        nlow = bt/s;
    else
        nlow = bt/s+1;
    int cmax = at + bt - 1;
    if( cmax > limit -at - bt)
        cmax = limit -at -bt;
    nhigh = cmax/s;
    if(nhigh < nlow)
        return 0;
    else{ 
        //if((b<10 && a==1) ||(b<10 && a==b-1))
        //    printf("%d %d %d %d %lld\n", a, b, t, nhigh-nlow+1, total);
        return nhigh-nlow+1;
    }

}
int main()
{
    int cnt = 0;
    int abmax= limit*2/3; //a+b can not exceed this value
    int nlimit= limit*2/3; //a+b can not exceed this value
    int a = 0, b = 1, c = 1, d=nlimit;
    while( c <= nlimit){
        int k = (nlimit + b)/d;
        int a1 = a, b1 = b;  
        a = c; b = d;
        c = k*c-a1;
        d = k*d-b1;
        if(a+b < abmax){
            int tmax = abmax/(a+b);
            for(int t = 1; t <=tmax; ++t){
                int temp =  calc_cnt(a, b, t);
                total += temp;
            }
        }
    }
    printf("%lld\n", total+cnt);
    exit(1);
}
