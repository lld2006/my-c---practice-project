#include "../lib/tools.h"
#include <cstdio>
#include <cassert>
#include <cstdlib>
//chinese remainder theorem, a*ainv modp =1;
i64 n18 = 1000000000000000000LL;
i64 n9  = 1000000000LL;
vector<i64> v18, vp18;
// the first version of  mod_product doesnot work well, 
// number which is p*k is not considered well
i64 mod_product_new(const i64 low, const i64 high, const i64 prime)
{
    i64 prod = 1;
    i64 nlow = low;
    i64 nhigh = high;
    i64 nfull = 0; // to count number of -1
    while(nlow <= nhigh ){
        if(nlow == nhigh){
            while ( nlow % prime == 0){
                assert(0);
                nlow /= prime;
            }
            nlow %= prime;
            prod *= nlow;
            prod %= prime;
            break;
        }
        i64 end1 = 0, end2 = 0;//end1 for low end2 for high, all divisible by p
        i64 lowstart = nlow % prime;
        if(lowstart == 0){ 
            //lowstart = prime;//no need to multiply 
            end1 = nlow ; //start from the next is the integral part start
        }else if(lowstart == 1){
            //lowstart = prime; //no need to multiply
            end1 = nlow + prime - 1;
            if(end1 <= nhigh)
                ++nfull;//one additional integral part
        }else{
            end1 = nlow-lowstart+prime;
        }

        i64 highend = nhigh % prime;
        if(highend == 0){
            end2 = nhigh; //position of last number divisible by p 
        }else if(highend == prime - 1){//one additional integral part;
            end2 = nhigh-highend;
            highend = 0;
            if(end2 >= nlow) //chances are that this might not be an integral one
                ++nfull;
        }else{
            end2 = nhigh-highend;
        }
        

        //now reset nlow and nhigh
        assert(end1 % prime == 0);
        assert(end2 % prime == 0);
        nlow = end1/prime;
        nhigh = end2/prime;
        if(nlow <= nhigh){
            assert(lowstart <= prime && lowstart >= 0);
            assert(highend >= 0 && highend < prime);
            if(lowstart > 1){//lowstart need no multiplication if it is an integral seq
                for(i64 i = lowstart; i < prime; ++i){ //here it is not correct
                    prod *= i;
                    prod %= prime;
                }
            }

            for(i64 i = 1; i <= highend; ++i){
                prod *= i;
                prod %= prime;
            }
            nfull += (nhigh-nlow);
        }else{
            for(i64 i = lowstart; i <= highend; ++i){
                prod *= i;
                prod %= prime;
            }
        }
    }
    assert(prod > 0 && prod < prime);
    if(nfull & 1)
        return prime - prod;
    else
        return prod;
}
i64 factor_p(i64 prime, i64 value)
{
    i64 sum = 0;
    while(value > prime){
        value /= prime;
        sum += value;
    }
    return sum;
}
i64 find_inv(i64 a, i64 prime)
{
    
    i64 x, y, g;
    extended_euclid(a, prime, x, y, g);
    assert(g == 1);
    if(x < 0) 
        x += prime;
    assert( x > 0 && x < prime);
    assert((a*x) % prime == 1);
    return x;
}
i64 binomial_mod(i64 nlarge, i64 nsmall, i64 prime)
{
    i64 f1 = factor_p(prime, nlarge);
    i64 f2 = factor_p(prime, nsmall);
    i64 f3 = factor_p(prime, nlarge-nsmall);
    assert(f1-f2-f3>=0);
    if(f1-f2-f3>0)
        return 0;
    assert(nlarge > nsmall);
    if(nsmall * 2 > nlarge ) 
        nsmall = nlarge - nsmall;
    i64 nnum = mod_product_new(nlarge - nsmall + 1, nlarge, prime);
    i64 nden = mod_product_new(1, nsmall, prime);
    i64 den1 = find_inv(nden, prime);
    nnum *= den1;
    nnum %= prime;
    return nnum;
}
i64 chinese_remainder(i64 p, i64 q, i64 r, i64 bp, i64 bq, i64 br)
{
    i64 remainder = 0;
    i64 pq = p*q;
    i64 pr = p*r;
    i64 qr = q*r;
    i64 pqr = pq*r;
    if(bp != 0){
        i64 invp = find_inv(qr, p);
        remainder += invp*qr*bp;
    }
    if(bq != 0){
        i64 invq = find_inv(pr,q);
        remainder += invq*pr*bq;
    }
    if(br != 0){
        i64 invr = find_inv(pq, r);
        remainder += invr*pq*br;
    }
    remainder %= pqr;
    return remainder;
}
int main()
{
    //i64 result = binomial_mod(10000, 2200, 1009);
    //i64 result = chinese_remainder(7, 11, 13, 5, 7,3);
    //printf("%lld\n",result);
    //exit(1);
    int limit = 5000;
    vector<int> primes;
    primeWithin(primes, limit);    
    //first find all primes between 1000 and 5000;
    vector<int> p15;
    for(unsigned int i = 0; i < primes.size(); ++i){
        if(primes[i] > 1000){
            assert(primes[i]< 5000);
            p15.push_back(primes[i]);
        }
    }
    //first calculate the number of p's in the product
    //in numerator and denominator
    vp18.resize(p15.size(), 0);
    for(unsigned int i = 0; i < p15.size(); ++i)
        vp18[i] = factor_p(p15[i], n18) - factor_p(p15[i], n18-n9)-factor_p(p15[i], n9);

    v18.resize(p15.size(), 0);

    for(unsigned int i = 0; i < p15.size(); ++i){
        assert(vp18[i] >= 0);
        if(vp18[i] > 0)
            continue;
        else{// need to find out the mod
            v18[i] = binomial_mod(n18, n9, p15[i]);
        }
    }
    
    i64 sum = 0;
    for(unsigned int i = 0; i<p15.size(); ++i)
        for(unsigned int j = i+1; j < p15.size(); ++j)
            for(unsigned int k = j+1; k<p15.size();++k){
                i64 t = chinese_remainder(p15[i], p15[j], p15[k], v18[i], v18[j], v18[k]);
                assert( t >= 0);
                sum += t;
            }
    printf("%lld\n", sum);
}
