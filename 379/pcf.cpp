#include "pcf.h"
#include "../lib/tools.h"
#include <cmath>
#include <cassert>
i64 primeCountingFunction::compute(i64 num)
{
    i64 phi2 = compute_phi2(num);    
    i64 phi13 = compute_phi13(num);

    double dl = log(num);
    i64 v13 = exp(dl/3.0);
    if((v13+1)*(v13+1)*(v13+1)==num) ++v13;
    i64 pi13 = pcfTable[(v13-1)/2];
    return phi13-phi2-1+pi13;
}
i64 primeCountingFunction::compute_phi2(i64 num)
{
    i64 result = 0;
    double dl = log(num);
    i64 v13 = exp(dl/3.0);
    if((v13+1)*(v13+1)*(v13+1)==num) ++v13;
    i64 v12 = sqrt(num);
    if((v12+1)*(v12+1)==num) ++v12;
    assert(v13 < static_cast<int>(pcfTable.size()*2+1));
    assert(v12 < static_cast<int>(pcfTable.size()*2+1));
    i64 pi13 = pcfTable[(v13-1)/2];
    i64 pi12 = pcfTable[(v12-1)/2];
    result = -pi12*(pi12-1)+pi13*(pi13-1);;
    result /= 2;

    int idx1 = find_next_prime_high(v13);
    int idx2 = find_next_prime_low(v12);
    //these primes are in the range of x^1/3 to x^2/3
    for(int k =  idx1; k <= idx2; ++k){
        i64 n1 = num/primes[k];
        result += pcfTable[(n1-1)/2];
    }
    return result;
}
i64 primeCountingFunction::compute_phi13(i64 num)
{
    //first simple part
    i64 result = 0;
    double dl = log(num);
    double d2 = log(2.0);
    double d13 = exp(dl/3.0);
    i64 v13 = d13;
    if((v13+1)*(v13+1)*(v13+1)==num) {
        ++v13;
        d13 = v13;
    }
        
    //table look up method, very smart
    vector<vector<int>> A;
    int asize = dl*2/3/d2 + 1; //0 to 2^i
    A.resize(asize);
    for(unsigned int i = 0; i < A.size(); ++i){
        int scale = 1<<i;
        int bsize =  d13*d13 / scale +1; // j start from 1, 0 is always ignored
        A[i].resize(bsize, scale);
    }
    //checking each prime and set the correct number
    for(unsigned int i = 0; i < primes.size(); ++i){
        int np = primes[i];
        if(np > d13) break;
       
        // first sieve out the prime*1 
        for(unsigned int pow = 0; pow<A.size(); ++pow){
            int scale = 1 << pow;
            int pos = (np-1) /scale + 1;
            A[pow][pos] -= 1;
            assert(A[pow][pos] >= 0);
        }
        //sieve out the prime*n
        //next line is important, avoid double counting and
        //make code efficient
        for( int ai = A.size()-1; ai >= 0; --ai){
            int scale = 1<<ai;
            for(unsigned int j = np * np; j <= scale * (A[ai].size()-1); j += np){
                if(A[0][j] == 0) continue;
                int pos = (j-1)/scale + 1;
                assert(pos < A[ai].size());
                --A[ai][pos];
                assert(A[ai][pos] >= 0);
            }
        }
    }

    create_mobius(num);
    for(unsigned int i = 1; i < mobius_factor.size(); ++i) {
        if(mobius_factor[i] > 0)
            result += (num/i+1)/2;
        else if(mobius_factor[i] < 0)
            result -= (num/i+1)/2;
    }
    // algorithm use m instead of i, m > 1
    for(unsigned int i = 2; i < mobius_factor.size(); ++i){
        if(mobius_factor[i] == 0) continue;
        int minfac = abs(mobius_factor[i]);
        int pos = binary_find(minfac, primes);
        assert(pos >= 0);
        for( int j = pos-1; j >=0; --j){
            if(primes[j] * i <= d13 ) continue; 
            i64 value = phi13table(num/(primes[j] * i), A, j);
            if(mobius_factor[i] > 0 ) 
                result -= value;
            else
                result += value;
        }
    }
    return result;
}
i64 primeCountingFunction::phi13table(i64 value, vector<vector<int>>& A, int primeIdx)
{
    vector<int> vpow;
    i64 result = 0;
    i64 v1 = value;
    while(v1){
        vpow.push_back(v1 & 1);
        v1 >>= 1;
    } 
    v1 = 0;
    int nt = 0;
    for(int i = vpow.size()-1; i >= 0; --i){
        if(vpow[i]){
            nt = 1 << i; 
            v1 += nt;
            int pos = (v1-1) /(1<<i)+1;
            result += A[i][pos];
        }

    }
    return result;
}
void primeCountingFunction::init()
{
    assert(nmax > 0);

    double dl = log(nmax);
    double dt = exp(dl/3.0);
    i64 v13 = dt;
    //i64 v2 = sqrt(num);
    //if((v2+1)*(v2+1)==num) ++v2;
    if((v13+1)*(v13+1)*(v13+1)==nmax) ++v13;
    //generating primes
    int psize = (dt+1) * (dt+1);
    primeWithin(primes, psize);
    create_pcf(psize);
}
void primeCountingFunction::create_pcf(int limit)
{
    pcfTable.clear();

    int odd = (limit+1)/2;
    pcfTable.resize(odd, 1);
    pcfTable[0] = 0;
    int ip= 1;  // prime number from 2 3 5 ....
    int iprime = 3;
    int max = sqrt((double) limit)+1;
    while( iprime <= max )
    {
      // sieve
        for(int i =(iprime * iprime-1)/2; i < odd; i+=iprime)
            pcfTable[i] = 0;
      //find next prime
        while(pcfTable[++ip] == 0);

        iprime = 2*ip+1;
    }
    int cnt = 1;
    for(int i = 1; i< odd; ++i){
        cnt += pcfTable[i];
        pcfTable[i] = cnt;
    }
}
//this is for the sqrt(x) part
//prime must be less than or equal to num
i64 primeCountingFunction::find_next_prime_low(i64 num)
{
    assert(num < primes.back());
    int low = 0; 
    int high = primes.size()-1;
    int mid = 0;
    while(low < high){
        mid = (low +high)/2;
        if(primes[mid]==num)
            return mid;
        else if(primes[mid] > num){
            high = mid-1;
            if(primes[high] <= num)
                return high;
        }else{//low is equal to or less than num
            low = mid+1;
            if(primes[low]> num)
                return low-1;
        }
    }
    assert(low == high);
    assert(0);
    if(primes[low] > num)
        return low - 1;
    else 
        return low;
}
//this is for the cuberoot side, prime must be greater than num
i64 primeCountingFunction::find_next_prime_high(i64 num)
{
    assert(num < primes.back());
    int low = 0; 
    int high = primes.size()-1;
    int mid = 0;
    while(low < high){
        mid = (low + high)/2;
        if(primes[mid] == num)
            return mid + 1;
        else if(primes[mid] > num){
            high = mid - 1;
            if(primes[high] <= num)
                return high + 1;
        }else{
            low = mid + 1;
            if(primes[low] > num)
                return low;
        }
    }
    assert(low = high);
    assert(0);
    return -1;
}
//this is a special version of minimal factor number
//generating function accompanied with mobius_sign
void primeCountingFunction::create_mobius(i64 num)
{
    double dl = log(num);
    i64 v13 = exp(dl/3.0);
    if((v13+1)*(v13+1)*(v13+1)==num) ++v13;
    mobius_factor.clear();
    mobius_factor.resize(v13+1);
    for(unsigned int i = 0; i < mobius_factor.size(); ++i){
        mobius_factor[i] = i;
    }
    for(unsigned int i = 0; i < primes.size(); ++i){
        int np = primes[i];
        if(np > v13) break;
        for(unsigned int j = np; j < mobius_factor.size(); j += np){
            if(abs(mobius_factor[j])== j)
                mobius_factor[j] = -np;//this is kind of initialization
            else
                mobius_factor[j] = -mobius_factor[j];
        }
    }
    for(unsigned int i = 0; i < primes.size(); ++i){
        int np = primes[i];
        int np2 = np * np;
        if(np2 > v13) break;
        for(unsigned int j = np2; j < mobius_factor.size(); j += np2)
            mobius_factor[j] = 0;
    }
}
