#include "../lib/tools.h"
#include "../lib/typedef.h"
#include <cstdio>
#include <cassert>

int nt = 10;
vector<int> primes;
u64 sumPrime(int numDigit, int num){
    u64 thresh = power(10, nt -1);
    u64 xsum = 0;
    int nk = nt - numDigit;
    assert(nk > 0);
    vector<int> ncomm;
    ncomm.clear();
    ncomm.resize(nk, 0);
    for(unsigned int i = 0; i < nk; ++i){
        ncomm[i] = i;
    }
    vector<int>vvec;
    //combination initialized, the position 0 -- 9
    u64 alln = 0;
    for(int i = 0; i < nt; ++i){
        alln += power(10, i)*num;
    }
    do{
        int upper = power(10, nk);
        for(int value  = 0; value < upper; ++value){
            vvec.clear();
            int vt = value;
            int flag = true;
            for(int i = 0; i < nk; ++i){
                int remainder = vt % 10;
                if(remainder == num){
                    flag = false;
                    break;
                }
                vvec.push_back(remainder);
                vt /= 10;
            }
            if(!flag) continue;
            assert(vt == 0);
            //first digit can not be 0
            if(vvec.back() == 0 && ncomm.back() == 9)continue; 
            u64 seln=0, selnp =0;
            for(unsigned int i = 0; i < nk; ++i){
                u64 xp = power(10, ncomm[i]);
                seln += xp * num;
                selnp += xp * vvec[i]; 
            }
            selnp += (alln-seln);
            if(selnp < thresh) continue;
            if(isPrime(selnp, primes)){
                xsum += selnp;
                printf("num = %d selnp = %lld\n", num, selnp);
            }
        }
    }while(next_combination(ncomm, nt, nk));
    return xsum;
}
int main(){
    u64 sum = 0;
    primeWithin(primes, 100100);
    for(int i = 0; i <= 9 ; ++i){
        u64 psum = 0;
        int ndig = nt;//nt dig anything is composite even nt
        while(psum == 0){
            --ndig;
            psum = sumPrime(ndig, i);
        }
        sum += psum;
    }
    printf("%lld\n", sum);
}
