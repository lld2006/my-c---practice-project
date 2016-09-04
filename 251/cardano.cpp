#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <cstdio>
#include <cassert>
int limit = 110000000;
  
i64 cardano(IntPairVec& ifac, int index, i64 prod1, i64 prod2, int sum, int limitk)
{
    if(index == static_cast<int>(ifac.size()))
        return (prod1 + prod2 + sum <= limit);
    
    i64 cnt = 0; 
    i64 pd1 = prod1, pd2=prod2;
    
    //lesson when while loop on vector index, 
    //the index less than size should always be checked
    int pmax = ifac[index].second;
    i64 pfac = ifac[index].first;
    i64 pfac2 = pfac*pfac;
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
            cnt += cardano(ifac, index+1, pd1, pd2, sum, limitk);
        if(power2 > quote) break;
    }
    return cnt;
}

//lesson forgot to handle the case index=size
//lesson if the factor in ifac1 is too large, overflow.
//lesson start from large prime numbers
//
//prod1 for b and prod2 for c
void add_factors(const IntPairVec& ifac1, const IntPairVec& ifac2, IntPairVec& ifac,
                i64& prod1, i64& prod2, int sqrtlimit)
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
            if(ifac1[index1].first > sqrtlimit){ //type p^1
                //since b must be less than limit, if this factor 
                //is from c^2, it must belongs to c
                prod1 *= ifac1[index1].first;
            }else
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

//i64 psq = ((8*k+21)*k+18)*k+5; //(k+1)^2*(8k+5)
// b + c >= 3*(b/2 * b/2* c)^(1/3), a = 3k+2;
//so for a b c sum greater than 6.78k
int main(){
    struct timer mytime;
    vector<int> ftable;
    factor_table_min_odd(limit*8/6+25, ftable);
    IntPairVec ifac1, ifac2, ifac;
    i64 ncard = 1;//nk = 0
    printf("%.6f\n", mytime.getTime());
    double max_nk = 6/pow(4.0, 1.0/3.0) + 3;
    i64 nk;
    int sqrtlimit = sqrt((double) limit);
    for(nk = 1; nk< (limit/max_nk+1); ++nk){
        int limitk = limit - nk;
        if((nk & 1048575)==0)
            printf("%lld nk\n", nk);
        int sum = 3*nk+2; //a's value
        factor_using_table_odd(8*nk+5, ifac2, ftable);
        factor_using_table_odd(nk+1, ifac1, ftable);
        i64 prod1=1, prod2=1;
        add_factors(ifac1, ifac2, ifac, prod1, prod2, sqrtlimit);//combine all factors into one vector
        ncard += cardano(ifac, 0, prod1, prod2, sum, limitk); //factors, index, product, sum
    }
    printf("%lld\n", ncard);
}
