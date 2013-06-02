#include <cstdio>
#include <vector>
#include <cassert>
#include "../lib/typedef.h"
#include "../lib/tools.h"
using namespace std;

vector<vector<int> > vna, vnb;
// ncfg is the number of config using n colors; 0 == 3 colors
// vn is the neighbor vector
// ncolor is the color used uptil i
// ncolor is the color used uptil i 
// final result is in ncfg
void enum_all_cfg(vector<vector<int> >& vn, int cpos, int ncolor, vector<int>& vcolor, vector<int>& ncfg)
{
    if(cpos == 7){
        assert(ncolor >= 3 && ncolor <= 7);
        ++ncfg[ncolor-3];
        return;
    }
    vector<int>& neighbor = vn[cpos];
    vector<int> allowed_color;
    allowed_color.resize(ncolor+1, 1);//choose a new color or use the allowed ones
    //color start from 0, so there is a shift 1 here;
    for(unsigned int i = 0; i < neighbor.size(); ++i){
        int ni = neighbor[i];
        int cx = vcolor[ni];
        assert(cx <= ncolor);
        allowed_color[cx-1] = 0;
    }
    for(unsigned int i = 0; i < allowed_color.size(); ++i){
        if(allowed_color[i] == 0) 
            continue;
        vcolor[cpos] = i+1;
        if(i ==  allowed_color.size()-1){
            enum_all_cfg(vn, cpos+1, ncolor+1, vcolor, ncfg);
        }else{
            enum_all_cfg(vn, cpos+1, ncolor, vcolor, ncfg);
        }
        vcolor[cpos] = 0;
    }
}

i64 permute_mod(i64 n, i64 a, i64 mod)
{
    assert(a>=1);
    i64 prod = 1;
    for(i64 i = 0; i < a; ++i){
       prod *= (n-i); 
       prod %= mod;
    }
    return prod;
}
int main()
{
    vna.resize(7);
    vnb.resize(7);
    vna[1].push_back(0);
    vna[2].push_back(0);
    vna[3].push_back(1);
    vna[3].push_back(2);
    vna[4].push_back(0);
    vna[4].push_back(2);
    vna[5].push_back(1);
    vna[5].push_back(3);
    vna[6].push_back(4);
    vna[6].push_back(5);
    
    vnb[1].push_back(0);
    vnb[2].push_back(0);
    vnb[3].push_back(2);
    vnb[4].push_back(0);
    vnb[4].push_back(2);
    vnb[5].push_back(1);
    vnb[5].push_back(3);
    vnb[6].push_back(4);
    vnb[6].push_back(5);

    vector<int> nacfg, nbcfg;
    nacfg.resize(5,0);
    nbcfg.resize(5,0);
    
    vector<int> vcolor;
    vcolor.resize(7, 0);
    vcolor[0]=1;
//void enum_all_cfg(vector<vector<int> >& vn, int cpos, int ncolor, vector<int>& vcolor, vector<int>& ncfg)
    enum_all_cfg(vna, 1, 1, vcolor, nacfg);
    for(unsigned int i = 0; i < vcolor.size(); ++i){
        assert(vcolor[i]==0||(vcolor[i]==1 && i==0));
    }
    enum_all_cfg(vnb, 1, 1, vcolor, nbcfg);

    i64 mod = 100000000;
    i64 result = permute_mod(1984, 2, mod);
    i64 ar=0, br = 0;
    for(unsigned int i = 0; i < nacfg.size(); ++i){
        ar += permute_mod(1982, i+1, mod) * nacfg[i];
        ar %= mod;
        br += permute_mod(1982, i+1, mod) * nbcfg[i];
        br %= mod;
    }
    i64 a1 = powermodule(ar, 25LL, mod);
    i64 b1 = powermodule(br, 75LL, mod);
    result *= a1;
    result %= mod;
    result *= b1;
    result %= mod;
    result *= 21015504LL;//last 8 digit of C^100_25;
    result %= mod;
    printf("%lld\n", result);
    //for(unsigned int i = 0; i < nacfg.size(); ++i){
    //    printf("color %d cnta %d, cntb %d\n", i+3, nacfg[i], nbcfg[i]);
    //}
}
