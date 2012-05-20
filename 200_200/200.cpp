#include <cstdio>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <algorithm>
#include <cassert>
//simple and easy, but it looks difficult at first glance.
vector<int> primes;
bool has_sub200(i64 value)
{
    while(value >= 200){
        if((value-200)% 1000 == 0)
            return true;
        value/=10;
    }
    return false;
}
bool prime_proof(i64 value)
{
   assert(value < (i64)primes.back()*primes.back());
   vector<int> vdigits; 
   i64 v1 = value;
   while(v1){
       int res = v1 % 10;
       vdigits.push_back(res);
       v1 /= 10;
   }
   if(vdigits[0]%2==0){
        for(int i = 1; i <10; i+=2){
            v1 = value+i-vdigits[0];
            if(isPrime(v1, primes))
                return false;
        }
   }else{
        for(unsigned int i = 0; i<vdigits.size(); ++i){
            i64 order = power(10, (int)i);
            for( int j = 0; j < 10; ++j){
                if(j == vdigits[i]) continue;
                v1 = value +order*(j-vdigits[i]);
                if(isPrime(v1, primes))
                        return false;
            }
        }
   }
   return true;
}
int main()
{
    i64 gridsize = 240000000000LL;
    int plimit = 1000000;
    primeWithin(primes, plimit);
    vector<i64> cubes, squares;
    cubes.resize(primes.size());
    squares.resize(primes.size());
    for(unsigned int i = 0; i<primes.size(); ++i){
        i64 pi = primes[i];
        squares[i]=pi*pi;
        cubes[i] = squares[i]*pi;
    }
    vector<int> nextsquare;
    nextsquare.resize(primes.size(), 0);//store next prime index in primes;
    int cnt = 0, gcnt=0;
    i64 gridcnt = 0;
    vector<i64> squbes;
    while(cnt < 200){
        ++gridcnt;
        squbes.clear();
        for(unsigned int i = 0; i < primes.size(); ++i){//consider i^3
            do{
                if(nextsquare[i]==static_cast<int>(i)){
                    ++nextsquare[i];
                    continue;
                }
                i64 value = squares[nextsquare[i]] * cubes[i]; 
                if(value > gridcnt*gridsize){
                    break;
                }else{
                    ++nextsquare[i];
                    if(has_sub200(value)){
                        //need to check prime proof property
                        if(prime_proof(value)){
                            ++gcnt;
                            squbes.push_back(value);
                        }
                    }
                }
            }while(true);
        }
        int sqbsize = squbes.size();
        if(cnt+sqbsize < 200){
            cnt += sqbsize;//doing nothing
        }else{
            sort(squbes.begin(), squbes.end());
            for(unsigned int i = cnt+1; i<=200; ++i){
                if(i == 200) printf("%lld\n", squbes[i-cnt-1]);
            }
            //print the 200th number
            break;
        }
    }
}
