#include <vector>
#include <cmath>
#include <cassert>
#include <numeric>
#include <algorithm>
#include <cstdio>
#include "typedef.h"
#include "tools.h"
#include "int2.h"
#include <tr1/unordered_set>
using namespace std;
void primeWithin( vector<int>& vecr, int limit)
{
    vecr.clear();
    int odd = (limit+1)/2;
    vector<int> vec; //for i >=1 number represent 2i+1 assume all prime
    vec.resize(odd, 1);
    vec[0] = 0;
    int ip= 1;  // prime number from 2 3 5 ....
    int iprime = 3;
    int max = sqrt((double) limit)+1;
    while( iprime <= max )
    {
      // sieve
        for(int i =(iprime * iprime-1)/2; i < odd; i+=iprime)
            vec[i] = 0;
      //find next prime
        while(vec[++ip] == 0);

        iprime = 2*ip+1;
    }
    vecr.push_back(2);
    int nx = accumulate(vec.begin(), vec.end(), 0);
    vecr.reserve(nx+1);
    for( int i = 1; i< odd; ++i)
        if( vec[i] ) vecr.push_back(2*i+1);
}

//without prime list
bool isPrime( i64 num )
{
    if(num == 1) return false;
    if( num == 2 || num == 3) return true;
    else if( num % 2 == 0) return false;

    int root = sqrt((double) num )+1;
    for (int i = 3 ; i <=  root; i+=2){
        if( num % i == 0) return false;
    }
    return true;
}

//with prime list
bool isPrime(u64 num, vector<int>& primes){
    if( num == 1) return false;
    if( num == 2) return true;
    int root = round(sqrt((double) num)+1);
    assert(primes.back() >= root);
    u64 value = num;
    int pk = 0;
    bool factorNotFound = true;
    while(factorNotFound){
        int remainder = value % primes[pk];
        if(remainder == 0) return false;
        ++pk;
        if(primes[pk] >= root)
            return true;
    }
    return true;
}

//pollard rho prime 
//check return values, if non-zero, factor, else return 0, not composite
//the original version of this function is kind of brute force. 
//I will try the unordered map way
i64 pollard_rho(i64 n, int n0, int debug){
    typedef std::tr1::unordered_set<i64> hashset;
    hashset hset;

    i64 limit = 2000;
    i64 i  = 1; 
    i64 x = n0;
    i64 y = x;
    i64 k = 2;
    int iter = 0;
    hashset::iterator hiter;
    while(iter != limit){
        ++i;
        ++iter;
        // check paper: compute A*B mod N efficiently in ansi c
        if( x > 1000000000LL){
            double dn = n; 
            double dx = x;
            double dp = dx * dx - 1;
            double dq = dp/dn;
            i64 qpp = dq+0.5;
            i64 rp = x*x-1-qpp * n;
            i64 r = (rp & 0x8000000000000000LL)? rp+n:rp;
            x = r;
        }else{
            x = x*x-1;
            x %= n;
        }
        hiter = hset.find(x);
        if(hiter==hset.end())
            hset.insert(x);
        else{
            //printf("hashset size %d\n", static_cast<int>(hset.size()));
            return 0;//loop detected but still no factors found hopeless
        }
        if(x < 0) x += n;
        i64 delta =  y -x ;
        if( delta < 0) delta = -delta;
        i64 d = gcd( delta, n );
        if( d != 1 && d != n ){
            if(debug)
                printf("DEBUG %d %lld %lld \n", iter, n, d);
            //printf("hashset size %d\n", static_cast<int>(hset.size()));
            return d;
        }
        if( i == k){
            y = x;
            k <<= 1;
        }
    }
    //printf("hashset size %d\n", static_cast<int>(hset.size()));
    return 0;    
}

//prime factors, less than or equal to num. 
void factor(i64 num, I64PairVec& ifac, const IntVec& prime)
{
    //special case, not prime factor for 1
    ifac.clear();
    if(num==1){
        ifac.push_back(IntPair(1,1));
        return;
    }
    i64 n1 = num;
    int ubound = sqrt((double) num);
    for(unsigned int i = 0; i < prime.size(); ++i) {
        int nth = 0;
        if( n1 % prime[i] == 0){
            while(n1% prime[i] ==0) {
                n1/=prime[i];
                ++nth;
            }
            ifac.push_back(IntPair(prime[i], nth));
        }
        if(n1 == 1 || prime[i] > ubound)break;
    }
    if(n1 > 1) ifac.push_back(I64Pair(n1, 1));
}
//input is a combination of  0, 1, ..., k-1(distinct) from 0 -- n-1, 
//return the next combination
//the maximum for each bit is n-k,..., n-1
bool next_combination(vector<int>& cvec, int n, int k)
{
    assert(static_cast<int>(cvec.size())==k);
    assert(n>=k);
    int i = 0;
    ++cvec[k-1];
    while(i<=k-1 && cvec[k-1-i] > n-1-i ){
        ++i;
        if(k-1-i>=0)
            ++cvec[k-1-i];
    }
    if(i> k-1){
        for(int i =0 ; i<k; ++i)
            cvec[i]= i;
        return false;
    }
    //key part of the function
    assert(k>=i);
    for(int j=i; j >= 1; --j){
        cvec[k-j]=cvec[k-j-1]+1;
    }
    if(cvec[0] > n-k){
        for(int i =0 ; i<k; ++i)
            cvec[i]= i;
        return false;
    }
    else
        return true;
}

bool isPermutation(int im, int in)
{
    vector<int> digits;
    digits.resize(10,0); // 0----9
    while(im){
        int res = im % 10;
        ++digits[res];
        im /= 10;
    }
    while(in){
        int res = in % 10;
        --digits[res];
        in /= 10;
    }
    for(int i = 0; i < 10; ++i)
        if(digits[i]) return false;

    return true;
}

bool isPalindromic(i64 num, int base) //base generally 10
{
    vector<int> vec, rvec;
    while(num){
        int res = num % base;
        num = num /base;
        vec.push_back(res);
    }
    rvec.resize(vec.size(), 0);
    reverse_copy(vec.begin(), vec.end(),rvec.begin());
    return (vec == rvec);
}

//find the position of the elem
int binary_find(int num, vector<int>& vec){
    if(vec.empty()) return -1;
    unsigned int head = 0;
    unsigned int tail = vec.size()-1;
    while (head < tail ){
        int mid = (head + tail)/2;
        if(vec[mid] == num) 
            return mid;
        else if(vec[mid] < num){
            head = mid + 1;
        }else{//mid > num
            tail = mid - 1;
        }
    }
    assert( head == tail);
    if(vec[head] == num) 
        return head;
    else 
        return -1;
}

// a * x + b * y = gcd 
void extended_euclid(i64 a, i64 b, i64& x, i64& y, i64& gcd){
    if(b == 0){
        gcd = a;
        x = 1;
        y = 0;
    }else{
       i64 residue = a % b;
       extended_euclid(b, residue, x, y, gcd);
       i64 tp = x;
       x = y;
       y = tp - (a/b) * y;
    }
}

//I forgot to add a comment on this function, this is a bad habit.
//when I really need this function, I myself almost forgot how it works
//and why it is important for prime detection! 
// The idea is sometimes a series numbers are in quadratic form, so with 
// this function, we can sieve out those numbers that are composite.
// if the boolean returned is false, it means no solutiona available for
// the quadratic mod equation n^2 % prime == residue;
// otherwise the solution is in "sol"
bool tonelli_shank(i64 prime, i64 residue, i64& sol)
{
    sol = 0;

    assert((prime-1)%2 == 0);
    i64 pow = (prime-1)/2;
    if(powermodule(residue, pow, prime) != 1) return false;
    int s = 0;
    i64 q = prime - 1;
    while ((q & 1 )== 0){
        ++s; 
        q >>= 1;
    }
    if(s == 1){
        pow = (prime+1)/4;
        sol = powermodule(residue, pow, prime);
        return true;
    }else{
        bool found = false;
        i64 z = 0;
        for(i64 i = 2; i < prime -1; ++i){
            i64 ret = powermodule(i, (prime-1)/2, prime);
            if(ret == prime-1){
                z = i;
                found = true;
                break;
            }
        }
        assert(found == true);
        i64 r = powermodule(residue, (q+1)/2, prime);
        i64 t = powermodule(residue, q, prime);
        i64 c = powermodule(z,q, prime);
        i64 m = s;
        i64 b = 0;
        while(t != 1){
            int ix = 0;
            i64 t1 = t;
            while(t1 != 1){
                t1*= t1;
                t1%= prime;
                ++ix;
                assert (ix < m );
            }
            int px = m-ix-1;
            int pb = 0;
            b = c;
            while(pb < px){
                b *= b;
                b %= prime;
                ++pb;
            }
            r = r*b;
            r %= prime;
            c = b * b;
            c %= prime;
            t = t * c;
            t %= prime;
            m = ix;
        }
        sol = r;
        return true;
    }
}
//
void factor_table_min( int nmax, vector<int>& ftable)
{
    ftable.resize(nmax+1);
    for( unsigned int i = 1; i < ftable.size(); ++i )
        ftable[i] = i;
    
    for( unsigned int i = 2; i < ftable.size(); ++i ){
        if(ftable[i] < static_cast<int>(i)) continue;
        for(unsigned int j = i *i; j < ftable.size(); j+=i){
            if( ftable[j] > static_cast<int>(i) ) 
                ftable[j] = i;
        }
    }  
}

//if not necessary, use min, which is faster
void factor_table_max( int nmax, vector<int>& ftable)
{
    ftable.resize(nmax+1);
    for( unsigned int i = 1; i < ftable.size(); ++i )
        ftable[i] = i;
    
    for( unsigned int i = 2; i < ftable.size(); ++i ){
        if(ftable[i] < static_cast<int>(i)) continue;
        for(unsigned int j = 2*i;  j < ftable.size(); j+=i)
                ftable[j] = i; //overwrite to find the largest factor
    }
}
//quadratic reciprocity 
//quadratic_residue_test(int num, int prime)
/*  
//implement a 64 bit integer version Miller-Rabin primality test
//composite == 0 prime == 1
bool miller_rabin(i64 xn, unsigned int nsampling)
{
    for(unsigned int cnt = 0; cnt < nsampling; ++cnt){
      i64 xa = rand() %(xn-2)+2;//TODO refine this part since rand is not well written
      assert(xa < 4000000000LL);
        if(witness(xa, xn))
           return 0;
    }
    return 1;
}

bool witness(i64 xa, i64 xn)
{
    i64 xn1 = xn - 1;
    unsigned int expo = 0;
    while(xn1 % 2  == 0){
       xn1 = xn1 >> 1;
       ++expo;
    }
    //modular exponentiation 
    i64 x0 = powermodule2(xa, xn1, xn);
    i64 x1;
    for(unsigned int i = 1; i <= expo; ++i){
        x1 = product_mod(x0, x0, xn);
        if(x1 == 1 && x0 != 1 && x0 != xn - 1)
            return 1;
        x0 = x1;
    }
    if(x1 != 1)
        return 1;
    return 0;
}

i64 powermodule2(i64 base, i64 expo, i64 module){
    i64 result = 1;
    i64 cbase = base;
    while(expo){
       int remainder = expo & 1; 
       if(remainder){
            --expo;
            result = product_mod(result, cbase, module);
            assert(result >= 0);
       }
       else{
            expo /= 2;
            cbase = product_mod(cbase, cbase, module);
            assert(cbase >= 0);
       }
    }
    return result;
}

i64 product_mod(i64 n1, i64 n2, i64 mod)
{
    assert(mod < 1e15); 
    i64 low = 1000000000LL;
    assert(n1 <= low && n2 <= low)
        return (n1*n2)%mod;
    //GeneralInteger g1(n1), g2(n2), gx(1);
    //GeneralInteger denom(mod), remainder(1);
    //gx = g1 * g2;
    //gx.divide(denom, remainder);
    //return remainder.to_i64();
}
    //multiplier bound at 1e9 
    //result bound at 1e15;



void kara_mult(int nsize, int* a, int* b, int* ret)
{
    assert((nsize & 1) == 0 || nsize == 1);
    unsigned int n2 = nsize >> 1;
    int * ar = a;
    int * al = a + n2;
    int * br = b;
    int * bl = b + n2;
    int * asum = ret + 5 * nsize;
    int * bsum = asum + n2;
    int * x1 = ret;
    int * x2 = ret + nsize; // shift size
    int * x3 =  x2 + nsize; //shift 2 size
    if(nsize <= 4){
        for(unsigned int i = 0; i < static_cast<unsigned int>(nsize); ++i){
            if(a[i] == 0) continue;
            for(unsigned int j = 0; j < static_cast<unsigned int>(nsize); ++j){
                ret[i+j] += a[i]*b[j];
            }
        }
        return;
    } //normal multiplication
    for( unsigned int i = 0; i < n2; ++i){
        asum[i] = al[i] + ar[i];
        bsum[i] = bl[i] + br[i];
    }
    kara_mult(n2, ar, br, x1);
    kara_mult(n2, al, bl, x2);
    kara_mult(n2, asum, bsum, x3);
    for(unsigned int i = 0; i < static_cast<unsigned int>(nsize); ++i) x3[i] -= (x1[i]+x2[i]);
    for(unsigned int i = 0; i < static_cast<unsigned int>(nsize); ++i) ret[i+n2] += x3[i];
}
*/
//pi is a very small prime number 
//number is now less than 2^32;
bool strong_pseudo_test_int(i64 pi, i64 d, i64 s, i64 p) 
{
    if( pi == p) return true;
//itype powermodule(itype base, itype expo, itype module){
    bool isComposite = false;
    bool isPrime = true;
    i64 result = powermodule(pi, d, p);
    if(result == 1) 
        return isPrime;
    else if (result == p-1) 
        return isPrime;
    else{
        i64 prod = result;
        for(unsigned int j = 1; j < s; ++j){
            // lesson !!!! the following two lines are incorrect!
            // mult64mod should be used, I did not find the bug!
            //prod *= prod; 
            //prod %= p;
            prod = mult64mod(prod, prod, p);
            if(prod == p-1) 
                return isPrime;
        }
    }
    return isComposite;
}

bool strong_pseudo_test(i64 p)
{
    if( p == 2) return true;
    if(p % 2 == 0 || p == 1)
        return false;
    vector<int> vp;
    vp.resize(6, 0);
    vp[0] = 2;
    vp[1] = 3;
    vp[2] = 5;
    vp[3] = 7;
    vp[4] = 11;
    vp[5] = 13;
    i64 p1 = p - 1;
    int o2 = 0;
    while (p1 % 2 == 0){
        p1/=2;
        ++o2;
    }
    for(unsigned int i = 0; i <vp.size(); ++i){
       if(!strong_pseudo_test_int(vp[i], p1, o2, p)) //true composite
           return false; 
    }
    return true;
}

i64 mult64mod(u64 a, u64 b, u64 mod)
{
    assert(mod <(unsigned long long) 1LL<<63);
    double dn = mod;
    double da = a;
    double db = b;
    double dp = da*db;
    double dq = dp/dn;
    u64 qpp = dq + 0.5;
    u64 rp = a*b-qpp*mod;
    unsigned long r;
    if(rp & 0x8000000000000000)
        r =  rp+mod;
    else
        r = rp;
    return r;
}

i64 powermodule(i64 base, i64 expo, i64 module){
    i64 result = 1;
    i64 cbase = base;
    while(expo){
       int remainder = expo & 1; 
       if(remainder){
            result = mult64mod(result, cbase, module);
       }
        //i64 cbase1 = cbase;
        cbase = mult64mod(cbase, cbase, module);
        assert(cbase > 0);
        expo >>= 1;
    }
    return result;
}

void farey_sequence(vector<IntPair>& vf, int nlimit, bool ascending)
{
    vf.clear();
    int a=0, b=1, c=1, d=nlimit;
    int k=0;
    if(!ascending) {
       a=1; b=1; c=nlimit-1; d=nlimit;
    }
    if(ascending){
        vf.push_back(IntPair(0,1));
    }else{
        vf.push_back(IntPair(1,1));
    }

    while((ascending && c <= nlimit) || (!ascending && a > 0)){
        k = (nlimit + b) / d;
        int a1 = a, b1 = b;  
        a = c; b = d;
        c = k*c-a1;
        d = k*d-b1;
        //if(a + b <=  nlimit)
            vf.push_back(IntPair(a, b));
    }
}
