#include "../lib/typedef.h"
class primeCountingFunction
{
    public:
        i64 compute(i64 num);
        primeCountingFunction(int nx)
        {
            nmax = nx;
            init();
        }
    
    private:
        void init();
        i64 compute_phi2(i64 num);
        i64 compute_phi13(i64 num);
        void create_pcf(int limit);
        i64 find_next_prime_low(i64 num);
        i64 find_next_prime_high(i64 num);
        void create_mobius(i64 num);
        i64 phi13table(i64 value, vector<vector<int>>& A, int primeIdx);
    private:
        i64 nmax;
        vector<int> primes; //primes up to nmax^(2/3)
        vector<int> pcfTable;//table look up is effective upto n^2/3
        vector<int> mobius_factor; //utility function for pcf
};
