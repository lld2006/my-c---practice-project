#include <cstdio>
#include <cassert>
#include <vector>
#include "../lib/typedef.h"
using namespace std;
//this works, but still too slow!
vector<i64> vfac;
vector<int> vsq;
i64 nmod = 1000000000LL;
i64 search_all_numbers(int cnum, int dcnt, int dsum, int sum1, i64 prod)
{
    if(dcnt == 20){
        if(!vsq[dsum]) return 0;
        i64 val = prod*sum1;
        assert(val % 20 ==0);
        return (val/20)%nmod ;
    }else if(cnum == 9){
        int dsum1 = (20-dcnt) * 81+ dsum;
        if(!vsq[dsum1]) return 0;
        prod /= vfac[20-dcnt];
        sum1+=9*(20-dcnt);
        i64 val = prod * sum1;
        assert(val % 20 ==0);
        return (val/20)%nmod ;
    }
    i64 sum = 0;
    int c2 = cnum*cnum;
    for( int ni = 0; ni <= 20-dcnt; ++ni){
       int sumx = sum1+ni*cnum;
       sum += search_all_numbers(cnum+1, dcnt+ni, dsum+ni*c2, sumx, prod/vfac[ni]);
    }
    return sum%nmod;
}
int main()
{
    vfac.resize(21, 1);
    i64 prod = 1;
    for(i64 i = 2; i< vfac.size(); ++i){
        prod *= i;
        vfac[i] = prod;
    }

    vsq.resize(1621, 0);
    for(int i = 1; i*i < vsq.size(); ++i){
        vsq[i*i] = 1;
    }
    i64 value = search_all_numbers(0, 0,0,0,vfac[20]);
    vector<i64> vt;
    vt.resize(9, value);
    i64 carry = 0;
    for(unsigned int i = 0; i<vt.size(); ++i){
        i64 val = vt[i] + carry;
        vt[i] = val % 10;
        carry = val/10;
    }
    for( int i = vt.size()-1; i>=0; --i){
        printf("%lld", vt[i]);
    }
    printf("\n");
}
