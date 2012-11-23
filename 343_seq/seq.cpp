#include <cstdio>
#include <cassert>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "../lib/tools.h"
#include "../lib/typedef.h"
//#include <tr1/unordered_map>
//typedef std::tr1::unordered_map<i64, i64> hashmap;
int fac_limit = 2000000;
i64 limit = 2000000;
vector<int> factors;
vector<int> primes;
//function sequence is a bad method to solve this problem.
//a first start point is that k^3+1 is factorable
//i64 sequence(i64 value)
//{
//    i64 num = 1;
//    i64 den= value;
//    i64 common = 1;
//    while(den > 1){
//        ++num;
//        --den;
//        if(den == 1)
//            break;
//        if(true){
//            common = gcd(num, den);
//            if(common > 1){
//                num /= common;
//                den /= common;
//            }
//        }
//    }
//    return num;
//}
/*
i64 find1(i64 value)
{
    assert(factors[value] > 0);
    return factors[value];
}
i64 find2(i64 value)
{
    int plimit = sqrt(value)+1;
    bool factored = false;
    for(unsigned int i = 0; primes[i] <= plimit; ++i){
        factored = false;
        do{
            i64 quote = value/primes[i];
            if(quote * primes[i] == value){
                factored = true;
                value = quote;
            }else{
                break;
            }
        }while(true);
        if(value == 1)
            return primes[i];
        if(value < fac_limit)
            //return find1(value);
            return (factors[value] > primes[i]? factors[value]: primes[i]);
        if(factored)
            plimit = sqrt(value)+1;
    }
    return value;
}
int find_largest_factor(i64 value){
    if(value < fac_limit )
        //return find1(value);
        return factors[value];
    else
        return find2(value);
}
i64 find_largest_factor2(i64 value){
    i64 max_fac = 1;
    int ntest = 0;
    while(true){
        i64 seed = rand()%value;
        int fac = pollard_rho(value, seed, 0);
        ++ntest;
        if(ntest == 2)
            break;
        if(fac == 0) continue;
        if(fac < limit){
            assert(factors[fac] > 0);
            value /= fac;
            if(max_fac < factors[fac])
                max_fac = factors[fac];
            ntest = 0;
        }else{
            i64 fac2 = value / fac;
            if(fac2 > 1)
                max_fac = max_fac > factors[fac2]? max_fac:factors[fac2];
            value = fac;
            ntest = 0;
        }
    }
    if(value < limit) 
        return max_fac > factors[value]?max_fac:factors[value];
    else
        //need to check primality
        return value;
}
*/
int main()
{
    //int residue = 21; 
    //int prime = 101;
    //i64 sol = 0;
    //tonelli_shank(prime, residue, sol);
    //printf("%lld\n", sol);
    //exit(1);
    //limit = 100;

    // limit = 100;
    int plimit = 2000000;//sqrt(k^2-k+1)
    //fac_limit = 1000000;
    factors.resize(fac_limit+2, 0);
    primeWithin(primes, plimit+2); 
    factors[1] = 1;
    for(unsigned int i =0; i < primes.size(); ++i){
        int ip = primes[i];
        for( int j = ip; j < factors.size(); j += ip)
                factors[j] = ip;
    }
    printf("factor done\n");
    vector<pair<i64, i64> > maxfactor;
    maxfactor.resize(limit+1);
    //initialization value, maxfactor table
    for(i64 i = 0; i< static_cast<i64>(maxfactor.size()); ++i){
        maxfactor[i] = pair<i64, i64>(1, i*i-i+1);
    }
    //first factor out all factor of 3s//since 3 has only one solution
    for(unsigned int i =2; i< maxfactor.size(); i+=3){
        maxfactor[i].first = 3;
        i64 value = maxfactor[i].second;
        while(value % 3 == 0){
            value /=3;
        }
        maxfactor[i].second = value;
    }
    //now find all quadratic residues = p-3 for all primes p
    //using a sieve method
    for(unsigned int i = 2; i<primes.size(); ++i){
        i64 solution = 0;
        bool flag = tonelli_shank(primes[i], primes[i]-3, solution);
        
        if(!flag)
            continue;
        //is a quadratic residue
        assert(solution > 0 && solution < primes[i]);
        assert((solution * solution) % primes[i] == primes[i]-3);
        i64 sol1, sol2;//for k
        if(solution & 1){//odd
            sol1 = (solution+1)/2;
            sol2 = (2*primes[i] - solution+1)/2;
        }else{//even
            sol1 = (primes[i]-solution+1)/2;
            sol2 =  (solution + primes[i]+1)/2;
        }
        for(unsigned int j = sol1; j < maxfactor.size(); j+= primes[i]){
            if(maxfactor[j].first < primes[i])
                maxfactor[j].first = primes[i];
            assert(maxfactor[j].second %  primes[i] == 0);
            while(maxfactor[j].second % primes[i] == 0){
                maxfactor[j].second /= primes[i];
            }
        }
        for(unsigned int j = sol2; j < maxfactor.size(); j+= primes[i]){
            if(maxfactor[j].first < primes[i])
                maxfactor[j].first = primes[i];
            assert(maxfactor[j].second %  primes[i] == 0);
            while(maxfactor[j].second % primes[i] == 0){
                maxfactor[j].second /= primes[i];
            }
        }
        
    }
    i64 sum = 0;
    for(i64 i = 1; i <= limit; ++i){
        i64 ret1 = factors[i+1];
        assert(i+1 < static_cast<int>(factors.size()));
        i64 ret2 = maxfactor[i].second> maxfactor[i].first? maxfactor[i].second:maxfactor[i].first;
        assert(maxfactor[i].second  > 2000000 || maxfactor[i].second == 1);
        //assert(isPrime(ret1) && (isPrime(ret2)||ret2==1));
        //assert(ret2 == factors[i*i-i+1]);
        //i64 ret2 = find_largest_factor2(value2);
        //printf("%lld %lld %lld\n",i, ret1, ret2);
        if(ret1 > ret2){
            sum += ret1-1;
        }else{
            sum += ret2-1;
        }
        //printf("%lld %lld %lld %lld\n", i, sum, ret1, ret2);
    }
    printf("%lld\n", sum);
}
