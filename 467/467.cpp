#include <cstdio>
#include <cstdlib>
#include <set>
#include "../lib/tools.h"
#include <string>
#include <map>
class pairLess
{
  public:
    bool operator()(const IntPair& p1, const IntPair& p2)
    {
        return (p1.first + p1.second > p2.first + p2.second) 
            ||((p1.first+p1.second == p2.first+p2.second) && p1.first > p2.first);

    }
};
int sumdigit(int num){
    if(num < 10) return num;
    int sum = 0 ;
    while(num){
        int res = num % 10;
        sum += res;
        num /= 10;
    }
    return sumdigit(sum);
}
char itoa(int n)
{
    assert(0<n && n<10);//for this problem only, should be >= 0
    char c = '0'+n;
    return c;
}
bool strRevCmp(const string& s1, const string& s2)
{
    assert(s1.size() == s2.size());
    int size = s1.size();
    for(int k = size-1; k>=0; --k){
        if(s1[k] < s2[k])
            return true;
        else if (s1[k]> s2[k])
            return false;
    }
    return false;
}
//finally the result should be stored in (0, 0)
void insert_into_map(int pnum, map<IntPair, string, pairLess>& mstr, map<IntPair, string, pairLess>& newmap, set<IntPair, pairLess>& points, IntPair p, const vector<int>& vpd, const vector<int>& vcd, const vector<vector<int>>& vpath)
{
    typedef pair<IntPair, string> iis;
    if(p.first == 0 && p.second == 0) return;
    auto iter = mstr.find(p);
    assert(iter != mstr.end());
    if(vpd[p.first] == vcd[p.second]){
        assert(p.first >= 1 && p.second >= 1);
        string newstr(iter->second);   
        newstr.append(1, itoa(vpd[p.first]));    
        assert(vpath[p.first-1][p.second-1] == pnum - 1);
        assert(newmap.find(IntPair(p.first-1, p.second-1))==newmap.end());
        newmap.insert(iis(IntPair(p.first-1, p.second-1), newstr));
        //newpoints.insert(IntPair(p.first-1, p.second-1));
    }else{
        if(p.first > 0){
            if(vpath[p.first-1][p.second]==pnum){
                string newstr(iter->second);
                newstr.append(1, itoa(vpd[p.first]));
                auto iter2 = mstr.find(IntPair(p.first-1, p.second));
                if(iter2 == mstr.end()){
                    mstr.insert(iis(IntPair(p.first-1, p.second), newstr));
                }else if(strRevCmp(newstr, iter2->second)){
                    iter2->second = newstr;
                }
                points.insert(IntPair(p.first-1, p.second));
            }
        }
        if(p.second > 0){
            if(vpath[p.first][p.second-1] == pnum){
                string newstr(iter->second);
                newstr.append(1, itoa(vcd[p.second]));
                auto iter2 = mstr.find(IntPair(p.first, p.second-1));
                if(iter2 == mstr.end()){
                    mstr.insert(iis(IntPair(p.first, p.second-1), newstr));
                }else if(strRevCmp(newstr, iter2->second)){
                    iter2->second = newstr;
                }
                points.insert(IntPair(p.first, p.second-1));
            }
        }
    }
}
int main(int argc, char* argv[])
{
    int nmax = 10000;
    i64 nmod = 1000000007LL;
    if(argc == 2)
        nmax = atol(argv[1]);
    vector<int> primes; 
    sievePrimes(120000, primes);
    vector<int> composites; 
    composites.reserve(nmax);
    int pindex = 0;
    for(int i = 2; i<=110000; ++i){
        if(i == primes[pindex]){
            pindex++;
            continue;
        }else{
            composites.push_back(i);
            if((int)composites.size() == nmax)
                break;
        }
    }
    primes.resize(nmax);
    vector<int> vcd, vpd;
    vpd.reserve(nmax+1);
    vcd.reserve(nmax+1);
    assert(static_cast<int>(primes.size())==nmax && static_cast<int>(composites.size())==nmax);
    vpd.push_back(0);
    vcd.push_back(0);
    //sum digit of each number in the sequence respectively
    for(unsigned int i = 0; i<primes.size(); ++i){
        vpd.push_back(sumdigit(primes[i]));
        vcd.push_back(sumdigit(composites[i]));
    }
    vector<vector<int>> vpath;
    vpath.resize(nmax+1);
    for(unsigned int i = 0; i < vpath.size(); ++i){
        vpath[i].resize(nmax+1);
    }
    for(unsigned int i = 0; i < vpath.size(); ++i){
        vpath[i][0] = 0;
        vpath[0][i] = 0;
    }
    //create a traceback path
    for(int i = 1; i<= nmax; ++i){
        for(int j = 1; j<=nmax; ++j){
            if(vpd[i]==vcd[j])
                vpath[i][j] = vpath[i-1][j-1]+1;
            else{
                vpath[i][j] = max(vpath[i-1][j], vpath[i][j-1]);
            }
        }
    }
    //printf("the maximum path length is %d\n", vpath[nmax][nmax]);
    map<IntPair, string, pairLess> mstr;
    map<IntPair, string, pairLess> newMstr;
    set<IntPair, pairLess> points;
    int pnum = vpath[nmax][nmax];
    points.insert(IntPair(nmax, nmax));
    typedef pair<IntPair, string> iis;
    mstr.insert(iis(IntPair(nmax, nmax), string()));
    while(true){
        while(!points.empty()){
            IntPair point = *(points.begin());    
            points.erase(points.begin());
            insert_into_map(pnum, mstr, newMstr, points, point, vpd, vcd, vpath);
        }
        assert(!newMstr.empty() || pnum == 0);
        if(pnum == 0) break;
        if(!newMstr.empty()){
            assert(pnum > 0);
            for(auto iter = newMstr.begin(); iter != newMstr.end(); ++iter){
                points.insert(iter->first);
            }
            mstr.swap(newMstr); 
            newMstr.clear();
            --pnum;
        }
    }
    auto iter = mstr.find(IntPair(0, 0));
    assert(iter != mstr.end());
    //printf("%s\n", iter->second.c_str());
    string sr=iter->second;
    int size = sr.size();
    i64 sum = 0;
    for( int i = size-1; i >= 0; --i){
        sum *= 10LL;
        sum += sr[i] - '0';
        sum %= nmod;
    }
    printf("result %lld\n", sum);
}
