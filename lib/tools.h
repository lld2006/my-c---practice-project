#include "typedef.h"
#include <cassert>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <vector>

#ifndef TOOLS_H
#define TOOLS_H
// TODO FFT for two polynomial multiplication

using namespace std;
// it is very slow to see if p divides into num.
bool isPrime(u64 num, vector<int> &primes);
void factor_using_table(i64 num, IntPairVec &ifac, const vector<int> &ftable);
void factor_using_table_odd(i64 num, IntPairVec &ifac,
                            const vector<int> &ftable);
bool next_combination(IntVec &cvec, int n, int k);
bool isPermutation(i64 im, i64 in);
bool isPalindromic(i64 num, int base);
int binary_find(int num, vector<int> &vec);
void extended_euclid(i64 a, i64 b, i64 &x, i64 &y, i64 &gcd);
void extended_euclid2(i64 a, i64 b, i64 &x, i64 &y, i64 &gcd);
void xgcd(const i64 p, const i64 q, i64 &gcd, i64 &pcoeff, i64 &qcoeff);
i64 pollard_rho(i64 n, int n0, int debug);
bool miller_rabin(i64 xn, unsigned int nsampling);
// not good for very large numbers, prefer < 1e9
i64 product_mod(i64 n1, i64 n2, i64 mod);
i64 product_mod_new(i64 n1, i64 n2, i64 mod);
inline int index0(int dim, int i, int j) { return i * dim + j; }
inline int index3o(i64 i, i64 j, i64 k) {
  assert(i <= j && j <= k);
  return (k + 1) * (k + 2) * k / 6 + (j + 1) * j / 2 + i;
}
void factor_table_min(int nmax, vector<int> &ftable);
void factor_table_min_odd(int nmax, vector<int> &ftable);
void factor_table_max(int nmax, vector<int> &ftable);
// quadratic mod equation solve
bool tonelli_shank(i64 prime, i64 residue, i64 &sol);
int jacobi(int a, int m);
bool strong_pseudo_test(i64 p);
i64 mult64mod(i64 a, i64 b, i64 mod);
i64 powermodule(i64 base, i64 expo, i64 module);
void farey_sequence(vector<IntPair> &vf, int nlimit, bool ascending);
i64 chinese_remainder_theorem(const vector<i64> &vp, const vector<i64> &vr);
int find_multiplicative_order(i64 nbase, i64 prime, int power,
                              const vector<int> &vfac);

vector<i64> matrix_multiplication(const vector<i64> &A, const vector<i64> &B,
                                  i64 nmod, int dim);
vector<i64> matrix_power(vector<i64> A, i64 np, i64 nmod, int dim);

void prime_generate_sq2(i64 p, int &a, int &b);
double gettime();
struct timer {
  clock_t t;
  timer() { t = clock(); }
  ~timer() { printf("runtime %.6f secs\n", getTime()); }
  double getTime() {
    return ((double)clock() - (double)t) / (double)CLOCKS_PER_SEC;
  }
};

class DisJointSet {
public:
  DisJointSet() {
    p = 0;
    value = -1;
    rank = 0;
    nsize = 0;
  }
  void makeset(int vx) {
    p = this;
    value = vx;
    rank = 0;
    nsize = 1;
  }
  int get_value() { return value; }

  DisJointSet *find_set() {
    if (this != (this->p)) {
      this->p = (this->p)->find_set();
    }
    return this->p;
  }

  void union_set(DisJointSet &y) { return link_set(find_set(), y.find_set()); }
  void link_set(DisJointSet *x, DisJointSet *y) {
    if (x == y)
      return;
    if (x->rank > y->rank) {
      y->p = x;
      x->nsize += y->nsize;
    } else {
      x->p = y;
      y->nsize += x->nsize;
      if (x->rank == y->rank)
        ++(y->rank);
    }
  }
  int set_size() {
    if (this->p == this->p->p) {
      this->nsize = this->p->nsize;
    } else
      this->nsize = (this->p)->set_size();

    return this->nsize;
  }
  DisJointSet *parent() { return p; }

private:
  DisJointSet *p;
  int value;
  int rank;
  int nsize;
};

template <typename itype> u64 powerold(itype base, itype npow) {
  if (npow == 1)
    return base;
  u64 ret = 1;
  itype ibase = base;
  while (npow) {
    int remainder = npow & 1;
    if (remainder) {
      --npow;
      ret *= ibase;
    } else {
      npow /= 2;
      ibase *= ibase;
    }
  }
  return ret;
}

template <typename itype> u64 power(itype base, itype npow) {
  if (npow == 1)
    return base;
  u64 ret = 1;
  itype ibase = base;
  while (npow) {
    if (npow & 1) {
      ret *= ibase;
    }
    npow >>= 1;
    ibase *= ibase;
  }
  return ret;
}

template <typename itype> bool isPerfectSquare(itype num) {
  double val = sqrt(static_cast<double>(num));
  itype root = round(val);
  return (root * root == num);
}

template <typename itype> itype combination(itype n, itype m) {
  if (m == 0)
    return 1;
  if (m > n / 2)
    m = n - m;
  itype prod = 1;
  for (itype i = 1; i <= m; ++i) {
    prod *= (n - i + 1);
    prod /= i;
  }
  return prod;
}

// TODO still need to generalize its use, for example
// nmod must be a prime and all mult op should not equal
// to nmod!
template <typename itype> itype combination(itype n, itype m, itype nmod) {
  if (m == 0)
    return 1;
  if (m > n / 2)
    m = n - m;
  itype pn = 1;
  itype pd = 1;
  for (itype i = 1; i <= m; ++i) {
    pn = product_mod(pn, (n - i + 1), nmod);
    pd = product_mod(pd, i, nmod);
  }
  i64 x, y, g;
  extended_euclid(pd, nmod, x, y, g);
  return product_mod(pn, x, nmod);
}

// this is an optimized version of gcd.
// I compared with other method, this one is two times
// faster than other method.
// template functions
// gcd function from PE, Robert_Gerbicz!
template <typename itype> itype gcd(itype a, itype b) {
  itype c;

  while (b > 0) {
    if (a >= b) {
      a -= b;
      if (a >= b) {
        a -= b;
        if (a >= b) {
          a -= b;
          if (a >= b) {
            a -= b;
            if (a >= b) {
              a -= b;
              if (a >= b) {
                a -= b;
                if (a >= b) {
                  a -= b;
                  if (a >= b) {
                    a -= b;
                    if (a >= b)
                      a %= b;
                  }
                }
              }
            }
          }
        }
      }
    }
    c = a, a = b, b = c;
  }
  return a;
}

class TotientFunctions {
public:
  std::vector<int> totient_sieve(int nmax, int version = 0) {
    if (version == 0)
      return totient_sieve_0(nmax);
    else
      return totient_sieve_1(nmax);
  }

private:
  vector<int> totient_sieve_0(int nmax);
  vector<int> totient_sieve_1(int nmax);
};

class Sieve {
public:
  void PrimeSieve(int nmax);
private:
    std::vector<int> primes_;
};

template <typename itype> itype multmod(itype x, itype y, itype nmod) {
  x %= nmod;
  y %= nmod;
  itype result = x * y;
  result %= nmod;
  return result;
}

template <typename itype> itype addmod(itype x, itype y, itype nmod) {
  itype result = x + y;
  result %= nmod;
  return result;
}
// now it is time to find some smart way to represent two dimensional ordered
// array and three dimension ordered array where x <= y or x<=y<=z;
// for two dimensional x<=y the position of (i, j) is (j+1)*j/2+i, and the total
// size needed is (j+1)*(j+2)/2
// for three dimensional x<=y<=z, the position of (i, j, k) is
// k*(k+1)*(k+2)/6+j*(j+1)/2+i the total size needed is(k+1)*(k+2)*(k+3)/6

#endif
