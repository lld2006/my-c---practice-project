#include <cstdio>
#include <vector>
#include <algorithm>
#include "../lib/tools.h"
using namespace std;
class pairLess{
    public:
    bool operator()(const IntPair& p1, const IntPair& p2) const
    {
        return (p1.second < p2.second)||(p1.second==p2.second && p1.first < p2.first);
    }
};
int main()
{
    int target = 1000001;
    vector<int> vrad;
    vrad.resize(target+1, 1);
    //using sieve method to create radical for all n
    for( int i = 2; i <= target; ++i){
        if(vrad[i] == 1){
            for(unsigned int j = i; j < vrad.size(); j+=i){
                vrad[j] *= i;
            }
        }
    }
    vector<IntPair> vpairs;
    vpairs.reserve(target+1);
    int tag2 = target/2;
    for( int i = 1; i <= target; ++i){
        if(vrad[i] > tag2 ) continue;
        vpairs.push_back(IntPair(i, vrad[i])); 
    }
    sort(vpairs.begin(), vpairs.end(), pairLess());
    i64 sum = 0;
    for( int b= 2; b< target; ++b){
        int ramax = b/vrad[b];
        for(int i = 0; vpairs[i].second <= ramax; ++i){
            int a = vpairs[i].first;
            int c = a + b;
            if(a >= b || c >= target) continue;
            i64 value = (i64)vrad[a]*vrad[b]*vrad[c];
            if(value > c) continue;
            if(gcd(a, b) > 1) continue;
            sum += c;
        }
    }
    printf("%lld\n", sum);
}
