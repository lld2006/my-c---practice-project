//equation to be solved is x^2 - ny^2=1
// p q is the basic solution, 
// generate up to the nth solution(input)
// solution will be provided int xi and yi
#include <cstdio>
#include <cassert>
#include <set>
#include "../lib/typedef.h"
void pell_type1(i64 n, i64 p, i64 q, int nth, vector<i64>& xs, vector<i64>& ys)
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
//equation to be solved is x^2 - ny^2=-1
// p q is the basic solution
void pell_type2(i64 n, i64 p, i64 q, int nth, vector<i64>& xs, vector<i64>& ys)
{
    xs.clear();
    ys.clear();
    assert(p*p-n*q*q==-1);
    int cnt = 0;
    i64 pm = p*p+q*q*n;//p multiplier
    i64 qm = 2*p*q;    //q multiplier
    i64 ap = p, aq=q;
    while(cnt < nth){
        ++cnt;
        xs.push_back(ap);
        ys.push_back(aq);
        i64 apnew = ap*pm+aq*qm*n;
        i64 aqnew = ap*qm+aq*pm;
        assert(apnew >ap);// overflow check
        assert(aqnew >aq);
        ap= apnew;
        aq= aqnew;
    }
}
int main()
{
    set<i64> sol_set;
    vector<i64> xs, ys;
    pell_type1(8, 3, 1, 12, xs, ys);
    //solution 1 1
    for(unsigned int i = 0; i <xs.size(); ++i){
        i64 y = xs[i]*xs[i]+2*xs[i]*ys[i]+8*ys[i]*ys[i];
        sol_set.insert(y-1);
        y = xs[i]*xs[i]-2*xs[i]*ys[i]+8*ys[i]*ys[i];
        sol_set.insert(y-1);
    }
    //another sol 5 2
    for(unsigned int i = 0; i <xs.size(); ++i){
        i64 y = 2*xs[i]*xs[i]+10*xs[i]*ys[i]+16*ys[i]*ys[i];
        sol_set.insert(y-1);
        y =2*xs[i]*xs[i]-10*xs[i]*ys[i]+16*ys[i]*ys[i];
        sol_set.insert(y-1);
    }
    //p=181 q=64
    for(unsigned int i = 0; i <xs.size(); ++i){
        i64 y = 64*xs[i]*xs[i]+2*181*xs[i]*ys[i]+512*ys[i]*ys[i];
        sol_set.insert(y-1);
        y =64*xs[i]*xs[i]-2*181*xs[i]*ys[i]+512*ys[i]*ys[i];
        sol_set.insert(y-1);
    }
    i64 sum = 0;
    set<i64>::iterator iter= sol_set.begin();
    for(unsigned int i = 0; i < 40; ++i, ++iter){
        //printf("%lld\n", *iter);
        sum += *iter;
    }
    printf("summation is %lld\n", sum);
}
