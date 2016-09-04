#include <cstdio>
#include <cassert>
#include <algorithm>
#include "../lib/tools.h"

int convert_input(int n)
{
    assert(n>=0 && n<64);
    int na = n & 1;
    int nb = (n & 2)>>1;
    int nc = (n & 4)>>2;
    n >>= 1;
    nb = nb & nc;
    na += nb;
    na %= 2;
    n+= (na<<5);
    return n;
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
    //add in front of the i...j sequence and always 
    //satisfy the condition, first is i last is j
    for(unsigned int i= 3; i < data.size();++i){
        v00[i]=v00[i-1]+v10[i-1];
        v01[i]=v01[i-1]+v11[i-1];
        v10[i]=v00[i-1];
        v11[i]=v01[i-1];
        data[i]=v00[i]+v01[i]+v10[i];//satisfy the criteria
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
