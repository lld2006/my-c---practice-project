#include <cstdio>
#include "../lib/typedef.h"
#include <vector>
using namespace std;
int main()
{
    int target = 1000000;
    vector<int> vn;
    vn.resize(target+1, 0);
    for(i64 i = 250001; i>=3; --i){
        for(i64 j = i-2; j > 0;j-=2 ){
            i64 val = i*i-j*j;
            if(val > target) break;
            ++vn[val];
        }
    }
    int cnt = 0;
    for(unsigned int i = 0; i < vn.size(); ++i){
        if(vn[i]>0 && vn[i]<=10)++cnt;
    }
    printf("%d\n", cnt);
}
