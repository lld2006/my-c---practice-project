#include <vector>
#include "typedef.h"
using namespace std;
void primeWithin( vector<int>& vecr, int limit);
bool isPrime( int i );
bool isPrime(u64 num, vector<int>& primes);
void factor(int num, IntPairVec& ifac, const vector<int>& prime);
bool next_combination(IntVec& cvec, int n, int k);
bool isPermutation(int im, int in);
unsigned long long int power(int base, int exp);
bool isPalindromic(int num, int base);
int binary_find(int num, vector<int>& vec);
void extended_euclid(int a, int b, int& x, int& y, int& gcd);
bool isRhoPrime(i64 n, int debug);
template <typename itype> 
itype gcd(itype ia, itype ib){
    if (ia > ib) return gcd ( ib, ia);
    // ia < ib;
    while (ia){
        itype res = ib % ia;
        ib = ia;
        ia = res;
    }
    return ib;
}
//template <typename itype> 
//void powermodule(itype base, itype expo, itype& low, itype& high, itype tbase){
//    itype rl=1, rh = 0;
//    itype bl = base, bh = 0;
//    while(expo){
//       int remainder = expo %2; 
//       if(remainder == 1){
//            result *= cbase;
//
//       }
//       else
//            cbase *= cbase;
//    }
//}
