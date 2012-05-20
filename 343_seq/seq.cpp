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
int main()
{
    srand(time(0));
    //limit = 100;
    int plimit = limit;//sqrt(k^2-k+1)
    fac_limit = limit;
    factors.resize(limit+1, 0);
    primeWithin(primes, plimit+1); 
    for(unsigned int i =0; i < primes.size(); ++i){
        int ip = primes[i];
        for( int j = ip; j < fac_limit; j += ip)
                factors[j] = ip;
    }
    //int start = 0; int mid = 0;
    //int last = primes.size()-1; 
    //while (start < last -1){
    //    mid = (start +last)/2;
    //    if(primes[mid] < limit)
    //        start = mid;
    //    else if( primes[mid] > limit){
    //        last = mid;
    //    }else{
    //        assert(0);
    //    }
    //}
    //assert(last = start + 1);
    //assert(primes[start] < limit && primes[last] > limit);
    //primes.resize(last + 1);
    printf("factor done\n");
    i64 sum = 0;
    for(i64 i = 1; i <= limit; ++i){
        i64 value1 = i+1;
        i64 value2 = i*(i-1)+1;
        i64 ret1 = factors[value1];
        i64 ret2 = find_largest_factor2(value2);
        //printf("%lld %lld %lld\n",i, ret1, ret2);
        if(ret1 > ret2){
            sum += ret1-1;
        }else{
            sum += ret2-1;
        }
        if( i % 1000 == 0)
            printf("%lld %lld\n", i, sum);
    }
    printf("%lld\n", sum);
}
