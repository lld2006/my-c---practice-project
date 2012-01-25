#include <vector>
#include <cmath>
#include "typedef.h"
using namespace std;
void primeWithin( vector<int>& vecr, int limit);
bool isPrime( i64 i );
bool isPrime(u64 num, vector<int>& primes);
void factor(i64 num, I64PairVec& ifac, const vector<int>& prime);
bool next_combination(IntVec& cvec, int n, int k);
bool isPermutation(int im, int in);
bool isPalindromic(int num, int base);
int binary_find(int num, vector<int>& vec);
void extended_euclid(int a, int b, int& x, int& y, int& gcd);
bool isRhoPrime(i64 n, int debug);
inline int index0(int dim, int i, int j) { return i*dim+j;}

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
itype powermodule(itype base, itype expo, itype module){
    itype result = 1;
    itype cbase = base;
    while(expo){
       int remainder = expo & 1; 
       if(remainder){
            --expo;
            result *= cbase;
            result %= module;
       }
       else{
            expo /= 2;
            cbase *= cbase;
            cbase %= module;
       }
    }
    return result;
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
