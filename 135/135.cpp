#include <cstdio>
#include <vector>
#include "../lib/typedef.h"
using namespace std;
int main()
{
    int limit = 1000000;
    vector<int> vflags;
    vflags.resize(limit, 0);
    for(i64 d = 1; d < limit/4+1; ++d){
        bool found = true;
        for(i64 y = d+1; y<=2*d; ++y){
            i64 value = y*(4*d-y);
            if(value >= limit )
                break;
            ++vflags[value];
        }
        for(i64 y = 4*d-1; y>2*d; --y){
            i64 value = y*(4*d-y);
            if(value >= limit )
                break;
            ++vflags[value];
        }
        if(!found) break;
    }
    int cnt = 0;
    for(unsigned int i= 1; i< vflags.size();++i){
        if(vflags[i]==10){
            ++cnt;
        }
    }
    printf("%d\n", cnt);
}
