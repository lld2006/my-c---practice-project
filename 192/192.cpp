#include <cstdio>
#include <cassert>
#include <cmath>
#include "../lib/int.h"
#include "../lib/typedef.h"
i64 n12 = 1000000000000LL;
i64 check_period(i64 num, i64 root, vector<int>& vroot)
{
    vroot.clear();
    //initialization nt
    i64 nt = root;//nt is the number in the numerator
    assert(root*root < num);
    //negative sign is not included
    i64 stop = root * 2;
    i64 q = root; // the integer part for each step
    vroot.push_back(root);
    i64 period = 0;
    i64 den = 1; //initialization of denominator 
    while(q != stop){
        assert((num - nt * nt) % den == 0);
        den = (num - nt * nt)/den;
        q = (root + nt)/ den;
        vroot.push_back(q);
        nt =  q * den - nt;
        ++period;
    }
    assert(period + 1 == static_cast<int>(vroot.size()));
    return period;
}

i64 get_best_approximation(int num)
{
    vector<int> v100;
    v100.resize(101, 0);
    v100.back()= 1;
    GeneralInteger n100(v100);
    int root = sqrt(num);
    if(root * root == num) return 0;
    i64 nt = root, den = 1;
    i64 h0 = 1, h1 = root;
    i64 k0 = 0, k1 = 1;
    i64 h2, k2;
    i64 q;
    I64Pair p0, p1;
    p0 = I64Pair(h1, k1);
    vector<int> vn;
    i64 val1, val2;
    while(true){
        den = (num - nt * nt)/den;
        q = (root + nt)/ den; // a1
        nt =  q * den - nt;
        h2 = h1*q+h0;
        k2 = k1*q+k0;
        p1 = I64Pair(h2, k2);
        vn.push_back(q);
        if(k2 > n12){
            i64 x = (n12 - k0)/k1;
            if(2*x>q){
                return x*k1+k0;
            }else if(2*x < q){
                return k1;
            }
            //equal case
            val1 = k1; //h1
            val2 = q/2*k1+k0; //h1*x/2+h0
            GeneralInteger n1(h1);
            GeneralInteger remainder(1);
            n1 = n1.multiply(n1);
            n1 = n1.multiply(n100);
            //n1 *= n1;
            //n1 *= n100;
            GeneralInteger d1(k1);
            d1 = d1.multiply(d1);
            //d1 *= d1;
            GeneralInteger q1(1), q2(1);
            q1 = n1.divide(d1, remainder); //

            GeneralInteger n2(h1*x+h0);
            //n2 *= n2;
            //n2 *= n100;
            n2 = n2.multiply(n2);
            n2 = n2.multiply(n100);
            GeneralInteger d2(val2);
            //d2 *= d2;
            d2 = d2.multiply(d2);
            q2 = n2.divide(d2, remainder);

            GeneralInteger ni(num);
            //ni *= n100;
            ni = ni.multiply(n100);
            GeneralInteger res1(1), res2(1);
            if(ni < q1) 
                res1 = q1.minus(ni);
            else
                res1 = ni.minus(q1);

            if(ni <q2)
                res2 = q2.minus(ni);
            else
                res2 = ni.minus(q2);
            
            if(res1 < res2) 
                return val1;
            else 
                return val2;
        }
        h0 = h1; k0 = k1;
        h1 = h2; k1 = k2;
    }
}
int main()
{
    i64 sum = 0;
    i64 val = 0;
    for(int i = 2; i<= 100000; ++i){
        val = get_best_approximation(i);//return the denominator of best approximation
        //if(i < 10)
        //    printf("%d %lld\n", i, val);
        sum += val;
    }
    printf("%lld\n", sum);
}
