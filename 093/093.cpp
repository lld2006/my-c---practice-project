#include <cstdio>
#include <vector>
#include <cmath>
#include "../lib/tools.h"
using namespace std;

vector<int> gflags;

void solve(const vector<int>& vn, vector<int>& flags, vector<double>& vals, int used )
{
    if(used == 4){
        for(unsigned int i = 0; i < vals.size(); ++i){
            int tval = round(vals[i]);
            if(tval <= 0) continue;
            if(fabs(tval - vals[i]) < 1e-8 && tval < static_cast<int>(gflags.size())){
                gflags[tval] = 1;
            }
        }
        return;
    }
    if(vals.empty()){
        for(unsigned int i = 0; i < vn.size(); ++i){
            vals.push_back(vn[i]+1);
            flags[i] = 1;
            solve(vn, flags, vals, 1);
            flags[i] = 0;
            vals.clear();
        }
    }else{
        for(unsigned int i = 0; i < vn.size(); ++i){
            if(flags[i]) continue;
            flags[i] = 1;
            int nx = vn[i]+1;
            vector<double> val1;
            for(unsigned int j = 0; j < vals.size(); ++j){
                val1.push_back(vals[j] + nx);
                val1.push_back(vals[j] * nx);
                val1.push_back(vals[j] / nx);
                if(vals[j] != 0.0)
                    val1.push_back(nx/vals[j]);
                val1.push_back(vals[j] - nx);
                val1.push_back(nx - vals[j]);
            }
            solve(vn, flags, val1, used+1);
            flags[i] = 0;
        }
    }
}

int find_all_solutions(vector<int> vn)
{
    gflags.clear();
    gflags.resize(1000, 0);
    vector<double> vals;
    vector<int> flags;
    flags.resize(4,0);
    solve(vn, flags, vals, 0);
    unsigned int i = 0;
    for(i = 1; i < gflags.size(); ++i){
        if(gflags[i] == 0)
            break;
    }
    return i- 1;
}

int main()
{
    gflags.resize(1000, 0);
    vector<int> vn={0,1,2,3};
    int smax = 0;
    do{
        int ts = find_all_solutions(vn);
        if(ts > smax){
            smax = ts;
            printf("%d%d%d%d %d\n", vn[0]+1, vn[1]+1, vn[2]+1, vn[3]+1, smax);
        }
    }while(next_combination(vn, 9, 4));
}
