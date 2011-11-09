#include <vector>
#include "tools.h"
#include <cmath>
#include "typedef.h"
#include <cassert>
#include <numeric>
#include <algorithm>
#include <ctime>
#include <cstdio>
using namespace std;
void primeWithin( vector<int>& vecr, int limit)
{
    vecr.clear();
    int odd = (limit+1)/2;
    vector<int> vec; 
    vec.resize(odd);
    vec[0] = 0;
    for(int i = 1; i< odd; ++i)
        vec[i] = 1;   //for i >=1 number represent 2i+1 assume all prime
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

bool isPrime( int num )
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
bool isRhoPrime(i64 n, int debug){
    for(int test = 0 ; test <= 10; ++test){
        i64 limit = 1000;
        i64 i  = 1; 
        srand(time(0));
        i64 x = rand()%n;
        i64 y = x;
        i64 k = 2;
        int iter = 0;
        while(iter != limit){
            ++i;
            ++iter;
            x = x * x + 2;
            x %= n;
            if(x < 0) x += n;
            i64 delta =  y -x ;
            if( y < x) delta = -delta;
            i64 d = gcd( delta, n );
            if( d != 1 && d != n ){
                if(debug)
                    //printf("DEBUG %d %I64d %I64d \n", iter, n, d);
                    printf("DEBUG %d %lld %lld \n", iter, n, d);
                return false;
            }
            if( i == k){
                y = x;
                k *= 2;
            }
    }
    }
    return true;    
}

//prime factors, less than num. so for primes, empty
void factor(int num, IntPairVec& ifac, const IntVec& prime)
{
    //special case, not prime factor for 1
    ifac.clear();
    if(num==1){
        ifac.push_back(IntPair(1,1));
        return;
    }
    int n1 = num;
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
    if(n1 > 1) ifac.push_back(IntPair(n1, 1));
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


u64 power(int base, int exp)
{
    unsigned long long int ret = 1;
    for(int i= 0; i< exp; ++i)
        ret *= base;
    return ret;
}



bool isPalindromic(int num, int base) //base generally 10
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

void extended_euclid(int a, int b, int& x, int& y, int& gcd){
    if(b == 0){
        gcd = a;
        x = 1;
        y = 0;
    }else{
       int residue = a % b;
       extended_euclid(b, residue, x, y, gcd);
       int tp = x;
       x = y;
       y = tp - (a/b) * y;
    }
}

