#http://mathafou.free.fr/themes_en/kpell.html
//still not quite clear in this page
#include <cstdio>
#include "../lib/typedef.h"
#include <cassert>
#include "../lib/int.h"
#include <cmath>
#include "../lib/tools.h"
//after a lot of thought, I believe this is a pell's equation problem
//I am so stupid that I did not figure it out earlier.
//now I am still missing a solution of x^2-Dy^2=q^2

//need to figure out the basic equation of p q for all solution
/*
void pell_type1(i64 n, i64 p, i64 q, i64 nmax, vector<i64>& xs, vector<i64>& ys)
{
    xs.clear();
    ys.clear();
    assert(p*p-n*q*q==1);
    //the solution is a=(p+sqrt(n)q)^k b=(p-sqrt(n)q)^k
    //x = (a+b)/2 y = (a-b)/2
    i64 ap = p, aq=q; //bp ==ap; bq = -aq; 
    int cnt = 0;
    while(cnt < nth){
        ++cnt;
        xs.push_back(ap);
        ys.push_back(aq);
        i64 apnew = ap*p+aq*q*n;
        i64 aqnew = ap*q+aq*p;
        assert(apnew >ap);// overflow check
        assert(aqnew >aq);
        ap= apnew;
        aq= aqnew;
    }
}
*/
//i64 pqaOld(i64 num, i64 root, vector<int>& vroot)
//{
//    vroot.clear();
//    //initialization nt
//    i64 nt = root;//nt is the number in the numerator
//    assert(root*root < num);
//    //negative sign is not included
//    i64 stop = root * 2;
//    i64 q = root; // the integer part for each step
//    vroot.push_back(root);
//    i64 period = 0;
//    i64 den = 1; //initialization of denominator 
//    while(q != stop){
//        assert((num - nt * nt) % den == 0);
//        den = (num - nt * nt)/den;
//        q = (root + nt)/ den;
//        vroot.push_back(q);
//        nt =  q * den - nt;
//        ++period;
//    }
//    assert(period + 1 == static_cast<int>(vroot.size()));
//    return period;
//}
//==============================================================
i64 nmax = 1000000;
vector<int> ftable;
void pqa(i64 D, i64 N, vector<i64>& vx, vector<i64>& vy);
void generate_all_divisors(unsigned int level, int prod, const IntPairVec& vpairs, vector<i64>& vd)
{
    if(level == vpairs.size()){
        vd.push_back(prod);
        return;
    }
    int px = vpairs[level].first;
    int pw = vpairs[level].second;
    int tp = 1;
    int prod1 = prod;
    for( int j = 0; j <= pw; ++j){
        generate_all_divisors(level+1, prod1, vpairs, vd);
        tp *= px;
        prod1 = prod * tp;
    }
    return;
}
//TODO the following function is not for general purpose
void find_all_squares_of_N(i64 N, vector<i64>& divisors, vector<int>& ftable){
    i64 root = sqrt(N);
    assert(root *root ==N);//this is for problem 390 only, will try to improve LMM later
    IntPairVec ifac;
    factor_using_table(root, ifac, ftable);
    generate_all_divisors(0, 1, ifac, divisors);
}

void pqav2(i64 D, i64 N, i64 z, i64 m, i64 r, i64 s, vector<i64>& vx, vector<i64>& vy) //for LMM algo only
{
    vx.clear(); vy.clear();
    //r s are prim solution for x^2 - dy^2 == -1
    i64 u=z, v=m, a=0;
    i64 x, y, x1=v, y1=0, x0=-u, y0=1;
    i64 p2, p1=1, p0=0;
    i64 root = sqrt(D);
    if(root*root==D){
        x=0, y=0;
        printf("square ERROR in solving pell equation\n");
        return;
    }
    assert(root*root < D);
    int count = 0;
    i64 stop = 2 * root;
    while(stop != a){//periodic
        a = (u+root)/v;
        u = (a*v-u);
        assert((D-u*u) % v == 0);
        v = (D-u*u)/v;
        if(v==1 && count > 0){
            assert(x <= nmax);
            vx.push_back(x1);
            vy.push_back(y1);
        }else if(v==-1 && count > 0){
            i64 xt = x1*r+y1*s*D;
            i64 yt = x1*s+y1*r;
            if(xt > nmax) break;
            vx.push_back(xt);
            vy.push_back(yt);
        }
        x=a*x1+x0;
        y=a*y1+y0;
        if(x > nmax) break;
        p2=a*p1+p0;
        x0 = x1; y0=y1;
        x1 = x; y1=y;
        p0=p1;p1=p2;
        ++count;
    }
    return;
}
void LMM_Solve(i64 D, i64 N, vector<i64>& vx, vector<i64>& vy)
{
    vector<i64> vn;
    vector<i64> vx1, vy1;
    i64 r, s;
    find_all_squares_of_N(N>0? N:-N, vn, ftable);
    
    //to create primitive solutions of x^2 - dy^2==-1
    pqa(D, -1, vx1, vy1);
    assert(vx1.size() <= 1);
    if(vx1.size() == 0){
        r = 0; s = 0;
    }else{
        r = vx1[0]; s = vy1[0];
    }
    vx.clear(); vy.clear();

    for(unsigned int i = 0; i<vn.size(); ++i){
        i64 f = vn[i];
        i64 m = N/(f*f);
        i64 mp = std::abs(m);
        i64 m2 = mp/2;
        vector<i64> vz;
        i64 residue = 1; //TODO this is special case for this problem
        vector<i64> vxt, vyt;
        for(i64 z=-m2; z<= m2; ++z){
            i64 z2 = z * z;
            z2 %= mp;
            if(z2 != residue) continue;
            pqav2(D, N, z, mp, r, s, vxt, vyt);
            for(unsigned int i = 0; i < vxt.size(); ++i){
                vx.push_back(vxt[i]);
                vy.push_back(vyt[i]);
            }
        }
    }
}


//this is for N^2 < D
//please notice that if N!=1,-1, it may have multiple fundamental solutions
void pqa(i64 D, i64 N, vector<i64>& vx, vector<i64>& vy)
{
    i64 u=0, v=1, a=0;
    i64 x, y, x1=v, y1=0, x0=-u, y0=1;
    i64 p2, p1=1, p0=0;
    i64 root = sqrt(D);
    if(root*root==D){
        x=0, y=0;
        printf("square ERROR in solving pell equation\n");
        return;
    }
    assert(root*root < D);
    int count = 0;
    i64 stop = 2 * root;
    while(stop != a){//periodic
        ++count;
        a = (u+root)/v;
        u = (a*v-u);
        assert((D-u*u) % v == 0);
        v = (D-u*u)/v;
        x=a*x1+x0;
        y=a*y1+y0;
        if(x > nmax) break;
        p2=a*p1+p0;
        x0 = x1; y0=y1;
        x1 = x; y1=y;
        p0=p1;p1=p2;
        bool odd = count & 1;
        i64 vt = odd? -v:v;
        if(( N>0 && vt < 0) || (N <0 && vt > 0))
            continue;
        if(N%vt)continue;
        i64 m = N/vt;
        i64 mr = sqrt(m);
        if(mr*mr==m){//N = mr*mr*v, fund solution
            vx.push_back(mr*x);
            vy.push_back(mr*y);
        }
    }
    return;
}
void max_dig_pell(int num, vector<int>& vroot, i64& p, i64& q)
{
    GeneralInteger p0(vroot[0]);
    GeneralInteger q0(1);
    GeneralInteger p1(vroot[0]*vroot[1]+1);
    GeneralInteger q1(vroot[1]);
    GeneralInteger p2(1);
    GeneralInteger q2(1);

    vroot.erase(vroot.begin());
    int vsize = vroot.size();
    int r = vsize - 1;
    int start = 2;
    int final = (r & 1)? r: 2*r+1;
    for(int s = start; s <= final; ++s){
        int idx = (s-1)%vsize;
        int value = vroot[idx];
        p2 = p1.multiply(value) + p0;
        q2 = q1.multiply(value) + q0;
        p0 = p1; q0 = q1; 
        p1 = p2; q1 = q2;
    }
    if(p1.numberDigit() < 10){
        p = p1.to_i64();
        q = q1.to_i64();
    }else{
        p=0;
        q=0;
    }
}

bool fundSol(i64 n, i64& p, i64& q)
{
    p=0; q=0;
    i64 root = sqrt(n);
    if(root*root == n) {
        assert(0); //only for this problem !!!!
        return false; //actually this cannot be true in  this problem, but still 
    }
    //it is a not bad thing to do this check
    vector<int> vroot;
    //pqa(n, root, vroot);
    max_dig_pell(n, vroot, p, q);
    return true;
}


int main()
{
    vector<i64> vx, vy;
    factor_table_min(5000, ftable);
    LMM_Solve(65, 16, vx, vy);
    for(unsigned int i = 0; i< vx.size(); ++i){
        printf("fundamental solution %lld %lld\n",vx[i], vy[i]);
    }
    return 0;
    vector<i64> vxn, vyn;
    i64 area = 0;;
    for(unsigned int i = 1; i< 500; ++i){
        i64 p=0, q=0;
        i64 n = 1+4*i*i;
        if(fundSol(n, p, q)){
            printf("fundamental solutions %lld %lld %lld\n",n, p, q);
            i64 ap = p, aq=q; //bp ==ap; bq = -aq; 
            while(ap*i <= nmax){
                assert(ap*ap-n*aq*aq==1);
                area += ap*i;
                printf("%lld %lld %lld\n", i*2LL, aq*i*2, ap*i*2);
                i64 apnew = ap*p+aq*q*n;
                i64 aqnew = ap*q+aq*p;
                assert(apnew >ap);// overflow check
                assert(aqnew >aq);
                ap= apnew;
                aq= aqnew;
            }
        }
    }
    printf("%lld\n", area);
}
