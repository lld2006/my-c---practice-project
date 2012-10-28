#include <vector>
#include <cmath>
#include "typedef.h"
#ifndef TOOLS_H
#define TOOLS_H
using namespace std;
void primeWithin( vector<int>& vecr, int limit);
bool isPrime( i64 i );
bool isPrime(u64 num, vector<int>& primes);
void factor(i64 num, I64PairVec& ifac, const vector<int>& prime);
bool next_combination(IntVec& cvec, int n, int k);
bool isPermutation(int im, int in);
bool isPalindromic(i64 num, int base);
int binary_find(int num, vector<int>& vec);
void extended_euclid(i64 a, i64 b, i64& x, i64& y, i64& gcd);
i64 pollard_rho(i64 n, int n0, int debug);
bool miller_rabin(i64 xn, unsigned int nsampling);
i64 product_mod(i64 n1, i64 n2, i64 mod);
i64 powermodule2(i64 base, i64 expo, i64 module);
void kara_mult(int nsize, int* a, int* b, int* ret);
inline int index0(int dim, int i, int j) { return i*dim+j;}
void factor_table_min( int nmax, vector<int>& ftable);
void factor_table_max( int nmax, vector<int>& ftable);
bool tonelli_shank(i64 prime, i64 residue, i64& sol); 
bool strong_pseudo_test(i64 p);
i64 mult64mod(u64 a, u64 b, u64 mod);
i64 powermodule(i64 base, i64 expo, i64 module);
void farey_sequence(vector<IntPair>& vf, int nlimit, bool ascending);


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

// template functions
template <typename itype> 
itype gcd(itype ia, itype ib){
    if (ia > ib) swap(ia, ib);
    // ia < ib;
    while (ia){
        itype res = ib % ia;
        ib = ia;
        ia = res;
    }
    return ib;
}

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
    for(itype i = 1; i<= m; ++i)
        div *= i;
    return prod / div;
}
#endif
