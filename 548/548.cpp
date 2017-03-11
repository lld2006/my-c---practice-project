//01162017 after some careful investigation, found the value of this number
//relies on q1 q2...qn. where n = p1^q1 p2^q2...pn^qn
#include "../lib/tools.h"
#include <map>
#include <cstring>
#include <algorithm>

i64 getValue(vector<int> vp);
i64 nmax = 10000000000000000LL;
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
vector<i64> vn1;

map<vector<int>, i64, vectorLess> vmap;
//may be the following function is not necessary, but I will leave 
//it as is.
char* printIntVec(const vector<int>& vp, char* str)
{
    str[0]= 0;
    char buf[128];
    for(unsigned int i = 0; i < vp.size(); ++i){
        sprintf(buf, "%3d", vp[i]);
        strcat(str, buf);
    }
    return str;
}
i64 gozinta_dim0()
{
    vector<i64> vbin, vtp; 
    vector<i64>& vn(vn1); //vn1 is v(1) v(1, 1) v( 1,1,1), etc
    vtp.resize(20, 0);
    vbin.resize(20, 0);
    vn.resize(16, 0);
    vbin[0] = 1;
    vn[0] = 1;
    for(int i = 1; i < 16; ++i){
        vtp[0]=1;
        vtp[i]=1;
        for(int j = 1; j<i; ++j){
            vtp[j] = vbin[j]+ vbin[j-1];
        }
        vbin.swap(vtp);
        i64 val = 0;
        for(int k = 1; k<=i; ++k){
            val += vbin[k]*vn[i-k];
        }
        vn[i] = val;
        if(val > 1e16) break;
        printf("%d %lld\n", i, val);
    }
    return 0;
}
i64 loop_sum(const vector<int>& vp, vector<int>& vp1, int index,  bool allEq)
{

    if(index == (int)vp.size()-1){
        if(allEq)
            return 0;
        return getValue(vp1);
    }
    i64 sum = 0;
    for(int i = 0; i<=vp[index]; ++i){
        vp1[index] = i;
        sum += loop_sum(vp, vp1, index+1, allEq & (i==vp[index])); 
    }
    return sum;
}
i64 getValue(vector<int> vp)
{
    assert(vp.size() > 0);
    sort(vp.begin(), vp.end(), greater<int>());//from large to small 
    while((!vp.empty()) && vp.back()==0) vp.pop_back();
    if(vp.empty()) return 1LL; //missed this special case
    if(vp.size()==1) return 1LL<<(vp[0]-1);
    auto iter = vmap.find(vp);
    if(iter != vmap.end()) 
        return iter->second;
    bool allEq=true;
    vector<int> vp1(vp);
    vp1.back() -= 1;
    i64 sum = 2*getValue(vp1);
    vp1.clear(); 
    vp1.resize(vp.size(), 0);
    vp1.back() = vp.back();
    i64 val = loop_sum(vp,vp1, 0, allEq);
    sum += val;
    if(sum <= nmax){
        assert(sum > 0);
        vmap.insert(pair<vector<int>, i64>(vp, sum));
    }
    //char str[4096];
    //printf("map size %d vp size %d %s, %lld\n", (int)vmap.size(), (int)vp.size(), printIntVec(vp, str), sum );
    return sum;
}
i64 recursive_set_loop(int dim, vector<int>& vp, int lx)
{
    if(lx == dim){
        i64 vx = getValue(vp);
        return vx;
    }
    i64 val = 0, v0 = 0;
    int end = lx ==0? 55: vp[lx-1];
    for( int i = 1; i<=end; ++i){
        assert(i < 60);
        vp[lx] = i;
        val = recursive_set_loop(dim ,vp, lx+1);
        if(i==1) v0=val;
        if(val > nmax || val < 0)break;
    }
    return v0;//return f(n, n, n ,...a, 1) if exceed max, no need to try n+1 
}
void gozinta_dim()
{
    //first calculate the n"1" values! 
    gozinta_dim0();
    //now put it in the map
    for(unsigned int i = 1; i<vn1.size(); ++i){
        vector<int> vp;
        vp.resize(i, 1);
        vmap.insert(pair<vector<int>, i64>(vp, vn1[i]));
    }
    for(int dim = 2; dim <=15; ++dim){
        vector<int> vIndex;
        vIndex.resize(dim, 1);
        recursive_set_loop(dim, vIndex, 0);
    }
}
bool special_factor(i64 val, const vector<int>& vp, const vector<int>& primes)
{
    i64 val0 = val;
    vector<int> vx;
    bool check = false;
    int psum = accumulate(vp.begin(), vp.end(), 0);
    int pmin = pow(val, 1.0/psum);
    for(unsigned int i = 0; i < primes.size(); ++i){
        int px = primes[i];
        if(val < px ) {
            char str[4096];
            if(val != 1LL)
                printf("ERROR %lld %lld %d %s\n", val0, val, px, printIntVec(vp, str));
            break;
        }
        if(!check && px > pmin) 
            return false;
        int count = 0;
        while(val % px ==0){
            check = true;
            val /=px;
            ++count;
        }
        if(count){
            if(find(vp.begin(), vp.end(), count) == vp.end())
                return false;
            vx.push_back(count);
        }
    }
    if(val > 1) vx.push_back(1);
    sort(vx.begin(),vx.end(), greater<i64>());
    return vx == vp;
}
int main(int argc, const char *argv[])
{
    i64 total = 0;
    gozinta_dim();
    vector<int> primes;
    sievePrimes(1e8, primes);
    for(auto iter = vmap.begin(); iter != vmap.end(); ++iter){
        const vector<int>& vp = iter->first;
        i64 val = iter ->second;
        if(special_factor(val, vp, primes)){
            total += val;
            printf("%lld\n", val);
        }
    }
    printf("found %d\n", (int)vmap.size());
    printf("found %lld\n", total+1);
    return 0;
}
