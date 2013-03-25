#include <cstdio>
#include <cassert>
#include <vector>
using namespace std;
int find_nim(int n, vector<int>& vn)
{
    vector<int> flags;
    flags.resize(1000, 0);
    for( int i = 0; i<=n/2-1;++i){
        int j = n-2-i;
        assert(i<=j);
        int tres = vn[i] ^ vn[j];
        flags[tres]=1;
    }
    for(unsigned int i =0; i < flags.size(); ++i)
        if(flags[i] == 0)
            return i;
    assert(0);
    return -1;
}
int main()
{
    int limit = 1000;
    vector<int> vn;
    vn.resize(limit+1, 0);
    vn[0] = 0;
    vn[1] = 0;
    vn[2] = 1;
    for(int k = 3; k <= limit; ++k){
        vn[k] = find_nim(k, vn);
    }
    for(unsigned int i = 0; i < vn.size(); ++i){
        if(vn[i] == 0)
        printf("%d %d\n", i, vn[i]);
    }
}
