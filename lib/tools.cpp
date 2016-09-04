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
#include <sys/time.h>
#include <bitset>
using namespace std;
//here I tried some other possibility like char or short
//but bool is best up till now
void primeWithin( vector<int>& vecr, const int limit)
{
    vecr.clear();
    int odd = (limit+1)/2;
    vector<bool> vec; //for i >=1 number represent 2i+1 assume all prime
    vec.resize(odd, true);
    vec[0] = 0;
    int ip= 1;  // prime number from 2 3 5 ....
    int iprime = 3;
    int max = sqrt((double) limit)+1;
    while( iprime <= max )
    {
      // sieve
        for(int i =(iprime * iprime-1)/2; i < odd; i+=iprime)
            vec[i] = false;
      //find next prime
        while(vec[++ip] == false);

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
    if( num < 2 ) return false;
    if( num == 2) return true;
    int root = round(sqrt((double) num)+1);
    //this assert should be guarranted somehow
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
//check each prime number to square root
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

//the factors are from small to large
//first is prime number, second is power
void factor_using_table(i64 n, IntPairVec& vpairs, const vector<int>& ftable)
{
    vpairs.clear(); 
    int pwr = 0;
    int curr_fac = ftable[n];
    while(curr_fac>1){
        ++pwr;
        n /= ftable[n];
        while(curr_fac == ftable[n]){
            ++pwr;
            n /= ftable[n];
        }
        vpairs.push_back(IntPair(curr_fac, pwr));
        curr_fac = ftable[n];
        pwr = 0;
    }
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

bool isPermutation(i64 im, i64 in)
{
    if((im - in) % 9 ) return false;
    vector<int> digits;
    digits.resize(10,0); // 0----9
    while(im){
        int res = im % 10;
        ++digits[res];
        im /= 10;
    }
    while(in){
        int res = in % 10;
        if(digits[res] == 0) 
            return false;
        --digits[res];
        in /= 10;
    }

    return true;
}

bool isPalindromic(i64 num, int base) //base generally 10
{
    int nr = 0;
    if(num % base == 0) return false;
    while(nr < num){
        nr *= base;
        int res = num % base;
        nr += res;
        if(nr >= num) break;
        num /= base;
    }
    return (num == nr);
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
// x y maybe negative
// x y gcd are output and a b are input
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

// Sometimes a series numbers are in quadratic form, so with 
// this function, we can sieve out those numbers that are composite.
// if the boolean returned is false, it means no solutiona available for
// the quadratic mod equation n^2 % prime == residue;
// otherwise the solution is in "sol"
bool tonelli_shank(i64 prime, i64 residue, i64& sol)
{
    sol = 0;

    assert(prime & 1);
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
        //old trial and error method for non residual
        //for(i64 i = 2; i < prime -1; ++i){
        //    i64 ret = powermodule(i, (prime-1)/2, prime);
        //    if(ret == prime-1){
        //        z = i;
        //        found = true;
        //        break;
        //    }
        //}
        //following jacobi symbol is from PE problem 216
        // stubbscroll in page 5 of the discussion
        for(z = 3; z < prime -1; z+= 2){
            if(jacobi(z, prime)== -1){
                found = true;
                break;
            }
        }
        assert(found == true);
        //old shank tonelli method
        i64 r = powermodule(residue, (q+1)/2, prime);
        i64 t = powermodule(residue, q, prime);
        i64 c = powermodule(z,q, prime);//equivalent to b ofsq
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
            b = c;
            for( int j = 0; j < px; ++j){
                b*=b; b%= prime;
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
        //from stubb
        //i64 b = powermodule(z,q, prime);
        //i64 r = powermodule(residue, (q+1)/2, prime);
        //i64 r2a = r*powermodule(residue,(q+1)/2-1,prime)%prime;
        //int J=0;
        //for(int i=0;i<s-1;i++) {
        //   i64 c=powermodule(b,2*J,prime);
        //   c=r2a*c%prime;
        //   c=powermodule(c,1ULL<<(s-i-2),prime);
        //   if(c==prime-1) J+=1ULL<<i;
        //}
        //sol =  r*powermodule(b,J,prime)%prime;
        return true;
    }
}
//
void factor_table_min( int nmax, vector<int>& ftable)
{
    ftable.resize(nmax+1);
    for( unsigned int i = 1; i < ftable.size(); ++i )
        ftable[i] = i;

    int root = sqrt(nmax);
    
    for( int i = 2; i<= root; ++i ){
        if(ftable[i] < static_cast<int>(i)) continue;
        for(unsigned int j = i*i; j < ftable.size(); j+=i){ 
            //an equal sign up here with size, should be bug. now fixed
            if( ftable[j] > static_cast<int>(i) ) 
                ftable[j] = i;
        }
    }  
}
//no even number in the table
void factor_using_table_odd(i64 n, IntPairVec& vpairs, const vector<int>& ftable)
{
    vpairs.clear(); 
    i64 n2 = 0;
    while( (n & 1) == 0){
        n >>= 1;
        ++n2;
    }
    if(n2)
        vpairs.push_back(IntPair(2, n2));

    assert( (n & 1) > 0);
    int np = (n-1) >> 1;
    int pwr = 0;
    int curr_fac = ftable[np];
    while(curr_fac>1){
        ++pwr;
        n /= curr_fac;
        np = (n-1) >> 1;
        while(curr_fac == ftable[np]){
            ++pwr;
            n /= ftable[np];
            np = (n-1) >> 1;
        }
        vpairs.push_back(IntPair(curr_fac, pwr));
        curr_fac = ftable[np];
        pwr = 0;
    }
}

//just for even numbers, need to double the space is not a good
//idea. let me try 
void factor_table_min_odd( int nmax, vector<int>& ftable)
{
    int nsize = (nmax+1)/2;//the numbers are 1 3 5 7 ...
    ftable.resize(nsize);
    for( unsigned int i = 0; i < ftable.size(); ++i )
        ftable[i] = (i<<1)+1;

    int root = sqrt(nmax);
    
    for( int i = 1; i<= root; ++i ){
        int value = (i<<1)+1;
        //already assigned a min factor to i, so it 
        //is not a prime
        if(ftable[i] < value) continue; 
        int start = (value*value-1) >> 1;
        for(unsigned int j = start; j < ftable.size(); j+=value){
            if( ftable[j] > value ) 
                ftable[j] = value;
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
/* 
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
*/
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
    vector<int> vp = {2,3,5,7,11,13};
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
    assert(expo>=0);
    i64 result = 1;
    i64 cbase = base;
    while(expo){
       int remainder = expo & 1; 
       if(remainder){
            result = mult64mod(result, cbase, module);
       }
        //i64 cbase1 = cbase;
        cbase = mult64mod(cbase, cbase, module);
        assert(cbase >= 0);
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
//this is a flawed version of totient calculation. but sometimes
//we just need some such kind of simple calculations
i64 totient(int n, vector<int>& primes)
{
    //assert(n < 1000);
    if(n == 1)
        return 1;
    int prod = 1;
    int total = 1;
    for(unsigned int i = 0; i < primes.size(); ++i){
        prod = 1;
        bool first = true;
        while((n % primes[i] )== 0){
            n/= primes[i];
            if(first){
                prod *= (primes[i]-1);
                first = false;
            }else
                prod *= primes[i];
        }
        total *= prod;
        if(n == 1)
            break;
    }
    return total;
}
void prime_generate_sq2(i64 p, int& a, int& b)
{
    assert((p-1)%4==0);
    i64 result = 0;
    for(i64 n = 2; n <= p-2; ++n){
        result = powermodule(n, (p-1)/4, p);
        i64 r2 = result * result;
        if ((r2)%p==1) 
            continue;
        else
            break;
    }
    double root = sqrt(p);
    i64 rk = p; 
    i64 rk1=result;
    i64 tp;
    while(rk >= root){
        tp = rk % rk1;
        rk=rk1;
        rk1 = tp;
    }
    assert(rk*rk+rk1*rk1==p);//this is what this function about
    a=rk; b=rk1;
    if(a > b)
        swap(a, b);
}

i64 totient_with_factor(const IntPairVec& vfac)
{
    i64 prod = 1;
    for(unsigned int i = 0; i < vfac.size(); ++i){
        i64 px = vfac[i].first;
        i64 npow = vfac[i].second;
        prod *= (px-1);
        prod *= power(px, npow-1);
    }
    return prod;
}

//sieve version to get totient, I am so stupid that 
//that I forget using sieve
void totient_using_table(vector<int>& vt, int nmax)
{
    //initialization
    vt.clear();
    vt.resize(nmax+1);
    for(unsigned int i = 1; i <vt.size(); ++i){
        vt[i] = i;
    }
    //sieve
    for(int i = 2; i < (int)vt.size(); ++i){
        if(vt[i] != i) continue;
        vt[i] = i - 1;
        for(unsigned int j = i + i; j < vt.size(); j+= i){
            vt[j] /= i;
            vt[j] *= (i-1);
        }
    }
}

int jacobi(int a,int m) 
{
   int t=1,z;
   a%=m;
   while(a) {
      int cnt = 0;
      while(!(a&1)) {
         a>>=1;
         ++cnt;
      }
      if((cnt & 1) && (((m&7)==3 || (m&7)==5))) 
          t=-t;
      z=a,a=m,m=z;
      if((a&3)==3 && (m&3)==3) 
          t=-t;
      a%=m;
   }
   if(m==1) return t;
   return 0;
}
double gettime() 
{
  struct timeval t;
  gettimeofday(&t,NULL);
  return t.tv_sec+t.tv_usec/1000000.;
}

void xgcd(const i64 p, const i64 q, i64& gcd, i64& pcoeff, i64& qcoeff)
{ i64 a[3]; a[0] = 1; a[1] = 0; a[2] = p; 
   i64 b[3]; b[0] = 0; b[1] = -1; b[2] = q; 
   while (a[2] != 0){ 
       i64 k = b[2]/a[2]; 
       b[0] -= k * a[0]; 
       b[1] -= k*a[1]; 
       b[2] -= k*a[2]; 
       if (b[2] == 0){ 
           b[0] = a[0]; a[0] = 0; b[1] = a[1]; a[1] = 0; b[2] = a[2]; a[2] = 0; 
       } else { 
           i64 k = a[2]/b[2]; a[0] -= k*b[0]; a[1] -= k*b[1]; a[2] -= k*b[2]; 
       } 
   } 
   gcd = b[2]; pcoeff = b[0]; qcoeff = b[1]; 
} 

//TODO check numbers in vp has no common factors
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

