#include <cstdio>
vector<i64> allcfgs;
map<i64, i64> nmaps;
i64 shortest = 10000000;

//one number corresponding a configuration
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

//find all neighbors
void build_map(const vector<int>& vcfg, i64 nc)
{
    int row = -1; int col = -1; int ni=-1;
    for(unsigned int i = 0; i < vcfg.size(); ++i){
        if(vcfg[i] == 2){
            ni = i;
            break;
        }
    }
    assert(ni >= 0);
    row = ni/4;
    col = ni%4;
    vector<int> vt(vcfg);
    if(row != 0){
        int nt = ni - 4;
        swap(vt[ni], vt[nt]);
        i64 nc1 = calc_ncfg(vt);
        nmaps.insert(pair<i64, i64>(nc, nc1));
        swap(vt[ni], vt[nt]);
    }
    if(row !=3){
        int nt = ni + 4;
        swap(vt[ni], vt[nt]);
        i64 nc1 = calc_ncfg(vt);
        nmaps.insert(pair<i64, i64>(nc, nc1));
        swap(vt[ni], vt[nt]);
    }
    if(col != 0){
        int nt = ni - 1;
        swap(vt[ni], vt[nt]);
        i64 nc1 = calc_ncfg(vt);
        nmaps.insert(pair<i64, i64>(nc, nc1));
        swap(vt[ni], vt[nt]);
    }
    if(col != 3){
        int nt = ni - 1;
        swap(vt[ni], vt[nt]);
        i64 nc1 = calc_ncfg(vt);
        nmaps.insert(pair<i64, i64>(nc, nc1));
        swap(vt[ni], vt[nt]);
    }
}
//get all possible configurations
void search_configs(int cpos, const vector<int>& vcfg)
{
    if(cpos == 16){
        i64 nc = calc_ncfg(vcfg); 
        allcfgs.push_back(nc);
        build_map(vcfg, nc);
        return ;
    } 
    vector<int> vc1(vcfg);
    for(int i = 0; i<3; ++i){
        vc1[cpos] = i;
        search_configs(cpos+1, vc1);
    }
}

int ndist(int ndiff)
{
    int cnt = 0;
    while(ndiff > 0){
        if(n % 3 != 0){
            ++cnt;
        }
        n /= 3;
    }
    assert(cnt != 1);
    //in my case, if one square is not correct, at least cnt >= 2
    return cnt;
}

int main()    
{
    vector<int> vcfg;
    vcfg.resize(16, 0);
    search_configs(0, vcfg); 
    i64 ndest = 0;
    vector<int> vdest, vsource;
    vdest.resize(16, 0);
    vsource.resize(16, 0);
    //just 16 squares, set it directly, no need to use algo
    vsource[0] = 2; vsource[2] = 1; vsource[3] = 1; vsource[6] = 1;
    vsource[7] = 1; vsource[10] = 1; vsource[11] = 1; vsource[14] = 1;
    vsource[15] = 1;
    vdest[0] = 2; vdest[1] = 1; vdest[3] = 1; vdest[4] = 1; vdest[6] = 1; 
    vdest[9] = 1; vdest[11] = 1; vdest[12] = 1; vdest[14] = 1; 
    i64 nstart = 0, nend = 0;
    nstart = calc_ncfg(vsource);
    nend = calc_ncfg(vdest);
    search_all_shortest_pathes();
}
