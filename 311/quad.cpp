#include "../lib/tools.h"
#include <cstdio>
#include <cstdlib>
i64 limit = 10000/2;
i64 root = 100;
//how to handle BD is the challenging part
vector<int> primes;
//cpos is the current pos in primes
//ncurr is the current product of powers
//pcurr is the current number (product of primes)
//np1 is how many p1 types of 
i64 find_quad(i64 pcurr,  i64 np1, int cpos, i64 ncurr)
{
    if(pcurr >  limit || cpos == static_cast<int>(primes.size())) //no need to multiply anything
        return 0;
    i64 total = 0;
    if(primes[cpos] % 4 == 1){ //4k+1 type
        i64 pc1 = pcurr;
        for(unsigned int i = 0; ;++i){
            if(i==0){
                //nothing new introduced
                total += find_quad(pc1, np1, cpos+1, ncurr);
            }else{
                if(pc1 <= limit && np1 >= 1){
                    i64 tp = ncurr * (i+1)/2;
                    printf("%lld %lld\n", 2*pc1, tp*(tp-1)/2);
                    total += (tp-1)*tp/2; 
                }
                i64 ntp = find_quad(pc1, np1+1, cpos+1, ncurr*(i+1));
                total += ntp;
            }
            pc1 *= primes[cpos];
            if(pc1 > limit)
                break;
        }
    }else{// 4k+3 type primes
        i64 np = static_cast<i64>(primes[cpos]) * primes[cpos];
        i64 pc1 = pcurr;
        for(unsigned int i = 0; ;++i){
                total += find_quad(pc1, np1, cpos+1, ncurr);
                pc1 *= np;
                if(pc1 > limit)
                    break;
        }
    }
    return total;

}

int main()
{
    int cnt = 0;
    int nx = 6800;
    int nr = sqrt(nx);
    for(int i = 1; i <= nr; ++i)
        for(int j = i; j <= nr+1; ++j){
            if(i*i+j*j == nx){
                ++cnt;
                printf("%d %d %d\n", i, j, cnt);
            }
        }
    exit(1);
    root = sqrt(limit);
    primeWithin(primes, root);
    //vector<int> flags;
    //flags.resize(primes.size(), 0);
    //for(unsigned int i = 0; i < primes.size(); ++i){
    //    if(primes[i] % 4 == 1){
    //        flags[i] = 1;
    //    }
    //}
    int n2 = log(static_cast<double>(limit)/65)/log(2.0);
    i64 p2 = 2;
    i64 sum = 0;
    for( int i2 = 1; i2 <= n2; ++i2, p2 *= 2)
        sum += find_quad(p2, 0, 1, 1 );
    printf("%lld\n", sum); 

}
