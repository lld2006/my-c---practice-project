#include <cstdio>
#include <vector>
#include "../lib/tools.h"
using namespace std;
//this problem is relatively easy to solve since 
//we can find a formula called hook length formula
//for this problem the rest part is just coding
void update_cnt_vector(vector<int>& vcnt, int multiplier, int nstart, int length, int width)
{
    if(length < width)
        swap(length, width);
    int nvalue = nstart - 1;
    int i;
    for( i = 1; i <= width; ++i){
        vcnt[nvalue+i] += i *multiplier;
    }
    for(int i = width+1; i <= length;++i){
        vcnt[nvalue + i] += width * multiplier;
    }
    for(int i = length + 1; i < length + width; ++i){
        vcnt[nvalue + i] += multiplier * (length + width - i);
    }
}
int main()
{
    int n1 = 10000;
    int n2 = 5000;
    i64 nmod = 76543217;
    vector<int> primes;
    primeWithin(primes, 2*n1-1);
    vector<int> vgcd;
    vgcd.resize(primes.size(), 0);
    i64 x, y, gcd;
    for(unsigned int i = 0; i < primes.size(); ++i){
        i64 px = primes[i];
        xgcd(px, nmod, gcd, x, y);
        if(x < 0) 
            x+= nmod;
        assert(x > 0 && x < nmod);
        vgcd[i] = x;
    }
    vector<int> vcnt;
    vcnt.resize(2*n1, 0);
    int length = n1- n2;
    int width = n2;
    update_cnt_vector(vcnt, 2, 1, length, width);
    width = length; //n1-n2 * n1 - n2
    update_cnt_vector(vcnt, 1, 2*n2+1, length, width);
    
    vector<i64> inverse;
    inverse.resize(2*n1,0);
    for(unsigned int i = 0; i < primes.size(); ++i){
        int px = primes[i];
        inverse[px] = vgcd[i];
    }
    // the maximum value is 2*n1-1
    for( int i = 2; i; ++i){
        if( i * 2 >= 2*n1) break;
        for(unsigned int j = 0; j < primes.size(); ++j){
            int value = primes[j] * i;
            if(value >= 2 * n1) break;
            if(inverse[value]) continue;
            inverse[value] = inverse[i] * vgcd[j];
            inverse[value] %= nmod;
        }
    }
    i64 prod = 1;
    i64 nmax = n1*n1 - n2*n2;
    //first calculate (n1*n1-n2*n2)!
    for(unsigned int i = 2; i <= nmax; ++i){
        prod *= i;
        prod %= nmod;
    }
    for(unsigned int i = 2; i < vcnt.size(); ++i){
        if(!vcnt[i]) continue;
        i64 value = powermodule(inverse[i], vcnt[i], nmod);
        prod *= value;
        prod %= nmod;
    }
    printf("%lld\n", prod);
}
