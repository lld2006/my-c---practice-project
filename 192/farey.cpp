#include <cstdio>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include "../lib/typedef.h"
#include "../lib/int2.h"
//need to understand what is semiconvergent
i64 farey(i64 value, i64 limit)
{
    i64 na = 0, da = 1;
    i64 nb = 1, db = 1;
    i64 nnew, dnew;
    i64 iroot = sqrt(value);
    GeneralInteger g3(value);
    while(true){
       nnew = na + nb;
       dnew = da + db;
       if(dnew > limit) break;
       GeneralInteger gnn(nnew+iroot*dnew);
       GeneralInteger gnd(dnew);
       GeneralInteger g1 = gnn * gnn;
       GeneralInteger g2 = gnd * gnd;
       if(g1 < g2 * g3 ){
           na = nnew;
           da = dnew;
       }else{
           nb = nnew;
           db = dnew;
       }
    }
    GeneralInteger ga0(na+iroot*da); 
    GeneralInteger ga1(ga0*ga0);//na*na
    GeneralInteger gb0(da);
    GeneralInteger gb1(gb0*gb0); //da*da
    GeneralInteger gc0(nb+iroot*db);
    GeneralInteger gc1(gc0*gc0);//nb*nb
    GeneralInteger gd0(db);
    GeneralInteger gd1(gd0*gd0);//db*db
    if(((gb1*g3).minus(ga1))*gd1 < (gc1.minus(g3*gd1))*gb1){
        //printf("select b %lld %lld  %lld %lld\n", nb+iroot*db, db, na+iroot*da, da);
        assert(da < limit);
        return da;
    }else{
        //printf("select a %lld %lld %lld %lld\n", nb+iroot*db, db, na+iroot*da, da);
        assert(db < limit);
        return db;
    }
}
int main()
{
    i64 limit = 1e12;
    i64 sum = 0;
    assert(limit % 10000 == 0);
    printf("69 limit %lld\n",farey(4850, limit));
    printf("%lld\n",farey(13, 30));
    //exit(1);
    for(int i = 2; i<= 100000; ++i){
        if(i % 1000 == 0)
            printf("%d\n",i);
        double droot = sqrt(i);
        int iroot = round(droot);
        if(iroot * iroot == i) continue;

        i64 den = farey(i, limit);
        if(i < 10) 
            printf("%d %lld\n",i, den);
        sum += den;
    }
    printf("%lld\n", sum);
}
