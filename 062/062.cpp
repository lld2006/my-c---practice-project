#include <cstdio>
#include <cmath>
#include <cstdlib>
#include "../lib/typedef.h"
#include "../lib/tools.h"
#include <unordered_map>

i64 getNumber(i64 num){
    vector<int> vn;
    vn.resize(10, 0);
    while(num){
        int remainder = num%10;
        ++vn[remainder];
        num/=10;
    }
    i64 sum = 0;
    for(unsigned int i = 0;i < vn.size(); ++i){
        sum *= 10;
        sum += vn[i];
    }
    return sum;
}
int main()
{
    unordered_map<i64, pair<i64, int>> hmap;
    for( i64 i = 346; i; ++i){
        i64 n3 = i*i*i;
        i64 value = getNumber(n3);
        auto iter = hmap.find(value);
        if(iter != hmap.end()){ 
            ++iter->second.second;
            if(iter->second.second == 5){
                printf("%lld\n", iter->second.first);
                return 0;
            }
        }else
            hmap.insert(make_pair(value, pair<i64, int>(n3, 1)));
    }
}
