#include <cstdio>
#include <vector>
#include <numeric>
#include "../lib/tools.h"
using namespace std;
int target = 6000;
void backtrack_solve(int level, int cvalue, vector<int>& data, vector<int>& mincost)
{
    if(cvalue > target || mincost[cvalue] < level) return;
    mincost[cvalue] = level;
    data[level] =  cvalue;
    int newlevel = level+1;
    for(int i = level; i>=0; --i){
        int newvalue = cvalue+data[i];
        backtrack_solve(newlevel, newvalue, data, mincost);
    }
}
int main()
{
    vector<int> mincost;
    vector<int> data;
    mincost.resize(target+1, target);
    data.resize(target+1, 0);
    data[0] = 1;
    mincost[0]= 0;
    mincost[1]= 0;
    int level = 0, cvalue = 1;
    backtrack_solve(level, cvalue, data, mincost);
    int sum = accumulate(mincost.begin(), mincost.end(), 0);
    printf("%d\n", sum);
}
