#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <cstdio>
#include <cassert>
//TODO use sieve factor to do this problem again
//each number only remember the first prime factor
//110000000
int limit = 110000000;
int limitk = 1;
int sqrtlimit = 1;
i64 nk;
//prod1 for b and prod2 for c
  
i64 cardano(I64PairVec& ifac, int index, i64 prod1, i64 prod2, int sum)
{
    if(index == static_cast<int>(ifac.size())){
        if(prod1 + prod2 + sum <= limit){
            //assert(prod1 * prod1 * prod2 == (8*nk+5)*(nk+1)*(nk+1));//for bug check
            //if(nk > limit/6.8)
            //if((nk-5) %9!=0 && (nk-15)%50!=0)
            //    printf("%lld %lld %d %lld\n", prod1, prod2, sum, nk);
            return 1; 
        }
        else
            return 0;
    }
    i64 cnt = 0; 
    i64 pd1 = prod1, pd2=prod2;
    
    //lesson when while loop on vector index, 
    //the index less than size should always be checked
    int pmax = ifac[index].second;
    i64 pfac = ifac[index].first;
    i64 pfac2 = pfac*pfac;
    //double quot = (double)limit/prod2;
    //int p2 = log((double)quot)/log((double)pfac2);
    i64 quote = limitk/prod2;
    int istart = 0;
    i64 power2=1;
    vector<i64> powerfac;
    powerfac.resize(pmax+1, 0);
    i64 tp = 1;
    for(int i = 0; i<= pmax; ++i){
        powerfac[i] = tp;
        tp *= pfac;
    }
    for(int i = istart; i<= pmax; ++i){//here I need to modify
        pd1 = prod1 * powerfac[pmax-i];
        pd2 = prod2 * power2;
        assert(pd1 > 0);
        assert(pd2 > 0);
        power2 *= pfac2;
        if(pd1+pd2+sum <= limit)
            cnt += cardano(ifac, index+1, pd1, pd2, sum);
        if(power2 > quote) break;
    }
    return cnt;
}

//i64 cardano(I64PairVec& ifac, int index, i64 prod1, i64 prod2, int sum)
//{
//    i64 pdn1=prod1, pdn2=prod2;
//    for(unsigned int nindex= 0; nindex < ifac.size(); ++nindex){
//        int pmax = ifac[nindex].second;
//        i64 pfac = ifac[nindex].first;
//        i64 pfac2 = pfac *pfac;
//        i64 quote = limit/prod2;
//        int i;
//        for(i = 0; i <=pmax; ++i){
//            pd1 = prod1 * power(pfac, static_cast<i64>(pmax-i));
//            i64 power2 = power(pfac2, static_cast<i64>(i));
//            if(power2 > quote) break;
//            pd2 = prod2 * power2;
//            assert(pd1 > 0);
//            assert(pd2 > 0);
//            if(pd +pd2 +sum > limit)
//                continue;
//        }
//        if(nindex == 
//    }
//}
//lesson forgot to handle the case index=size
//lesson if the factor in ifac1 is too large, overflow.
//lesson start from large prime numbers
void add_factors(const I64PairVec& ifac1, const I64PairVec& ifac2, I64PairVec& ifac,
                i64& prod1, i64& prod2)
{
    int size1 = ifac1.size();
    int size2 = ifac2.size();
    int index1 = size1-1, index2=size2-1;
    ifac.clear();
    ifac.reserve(size1+size2);
    prod2 = 1;
    prod1 = 1;
    while(index1 >= 0 && index2 >= 0){
        if(ifac1[index1].first > ifac2[index2].first){
            if(ifac1[index1].first > sqrtlimit)
                prod1 *= ifac1[index1].first;
            else
                ifac.push_back(ifac1[index1]);
            --index1;
        }else if(ifac1[index1].first < ifac2[index2].first){
            int res = ifac2[index2].second & 1;
            int quotient = ifac2[index2].second >> 1;
            if(res == 1)
                prod2 *= ifac2[index2].first;
            if(quotient > 0)
                ifac.push_back(IntPair(ifac2[index2].first, quotient));
            --index2;
        }else{
            int power=2*ifac1[index1].second+ifac2[index2].second; 
            int res = power & 1;
            int quotient = power>>1;
            if(res==1)
                prod2 *= ifac1[index1].first;
            if(quotient > 0)
                ifac.push_back(IntPair(ifac1[index1].first,quotient));
            --index1; 
            --index2;
        } 
    }
    while(index1 >= 0){
        if(ifac1[index1].first > sqrtlimit)
            prod1 *= ifac1[index1].first;
        else
            ifac.push_back(ifac1[index1]);
        --index1;
    }

    while(index2>=0){
        int power = ifac2[index2].second;
        int res  = power & 1;
        int quotient = power >> 1;
        if(res >0) prod2 *= ifac2[index2].first;
        if(quotient> 0)
            ifac.push_back(IntPair(ifac2[index2].first, quotient));
        --index2;
    }
}

int main(){
    int primelimit = 11000;
    vector<int> primes;
    primeWithin(primes, primelimit);
    I64PairVec ifac1, ifac2, ifac;
    i64 ncard = 0;
    sqrtlimit = sqrt((double) limit);
    for(nk = 1; nk<= (limit/6+1); ++nk){
        limitk = limit - nk;
        //i64 psq = ((8*k+21)*k+18)*k+5; //(k+1)^2*(8k+5)
        if((nk % 1000000)==0)
            printf("%lld nk\n", nk);
        int sum = 3*nk+2; //a's value
        factor(8*nk+5, ifac2, primes); 
        factor(  nk+1, ifac1, primes);
        i64 prod1=1, prod2=1;
        add_factors(ifac1, ifac2, ifac, prod1, prod2);//combine all factors into one vector
        ncard += cardano(ifac, 0, prod1, prod2, sum); //factors, index, product, sum
    }
    printf("%lld\n", ncard+1);
}
