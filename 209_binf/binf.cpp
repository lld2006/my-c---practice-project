#include <cstdio>
#include <cassert>
#include "../lib/tools.h"
#include <algorithm>
#include <deque>

int convert_input(int n)
{
    assert(n>=0 && n<64);
    vector<int> vr;
    vr.resize(6, 0);
    int cnt = 0;
    while(n > 0){
        int res = n&1;
        n/=2;
        if(res)
            vr[cnt]=1;
        ++cnt;
    }
    int nx = vr[0];
    nx = vr[1] & vr[2];
    nx += vr[0];
    nx %= 2;
    vr.erase(vr.begin());
    vr.push_back(nx);
    int sum = 0;
    for(int i = 5; i >= 0; --i){
        sum*=2;
        sum += vr[i];
    }
    assert(sum >= 0 && sum < 64);
    return sum;
}

void create_data(int nmax, vector<i64>& data)
{
    assert(nmax >= 2);
    data.resize(nmax, 0);
    vector<i64> v00, v01, v10, v11;
    v00.resize(nmax, 0);
    v01.resize(nmax, 0);
    v10.resize(nmax, 0);
    v11.resize(nmax, 0);
    v00[2] = 1;
    v01[2] = 1;
    v10[2] = 1;
    v11[2] = 0;
    data[1]=1;
    data[2]=3; 
    for(unsigned int i= 3; i < data.size();++i){
        v00[i]=v00[i-1]+v10[i-1];
        v01[i]=v01[i-1]+v11[i-1];
        v10[i]=v00[i-1];
        v11[i]=v01[i-1];
        data[i]=v00[i]+v01[i]+v10[i];
    }
    return;
}

int main()
{
    vector<DisJointSet> vb;
    vb.resize(64);
    vector<i64> data;
    for(unsigned int ni= 0; ni <vb.size(); ++ni){
        unsigned int nout = convert_input(ni);
        if(vb[ni].get_value() == -1)
            vb[ni].makeset(ni);
        if(vb[nout].get_value() == -1)
            vb[nout].makeset(nout);
        if(ni != nout){
            vb[ni].union_set(vb[nout]);
        }
    }
    create_data(50, data);
    i64 product = 1;
    for(unsigned int ni = 0; ni < vb.size(); ++ni){
        if(vb[ni].parent() == &vb[ni]){
            printf("%d %d %lld\n",ni, vb[ni].set_size(), data[vb[ni].set_size()]);
            product*=data[vb[ni].set_size()];
        }
    }
    printf("%lld\n", product);
}
