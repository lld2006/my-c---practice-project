#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
using namespace std;
//it would be nice if I check the three numbers goes back to 1 1 1
int main()
{
    bool flag = false;
    vector<int> vtf;
    int limit = 50000;
    for(unsigned int ni =3; ni ; ni+=2){
        vector<int> vtri;
        vtri.resize(4,1);
        vtri.resize(limit+1, 0);
        flag = false;
        for(unsigned int i = 4; i < limit+1; ++i){
            i64 nt = vtri[i-1] + vtri[i-2] + vtri[i-3];
            nt %= ni;
            if(nt % ni == 0){
                flag = true;
                break;
            }
            vtri[i] = nt;
        }
        if(!flag)
            vtf.push_back(ni);
        if(vtf.size()==124)break;
    }
    printf("%d\n", vtf.back());
}
