#include "../lib/tools.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cassert>
//TODO check umu's code in second page of the thread
//the first key point is that all primes can either 
//have 1 or 3 solutions to this x^3==1 mod p. then we need to
//find all prime candidates. then we need to use a recursive
// function to find all solutions that have 243 solutions.
// Two things need to be noted. First, sort all primes in asscending
// order, then we do not need to search all primes spaces. If no 
// primes selected then the first number to be selected should be less than
//(1e11)^(1/5);
//
//we can see a pattern that only p = 3k+1, we have 3 solutions, p = 3k+2, 1 solution
//
// the second part to accelerate the summation is to use a sieve to find out
//all numbers' sum up to n(than has only one solution x^3 ==1 mod p; We just
// need to take out all numbers that are multiples of p has 3 solutions.
//Watch out!!! two sieves are required because of 9=3^2; which is the only 
//non prime number that has 3 solutions. if number(243 solutions) has a factor of 3^n(n>=2)
// then the sieve should sieve all numbers that is a multiple of 3. But in
//the other sieve we only need to sieve out numbers are multiple of 9;
// the numbers we want to find is p1^a p2^b p3^c p4^d p5^e q1 q2...qn
//where p1 ...p5 has three solutions while q has one.
u64 ntop=100000000000LL;
vector<int> cands;
vector<u64>  vaccu; //let us say in this one, 3 is allowed, but 9 is not allowed
vector<u64>  vaccu3;//let us say 3*k is never allowed
vector<int> vn;
int maxcnt = 5;
u64 search243(u64 prod, int cnt, int cpos)
{
    //assert(prod > 0);
    if(prod > ntop ) return 0;
    //if(prod % 3 == 0)
    //    assert(prod % 9 ==0);
    if(cnt == maxcnt){
        if(prod > ntop) return 0;
        u64 nmax = ntop/prod;
        assert(nmax < vaccu.size());

        u64 value; //prod * vaccu[nmax];
        //if 3 is not a factor then multiply by 3 is allowed
        // but multiple of 9 is not allowed
        if(prod % 9 == 0){
            value = vaccu3[nmax];
        }else{
            value = vaccu[nmax];
        }
        value *= prod;
        assert(value > 0);
        //printf("%lld %lld %lld\n", prod,nmax, value);
        //assert(value == test3(prod));
        return value;
    }
    if(cpos == static_cast<int>(cands.size())) // cnt < maxcnt 
        return 0;
    u64 sum = 0;
    for(unsigned int i = cpos; i < cands.size(); ++i){
        u64 prod1 = prod;
        if(cands[i]==3) prod1 = 3;
        
        assert(cnt <= maxcnt-1);
        double v1 = pow(cands[i], maxcnt-1-cnt);
        double vnext = cands[i] * v1;
        if(prod * vnext > ntop) break;
        for(unsigned int pi = 1; pi; ++pi){
            if(prod1 > ntop) break;
            prod1 *= cands[i];
            sum += search243(prod1, cnt+1, i+1);
        }
    }
    return sum;
}
/* 
int test(u64 np)
{
    int cnt = 0;
    for( u64 i = 1; i<np; ++i){
        if((i*i*i-1)%np==0)
            ++cnt;
    }
    //commented code for primes only
    //if(np % 3 == 1)
    //    assert(cnt == 3);
    //else
    //    assert(cnt == 1);
    return cnt;
}
i64 test2(int nmax)
{
    vn.resize(nmax+1, 0);
    for(unsigned int i = 1; i < cands.size(); ++i){
        int px = cands[i];
        for(unsigned int j = px; j < vn.size(); j+=px){
            ++vn[j];
        }
    }
    for(unsigned int j = 9; j < vn.size(); j+=9)
        ++vn[j];
    
    i64 sum = 0;
    int tcnt = 0;
    for(unsigned int i = 0; i < vn.size(); ++i){
        if(vn[i]==maxcnt){
            sum += i;
            ++tcnt;
            //printf("t %d\n", i);
        }
    }
    printf("number of solutions %d, %lld\n", tcnt,sum);
    return sum;
}
*/
int main()
{
    //the first four candidates are 7 9 13 19 for 3 solutions
    // so the maximum one for the next is less than 1e11/(7*9*13*19)

    u64 limit = 6426322;
    //ntop = 30000000;
    limit = ntop/(7*9*13*19);
    if(limit < 31) limit = 100;

    //generate all primes to the prod of 1e11
    vector<int> primes;
    primeWithin(primes, limit);
    
    cands.push_back(3);
    for(unsigned int i = 2; i < primes.size(); ++i)
        if((primes[i] % 3) == 1) cands.push_back(primes[i]);
    
    printf("number of primes is %zu\n", cands.size());

    printf("%d %d %d %d %d %d\n", cands[0], cands[1],cands[2],cands[3],cands[4], cands[5]);

    ///printf("test2 %lld\n", test2(ntop));

    //this part is to memorize some info to speed up
    vaccu.resize(limit+1, 1);
    for(unsigned int i = 0; i < cands.size(); ++i){
        int px = cands[i];
        if(px==3) px = 9;
        for(unsigned int j = px; j < vaccu.size(); j += px){
            vaccu[j] = 0;
        }
    }
    u64 na = 0; 
    for(unsigned int i =0 ; i < vaccu.size(); ++i){
        if(vaccu[i]==1) na += i;
        vaccu[i] = na;
    }

    vaccu3.resize(limit+1, 1);
    for(unsigned int i = 0; i < cands.size(); ++i){
        int px = cands[i];
        for(unsigned int j = px; j < vaccu3.size(); j += px){
            vaccu3[j] = 0;
        }
    }

    na = 0; 
    for(unsigned int i =0 ; i < vaccu3.size(); ++i){
        if(vaccu3[i]==1) na += i;
        vaccu3[i] = na;
    }

    u64 prod = 1;
    u64 sum = 0;
    int cnt = 0, cpos = 0;
    sum = search243(prod, cnt, cpos);
    printf("%lld %lld\n", sum, 0LL);
}
