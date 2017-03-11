#include <cstdio>
#include <cstdlib>
#include <vector>
#include "../lib/tools.h"
using namespace std;
//this problem is not that easy, it is about the ordered bell number.
//which is a weird sequence. The first thing I need to do is to find
//ordered bell number mod a prime p (A_n mod p), The equation needed here
//is A_n = sum_k=1^n C(n,k) A(n-k). 
//
//The key to solve this problem is that A(n) mod p is periodic
//
//if m-n ==0 mod (p-1) then A(m) -A(n) mod p ==0 where m and n >=1
//
//so if we view the sequence mod p it is:
//
//A(0), A(1), A(2), .... A(p), A(1), A(2), ..., A(p), so we need to 
//calculate all fubini numbers up to p, which means we need  C(n,k)
//where n le p
// note 1, binomial number mod prime: use the formula
// C(n, k) = C(n-1, k-1) + C(n, k)
void binomial_mod_p(vector<vector<i64>>& vb, i64 p)
{
    //p is not required to be a prime in this function.
    //but in this problem it is required.
    vb.clear();
    vb.resize(p+1);
    for(unsigned int i =0; i < vb.size(); ++i){
        vb[i].resize(i+1, 0);
    }
    vb[0][0] = 1;
    vb[1][0] = vb[1][1]= 1;
    for(unsigned int i = 2; i<=p; ++i){
        vb[i][0] = vb[i][i]=1;
        for(unsigned int j = 1; j < i; ++j){
            vb[i][j] = vb[i-1][j] + vb[i-1][j-1];
            vb[i][j] %= p;
        }
    }
}

//assuming fubini sequence B_0 == 1, if not all
//terms just multiply by the same factor
void create_fubini_mod_p(i64 p, vector<i64>& vf)
{
    vector<vector<i64>> vb;
    binomial_mod_p(vb, p);
    vf.resize(p+1); // 0---p
    vf[0] = 1;
    for(unsigned int i = 1; i < vf.size(); ++i){
        //printf("%d\n", i);
        i64 sum = 0;
        for(unsigned int j = 1; j <=i; ++j){
            sum += vb[i][j] * vf[i-j];
            sum %= p;
        }
        vf[i] = sum;
    }
}
//a0 = e-1 a_{-1}= 1 b0 = a0 - a{-1}, b is fubini sequence
// now realize c_n = b_n *n! = a_n n! -a_{n-1} n! = a1_n - n a1_{n-1}
// so the equations are 
//  c_n = a1_n - n a1_{n-1}
//  n*c_{n-1} = n *a1_{n-1} - n(n-1) a_n-2
//  so a1_n = c_n+ n*c_{n-1} +....+ n*(n-1)*...*(n-k+1) c_{n-k} 
//  where n-k mod p = 0;
//  so once we find out the mod is zero, we do not need to sum further
i64 get_An_modp(i64 p, i64 n)
{
    vector<i64> vf;
    create_fubini_mod_p(p, vf);
    int nres = n % p;
    i64 sum = 0;
    i64 product =  1; 
    for(int i = 0; i <= nres; ++i){
       i64 nt = nres -i; 
       int cIndex = (n-i-1) % (p-1)+1;// index is within 1--p
       sum += product * vf[cIndex];
       sum %= p;
       //update product
       product *= nt;
       product %= p;
    }
    return sum;
}

i64 chinese_remainder_theorem(const vector<i64>& vp, const vector<i64>& vr)
{
    i64 N = 1; 
    for(unsigned int i = 0; i < vp.size(); ++i)
        N*= vp[i];
    i64 sum = 0;
    for(unsigned int i = 0; i< vp.size(); ++i){
        i64 a =  N /vp[i];
        i64 b = vp[i];
        i64 x=1, y=1, gcd=1;
        extended_euclid(a, b, x, y, gcd);
        if((a *x ) % b != 1){
            assert(x < 0);
            x+=b;
            assert((a * x )% b == 1);
        }
        sum +=  vr[i] * a *x;
    }
    sum %= N;
    return sum;
}
int main(int argc, char** argv)
{
    //vector<i64> vp ={3,5,7};
    //vector<i64> vr ={2,3,2};
    //i64 rem = chinese_remainder_theorem(vp, vr);
    //printf("%lld\n", rem);
    i64 n = 1000000000LL;
    //n = 3;
    vector<i64> vp = {7, 11,73, 101, 137};
    vector<i64> vr;
    vr.resize(vp.size(), 0);
    for(unsigned int i = 0; i < vr.size(); ++i){
        vr[i] = get_An_modp(vp[i], n);
        printf("i=%lld, %lld\n",vp[i], vr[i]);
    }
    i64 result = chinese_remainder_theorem(vp, vr);
    printf("before sum %lld\n", result);
    result = 77777777 - result;
    printf("%lld\n", result);
}
