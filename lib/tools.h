#include <vector>
#include "typedef.h"
using namespace std;
void primeWithin( vector<int>& vecr, int limit);
bool isPrime( i64 i );
bool isPrime(u64 num, vector<int>& primes);
void factor(i64 num, I64PairVec& ifac, const vector<int>& prime);
bool next_combination(IntVec& cvec, int n, int k);
bool isPermutation(int im, int in);
unsigned long long int power(int base, int exp);
bool isPalindromic(int num, int base);
int binary_find(int num, vector<int>& vec);
void extended_euclid(int a, int b, int& x, int& y, int& gcd);
bool isRhoPrime(i64 n, int debug);
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
