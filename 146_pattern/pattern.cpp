#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <cstdio>
#include <cassert>

const int NOT_FOUND = -1000;
i64 find_non_residue(i64 prime){
    i64 power = (prime - 1)/2;
    i64 i;
    for(i = 2; i < prime; ++i){
        i64 result = powermodule(i, power, prime);       
        if(result == prime -1)
            break;
        if(i == prime - 1)
            printf("no result found, please check\n");
    }
    return i;
}
i64 Tonelli_Shanks(i64 prime, i64 nonres, i64 modfac){
    assert(modfac >= 0);
    if(modfac == 0) return 0;
    //my understanding is that this based on fermat's theorem a^(p-1) mod p == 1
    if(powermodule(modfac, (prime-1)/2, prime) != 1) 
        return NOT_FOUND;
    else if(prime == 2)
        return prime;
    else if (prime%4 == 3)
        return powermodule(modfac, (prime+1)/4, prime);
    i64 p1 = prime - 1;
    int s = 0;
    while((p1 & 1 )== 0){
        ++s;
        p1 = p1 >> 1;
    }
    i64 c = powermodule(nonres, p1, prime);
    i64 r = powermodule(modfac, (p1+1)/2, prime);
    i64 t = powermodule(modfac, p1, prime);
    if(t == 1)
        return r;
    while(t != 1){
        int rep = 0;
        i64 t1 = t;
        while(t1 != 1){
            t1 *= t1;
            ++rep;
            assert( rep < s);
            t1 %= prime;
        }
        int sqc = s - rep - 1;
        assert(sqc >= 0);
        for(int i= 0; i < sqc; ++i){
            c *= c;
            c %= prime;
        }
        i64 b = c;
        r *= b;
        r %= prime;
        t = t *b;
        t %= prime;
        t *= b;
        t %= prime;
        c = b * b;
        c %= prime;
        s = rep;
    }
    return r;
}
//r  + prime k = 10 n
int simpleEq(i64 r, i64 prime){
   int r1 = r % 10; 
   int p1 = prime% 10;
   int k = 0;
   int sum = r1;
   while(sum % 10 != 0){
        sum += p1;
        ++k;
   }
   return k;
}
bool find_init_composite_pos(int prime, int residue, int& pos1, int& pos2){
    int rd2 = residue;
    if(residue > prime || residue < 0) rd2 = residue % prime;
    if(rd2 < 0) rd2 +=prime;
    i64 nonres = find_non_residue(prime);
    i64 r = Tonelli_Shanks(prime, nonres, rd2);
    i64 r2 = prime - r;
    if( r == NOT_FOUND) return false;
    int coeff = simpleEq( r, prime) ;
    assert((coeff * prime + r )%10 ==0);
    pos1 = (coeff * prime + r)/ 10;
    if(100LL*pos1*pos1 + prime - residue == prime) 
        pos1 += prime;
    coeff = simpleEq( r2, prime);
    assert((coeff * prime + r2 )%10 ==0);
    pos2 = (coeff * prime + r2)/ 10;
    if(100LL*pos2*pos2 + prime - residue == prime)
        pos2 += prime;
    return true;
}
int main(){
    int limit = 15000000;
    vector<int> fvec;
    vector<int> primes;
    primeWithin(primes, limit*10);
    fvec.resize(limit+1, 1);
    for(unsigned int i = 0; i <fvec.size(); i+=3){
        fvec[i] = 0;
    }
    printf("number of primes is %d\n", static_cast<int>( primes.size()));
    for(unsigned int i = 3; i< primes.size(); ++i){
        if( i % 10000 == 0)
            printf("%d\n", i);
        i64 prime = primes[i];
        int pos1=0, pos2=0;
        int residue = prime - 1;
        if(find_init_composite_pos(prime, residue, pos1, pos2)){
            for(unsigned int i = pos1; i < fvec.size(); i+= prime){
                fvec[i] = 0;
                int pos = i+pos2-pos1;
                if(pos > 0 && pos < static_cast<int>(fvec.size()))
                    fvec[pos] = 0;
            }
        }
        residue = prime- 3;
        if(find_init_composite_pos(prime, residue, pos1, pos2)){
            for(unsigned int i = pos1; i < fvec.size(); i+= prime){
                fvec[i] = 0;
                int pos = i+pos2-pos1;
                if(pos > 0 && pos < static_cast<int>(fvec.size()))
                    fvec[pos] = 0;
            }
        }
        residue = prime - 7;
        if(find_init_composite_pos(prime, residue, pos1, pos2)){
            for(unsigned int i = pos1; i < fvec.size(); i+= prime){
                fvec[i] = 0;
                int pos = i+pos2-pos1;
                if(pos > 0 && pos < static_cast<int>(fvec.size()))
                    fvec[pos] = 0;
            }
        }
        residue = prime -9;
        if(find_init_composite_pos(prime, residue, pos1, pos2)){
            for(unsigned int i = pos1; i < fvec.size(); i+= prime){
                fvec[i] = 0;
                int pos = i+pos2-pos1;
                if(pos > 0 && pos < static_cast<int>(fvec.size()))
                    fvec[pos] = 0;
            }
        }
        residue = prime - 13;
        if(find_init_composite_pos(prime, residue, pos1, pos2)){
            for(unsigned int i = pos1; i < fvec.size(); i+= prime){
                fvec[i] = 0;
                int pos = i+pos2-pos1;
                if(pos > 0 && pos < static_cast<int>(fvec.size()))
                    fvec[pos] = 0;
            }
        }
        residue = prime - 27;
        if(find_init_composite_pos(prime, residue, pos1, pos2)){
            for(unsigned int i = pos1; i < fvec.size(); i+= prime){
                fvec[i] = 0;
                int pos = i+pos2-pos1;
                if(pos > 0 && pos < static_cast<int>(fvec.size()))
                    fvec[pos] = 0;
            }
        }
    }
    i64 sum = 0;
    for(unsigned int i = 0; i < fvec.size(); ++i){
        if(fvec[i]){
            printf("%d\n", i);
            sum += i;
        }
    }
    printf("%lld\n", sum*10);
}
