#include <cstdio>
#include <queue>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <cmath>
#include "../lib/tools.h"
#include "../lib/typedef.h"
using namespace std;

//one number corresponding a configuration
//each digit can be 0, 1,2. so trinary
i64 calc_ncfg(const vector<short>& vcfg)
{
    i64 sum = 0;
    assert(vcfg.size() == 16);
    for(unsigned int i = 0; i < vcfg.size(); ++i){
        sum *= 3;
        sum += vcfg[i];
    }
    return sum;
}

vector<short> calc_grid(int nstate)
{
    vector<short> vcfg;
    vcfg.resize(16, 0);
    for(int i = 15; i >= 0; --i){
        vcfg[i] =  nstate % 3;
        nstate /= 3;
    }
    return vcfg;
}

//find all neighbors
vector<int> getNeighbors(int nstate )
{
    vector<short> vcfg = calc_grid(nstate);
    int row = -1; int col = -1; int ni=-1;
    //find the "empty grid"
    for(unsigned int i = 0; i < vcfg.size(); ++i){
        if(vcfg[i] == 2){
            ni = i;
            break;
        }
    }
    assert(ni >= 0 && ni < 16);
    row = ni/4;
    col = ni%4;

    vector<int> neighbors;
    neighbors.resize(4, -1);

    vector<short> vt(vcfg);
    if(row != 0){ //down 0
        int nt = ni - 4;
        swap(vt[ni], vt[nt]);
        i64 nc1 = calc_ncfg(vt);
        swap(vt[ni], vt[nt]);
        neighbors[0]= nc1;
    }
    if(row !=3){//up 1
        int nt = ni + 4;
        swap(vt[ni], vt[nt]);
        i64 nc1 = calc_ncfg(vt);
        swap(vt[ni], vt[nt]);
        neighbors[1]= nc1;
    }
    if(col != 0){//right 2
        int nt = ni - 1;
        swap(vt[ni], vt[nt]);
        i64 nc1 = calc_ncfg(vt);
        swap(vt[ni], vt[nt]);
        neighbors[2]= nc1;
    }
    if(col != 3){//left 3
        int nt = ni + 1;
        swap(vt[ni], vt[nt]);
        i64 nc1 = calc_ncfg(vt);
        swap(vt[ni], vt[nt]);
        neighbors[3]= nc1;
    }
    return neighbors;
}

i64 search_all_shortest_pathes(int g0, int g1, unordered_set<int>& idmaps, int gid)
{
    // dmin is the minimum step globally.
    vector<int> vsteps; vsteps.resize(102960, 0);
    vector<int> vids; vids.resize(102960);
    vids[gid++] = g0;
    vector<int> vchecksum = {68, 85, 82, 76};
    bool notFound = true;
    int nstart = 0, nend = 1, n,n1, steps = 0;
    i64 sum = 0;
    while(notFound){
        n1 = nend;
        for(n = nstart; n < nend; ++n){
            ++steps;
            //vnb stores the state number
            vector<int> vnb = getNeighbors(vids[n]);
            for(unsigned int i = 0; i < vnb.size(); ++i){
                if(vnb[i]== -1) continue;
                auto iter = idmaps.find(vnb[i]);
                if(iter != idmaps.end()) 
                    continue;
                idmaps.insert(vnb[i]);
                i64 value = vsteps[n]*243LL+vchecksum[i];
                value %= 100000007LL;
                vsteps[gid] = value;
                vids[gid++] = vnb[i];
                if(vnb[i] == g1){
                    sum += value;
                    notFound = false;
                }
                ++n1;
            }
        }
        nstart = nend;
        nend = n1;
    }
    return sum;
}
int main()    
{
    unordered_set<int> idmaps;
    int gid = 0;
    struct timer mytimer;
    vector<int> vcnt = {7, 8, 1};
    vector<short> vcfg; vcfg.resize(16, 0);
    //RED=0, BLUE=1, EMPTY=2; // 8 blue, 7 red, 1 empty
    vector<short> vdest =   {2, 1, 0, 1,1,0,1,0,0,1,0,1,1,0,1,0};
    vector<short> vsource = {2, 0, 1, 1,0,0,1,1,0,0,1,1,0,0,1,1};
    i64 nstart = calc_ncfg(vsource);
    i64 nend = calc_ncfg(vdest);
    i64 shortest = search_all_shortest_pathes(nstart, nend, idmaps, gid);
    printf("%lld size %zu\n", shortest, idmaps.size());
}
