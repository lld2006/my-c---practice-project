#include <cstdio>
#include <unordered_set>
#include <vector>
using namespace std;

int limit = 1000000;
int main()
{
    vector<int> vn;
    vn.resize(limit+1, 1);
    vn[0] = 0;
    vn[1] = 0;
    for( int i =2; i <= limit/2; ++i){
        int nx = i;
        for(unsigned int j = 2*nx; j < vn.size(); j+=nx){
            vn[j] += nx;
        }
    }
    vector<int> flags;//this vector is used to find those numbers 
    //that return to itself
    flags.resize(limit+1, 0);//-1 means uninitialized
    int level = 0, level0 = 0;
    for(unsigned int i = 2; i <vn.size(); ++i ){
        if(flags[i]) continue;
        level0 = level;
        int nx = i;
        while(nx <= limit && flags[nx] == 0){
            flags[nx] = --level;
            nx = vn[nx];
        }
        if(nx > limit ) continue;
        if(flags[nx] < level0)
            flags[nx] -= (level-1);
    }
    int chain_length = 0;
    int maxi = 0;
    for(unsigned int i = 1; i < flags.size(); ++i){
        if(flags[i] > chain_length){
            chain_length = flags[i];
            maxi = i;
        }
    }
    printf("value is %d length is %d\n", maxi, chain_length);
}
