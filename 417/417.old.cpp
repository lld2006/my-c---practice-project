#include "../lib/tools.h"
#include <cstdio>
#include <cstdlib>
//looks like that I am on the right track. But the first time I tried to solve 
//the problem, I do not understand why the algorithm is doing those kind of thing. 
//
//Ah, I am so stupid! I should only calculate the n-digit recurring cyle for primes
//not for every number
//
//i64 cycle(i64 num)
//{
//    //brute force function
//    while((num & 1) == 0)
//        num >>= 1;
//    while(num% 5 == 0)
//        num /= 5;
//    if(num == 1) return 0;
//    if(num==3 || num==9)
//        return 1;
//    i64 m = 1;
//    int prod = 10;
//    
//    while(prod != 1){
//        ++m;
//        prod *= 10;
//        prod %= num;
//    }
//    return m;
//}
int simplify(int num)
{
    while((num & 1 ) == 0) num >>= 1;
    while(num % 5 == 0) num /= 5;
    return num;
}

//
//int find_multiplicative_order(i64 nbase, i64 number, const vector<int>& vfac)
//{
//    assert(nbase == 10);
//    IntPairVec vpairs;
//    assert(number &  1);
//    factor_using_table(number, vpairs, vfac);
//    //find totient number 
//    int totient = number;
//    for(unsigned int i = 0; i < vpairs.size(); ++i){
//        int pi = vpairs[i].first;
//        totient/= pi; 
//        totient *= (pi-1);
//    }
//
//    //this is the factorization of the totient number
//    factor_using_table(totient, vpairs,  vfac);
//        
//    i64 result = 1;
//    for(unsigned int i = 0; i < vpairs.size(); ++i){
//        int pi = vpairs[i].first;
//        int powi= vpairs[i].second;
//        int yi = totient / power(pi, powi);
//        int xi = powermodule((i64)nbase, (i64)yi, number);
//        if(xi == 1) continue; //has nothing to do with this prime factor
//        i64 t = xi; //powermodule((i64)xi, pi, number);
//        int cnt = 0;
//        do{
//            t = powermodule((i64)t , pi, number);
//            ++cnt;
//            assert(cnt <= powi);
//        }while(t != 1);
//        assert(t ==1);
//        result *= power(pi, cnt);
//    }
//    return result;
//}

//this function is now revised for number =  prime^power  like numbers only
int find_multiplicative_order(i64 nbase, i64 prime, int np, const vector<int>& vfac)
{
    assert(nbase == 10);
    IntPairVec vpairs;
    assert(prime &  1);
    //find totient number 
    int number = power(prime, (i64)np);
    int totient = number / prime * (prime-1);

    //this is the factorization of the totient number
    factor_using_table(prime-1, vpairs,  vfac);
    if(np > 1)
        vpairs.push_back(IntPair(prime, np-1));
        
    i64 result = 1;
    for(unsigned int i = 0; i < vpairs.size(); ++i){
        int pi = vpairs[i].first;
        int powi= vpairs[i].second;
        int yi = totient / power(pi, powi);
        int xi = powermodule((i64)nbase, (i64)yi, number);
        if(xi == 1) continue; //has nothing to do with this prime factor
        i64 t = xi; 
        int cnt = 0;
        do{
            t = powermodule((i64)t , pi, number);
            ++cnt;
            assert(cnt <= powi);
        }while(t != 1);
        assert(t ==1);
        result *= power(pi, cnt);
    }
    return result;
}
int main()
{
    int target = 100000000;
    vector<int> primes;
    vector<int> vfac;
    factor_table_min(target, vfac);
    for(unsigned int i= 2; i<vfac.size(); ++i){
        if(vfac[i] == static_cast<int>(i)) primes.push_back(i) ;
    }
    vector<int> vn, vorder;
    vn.resize(target+1, 1);
    vorder.resize(target+1, 0);
    //value could be 1, but these numbers has no contribution
    //to the result
    for(unsigned int i = 4; i <= vn.size(); ++i){
        if(i %2 == 0 || i%5 ==0 ) {
            vn[i] = 0;
            int value = simplify(i);
            ++vn[value];
        }
    }
    for(unsigned int i = 1; i < primes.size(); ++i){
        //if( i % 100000 ==0) 
        //    printf("%d\n", i);
        i64 prod = primes[i];
        if(prod == 5) continue;
        for(int j = 1; j ; ++j){
            int order = find_multiplicative_order(10LL, primes[i], j, vfac);
            vorder[prod] = order;
            prod *= primes[i];
            if(prod > target) break;
        }
    }
    i64 sum = 0;
    IntPairVec vpairs;
    for(unsigned int i = 3; i < vn.size(); i+=2){
        if(vn[i] == 0) continue;
        factor_using_table(i, vpairs, vfac);
        int lcm = 1;
        for(unsigned int i = 0; i < vpairs.size(); ++i ){
            i64 value = power(vpairs[i].first, vpairs[i].second);
            int t  = vorder[value];
            int g = gcd(lcm , t);
            lcm = t * lcm/g;
        }
        sum += (i64)lcm * vn[i];
    }

    printf("%lld\n", sum);
}

