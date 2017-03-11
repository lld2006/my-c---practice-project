#include <cstdio>
#include <map>
#include <algorithm>
#include "../lib/tools.h"
using namespace std;
//this problem need some research before coding.
//the antichain follow some math rules which needs
//to be figured out before coding, 
//brute forced to figure out the maximum antichain number
//which is related to only the power coefficent of the prime number

class vectorLess
{
    public: 
        bool operator() (const vector<int>& o1, const vector<int>& o2)
        {
            if(o1.size() < o2.size()) 
                return true;
            else if (o1.size() == o2.size()){
                for(unsigned int i = 0 ; i < o1.size(); ++i){
                    if(o1[i] < o2[i]) 
                        return true;
                    else if(o1[i]> o2[i])
                        return false;  
                }
            }
            //all equal or o1.size()> o2.size()
            return false;
        }
};
map<vector<int>, i64, vectorLess> vmap;

void recursive_sum(const vector<int>& vp, vector<int>& vcollect, int index, int sum)
{
    if(index == static_cast<int>(vp.size())){
        ++vcollect[sum];
        return;
    }
    for(int k = 0; k <= vp[index];++k){
        recursive_sum(vp, vcollect, index+1, sum+k);
    }
}
i64 getValue(vector<int> vp)
{
    sort(vp.begin(), vp.end(), greater<int>());
    //something like 5 3 2 1
    if(vp.back() < 0) return 0;
    //while(vp.back()==0)vp.pop_back();
    assert(vp.back());
    if(vp.size()==1) return 1;
    if(vp.size()==2){
        assert(vp[0]>=vp[1]);
        return vp[1]+1;
    }
    auto iter = vmap.find(vp);    
    i64 val = 0;
    if(iter == vmap.end()) {
        int nmax = accumulate(vp.begin(), vp.end(), 0);
        vector<int> vcollect;
        vcollect.resize(nmax, 0);
        //The first power will be skipped.
        recursive_sum(vp, vcollect, 1, 0);
        sort(vcollect.begin(), vcollect.end(), greater<int>());
        val = accumulate(vcollect.begin(), vcollect.begin()+vp[0]+1, 0);
        vmap[vp] = val;
    }else{
        val = iter->second;
    }
    return val;
}
int main()
{
    int nmax = 100000000;
    vector<int> ftable;
    factor_table_min(nmax ,ftable);
    i64 total = 1;
    for(unsigned int i = 2; i <ftable.size(); ++i ){
        if(i % 1000000==0) printf("%d\n", i);
        IntPairVec ifac;
        factor_using_table(i, ifac, ftable);
        vector<int> vp;
        for(unsigned int j = 0; j < ifac.size(); ++j){
            vp.push_back(ifac[j].second);
        }
        i64 tp = getValue(vp);
        total += tp;
        //printf("%d %lld\n", i, tp);
    }
    printf("%lld\n", total);
}
