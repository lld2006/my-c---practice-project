#include <cstdio>
#include <unordered_map>
#include <cassert>
#include <vector>
#include "../lib/typedef.h"
using namespace std;
vector<int> vperiods;
unordered_map<int, int> cyclic_number_map;
int facsum(int num, const vector<int>& vfac)
{
    int sum = 0;
    while(num){
        int res = num % 10;
        sum += vfac[res];
        num /= 10;
    }
    return sum;
}
int non_repeating(int num, int cnt, const vector<int>& vfac, unordered_map<int,int>& hmap, bool& flag, int& firstnum)
{
    int sum = facsum(num, vfac);
    auto iter = cyclic_number_map.find(sum);
    if(iter == cyclic_number_map.end()){//sum is not a cyclic number
        if(sum < static_cast<int>(vperiods.size())){
            if(vperiods[sum] > 0){
               flag = true;
               return vperiods[sum];
            }
        }
        auto iter2 =  hmap.find(sum);
        if(iter2 == hmap.end()){ //sum is a different number in this sequence
            hmap.insert(IntPair(sum, cnt+1));
            int period = non_repeating(sum, cnt+1, vfac, hmap, flag, firstnum);
            if(flag == false){
                if(sum == firstnum){
                    flag = true;
                    return period;
                }else{
                    return period;
                }
            }else{
                if(sum < static_cast<int>(vperiods.size()))
                    vperiods[sum] = period + 1;
                return period + 1;
            }
        }else{//sum appeared in the sequence
            firstnum = sum;
            cyclic_number_map.insert(IntPair(sum, cnt+1-iter2->second));
            if(sum < static_cast<int>(vperiods.size()))
                vperiods[sum] = cnt+1-iter2->second;
            return cnt +1 - iter2->second;
        }
    }else{//sum is a cyclic number
        flag = true;
        return iter->second;
    }
}
int main()
{
    vector<int> vfac;
    vperiods.resize(1000000, -1);
    int prod = 1;
    vfac.push_back(1);
    for(unsigned int i = 1; i < 10; ++i){
        prod *= i;
        vfac.push_back(prod);
    }
    int cnt = 0;
    for( int i = 3; i <= 1000000; ++i){
        if(vperiods[i] >= 0){
            assert(vperiods[i] != 60);
            continue;
        }
        unordered_map<int, int> h2map;
        h2map.insert(IntPair(i, 0));
        bool flag = false;
        int firstnum = 0;
        int value = non_repeating(i, 0, vfac, h2map, flag, firstnum)+1;
        if(i==firstnum){
            cyclic_number_map.insert(IntPair(i,1));
        }else{
            assert(flag == true);
        }
        //printf("%d %d\n", i, value);
        if(value ==60)
            ++cnt;
    }
    printf("%d\n", cnt);
}
