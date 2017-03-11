//I learned a little bit about babystep giant step algorithm.
//it is an interesting algorithm. without this algorithm, I need
//O(n) to find all solutions for x^15=-1 mod p. but with this algorithm, I can solve it in O(sqrt(n)*log n) which much nicer!
//but it may have nothing to do with this problem.
//
//a second algorithm I learned is howto find a primitive root
// 
// prime = p, if(p-1) mod 5 != 0 && (p-1) mod 3 != 0, then 
// the only solution is p-1 since p-1 = -1, -1^15+1=0
// if(p-1) mod 3 = 0 but (p-1) mod 5 ! =0; then 
// theare are 3 solutions where x^15+1 =0; 
// if(p-1) %15 ==0, there are 15 solutions. which can be found 
// by power the primitive root
#include "../lib/tools.h"
#include <cstdio>
#include <cassert>
using namespace std;
//return the smallest primitive root
//vfac stores the minimum factor of the index
int primitive_root_for_prime(int prime, const vector<int>& vfac)
{
    //first get all distinct prime factors of p-1
    vector<int> factors;
    int num = prime - 1;
    while(num > 1){
        int nfac = vfac[num];
        factors.push_back(nfac);
        while(vfac[num] == nfac) num/= nfac;
    }
    for(int ni = 2; ni <= prime; ++ni){
        bool is_primitive = true;
        for(unsigned int i = 0; i < factors.size(); ++i){
            int nmod = powermodule(ni, (prime-1)/factors[i], prime);
            if(nmod == 1){
                is_primitive = false;
                break;
            }
        }
        if(is_primitive)
            return ni;
    }
    assert(0);
    return 0;
}
i64 solution_sum(i64 num, i64 prime, i64 limit)
{
    return (limit+(prime-num))/prime*prime;
}
i64 add_sum_of_all_solutions(int prime, int nsol, int np, i64 limit)
{
    i64 sum = 0;
    assert((prime-1)%nsol == 0);
    int nstart = (prime-1)/(2*nsol);
    i64 prod =  powermodule(np, nstart, prime );
    i64 value = prod * prod;
    value %= prime;

    for( int i = 0; i < nsol; ++i){
        prod *= value;
        prod %= prime;
        //assert(powermodule(prod, 15, prime)== prime - 1);
        //if(prod == 10) printf("check ten %d\n", prime);
        sum += solution_sum(prod, prime, limit);
    }

    return sum;
}
int main()
{
    i64 limit = 100000000000LL;
    //limit = 1000;
    int plimit = 100000000;
    //plimit = 1000;
    vector<int> primes, vfac;
    primeWithin(primes, plimit);
    factor_table_min(plimit, vfac);
    //for(unsigned int i = 1; i < primes.size(); ++i){
    //    int px = primes[i];
    //    printf("%d:", px);
    //    for( int j = 2; j < px; ++j){
    //        i64 value = powermodule(j, 15, px);
    //        if(value == px - 1) 
    //            printf("%d ", j);
    //    }
    //    printf("\n");
    //}
    //for(unsigned int i = 5; i < 20; ++i){
    //    printf("root %d %d\n", primes[i], primitive_root_for_prime(primes[i], vfac));
    //}

    i64 sum = 0;
    //has a factor of 2
    sum += (limit+1)/2*2; 
    //for the rest of the primes
    for(unsigned int i = 1;  i < primes.size(); ++i){
        if(i % 100000 == 0) 
            printf("%d\n", primes[i]);
        int px = primes[i];
        //if not divisible by 3 and 5, only one solution
        if((px-1)%3 != 0 && (px-1)%5 !=0){
            sum += solution_sum(px-1, px, limit);
        }else{ 
            //at least one is divisible
            int nprm = primitive_root_for_prime(px, vfac);
            if((px-1)% 3 ==0 && (px-1)%5 != 0){
                sum += add_sum_of_all_solutions(px, 3, nprm, limit);
                //3 solutions

            }else if((px-1)%5 ==0 && (px-1)%3 != 0){
                //5 solutions
                sum += add_sum_of_all_solutions(px, 5, nprm, limit);


            }else{
                //15 solutions
                assert((px-1) % 15 ==0);
                sum += add_sum_of_all_solutions(px, 15, nprm, limit);
            }
        }
    }
    printf("%lld\n", sum);

}
