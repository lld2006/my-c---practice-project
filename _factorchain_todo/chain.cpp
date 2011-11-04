#include <vector>
#include <map>
#include <cstdio>
#include <cassert>
#include <climits>
#include <algorithm>
using namespace std;
//              0  1  2  3   4   5    6     7      8      9
   int fac[10]={1, 1, 2, 6, 24,120, 720, 5040, 40320,362880};
int chain(int i, vector<int>& len, map<int,int>& dist, int& count)
{
    if(len[i]) {
        count = INT_MAX;
        return len[i];
    }
    map<int,int>::iterator iter;
    if( (iter=dist.find(i)) == dist.end()){ 
        // not found need to calc sum
        dist.insert(pair<int, int>(i, ++count));
        int ix = i;
        int sum = 0;
        while(ix){
            int res = ix % 10;
            sum += fac[res];
            ix /= 10;
        }
        int length = chain(sum, len, dist, count);
        iter = dist.find(i);
        assert(iter != dist.end());
        if(iter->second >= count){
            //assert(len[i] == 0); not correct for period 1
            len[i] = length;
            return length;
        }else{
            len[i]=length+1;
            return len[i];
        }
        
    }else{
        int cnt0 = iter->second;
        len[i] = count-cnt0+1;
        count = cnt0;
        return len[i];
    }
}

int main()
{
    vector<int> len;
    map<int, int> dist;
    int upper = 1000000;
    len.resize(10000000, 0);
    for(int i = 0; i < upper; ++i){
        int cnt = 0;
        dist.clear();
        chain(i, len, dist, cnt);
    }
    int num = count(len.begin(), len.begin()+999999,60);
    printf("%d\n", num);
}
