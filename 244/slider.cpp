#include <cstdio>
#include <queue>
#include <vector>
#include <map>
#include <cassert>
#include <cmath>
#include "../lib/tools.h"
#include "../lib/typedef.h"
using namespace std;
vector<vector<int>> cfgnbrs;
vector<int> vns;
map<i64, int> idmaps;
int gid = 0;
int gfinal = 0;

struct block 
{
    int id;
    int steps;
    i64 checksum;
    block(int id0, int step0, i64 ck0){
        id = id0;
        steps = step0;
        checksum = ck0;
    }
};

//one number corresponding a configuration
//each digit can be 0, 1,2. so trinary
i64 calc_ncfg(const vector<int>& vcfg)
{
    i64 sum = 0;
    assert(vcfg.size() == 16);
    for(unsigned int i = 0; i < vcfg.size(); ++i){
        sum *= 3;
        sum += vcfg[i];
    }
    return sum;
}

void insert_map(i64 nc1, vector<int>& neighbors, int pos )
{
    assert(gid <= 102960);
    assert(gid == static_cast<int>(idmaps.size()));
    auto iter = idmaps.find(nc1);
    if( iter == idmaps.end()){
        neighbors[pos] = gid;
        idmaps.insert(make_pair(nc1, gid++));
    }else{
        neighbors[pos] = iter->second;
    }
}
//find all neighbors
void build_map(const vector<int>& vcfg, i64 nc)
{
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

    auto iter0 = idmaps.find(nc);
    assert(iter0 != idmaps.end());
    int g0 = iter0->second;

    vector<int> neighbors;
    neighbors.resize(4, -1);

    vector<int> vt(vcfg);
    if(row != 0){ //down 0
        int nt = ni - 4;
        swap(vt[ni], vt[nt]);
        i64 nc1 = calc_ncfg(vt);
        insert_map(nc1, neighbors, 0);
        swap(vt[ni], vt[nt]);
    }
    if(row !=3){//up 1
        int nt = ni + 4;
        swap(vt[ni], vt[nt]);
        i64 nc1 = calc_ncfg(vt);
        insert_map(nc1, neighbors, 1);
        swap(vt[ni], vt[nt]);
    }
    if(col != 0){//right 2
        int nt = ni - 1;
        swap(vt[ni], vt[nt]);
        i64 nc1 = calc_ncfg(vt);
        insert_map(nc1, neighbors, 2);
        swap(vt[ni], vt[nt]);
    }
    if(col != 3){//left 3
        int nt = ni + 1;
        swap(vt[ni], vt[nt]);
        i64 nc1 = calc_ncfg(vt);
        insert_map(nc1, neighbors, 3);
        swap(vt[ni], vt[nt]);
    }
    cfgnbrs[g0] = (neighbors);
    vns[g0] = nc;
}
//get all possible configurations for 7 8 1
void search_configs(int cpos, vector<int>& vcfg, vector<int>& vcnt )
{
    if(cpos == 16){
        i64 nc = calc_ncfg(vcfg); 
        assert(gid <= 102960);
        assert(gid == static_cast<int>(idmaps.size()));
        if(idmaps.find(nc) == idmaps.end())
            idmaps.insert(make_pair(nc, gid++));
        build_map(vcfg, nc);
        return;
    } 
    for(int i = 0; i<3; ++i){
        if(vcnt[i]==0) continue;
        vcfg[cpos] = i;
        --vcnt[i];
        search_configs(cpos+1, vcfg, vcnt);
        ++vcnt[i];
        vcfg[cpos] = 0;
    }
}

//if it takes less steps or closer to the destination
class pairless{
    public:
        bool operator()(const block& p1, const block& p2){
            return p1.steps > p2.steps || ((p1.steps== p2.steps) && abs(vns[p1.id]-vns[gfinal]) > abs(vns[p2.id]-vns[gfinal]));
        }
};

void search_all_shortest_pathes(int g0, int g1, int dmin)
{
    priority_queue<block, vector<block>, pairless> vpq; 
    vpq.push(block(g0,0, 0));
    i64 dsum = 0;//return answer
    // dmin is the minimum step globally.
    vector<int> vsteps; vsteps.resize(102960, 10000000);
    vsteps[g0] = 0;
    vector<int> vchecksum = {68, 85, 82, 76};
    while(!vpq.empty()){
        block tblock = vpq.top();
        vpq.pop();
        int id = tblock.id;
        if(tblock.steps > vsteps[id]) continue;
        if(id==gfinal){
            if(tblock.steps < dmin){
                printf("number of steps is %d\n", tblock.steps);
                dmin = tblock.steps;
                dsum = tblock.checksum;
            }else if(tblock.steps == dmin){
                printf("%lld\n", dsum);
                dsum += tblock.checksum;
            }
            continue;
        }
        vector<int>& vnbrs = cfgnbrs[id];
        int nsteps = tblock.steps + 1;
        for(unsigned int i = 0; i < vnbrs.size(); ++i){
            if(vnbrs[i] < 0) continue;
            int nb = vnbrs[i];
            if(nsteps > vsteps[nb] || nsteps > dmin)continue;
            vsteps[nb] = nsteps;
            i64 newsum = tblock.checksum * 243LL + vchecksum[i];
            newsum %= 100000007LL; 
            vpq.push(block(nb, nsteps, newsum));
        }
    }
    printf("%lld\n", dsum);
}
int main()    
{
    struct timer mytimer;
    vector<int> vcnt = {7, 8, 1};
    vector<int> vcfg; vcfg.resize(16, 0);
    cfgnbrs.resize(102960);
    vns.resize(102960);
    search_configs(0, vcfg, vcnt); 
    //RED=0, BLUE=1, EMPTY=2; // 8 blue, 7 red, 1 empty
    vector<int> vdest =   {2, 1, 0, 1,1,0,1,0,0,1,0,1,1,0,1,0};
    vector<int> vsource = {2, 0, 1, 1,0,0,1,1,0,0,1,1,0,0,1,1};
    i64 nstart = calc_ncfg(vsource);
    i64 nend = calc_ncfg(vdest);
    int shortest = 100000;
    int g0 = idmaps.find(nstart)->second;
    int g1 = idmaps.find(nend)->second;
    gfinal = g1;
    assert(vns[g0]==nstart);
    assert(vns[g1]==nend);
    printf("%.6f\n", mytimer.getTime());
    search_all_shortest_pathes(g0, g1, shortest);
}
