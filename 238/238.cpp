#include <cstdio>
#include <cassert>
#include <numeric>
#include <vector>
#include <bitset>
#include "../lib/tools.h"
#include "../lib/typedef.h"
using namespace std;

vector<int> get_vector(int num)
{
    vector<int> vr;
    int sum = 0;
    while(num){
        sum = num%10;
        vr.push_back(sum);
        num/=10;
    }
    return vr;
}

void create_vns(i64 seed, vector<int>& vns, vector<short>& vds, i64& span, i64& period)
{
    i64 nmod = 20300713;
    i64 n0 = seed;
    vds.resize(20000000);
    int iter = 0;
    
    while(true){
        vns.push_back(seed);
        vector<int> vt = get_vector(seed);
        for(unsigned int j = vt.size(); j> 0; --j)
            vds[iter++] = vt[j-1];
        seed *= seed;
        seed %= nmod;
        if(n0 == seed) break;
    }
    span = accumulate(vds.begin(), vds.begin()+iter, 0LL);
    period = iter;
    for(unsigned int i = 0; i < 200; ++i){
        vector<int> vt = get_vector(seed);
        for(unsigned int j = vt.size(); j> 0; --j)
            vds[iter++] = vt[j-1];
        seed *= seed;
        seed %= nmod;
    }
    vds.resize(iter+1);
}
int main()
{
    timer mytime;
    vector<int> vn;
    const int val =  80846691;
    const int val2 = val+1;
    bitset<val2>* pbit = new bitset<val2>;
    bitset<val2>& mybit = *pbit;
    mybit.reset();

    vector<short> vds;
    i64 span, period; 
    create_vns(14025256, vn, vds, span, period);
    i64 sum = 0;
    //the starting digit is nth+1;
    i64 limit = 2000000000000000LL;
    //limit = 1000;
    mybit.set(0);
    printf("%.6f\n", mytime.getTime());
    int nmod = limit % span;
    int value = limit/span;
    for(unsigned int nth = 0; nth < 200; ++nth){
        //if(nth % 10 ==0) 
        //    printf("%d %lld\n", nth, sum);
        if(nth > 0 && !vds[nth-1]) continue;
        int dsum = 0;
        for(unsigned int j = nth; j< nth+period; ++j){
           int nt = j;
           dsum += vds[nt];
           if(!mybit.test(dsum)){
                mybit.set(dsum);
                // the following code is necessary when limit is small
                //if(dsum > limit) break;
                if(dsum <= nmod)
                    sum += (value+1) * (nth+1); 
                else
                    sum += (value) * (nth+1); 
           } 
        }
    }
    printf("%lld\n", sum);
}
