#include "../lib/tools.h"

vector<vector<int>> vcands;
vector<int> find_n3(int prime )
{
    vector<int> vp;
    vp.push_back(1);
    for(int i = 2; i < prime; ++i){
        int value = i*i*i;
        if(value % prime == 1)
            vp.push_back(i);
    }
    return vp;
}
void find_all_n3_numbers(int cpos, i64 value, i64& sum, 
        vector<int>& remainders, const vector<int>& primes)
{
    if(cpos == static_cast<int>(remainders.size())){
        //now it is time to use chinese remainder theorem
        i64 x, y, gcd;
        i64 nc = 0;
        for(unsigned int i = 0; i < primes.size(); ++i){
            int px = primes[i];
            i64 mi = value/px;
            // we need x
            xgcd(mi, px, gcd, x, y); 
            if(x < 0){
                x%=px;
                x+=px;
            }
            i64 t = mi * x;
            t %= value;
            t*= remainders[i];
            t %= value;
            nc += t;
        }
        nc %= value;
        sum += nc;
        return;
    }
    for(unsigned int i = 0; i < vcands[cpos].size(); ++i){
        remainders[cpos] = vcands[cpos][i];
        find_all_n3_numbers(cpos+1, value, sum, remainders, primes);
    }
}
int main()
{
    i64 value = 13082761331670030LL;
    vector<int> primes; 
    primeWithin(primes, 44);
    vcands.resize(primes.size());
    for(unsigned int i = 0; i < primes.size(); ++i){
        vcands[i] = find_n3(primes[i]);
    }

    vector<int> remainders;
    remainders.resize(primes.size());
    i64 sum = 0;
    find_all_n3_numbers(0, value, sum, remainders, primes);
    printf("%lld\n", sum-1);
}
