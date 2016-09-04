#include <cstdio>
#include <vector>
#include <set>
#include <cassert>
#include "../lib/tools.h"
#include "../lib/typedef.h"
using namespace std;
//lesson, why did not I group those 3 similar groups together?! 
//too stupid on such an easy problem!
vector<int> va, vb, multa, multb, ma, mb;
set<i64> ratioset;
int cnt = 0;
void search_level(int level, int da_left, int db_left, const int da, const int db, bool& found)
{
    if(found) return;
    if(level == 2){
        //check if we can find any result
        int ta = da * multa[level];
        int tb = db * multb[level];
        int tg = gcd(ta, tb);
        ta /= tg;
        tb /= tg;
        if(da_left > va[2] || db_left > vb[2]) return;
        if( tb > da_left || ta > db_left)
            return;
        if ( tb > 1312 || ta > 1888) 
            return;
        if(da_left % tb != 0 ) return;
        if(db_left % ta != 0 ) return;
        if(da_left * ta != db_left*tb) return;
        int a1 = da *246;
        int b1 = db*295;
        int gab = gcd(a1, b1);
        a1/=gab;
        b1/=gab;
        i64 result = a1 * 100000000LL + b1;
        double dr=(double) a1/b1;
        if(ratioset.find(result)==ratioset.end()){
            ratioset.insert(result);
            ++cnt;
            if(dr > 2.0)
            printf("final cnt=%d da=%d db=%d %d %d %30.20f\n",cnt,da, db,a1, b1,dr  );
        }
        found = true;
        return;
    }
    int ta = da * multa[level];
    int tb = db * multb[level];
    int tg = gcd(ta, tb);
    assert(ta % tg == 0);
    assert(tb % tg == 0);
    ta /= tg;
    tb /= tg;
    int na = min(da_left, va[level])/tb;
    int nb = min(db_left, vb[level])/ta;
    int nmax = min(na, nb);
    int la, lb;
    for(int j = 1; j <= nmax; ++j){
        ma[level] = j * tb;
        mb[level] = j * ta;        
        la = da_left - ma[level];
        lb = db_left - mb[level];
        search_level(level+1, la, lb, da, db, found);
        if(found) break;
    }
    return;

}
int main()
{
    int da, db;
    int da_total=18880;
    int db_total=15744;
    int dbmax;
    va.push_back(5248);
    vb.push_back(640);

    va.push_back(5760);
    vb.push_back(3776);

    va.push_back(7872);
    vb.push_back(11328);

    multa.push_back(6);
    multb.push_back(59);

    multa.push_back(41);
    multb.push_back(75);

    multa.push_back(6);
    multb.push_back(5);

    ma.resize(3);
    mb.resize(3);

    bool found = false;
    //da_total = 6720;
    for(da=da_total; da>0; --da){
        if(da %295 == 0)
            dbmax =da/295*246-1;//since m is greater than 1,no equal.
        else
            dbmax = da*246/295;
            //if(da % 100 == 0)
            //    printf("%d\n", da);
        for(db = 1; db <= dbmax; ++db){
            found = false;
            search_level(0, da, db, da, db, found);
        }
    }
}
