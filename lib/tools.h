#include <vector>
#include <cmath>
#include <cassert>
#include "typedef.h"
#ifndef TOOLS_H
#define TOOLS_H
using namespace std;
void primeWithin( vector<int>& vecr, int limit);
bool isPrime( i64 i );
bool isPrime(u64 num, vector<int>& primes);
//this is a costly factorization method, but if we 
//do not need to factor a lot of numbers it is OK.
void factor(i64 num, I64PairVec& ifac, const vector<int>& primes);
void factor_using_table(i64 num, IntPairVec& ifac, const vector<int>& ftable);
bool next_combination(IntVec& cvec, int n, int k);
bool isPermutation(i64 im, i64 in);
bool isPalindromic(i64 num, int base);
int binary_find(int num, vector<int>& vec);
void extended_euclid(i64 a, i64 b, i64& x, i64& y, i64& gcd);
i64 pollard_rho(i64 n, int n0, int debug);
bool miller_rabin(i64 xn, unsigned int nsampling);
i64 product_mod(i64 n1, i64 n2, i64 mod);
//i64 powermodule2(i64 base, i64 expo, i64 module);
void kara_mult(int nsize, int* a, int* b, int* ret);
inline int index0(int dim, int i, int j) { return i*dim+j;}
inline int index3o(i64 i, i64 j, i64 k) 
{ 
    assert(i <= j && j <= k);
    return (k+1)*(k+2)*k/6+(j+1)*j/2+i;
}
void factor_table_min( int nmax, vector<int>& ftable);
void factor_table_max( int nmax, vector<int>& ftable);
bool tonelli_shank(i64 prime, i64 residue, i64& sol); 
bool strong_pseudo_test(i64 p);
i64 mult64mod(u64 a, u64 b, u64 mod);
i64 powermodule(i64 base, i64 expo, i64 module);
i64 totient(int n, vector<int>& primes);
i64 totient_with_factor(IntPairVec& vp);
void farey_sequence(vector<IntPair>& vf, int nlimit, bool ascending);
void prime_generate_sq2(i64 p, int& a, int& b);

class DisJointSet{
   public:
      DisJointSet()
      {
          p = 0;
          value = -1;
          rank = 0;
          nsize = 0;
      }
      void makeset(int vx)
      {
          p = this;
          value = vx;
          rank = 0;
          nsize = 1;
      }
      int get_value(){return value;}

      DisJointSet* find_set()
      {
        if(this != (this->p)){
            this->p = (this->p)->find_set();
        }
        return this->p;
      }

      void union_set(DisJointSet& y)
      {
            return link_set(find_set(), y.find_set());
      }
      void link_set(DisJointSet* x, DisJointSet* y)
      {
        if( x == y)
            return;
        if(x->rank > y->rank){
            y->p = x;
            x->nsize += y->nsize;
        }
        else{
            x->p = y;
            y->nsize += x->nsize;
            if(x->rank == y->rank)
                ++(y->rank);
        }
      }
      int set_size(){
          if(this->p == this->p->p){
              this->nsize = this->p->nsize;
          }
          else
              this->nsize = (this->p)->set_size();

          return this->nsize;
      }
      DisJointSet* parent()
      {
          return p;
      }
   private:
     DisJointSet* p;
     int value;
     int rank;
     int nsize;
};


template <typename itype>
u64 power(itype base, itype npow)
{
    u64 ret = 1;
    itype ibase = base;
    while(npow){
        int remainder = npow & 1;
        if(remainder){
            --npow;
            ret *= ibase;
        }else{
            npow/=2;
            ibase *= ibase;
        }
    }
    return ret;
}



template <typename itype> 
bool isPerfectSquare(itype num){
    double val = sqrt(static_cast<double>(num));
    itype root = round(val);
    if(root*root == num)
        return true;
    return false;
}

template <typename itype>
itype combination(itype n, itype m){
    if(m == 0) return 1;
    if( m > n/2) m = n-m;
    itype prod = 1;
    itype div = 1;
    for(itype i = n; i> n-m; --i)
        prod *= i;
    for(itype i = 2; i<= m; ++i)
        div *= i;
    return prod / div;
}

// template functions
// gcd function from PE, Robert_Gerbicz!
template <typename itype> 
itype gcd(itype a, itype b)
//int gcd(int a,int b)
{
  itype c;
 
  while(b>0)  {
     if(a>=b)  {
        a-=b;
        if(a>=b)  {
           a-=b;
           if(a>=b)  {
              a-=b;
              if(a>=b)  {
                 a-=b;
                 if(a>=b)  {
                    a-=b;
                    if(a>=b)  {
                       a-=b;
                       if(a>=b)  {
                          a-=b;
                          if(a>=b)  {
                             a-=b;
                             if(a>=b)  a%=b;
              }}}}}}}}
     c=a,a=b,b=c;
  }
  return a;
}

// now it is time to find some smart way to represent two dimensional ordered 
// array and three dimension ordered array where x <= y or x<=y<=z;
// for two dimensional x<=y the position of (i, j) is (j+1)*j/2+i, and the total 
// size needed is (j+1)*(j+2)/2
// for three dimensional x<=y<=z, the position of (i, j, k) is k*(k+1)*(k+2)/6+j*(j+1)/2+i 
// the total size needed is(k+1)*(k+2)*(k+3)/6

#endif
