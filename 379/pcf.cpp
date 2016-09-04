#include "pcf.h"
#include "../lib/tools.h"
#include <cmath>
#include <cassert>
//==============================================================
void primeCountingFunction::init()
{
    double dt = pow(m_nmax, 1.0/3.0);
    int x = dt;
    if((x+1)*(x+1)*(x+1)==m_nmax) ++x;
    x = x* x;  //x**(2/3)
    i64 x1 = x;
    if(x1 < 100000) x1 = 100000;
    primeWithin(m_primes, x1);    
    direct_count(x1, m_pcfTable);
    //generating primes to nmax^(1/2)
    ////now find the index of m_n13
    //double dt = pow(m_nmax, 1.0/3.0);
    //if((dt+1)*(dt+1)*(dt+1)==m_nmax) ++dt;
    //unsigned int i;
    //for(i = 0; i < m_primes.size(); ++i){
    //    if(m_primes[i] > v13) break;
    //}
    //m_n13 = i;
    //assert(m_n13 < m_primes.size());
}
//==============================================================
//key function: pi(x) = phi(x, x^(1/3)) - 1 + pi(x^(1/3)) - phi2(x, x^(1/3))
i64 primeCountingFunction::compute(i64 num)
{
    i64 phi2 = compute_phi2(num);//phi_2(x, x^(1/3))  
    i64 phi13 = compute_phi13(num);//phi(x, x^(1/3))

    i64 v13 = pow(num, 1.0/3.0);
    if((v13+1)*(v13+1)*(v13+1)==num) ++v13;
    i64 pi13 = lookup(v13);
    return phi13-phi2-1+pi13;
}

//this is the part of phi_2(x, x^(1/3))
i64 primeCountingFunction::compute_phi2(i64 num)
{
    i64 result = 0;
    double dl = log(num);

    i64 v13 = exp(dl/3.0);
    if((v13+1)*(v13+1)*(v13+1)==num) ++v13;

    i64 v12 = sqrt(num);
    if((v12+1)*(v12+1)==num) ++v12;
    assert(v13*v13*v13<=num);
    assert(v12*v12<=num);

    i64 pi13 = lookup(v13);
    i64 pi12 = lookup(v12);
    result = (pi13-pi12)*(pi13+pi12-1)/2;

    int idx1 = find_primeIndex_max_le(v13);
    ++idx1;
    if(m_primes[idx1]==v13) ++idx1;
    assert(m_primes[idx1] > v13 && m_primes[idx1-1] <= v13 );
    int idx2 = find_primeIndex_max_le(v12);
    assert(m_primes[idx2] == v12 || (m_primes[idx2] < v12 && m_primes[idx2+1] > v12));
    //////these primes are in the range of x^1/3 to x^2/3
    for(int k =  idx1; k <= idx2; ++k){
        i64 n1 = num/m_primes[k];
        result += lookup(n1);
    }
    return result;
}
i64 primeCountingFunction::compute_phi13(i64 num)
{
    //first simple part
    //i64 result = 0;
    //double d2 = log(2.0);
    //i64 v13 = pow(num, 1.0/3.0);
    //if((v13+1)*(v13+1)*(v13+1)==num) {
    //    ++v13;
    //    d13 = v13;
    //}
    //    
    ////table look up method, very smart
    //vector<vector<int>> A;
    //int asize = dl*2/3/d2 + 1; //0 to 2^i
    //A.resize(asize);
    //for(unsigned int i = 0; i < A.size(); ++i){
    //    int scale = 1<<i;
    //    int bsize =  d13*d13 / scale +1; // j start from 1, 0 is always ignored
    //    A[i].resize(bsize, scale);
    //}
    ////checking each prime and set the correct number
    //for(unsigned int i = 0; i < primes.size(); ++i){
    //    int np = primes[i];
    //    if(np > d13) break;
    //   
    //    // first sieve out the prime*1 
    //    for(unsigned int pow = 0; pow<A.size(); ++pow){
    //        int scale = 1 << pow;
    //        int pos = (np-1) /scale + 1;
    //        A[pow][pos] -= 1;
    //        assert(A[pow][pos] >= 0);
    //    }
    //    //sieve out the prime*n
    //    //next line is important, avoid double counting and
    //    //make code efficient
    //    for( int ai = A.size()-1; ai >= 0; --ai){
    //        int scale = 1<<ai;
    //        for(unsigned int j = np * np; j <= scale * (A[ai].size()-1); j += np){
    //            if(A[0][j] == 0) continue;
    //            int pos = (j-1)/scale + 1;
    //            assert(pos < A[ai].size());
    //            --A[ai][pos];
    //            assert(A[ai][pos] >= 0);
    //        }
    //    }
    //}

    //create_special_mobius(num);
    //for(unsigned int i = 1; i < mobius_factor.size(); ++i) {
    //    if(mobius_factor[i] > 0)
    //        result += (num/i+1)/2;
    //    else if(mobius_factor[i] < 0)
    //        result -= (num/i+1)/2;
    //}
    //// algorithm use m instead of i, m > 1
    //for(unsigned int i = 2; i < mobius_factor.size(); ++i){
    //    if(mobius_factor[i] == 0) continue;
    //    int minfac = abs(mobius_factor[i]);
    //    int pos = binary_find(minfac, primes);
    //    assert(pos >= 0);
    //    for( int j = pos-1; j >=0; --j){
    //        if(primes[j] * i <= d13 ) continue; 
    //        i64 value = phi13table(num/(primes[j] * i), A, j);
    //        if(mobius_factor[i] > 0 ) 
    //            result -= value;
    //        else
    //            result += value;
    //    }
    //}
    //return result;
    return 0;
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


//this is for the sqrt(x) part
//prime must be less than or equal to num
i64 primeCountingFunction::find_primeIndex_max_le(i64 num)
{
    assert(num <= m_primes.back());
    int low = 0; 
    int high = m_primes.size()-1;
    int mid = 0;
    while(low < high){
        mid = (low +high)/2;
        if(m_primes[mid]==num)
            return mid;
        else if(m_primes[mid] > num){
            high = mid-1;
            if(m_primes[high] <= num)
                return high;
        }else{//low is equal to or less than num
            low = mid+1;
            if(m_primes[low]> num)
                return low-1;
        }
    }
    assert(low == high);
    if(m_primes[low] > num)
        return low - 1;
    else 
        return low;
    return 0;
}
//this is a special version of minimal factor number
//generating function accompanied with mobius_sign
void primeCountingFunction::create_special_mobius(i64 num)
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
//do not access the pcfTable directly, using this function 
//for easy debugging and less bugs
int primeCountingFunction::lookup(int num)
{
    if(num <= 1) return 0;
    if(num==2) return 1;
    int n1 = (num-1)/2;
    assert(n1 < static_cast<int>(m_pcfTable.size()));
    return m_pcfTable[n1];
}

//some times, direct count is OK for not so big numbers
//since even numbers almost have no contribution, only odd numbers 
//are returned for instant check up
void primeCountingFunction::direct_count(int num, vector<int>& vp)
{
    int size = (num+1)/2;
    vp.clear();
    vp.resize(size, 0);
    int cnt = 1;
    for(unsigned int i = 1; i<m_primes.size() - 1; ++i){
        int nstart = (m_primes[i]-1)/2;
        int nend = (m_primes[i+1]-1)/2;
        ++cnt;
        for(int n = nstart; n< nend; ++n){
            vp[n] = cnt;
        }
    }
    //tail 
    ++cnt;
    int nstart = (m_primes.back() - 1)/2;
    for(unsigned int n = nstart; n < vp.size(); ++n){
        vp[n] = cnt;
    }
}
void primeCountingFunction::test()
{
    //2 3 5 7  11 13 17 19
    assert(lookup(3) == 2);
    assert(lookup(19) == 8);
    assert(lookup(10000)==1229);
    assert(find_primeIndex_max_le(20)==7);
    assert(find_primeIndex_max_le(100)==24);
    assert(find_primeIndex_max_le(997)==167);
    assert(find_primeIndex_max_le(1000)==167);
}
