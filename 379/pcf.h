#ifndef LIBPCF
#define LIBPCF
#include "../lib/typedef.h"
// ======================definition============================
//phi(x, y) the number of value in 1<=n<=x, which satisfy: n has no factors less than or equal to y
//y is not necessarily to be a prime. it can be composite
// ======================property=======================================
// i) pi(x) - pi(sqrt(x)) +1 = phi(x, sqrt(x))
//  since this phi function originate from sieve method, 1 is always left untouched after sieving those numbers that has a factor less than y;
//      with this property, it is easy to see that one just need to figure out how to compute phi(x, sqrt(x)); 
// But this does not help much! if one use sieve, it is still need
// a lot of computation time
// let us now define phi_k(x,y) as the numbers of values in [1,x] which has exactly k factors with all factor > y, notice if a number has two or more factors, those factors might be equal.
// So it is obvious phi(x, y) = phi0(x, y) + phi1(x, y) + phi2(x, y) + ...
// the key to figure out pi(x) it to use the following function;
// phi(x, x^(1/3)) = 1 + pi(x) -pi(x^(1/3)) + phi2(x, x^(1/3));
// so one need to find phi(x, x^(1/3)) and phi2(x, x^(1/3))
// pi (x^(1/3)) is easy to compute
// The identity used to compute phi2 is 
// phi2(x, x^(1/3)) = nchoosek(pi(x^(1/3)), 2) - nchoosek(pi(x^(1/2))) + 
// sum(pi(x/p)) where p is from x^(1/3) (not included) to x^(1/2) 
// to calculate pi(x/p), let me just find all of them up to sqrt(x);
// this maybe a little bit costly, but I do not need to be too professional on this
// to calculate phi(x, x^(1/3)), use 
//     phi(y, p_b) = phi(y, p_(b-1)) - phi(y/p_b, p_(b-1))
class primeCountingFunction
{
    public:
        i64 compute(i64 num);
        primeCountingFunction(int nx)
        {
            m_nmax = nx;
            init();
        }
        void test();
    
    private:
        void init();
        int lookup(int num);
        i64 find_primeIndex_max_le(i64 num);
        i64 compute_phi2(i64 num);
        i64 compute_phi13(i64 num);
        void create_special_mobius(i64 num);//mobius list for odd number
        i64 phi13table(i64 value, vector<vector<int>>& A, int primeIdx);
    private:
        void direct_count(int num, vector<int>& vp);
        i64 m_nmax; //count the number of primes le m_nmax, input
        i64 m_n13;  //index in m_primes which is gt x^1/3
        vector<int> m_primes; //primes up to nmax^(2/3)
        vector<int> m_pcfTable;//table look up is effective upto n^2/3
        vector<int> mobius_factor; //utility function for pcf
};
#endif
