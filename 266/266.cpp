#include "../lib/tools.h"
#include <cassert>
#include <numeric>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef pair<double, int> dipair;
class pairsort
{
  public:
    bool operator()(const dipair& p1, const dipair& p2)
    {
        assert(p1.first != p2.first);
        return p1.first < p2.first; 
    }
};
int bsearch(vector<dipair>& vn, double value)
{
    if(value > vn.back().first){
        return vn.size()-1;
    }
    if((vn.begin())->first > value){
        assert(0);
        assert(value == 0.0);
        return -1;    
    }
    int lb = 0, rb = vn.size()-1;
    while(true){
        int mid = (lb + rb)/2;
        if(vn[mid].first> value){
            rb = mid;
        }else{
            lb = mid;
        }
        if(rb-lb==1)break;
    };
    assert(rb-lb==1);
    assert(vn[lb].first < value && vn[lb+1].first > value);
    return lb;
}
int main()
{
    vector<int> primes;
    vector<double> vplogs;
    primeWithin(primes, 190);
    int half = primes.size()/2;
    vplogs.resize(primes.size(), 0);
    for(unsigned int i = 0; i < primes.size(); ++i)
        vplogs[i]=log(static_cast<double>(primes[i]));
    double dsum = accumulate(vplogs.begin(), vplogs.end(), 0.0);
    double d2 = dsum/2;
    vector<dipair> vl, vh;
    vl.resize(1<<half);
    vh.resize(1<<half);
    vl[0]=dipair(0.0,0); vl[1]=dipair(vplogs[0], 1);
    vh[0]=dipair(0.0,0); vh[1]=dipair(vplogs[half],1);
    for(int i = 1; i<half; ++i){
        int nshift = 1<<i;
        for(int j = 0; j < nshift; ++j){
            assert(i+half <vl.size());
            vl[nshift+j]=dipair(vl[j].first+vplogs[i],nshift+j);
            vh[nshift+j]=dipair(vh[j].first+vplogs[i+half], nshift+j);
        }
    }
    sort(vl.begin(), vl.end(), pairsort()); 
    sort(vh.begin(), vh.end(), pairsort()); 
    int nlow = -1, nhigh = -1;
    double vmin = 100.0;
    for(unsigned int i = 0; i < vh.size(); ++i){
        if(vh[i].first > d2) break;
        double left = d2 - vh[i].first;
        assert( left > 0);
        int nlt = bsearch(vl, left);
        if(nlt < 0) continue;
        
        if(left - vl[nlt].first < vmin){
            nlow = vl[nlt].second;
            nhigh = vh[i].second;
            vmin = left -vl[nlt].first;
        }
    }
    i64 prod = 1;
    for(int i = 0; i < half; ++i){
        if(nlow & (1<<i)){
            prod *= primes[i];
            prod %= 10000000000000000LL;
        }
    }
    for(int i = 0; i < half; ++i){
        if(nhigh & (1<<i)){
            prod *= primes[half+i];
            prod %= 10000000000000000LL;
        }
    }
    printf("%30.20f %lld\n", vmin, prod);
}
